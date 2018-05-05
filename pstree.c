#include <minix/ipc.h>
#include <stdio.h>
#include "proto.h"
#include "pm.h"
#include "mproc.h"

int print_level(int level) {
    while (level > 0) {
        if (printf ("---") < 0) {
            return -1;
        }
        level--;
    }

    return 0;
}

int pstree_print(short pid, int uid, int guid, int level) {
    short child[256];//contains sorted pids of child processes
    short mprocIndex, counter = 0, return_value = 0;

    /* find index of process with given pid in mproc table */
    for (int i = 0; i < NR_PROCS; i++) {
        if (mproc[i].mp_pid == pid) {
            mprocIndex = i;

            break;
        }
        if (i == NR_PROCS - 1) {
            return 0;//no process with given pid (this can happen only if do_pstree was given incorrect pid)
        }
    }

    /* find pids of children processes */
    for (int i = 0; i < NR_PROCS; i++) {
        if (mproc[i].mp_parent == mprocIndex && i != mprocIndex) {
            child[counter++] = mproc[i].mp_pid;
        }
    }

    /* sort children table (bubble sort) */
    short tmp, sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < counter - 1; i++) {
            if (child[i] > child[i + 1]) {
                sorted = 0;

                tmp = child[i];
                child[i] = child[i + 1];
                child[i + 1] = tmp;
            }
        }
    }

    /* check if process is valid for printing meaning:
     * its pid = given pid (always true this far)
     * mproc.real_uid = given uid
     * mproc.real_guid = callers guid
     * its alive */
    if (mproc[mprocIndex].mp_realuid == uid
        && mproc[mprocIndex].mp_realgid == guid
        && (mproc[mprocIndex].mp_flags & IN_USE) == 1) {
        /* print this process pid and pids of its eligible children recursively */
        if (print_level(level) == -1) {
            return -1;
        }
        if (printf("%d\n", pid) < 0) {
            return -1;
        }

        for (int i = 0; i < counter; i++) {
            return_value += pstree_print(child[i], uid, guid, level + 1);
        }
    }

    if (return_value < 0) {
        return -1;
    }

    return 0;
}

int do_pstree(void) {
    short pid;
    int uid, guid;
    
    pid = m_in.m_m1.m1i1;
    uid = m_in.m_m1.m1i2;
    guid = m_in.m_m1.m1i3;

    return pstree_print(pid, uid, guid, 0);
}
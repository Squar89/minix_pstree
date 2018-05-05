#include <minix/ipc.h>
#include <stdio.h>
#include "proto.h"
#include "pm.h"

int pstree_print(short pid, int uid, int guid) {
    

    return 0;
}

int do_pstree(void) {
    short pid;
    int uid, guid;
    
    pid = m_in.m_m1.m1i1;
    uid = m_in.m_m1.m1i2;
    guid = m_in.m_m1.m1i3;
    printf("Hello world!\nMy message is pid=%d uid=%d guid=%d\n", pid, uid, guid);/*TODO*/

    /* TODO przygotuj tablicę dzieci */

    /* TODO pstree_print */

    return 0;
}
#include <minix/ipc.h>
#include <stdio.h>
#include "proto.h"
#include "pm.h"

int do_pstree(void) {
    short pid;
    int uid, guid;
    
    pid = m_in.m_u32.data[0];
    uid = m_in.m_u32.data[1];
    guid = m_in.m_u32.data[2];

    printf("Hello world!\nMy message is %d %d %d", pid, uid, guid);
    return 0;
}
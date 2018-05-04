#include <minix/ipc.h>
#include <stdio.h>
#include "proto.h"
#include "pm.h"

int do_pstree(void) {
    short pid, uid, level;
    pid = m_in.m_u16.data[0];
    uid = m_in.m_u16.data[1];
    level = m_in.m_u16.data[2];

    printf("Hello world!\nMy message is %d %d %d", pid, uid, level);
    return 0;
}
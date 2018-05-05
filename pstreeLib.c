#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

int get_pm_endpoint(endpoint_t *pt)
{
    return minix_rs_lookup("pm", pt);
}

int pstree(pid_t pid, int uid) {
    message m;
    mess_u32 m_values;
    endpoint_t pm_ep;

    if (get_pm_endpoint(&pm_ep) != 0)
    {
        errno = ENOSYS;
        return -1;
    }

    m_values.data[0] = 0;
    m_values.data[1] = 1;
    m_values.data[2] = 2;
    m.m_u32 = m_values;

    _syscall(pm_ep, PM_PSTREE, &m);
    return 0;
}
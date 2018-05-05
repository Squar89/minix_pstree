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
    mess_1 m_values;
    endpoint_t pm_ep;

    if (get_pm_endpoint(&pm_ep) != 0)
    {
        errno = ENOSYS;
        return -1;
    }

    m_values.m1i1 = pid;
    m_values.m1i2 = uid;
    m_values.m1i3 = getgid();
    m.m_m1 = m_values;

    return _syscall(pm_ep, PM_PSTREE, &m);
}
#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

int main(int argc, char** argv)
{
    message m;
    mess_u16 m_values;
    endpoint_t pm_ep;

    if (minix_rs_lookup("pm", &pm_ep) == -1) {
        printf("Error at lookup");
        return 1;   
    }

    m_values.data[0] = 0;
    m_values.data[1] = 1;
    m_values.data[2] = 2;

    m.m_source = pm_ep;
    int m_type = 1;
    m.m_u16 = m_values;

    _syscall(pm_ep, PM_PSTREE, &m);
    return 0;
}
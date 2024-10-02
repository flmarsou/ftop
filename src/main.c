#include "../includes/ftop.h"

int main(void)
{
    t_cpu   cpu;

    if (!cpu_info(&cpu))
        return (1);

    printf("CPU Model:                %s\n", cpu.model);
    printf("Frequency:                %d\n", cpu.frequency);
    printf("Number of Threads:        %d\n", cpu.threads);

    return (0);
}

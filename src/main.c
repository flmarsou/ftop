#include "../includes/ftop.h"

void    init_struct(t_cpu *cpu)
{
    cpu->model[0] = 'N';
    cpu->model[1] = '/';
    cpu->model[2] = 'A';
    cpu->model[3] = '\0';
    cpu->frequency = 0;
    cpu->threads = 0;
}

int main(void)
{
    t_cpu   cpu;

    init_struct(&cpu);
    if (!cpu_info(&cpu))
        return (1);
    
    initscr();

    cpu_menu(cpu);

    endwin();
    return (0);
}

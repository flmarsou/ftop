#ifndef FTOP_H
# define FTOP_H

# include <ncurses.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

typedef struct  t_cpu
{
    char            model[64];
    unsigned int    frequency;
    unsigned int    threads;
    
}   t_cpu;

typedef struct  t_win
{
    unsigned int    xMax;
    unsigned int    yMax;
}   t_win;

bool            cpu_info(t_cpu *cpu);
void            cpu_menu(t_cpu cpu);


#endif

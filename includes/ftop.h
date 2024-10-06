#ifndef FTOP_H
# define FTOP_H

# include <ncurses.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>

struct  s_layout
{
    unsigned int    selected;
    unsigned int    checked[3];
};

struct  s_cpu
{
    char            model[64];
    unsigned int    frequency;
    unsigned int    threads;
};

typedef struct  s_info
{
    struct s_cpu    cpu;
    struct s_layout layout;
}   t_info;

bool            cpu_info(t_info *cpu);

void            handle_input(t_info *info);
void            cpu_menu(t_info info, unsigned int xMax, unsigned int yMax);

#endif

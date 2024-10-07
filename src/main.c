#include "ftop.h"

t_info          info;
unsigned int    xMax;
unsigned int    yMax;

void    handle_resize(int sig)
{
	(void)sig;

	endwin();
	refresh();
	clear();

	getmaxyx(stdscr, yMax, xMax);

	cpu_menu(info, xMax, yMax);
}

void    init_struct(t_info *info)
{
	info->cpu.model[0] = 'N';
	info->cpu.model[1] = '/';
	info->cpu.model[2] = 'A';
	info->cpu.model[3] = '\0';
	info->cpu.frequency = 0;
	info->cpu.threads = 0;

	info->layout.selected = 0;
	info->layout.checked[0] = 1;
	info->layout.checked[1] = 1;
	info->layout.checked[2] = 1;
}

int main(void)
{
	// Initializes structs
	init_struct(&info);
	if (!cpu_info(&info))
	{
		return (1);
	}

	// Initializes ncurses
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, true);

	// Resizing
	signal(SIGWINCH, handle_resize);
	handle_resize(0);

	// Core Loop
	while (1)
	{
		cpu_menu(info, xMax, yMax);
		handle_input(&info);
		usleep(10000);
	}

	endwin();
	return (0);
}

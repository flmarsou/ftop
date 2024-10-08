#include "ftop.h"

static void	draw_panel(unsigned int width, unsigned int height, unsigned int yStart, unsigned int contentType)
{
	WINDOW	*panel = newwin(height, width, yStart, 30);
	box(panel, 0, 0);

	switch (contentType)
	{
		case 0:
		{
			wclear(panel);
			break ;
		}
		case 1:
		{
			mvwprintw(panel, 1, 2, "Temperature [°C]");
			break ;
		}
		case 2:
		{
			mvwprintw(panel, 1, 2, "Frequency [MHz]");
			break ;
		}
		case 3:
		{
			mvwprintw(panel, 1, 2, "Usage [%%]");
			break ;
		}
	}

	wrefresh(panel);
}

void	cpu_menu(t_info info, unsigned int xMax, unsigned int yMax)
{
	// Create Menu Window
	WINDOW	*menu = newwin(0, 30, 0, 0);
	box(menu, 0, 0);

	// Title
	wattron(menu, A_BOLD);
	mvwprintw(menu, 1, 1, "       CPU Detected:");
	wattroff(menu, A_BOLD);

	// Print CPU Model (with left padding)
	char            *token = strtok(info.cpu.model, " ");
	unsigned int    token_size;
	unsigned int    x = 6;
	unsigned int    y = 2;
	unsigned int    padding = x;

	while (token != NULL)
	{
		token_size = strlen(token);
		if (x + token_size >= 30)
		{
			x = padding;
			y++;
		}
		mvwprintw(menu, y, x, "%s", token);
		x += token_size + 1;
		token = strtok(NULL, " ");
	}

	// Display Menu Item
	const char		*menuItems[3] = {"Temperature", "Frequency", "Usage"};
	unsigned int	ticked = 0;

	for (unsigned int i = 0; i < 3; i++)
	{
		if (i == info.layout.selected)
			wattron(menu, A_REVERSE);

		if (info.layout.checked[i])
		{
			mvwprintw(menu, i + 6, 1, "[x] - %s", menuItems[i]);
			ticked++;
		}
		else
			mvwprintw(menu, i + 6, 1, "[ ] - %s", menuItems[i]);

		wattroff(menu, A_REVERSE);
	}
	wrefresh(menu);

	// Creates Panel Window(s)
	unsigned int	numberOfWin = 0;
	unsigned int	panelHeight = 0;
	unsigned int	remainingHeight = yMax;

	for (unsigned int i = 0; i < 3; i++)
	{
		if (info.layout.checked[i])
		{
			if (numberOfWin == ticked - 1)
				panelHeight = remainingHeight;
			else
				panelHeight = yMax / ticked;

			draw_panel(xMax - 30, panelHeight, numberOfWin * (yMax / ticked), i + 1);

			remainingHeight -= panelHeight;
			numberOfWin++;
		}
		else if (!numberOfWin)
			draw_panel(0, 0, 0, 0);
	}
}

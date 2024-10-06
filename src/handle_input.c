#include "../includes/ftop.h"

void handle_input(t_info *info)
{
    unsigned int    input = getch();

    switch (input)
    {
        case KEY_UP:
        {
            if (info->layout.selected > 0)
                info->layout.selected--;
            break ;
        }
        case KEY_DOWN:
        {
            if (info->layout.selected < 2)
                info->layout.selected++;
            break ;
        }
        case ' ':
        {
            info->layout.checked[info->layout.selected] = !info->layout.checked[info->layout.selected];
            break ;
        }
    }
}
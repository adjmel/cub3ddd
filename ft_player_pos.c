#include "cub3d.h"

void ft_compare(char c, t_data *s)
{
    if (c == 'N')
        s->player_direction = 1.5f * M_PI;
    else if (c == 'S')
        s->player_direction = 0.5f * M_PI;
    else if (c == 'W')
        s->player_direction = M_PI;
    else if (c == 'E')
        s->player_direction = 0.0f;
}

void ft_find_player(t_data *s)
{
    int i;
    int j;

    i = 0;
   
    while (s->parsing.map[i + s->parsing.start_map])
    {
        j = 0;
        while (s->parsing.map[i + s->parsing.start_map][j])
        {
            if (strchr("NSEW", s->parsing.map[i + s->parsing.start_map][j]))
            {
                s->player_x = (float)j + 0.2f;
                s->player_y = (float)i + 0.2f;
                ft_compare(s->parsing.map[i + s->parsing.start_map][j], s);
                return ;
            }
            j++;
        }
        i++;
    }
}

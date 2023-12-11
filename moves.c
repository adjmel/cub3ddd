#include "cub3d.h"

int		ft_key_press(int key, t_data *cub3d)
{
	if (key == 119 || key == 65362)
		cub3d->move[0] = 1;
	else if (key == 115 || key == 65364)
		cub3d->move[1] = 1;
	else if (key == 97)
		cub3d->move[2] = 1;
	else if (key == 100)
		cub3d->move[3] = 1;
	else if (key == 65361)
		cub3d->move[4] = 1;
	else if (key == 65363)
		cub3d->move[5] = 1;
	return (1);
}

int ft_exit_loop(t_data *cub3d)
{
    mlx_destroy_window(cub3d->mlx, cub3d->win);
    exit(0);
}

int		ft_key_release(int key, t_data *cub3d)
{
	if (key == 119 || key == 65362)
		cub3d->move[0] = 0;
	else if (key == 115 || key == 65364)
		cub3d->move[1] = 0;
	else if (key == 97)
		cub3d->move[2] = 0;
	else if (key == 100)
		cub3d->move[3] = 0;
	else if (key == 65361)
		cub3d->move[4] = 0;
	else if (key == 65363)
		cub3d->move[5] = 0;
	else if (key == 65307)
		ft_exit_loop(cub3d);
	return (1);
}

int ft_move_forward(t_data *s, int speed)
{
    float new_x;
    float new_y;

    new_x = s->player_x + speed * sinf(s->alphacam);
    new_y = s->player_y + speed * cosf(s->alphacam);
    if (s->parsing.map[(int)new_x][(int)new_y] == '0')
    {
        s->player_x = new_x;
        s->player_y = new_y;
        return (1);
    }
    return (0);
}

int ft_move_left(t_data *s, int speed)
{
    float new_x;
    float new_y;

    new_x = s->player_x + speed * cosf(s->alphacam);
    new_y = s->player_y + speed * sinf(s->alphacam);
    if (s->parsing.map[(int)new_x][(int)new_y] == '0')
    {
        s->player_x = new_x;
        s->player_y = new_y;
        return (1);
    }
    return (0);
}

int ft_rotateminus(t_data *s)
{
    s->alphacam = s->alphacam + 0.035f;
    // printf("s->alphacam = %f\n", s->alphacam);
    if (s->alphacam > 6.2831853072f)
        s->alphacam -= 6.2831853072f;
    return (1);
}

int ft_rotate(t_data *s)
{
    s->alphacam = s->alphacam - 0.035f;
    // printf("s->alphacam = %f\n", s->alphacam);
    if (s->alphacam < 0.f)
        s->alphacam += 6.2831853072f;
    return (1);
}
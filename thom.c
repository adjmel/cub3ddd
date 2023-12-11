#include "cub3d.h"

void draw_game(t_data *s);
float ft_sign(float n);
float ft_ray(t_data *s, float angle);

void ft_free(t_data *s)
{
    int i;

    i = 0;

    while (i < 4)
    {
        if (s->texture[i].img != NULL)
            mlx_destroy_image(s->mlx, s->texture[i].img);
        i++;
    }
    free(s->parsing.so_texture_value);
    free(s->parsing.we_texture_value);
    free(s->parsing.no_texture_value);
    free(s->parsing.ea_texture_value);
    free(s->parsing.s_texture_value);
    free(s->texture);
    mlx_destroy_image(s->mlx, s->img.img);
    mlx_destroy_window(s->mlx, s->win);
    mlx_destroy_display(s->mlx);
    printf(" fs %s\n", s->parsing.map[s->parsing.start_map - 1]);
    i = s->parsing.config_count;
    while (i < s->parsing.start_map)
    {
        free(s->parsing.map[i]);
        i++;
    }
    i = 0;
    while (i < s->parsing.map_count - s->parsing.ligne_vide)
    {
        if(s->parsing.map[i + s->parsing.start_map])
            free(s->parsing.map[i + s->parsing.start_map]);
        i++;
    }
    free(s->parsing.map);
    free(s->mlx);
    exit (0);
}

int ft_init_textures(t_data *s)
{

    s->texture[0].img = mlx_xpm_file_to_image(s->mlx, s->parsing.no_texture_value, &s->texture[0].width, &s->texture[0].height);
    if (!s->texture[0].img)
        ft_free(s);
    s->texture[1].img = mlx_xpm_file_to_image(s->mlx, s->parsing.so_texture_value, &s->texture[1].width, &s->texture[1].height);
    if (!s->texture[1].img)
        ft_free(s);
    s->texture[2].img = mlx_xpm_file_to_image(s->mlx, s->parsing.we_texture_value, &s->texture[2].width, &s->texture[2].height);
    if (!s->texture[2].img)
        ft_free(s);
    s->texture[3].img = mlx_xpm_file_to_image(s->mlx, s->parsing.ea_texture_value, &s->texture[3].width, &s->texture[3].height);
    if (!s->texture[3].img)
        ft_free(s);
    s->texture[0].addr = mlx_get_data_addr(s->texture[0].img, &s->texture[0].bpp, &s->texture[0].line_l, &s->texture[0].endian);
    s->texture[1].addr = mlx_get_data_addr(s->texture[1].img, &s->texture[1].bpp, &s->texture[1].line_l, &s->texture[1].endian);
    s->texture[2].addr = mlx_get_data_addr(s->texture[2].img, &s->texture[2].bpp, &s->texture[2].line_l, &s->texture[2].endian);
    s->texture[3].addr = mlx_get_data_addr(s->texture[3].img, &s->texture[3].bpp, &s->texture[3].line_l, &s->texture[3].endian);
    return (1);
}

int ft_close(t_data *s)
{
    ft_free(s);
    return (0);
}

void ft_move (t_data *s, int direction)
{
    float dist;
    float dist_x;
    float dist_y;
    float angle;

    angle = s->player_direction + direction * M_PI / 2;
    dist_x = 0.1f * cos(angle);
    dist_y = 0.1f * sin(angle);
    dist = ft_ray(s, ft_sign(dist_y) * M_PI / 2);
    if (dist * dist < dist_y * dist_y)
        dist_y = 0.0f;
    dist = ft_ray(s, (1 - (ft_sign(dist_x) + 1) / 2) * M_PI);
    if (dist * dist < dist_x * dist_x)
        dist_x = 0.0f;
    dist = ft_ray(s, angle);
    if (dist * dist < dist_x * dist_x + dist_y * dist_y)
    {
        if (ft_sign(dist_y) * ft_sign(dist_x) != 0)
            dist_y = 0.0f;
    }
    s->player_x += dist_x;
    s->player_y += dist_y;
}

int ft_keys(int key, t_data *s)
{
    if (s->win == NULL)
        return (0);
    if (key == XK_Escape || key == XK_q || key == XK_Q)
    {
        ft_close(s);
        exit (0);
    }
    if (key == 65362 || key == 119)
        ft_move(s, 0);
    else if (key == 65364 || key == 115)
        ft_move(s, 2);
    else if (key == 65361)
        s->player_direction -= 0.02f * M_PI;
    else if (key == 65363)
        s->player_direction += 0.02f * M_PI;
    else if (key == 100)
        ft_move(s, 1);
    else if (key == 97)
        ft_move(s, 3);
    else
        return (0);
    mlx_destroy_image(s->mlx, s->img.img);
    draw_game(s);
    return (1);
}

float ft_sign(float n)
{
    if (n > 0)
        return (1.0f);
    else if (n < 0)
        return (-1.0f);
    else
        return (0.0f);
}

static void init_ray(t_data *s, t_ray *ray, float angle)
{
    ray->dir_x = cos(angle);
    ray->dir_y = sin(angle);
    ray->step_x = ft_sign(ray->dir_x);
    ray->step_y = ft_sign(ray->dir_y);
    ray->vert_x = (int)s->player_x;
    ray->horz_w = 0;
    ray->horz_x = 0;
    ray->vert_w = 0;
    ray->vert_y = 0;
    if (ray->step_x > 0)
        ray->vert_x += 1.0f;
    ray->horz_y = (int)s->player_y;
    if (ray->step_y > 0)
        ray->horz_y += 1.0f;
}

static void ft_ray2(t_data *s, t_ray *ray)
{
    if (ray->step_x != 0)
    {
        ray->vert_y = s->player_y + ray->dir_y / ray->dir_x * (ray->vert_x - s->player_x);
        ray->vert_dist = sqrt(pow(s->player_x - ray->vert_x, 2.0) + pow(s->player_y - ray->vert_y, 2.0));
        ray->vert_w = ray->vert_y - (int)ray->vert_y;
        if (ray->step_x > 0)
            ray->vert_w = 1 - ray->vert_w;
    }
    else
        ray->vert_dist = INFINITY;
    if (ray->step_y != 0)
    {
        ray->horz_x = s->player_x + ray->dir_x / ray->dir_y * (ray->horz_y - s->player_y);
        ray->horz_dist = sqrt(pow(s->player_x - ray->horz_x, 2.0) + pow(s->player_y - ray->horz_y, 2.0));
        ray->horz_w = ray->horz_x - (int)ray->horz_x;
        if (ray->step_y > 0)
            ray->horz_w = 1 - ray->horz_w;
    }
    else
        ray->horz_dist = INFINITY;
}

void	draw_floor_ceiling(t_data *s)
{
	unsigned int	*dst;
	unsigned int	i;

	dst = (unsigned int *)s->img.addr;
	i = WINDOW_WIDTH * WINDOW_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = s->parsing.ceiling_color;
	i = WINDOW_WIDTH * WINDOW_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = s->parsing.floor_color;
}

static float save_color(t_data *s, float dist, int color_idx, float wall_hit)
{
    s->i = color_idx;
    s->txt_width = wall_hit;
    return (dist);
}

float ft_ray(t_data *s, float angle)
{
    t_ray ray;

    init_ray(s, &ray, angle);
    while (1)
    {
        ft_ray2(s, &ray);
        if (ray.vert_dist < ray.horz_dist)
        {
            if (s->parsing.map[(int)ray.vert_y + s->parsing.start_map][(int)ray.vert_x + (ray.step_x - 1) / 2] == '1')
                return (save_color(s, ray.vert_dist, ray.step_x + 1, ray.vert_w));
            else
                ray.vert_x += ray.step_x;
        }
        else
        {
            if (s->parsing.map[((int)ray.horz_y + (ray.step_y - 1) / 2) + s->parsing.start_map][(int)ray.horz_x] == '1')
                return (save_color(s, ray.horz_dist, ray.step_y + 2, ray.horz_w));
            else
                ray.horz_y += ray.step_y;
        }
    }
}

void draw_line(t_data *s, int w, float dist)
{
    unsigned int *dst;
    unsigned int *src;
    unsigned int h;
    float src_factor;
    float dst_shift;

    h = (float)WINDOW_HEIGHT / dist;
    src_factor = 0.0f;
    dst_shift = (float)s->texture[s->i].height / h;
    if (h > WINDOW_HEIGHT)
    {
        src_factor = 0.5f * (h - WINDOW_HEIGHT) * dst_shift;
        h = WINDOW_HEIGHT;
    }
    src = (unsigned int *)s->texture[s->i].addr;
    src += (int)((float)s->txt_width * s->texture[s->i].width);
    dst = (unsigned int *)s->img.addr + w + (WINDOW_HEIGHT - h) / 2 * WINDOW_WIDTH;
    while (h-- > 0)
    {
        *dst = *(src + ((int)src_factor) * s->texture[s->i].width);
        dst += WINDOW_WIDTH;
        src_factor += dst_shift;
    }
}

void ft_raycast(t_data *s)
{
    int x;
    float dv;
    float angle;
    static float fov;

    fov = 60 * M_PI / 180;
    angle = s->player_direction - fov / 2;
    dv = fov / (WINDOW_WIDTH - 1);
    x = 0;
    while (x < WINDOW_WIDTH)
    {
        draw_line(s, x, ft_ray(s, angle) * cos(s->player_direction - angle));
        angle += dv;
        x++;
    }
}

void draw_game(t_data *s)
{
    s->img.img = mlx_new_image(s->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    s->img.addr = mlx_get_data_addr(s->img.img, &s->img.bpp, &s->img.line_l, &s->img.endian);
    draw_floor_ceiling(s);
    ft_raycast(s);
    mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
}

int init_var(t_data *s)
{
    int i;

    i = -1;
    s->i = 0;
    s->txt_width = 0.0f;
    s->texture = (t_image *)malloc(sizeof(t_image) * 4);
    if (!s->texture)
        ft_close(s);
    while (++i < 4)
        s->texture[i].img = NULL;
    return (0);
}

void init_window(t_data *s)
{
    s->mlx = mlx_init();
    if (!s->mlx)
        exit (1);
    ft_init_textures(s);
    s->win = mlx_new_window(s->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
    if (!s->win)
        exit (1);
}

void ft_raycasting(t_data *s)
{
    if (init_var(s) == 1)
        exit (1);
    init_window(s);
    ft_find_player(s);
    draw_game(s);
    mlx_hook(s->win, 17, 0, &ft_close, s);
    mlx_hook(s->win, 2, 1L<<0, &ft_keys, s);
    mlx_loop(s->mlx);
}
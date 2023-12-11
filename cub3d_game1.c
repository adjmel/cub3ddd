#include "cub3d.h"

// void	clean_exit(int exit_code, t_data *vars)
// {
// 	if (!vars)
// 		exit(exit_code);
// 	if (vars->img)
// 		mlx_destroy_image(vars->mlx, vars->img);
// 	if (vars->mlx_win && vars->mlx)
// 		mlx_destroy_window(vars->mlx, vars->mlx_win);
// 	if (vars->mlx)
// 	{
// 		mlx_loop_end(vars->mlx);
// 		mlx_destroy_display(vars->mlx);
// 		free(vars->mlx);
// 	}
// 	free(vars);
// 	exit(EXIT_SUCCESS);
// }

// t_data *init_window()
// {
//     t_data *vars;

//     vars = (t_data *)malloc(sizeof(t_data));
//     if (!vars)
// 		exit(1);
// 	vars->mlx = mlx_init();
// 	if (!vars->mlx)
// 	{
// 		free(vars);
// 		exit(1);
// 	}
//     vars->mlx_win = mlx_new_window(vars->mlx, 1000, 1000, "cub3d"); //changer 1000 par s.parsing.r_value_x et s.parsing.r_value_y
// 	vars->img = mlx_new_image(vars->mlx, 1000, 1000);
//     if (!vars->mlx_win || !vars->img)
// 		    clean_exit(1, vars);
//     return (vars);
// }

// int	mouse_click(t_data *vars)
// {
// 	clean_exit(1, vars);
// 	exit(1);
// }

// int	close_win(int keycode, t_data *vars)
// {
// 	if (keycode == 65307)
// 	{
// 		clean_exit(1, vars);
// 		exit(1);
// 	}
// 	return (0);
// }

// // int    key_event(int button, t_data *vars)
// // {
// //     if (button == 65361) 
// //         blabla
// //     if (button == 65363)
// //         blabla
// //     return (0);
// // }



// void	ft_init_all(t_parsing *parsing)
// {
// 	ftinit_win(parsing);
// 	ftinit_map(parsing);
// 	ftinit_player(parsing);
// 	ftinit_texts(parsing);
// 	ftinit_rays(parsing);
// 	ftinit_sprites(parsing);
// }

// int cub3d_game(t_parsing *parsing)
// {
//     ft_init_all(parsing);

//     (void)parsing;
//     t_data *vars;
//     vars = init_window();
//     //mlx_get_screen_size(vars->mlx, &parsing->r_value_x, &parsing->r_value_y);

//     //quelques keys
//     //mlx_hook(vars->mlx_win, 2, 1L << 0, key_event, vars);
//     mlx_hook(vars->mlx_win, 2, 1L << 0, close_win, vars);
// 	mlx_hook(vars->mlx_win, 17, 0L, mouse_click, vars);

//     mlx_loop(vars->mlx);
//     return 0;
// }


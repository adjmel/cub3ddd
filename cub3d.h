#ifndef CUB3D_H

# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include "mlx_linux/mlx_int.h"
# include "mlx_linux/mlx.h"
# include <fcntl.h>
# include <string.h>
# include <X11/Xlib.h>
# include <ctype.h>
# include <math.h>

# define WINDOW_HEIGHT 1280
# define M_PI 3.14159265358979323846
# define WINDOW_WIDTH 1280

# define MAX_LINE_LENGTH 204//1024 // longueur maximale d'une ligne (a ajuster mais les lignes sont courtes donc ca va)
# define MAX_MAP_SIZE_X 24 // Ajustez selon besoin
# define MAX_MAP_SIZE_Y 24

//# define MAPLETTERS "CNOSOWEEA"

typedef struct s_parsing
{
	/*variables pour substitut GNL*/
	int num_lines;
	int ligne_vide;
    int *num_lines_ptr;
	int config_count;
	int map_count;
	char buffer[MAX_LINE_LENGTH];
	ssize_t bytes_read;
	char current_char;
    int line_index;

	/*valeurs rgb du sol et plafond*/
	int floor_value_1;
	int floor_value_2;
	int floor_value_3;
	int floor_color;

	int sky_value_1;
	int sky_value_2;
	int sky_value_3;
	int ceiling_color;

	/*valeurs pour la resolution*/
	int r_value_x;
	int r_value_y;

	/*valeurs pour les textures*/
	char *no_texture_value;
    char *so_texture_value;
    char *we_texture_value;
    char *ea_texture_value;
    char *s_texture_value;

	/*map*/
	char **map;
	int map_height;
	int start_map;
	char **copied_map;

	/*elements de configuration*/
	char **config_elements;

	/*position x et y du player*/

	/*distances horizontale et verticale*/
	//float;

	/*direction dans laquelle il regarde en radiant*/
	//float;

	/*mlx*/

}			t_parsing;

typedef struct	s_image
{
	void *img;
	char *addr;
	int bpp;
	int endian;
	int line_l;
	int			width;
	int			height;
}				t_image;

typedef struct	s_ray
{
	float dir_x;
	float dir_y;
	int step_x;
	int step_y;
	float vert_x;
	float vert_y;
	float horz_x;
	float horz_y;
	float vert_dist;
	float horz_dist;
	float vert_w;
	float horz_w;
}	t_ray;

typedef struct s_data
{
	t_parsing   parsing;
	t_image img;
	t_image *texture;

	void *win;
	void *mlx;

	int i;
	float player_x;
	float player_y;
	float player_direction;
	float txt_width;

	int a[2];
	int facing_left;
	int vhit;
	float theta;

}			t_data;

int check_no_wall();
int map_closed();

int check_all_wall_closed();

int map_less_3_lines();
int check_nbr_player();
int correct_number();

void    init_textures(t_parsing *parsing);
int parsing(char *file_cub3d_name, t_data *data);
int parsing_rgbs();
int parsing_resolution();
int parsing_textures();
int check_map_prefixes();
int parsing_cub3d(char **text_file, t_parsing *parsing);
int put_text_struct();
int put_map_in_struct(t_parsing *parsing);
int check_nbr_directions(t_parsing *parsing);
int free_parsing(t_parsing *parsing);

/*EXECUTION*/
void ft_raycasting(t_data *s);
void ft_find_player(t_data *s);
int		ft_key_press(int key, t_data *cub3d);
int		ft_key_release(int key, t_data *cub3d);


int ft_move_forward(t_data *s, int speed);
int ft_move_left(t_data *s, int speed);
int ft_rotateminus(t_data *s);
int ft_rotate(t_data *s);

/*GNL*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

char		*ft_copy_before(char *buffer);
char		*ft_copy_after(char *buffer);
char		*ft_read_my_varstatic(int fd, char *varstatic);
char		*get_next_line(int fd);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
int			ft_search_newline(char *varstatic);
size_t		ft_strlen(const char *s);
int			ft_lenbuffern(char *buffer);


#endif
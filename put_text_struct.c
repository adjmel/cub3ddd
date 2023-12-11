#include "cub3d.h"

int count_empty_lines_after(char **lines, int start_index, int num_lines) 
{
    int empty_line_count = 0;
    int i = start_index + 1; // Commencez à partir de la ligne suivant la position start_index

    while (i < num_lines) 
    {
        // printf("%s\n", lines[i]);
        if (lines[i][0] == '\0' || (lines[i][0] == '\n' && lines[i][1] == '\0')) 
        {
            // Une ligne est vide si elle est soit complètement vide (ligne vide) soit composée uniquement d'un retour à la ligne.
            empty_line_count++;
        }
        i++;
    }
    return empty_line_count;
}

int check_map_section(t_parsing *parsing, int num_lines) 
{
    int i = 0;
    int sign_count = 0; // Initialisation du compteur de signes

    while (i < num_lines) 
    {
        char *line = parsing->config_elements[i];
         int j = 0;
        while (line[j] != '\0') 
        {   
                    //strncmp(line, "NO ", 3) == 0 ||
        if (strncmp(&line[j], "C ", 2) == 0 || 
            strncmp(&line[j], "NO ", 3) == 0 ||
            strncmp(&line[j], "SO ", 3) == 0 ||
            strncmp(&line[j], "WE ", 3) == 0 ||
            strncmp(&line[j], "EA ", 3) == 0 || 
            strncmp(&line[j], "S ", 2) == 0 ||
            strncmp(&line[j], "F ", 2) == 0)
            {
                sign_count++; // Incrémentez le compteur si un des signes est trouvé
            }
            // printf("-----> %d\n",sign_count);
            // printf("line = %c\n", line[j + 1]);
            // printf("pc = %s\n",parsing->config_elements[8]);
        if (i > 7 && sign_count < 7)
        {
            
            exit(0);
        }

        if (sign_count == 7)
        {
        int nb_ligne_vide = count_empty_lines_after(parsing->map, i, num_lines);
        parsing->ligne_vide = nb_ligne_vide;
        parsing->start_map = nb_ligne_vide + i + 1;
        //      printf("depart de la map = %s\n", parsing->map[parsing->start_map]);
        //    printf("\n- map config l15 --------> = %s\n", parsing->map[15]);
        //     printf("\n- element de config l5 = %s\n", parsing->config_elements[5]);
                return 0; // Vous êtes sur la carte
        }
            j++;
        }
        i++;  
    }
    return 1; // Vous n'avez pas trouvé le nombre requis de signes
}

int open_file(const char *filename, int *fd) 
{
    *fd = open(filename, O_RDONLY);
    printf("fd = %d\n", *fd);
    if (*fd < 0) 
    {
        printf("Error: Failed to open the file\n");
        return 1;
    }
    return 0;
}

int read_file(int fd, ssize_t *bytes_read, char *current_char) 
{
    *bytes_read = read(fd, current_char, 1);
    if (*bytes_read > 0) 
            return 1; // Indique qu'une ligne a été lue avec succès.
    else if (*bytes_read < 0) 
    {
        printf("Error: Failed to read the file\n");
        return 1; // Erreur de lecture du fichier.
    } 
    else 
        return 0; // Fin du fichier.
}

void resize_and_copy(char ***array, int current_size, int new_size) 
{
    char **new_array = (char **)malloc(new_size * sizeof(char *));
    if (!new_array)
        free(new_array);

    memcpy(new_array, *array, current_size * sizeof(char *));
    free(*array);
    *array = new_array;
}

void process_line(t_parsing *parsing, int *config_size, int *map_size) 
{
    parsing->buffer[parsing->line_index] = '\0';

    if (check_map_section(parsing, *parsing->num_lines_ptr) == 1) 
    {   
        if (*parsing->num_lines_ptr >= *config_size) 
        {
            (*config_size) *= 2;
            resize_and_copy(&parsing->config_elements, *parsing->num_lines_ptr, *config_size);   
        }
        parsing->config_elements[*parsing->num_lines_ptr] = strdup(parsing->buffer);
        parsing->config_count++;
    } 
    else 
    {
        
        if (*parsing->num_lines_ptr >= *map_size) 
        {
            (*map_size) *= 2;
            resize_and_copy(&parsing->map, *parsing->num_lines_ptr, *map_size);
        }
        //if (parsing->buffer)
        //{
            parsing->map[*parsing->num_lines_ptr] = strdup(parsing->buffer);
            parsing->map_count++;
        // }
        //printf("2ph = %s\n", parsing->config_elements[*parsing->num_lines_ptr]);
    }
    (*parsing->num_lines_ptr)++;
}

void    init_read_variables(t_parsing *parsing)
{
    parsing->num_lines = 0;
    parsing->num_lines_ptr = &parsing->num_lines;
	//parsing->buffer[MAX_LINE_LENGTH];
	parsing->bytes_read = 0;
	// parsing->current_char = NULL;
    parsing->line_index = 0;
}

int check_too_much_elmts(char *str) 
{
    if (str == NULL) 
        return 0; // La ligne n'existe pas

    int i = 0;
    while (str[i] != '\0') 
    {
        if (!isspace((unsigned char)str[i])) 
        {
            return 1; // La ligne contient autre chose que des espaces
        }
        i++;
    }
    return 0; // La ligne ne contient que des espaces ou est vide
}


int put_text_struct(char *file_cub3d_name, t_parsing *parsing) 
{
    int config_size = 10;
    int map_size = 10;

    int fd;
    if (open_file(file_cub3d_name, &fd) == 1) 
            return 1;
    
    printf("ici = %s\n,", file_cub3d_name);

    init_read_variables(parsing);
    // parsing->map = (char **)malloc(config_size * sizeof(char *));
    parsing->map = (char **)calloc(config_size, sizeof(char *));
    // parsing->config_elements = (char **)malloc(map_size * sizeof(char *));
    parsing->config_elements = (char **)calloc(map_size, sizeof(char *));

    while (read_file(fd, &parsing->bytes_read, &parsing->current_char) != 0) 
    {
       
        // if (check_too_much_elmts(parsing->map[7]) == 1)
        // {
        //     fprintf(stderr, "Error : too many configuration elements\n");
        // //printf("Error : too many configuration elements\n");
        //     return 1;
        // }

        if (parsing->current_char == '\n') 
        {
            process_line(parsing, &config_size, &map_size);
            parsing->line_index = 0;
        }  
        else if (parsing->line_index < MAX_LINE_LENGTH - 1) 
        {
            parsing->buffer[parsing->line_index] = parsing->current_char;
            parsing->line_index++;
        } 
        else 
        {
            printf("Error: Line too long\n");
            return 1;
        }
    }
    parsing->config_elements[parsing->config_count + 1] = NULL;
    if (parsing->line_index > 0) 
            process_line(parsing, &config_size, &map_size);
    //printf("CALCUL %d\n", parsing->map_count + parsing->start_map);

    // parsing->map[parsing->map_count + parsing->start_map - 1] = NULL;
    //printf("ici = %s\n", parsing->config_elements[5]);
    //close(fd);
    return 0;
}

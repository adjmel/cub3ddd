#include "cub3d.h"

//pour voir si la map a des caracteres correctes
int correct_number(t_parsing *parsing) 
{
    char *player_chars = "NSEW";

    int num_lines = 0;
    int start = parsing->start_map;
    // printf("-> dfgdf %d\n", parsing->start_map);
    while (start < parsing->num_lines) 
    {
        printf("-> dfgdf %s\n", parsing->map[start + 14]);
        char *line = parsing->map[start];
        
        size_t i = 0;

        
        while (line[i] == ' ')
                     i++;
        
        while (line[i] != '\0')
        {
            char current_char = line[i];
            //printf("ici = %c\n", current_char);
            // Vérifiez les caractères spéciaux
            if (current_char == '\n' || current_char == '\t' || current_char == '\r' ||
                current_char == '\v' || current_char == '\f')
            {
                // Caractère spécial trouvé, passez à la ligne suivante
                i++;
                continue;
            }
            // Vérifiez les espaces -> dernier lignes 
            // + changer car space possible au debut

            if (current_char == ' ') //&& current_char + 1 == '\n')
            {
                line[i] = '1';//current_char = 1;
                //  printf("Error: Do not put spaces in the map\n");
                // return 1;
            }

            if (strchr(player_chars, current_char) == NULL)
            {
                if (current_char >= 'A' && current_char <= 'Z')
                {
                    printf("Error : %c this direction does not exist\n", current_char);
                    return 1;
                }
            }

            if ((current_char < '0' || current_char > '2') && strchr(player_chars, current_char) == NULL && current_char != ' ')
            {
                printf("Error: %c is not a correct number\n", current_char);
                return 1;
            }

            i++;
        }
        num_lines++;
        start++;
    }
    return 0;
}

int		check_spaces(char c)
{
	if (c > 9 && c < 13)
		return (1);
	return (0);
}

int check_wall(char **strs, int i, int j)
{
    if (strs[i][j - 1] == 0 || check_spaces(strs[i][j - 1]))
        return (1);

    if (strs[i][j + 1] == 0 || check_spaces(strs[i][j + 1]))
        return (1);

    if (strs[i - 1][j] == 0 || check_spaces(strs[i - 1][j]))
        return (1);

    if (strs[i + 1][j] == 0 || check_spaces(strs[i + 1][j]))
        return (1);

    return 0; // Tous les côtés sont fermés
}


int check_all_wall_closed(t_parsing *parsing, int start_map) 
{
    int i = start_map + 1; //car premiere ligne deja traitee
    //mais attention car ne verifie pas le dernier mur
    int j;
    char **map = parsing->map;

    while (i < parsing->num_lines)
    {
        //printf("ici = %s\n", map[i]);
        j = 0;
        while (map[i][j] != '\0') 
        {
            //printf("ici = %c\n", map[i][j]);
            if (map[i][j] == '0' || map[i][j] == '2' ||
            map[i][j] == 'N' || map[i][j] == 'S' ||
            map[i][j] == 'E' || map[i][j] == 'W')
            {
                //printf("je suis different = %c\n", map[i][j]);
                if (check_wall(map, i, j) == 1)
                {
                    printf("Error: The walls are not closed\n");
                    return 1;
                }
            }           
            j++;
        }
        
        i++;
    }
    return 0;
}


int check_last_wall(t_parsing *parsing)
{
    int index_end = parsing->start_map; // Pointe vers la première ligne de la carte

    while (index_end < parsing->num_lines)
    {
        index_end++; // Avance jusqu'à la fin de la carte
    }

    index_end--; // Revenir à la dernière ligne de la carte

    char *map_line = parsing->map[index_end];
    int j = 0;

    while (map_line[j] != '\0')
    {
        //printf("%c\n", map_line[j]);
        if (map_line[j] != '1' && map_line[j] != ' ')
        {
            
            printf("Error: Last wall is not closed\n");
            return 1;
        }
        j++;
    }
    return 0;
}

int check_first_wall(t_parsing *parsing)
{ 
    int i = parsing->start_map;
    char *map_line = parsing->map[i];

    int j = 0;
    while (map_line[j] != '\0')
    {
        
        if (map_line[j] != '1' && map_line[j] != ' ')
        {
            printf("Error: First wall is not closed\n");
            return 1;
        }
        j++;
    }
    return 0;
}

int map_closed(t_parsing *parsing)
{
    if (check_first_wall(parsing) == 1)
        return 1;
    if (check_last_wall(parsing) == 1)
        return 1;
    if (check_all_wall_closed(parsing, parsing->start_map) == 1)
        return 1;
    return 0;
}

int map_less_3_lines(t_parsing *parsing) 
{
    //printf("start map = %d\n", parsing->start_map);
    //printf("result start map = %s\n", parsing->map[parsing->start_map]);

    int num_lines = 0;
    int start = parsing->start_map;
    while (start < parsing->num_lines) 
    {
        num_lines++;
        start++; // Avance au prochain élément de parsing->map
    }

    //printf("Nombre total de lignes : %d\n", num_lines);

    if (num_lines <= 3) 
    {
        printf("Error: The map has less than 3 lines.\n");
        return 1;
    }
    return 0;
}

int check_nbr_player(t_parsing *parsing) 
{
    //int num_lines = 0;
    int player_count = 0;

    int start = parsing->start_map;
    while (start < parsing->num_lines) 
    {
        char *line = parsing->map[start];
        char *player_chars = "NSEW";

        size_t i = 0; // Utilisez size_t pour éviter l'erreur de signe
        while (i < strlen(player_chars)) 
        {
            if (strchr(line, player_chars[i]) != NULL) 
            {
                player_count++;
                //printf("ici = %d\n", player_count);
                if (player_count > 1) 
                {
                    printf("Error: There is more than one player on the map\n");
                    return 1;
                }
                i++;
            }
            else 
            {
                i++;
            }
        }
        //num_lines++;
        start++;
    }
    if (player_count == 0)
    {
        printf("Error: There is no player on the map\n");
        return 1;
    }
    return 0;
}

int check_nbr_directions(t_parsing *parsing) 
{
    //int num_lines = 0;
    int destination_count = 0;

    int start = parsing->start_map;
    while (start < parsing->num_lines) 
    {
        char *line = parsing->map[start];
        char *destination_chars = "SWE";

        size_t i = 0; // Utilisez size_t pour éviter l'erreur de signe
        while (i < strlen(destination_chars)) 
        {
            if (strchr(line, destination_chars[i]) != NULL) 
            {
                destination_count++;
                if (destination_count > 1) 
                {
                    printf("Error: There is more than one direction on the map\n");
                    return 1;
                }
                i++;
            }
            else 
            {
                i++;
            }
        }
        //num_lines++;
        start++;
    }
    // if (destination_count == 0)
    // {
    //     printf("Error: There is no destination on the map\n");
    //     return 1;
    // }
    return 0;
}

/*Copie la carte d'origine dans une nouvelle structure de données 
pour une utilisation plus aisée des coordonnées x et y*/
/*int put_map_in_struct(t_parsing *parsing)
{
    // Obtenez la hauteur de la carte en comptant le nombre de ligne
    int index = parsing->start_map;
    int map_height = 0;
    while (parsing->map[index] != NULL) 
    {
        map_height++; 
        index++;  
    }
    printf("map height = %d\n", map_height);

    // Allouez de la mémoire pour la nouvelle structure de données
    parsing->copied_map = (char **)malloc(sizeof(char *) * (map_height + 1));
    if (!parsing->copied_map) 
        return 1;
    
    int i = 0;
    // Copiez chaque ligne de la carte dans la nouvelle structure
    while (i < map_height) 
    {
        parsing->copied_map[i] = strdup(parsing->map[i]);
        
        if (!parsing->copied_map[i]) 
        { 
            // En cas d'erreur, libérez la mémoire précédemment allouée et retournez 0
            int j = 0;
            while (j < i) 
            {
                free(parsing->copied_map[j]);
                j++;
            }
            free(parsing->copied_map);
            return 1;
        }
        i++;
    }
    
    // Marquez la fin du tableau avec une ligne nulle
    parsing->copied_map[map_height] = NULL;
    
    // Mettez à jour la hauteur de la carte copiée
    parsing->map_height = map_height;

    //printf("mp = %d\n", parsing->map_height);
    printf("cp = %s\n", parsing->copied_map[15]);
    return 0;
}*/


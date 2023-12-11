#include "cub3d.h"

//enlever char **text_file car deja parsing->text_file

void free_texture(t_parsing *parsing);

int free_parsing2(t_parsing *parsing)
{
    free_texture(parsing);
    int i = -1;
    while (++i < parsing->config_count)
        free(parsing->config_elements[i]);
    free(parsing->config_elements);
    free(parsing->map);
    exit(1);
    return 1;
}

int free_parsing(t_parsing *parsing)
{
    int i = -1;
    free_texture(parsing);
    while (++i < parsing->config_count)
        free(parsing->config_elements[i]);
    free(parsing->config_elements);
    i = 0;
    i = parsing->config_count;
    while (i < parsing->start_map)
    {
        free(parsing->map[i]);
        i++;
    }
    i = 0;
    
    while (i < parsing->map_count - parsing->ligne_vide)
    {
        if(parsing->map[i + parsing->start_map])
            free(parsing->map[i + parsing->start_map]);
        i++;
    }
    free(parsing->map);
    exit (1);
    return (0);
}

int	rgb_to_hex_floor(t_parsing *parsing)
{
	return (parsing->floor_value_1 << 16 | parsing->floor_value_2 << 8 | parsing->floor_value_3);
}

int	rgb_to_hex_sky(t_parsing *parsing)
{
	return (parsing->sky_value_1 << 16 | parsing->sky_value_2 << 8 | parsing->sky_value_3);
}

int is_digit(char c) 
{
    if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int parse_rgb(char *str, int *r, int *g, int *b, t_parsing *parsing) 
{
    //changer les messages d'erreur quand lettres alphabetiques

    int index = 2;  // Ignorer les deux premiers caractères "F " ou "C "
    int *values[3] = {r, g, b};  // Tableau de pointeurs pour les valeurs R, G et B -> attention norminette
    int i = 0;
    

    while (str[index] == ' ')
            index++;


    while (i < 3) 
    {
        


        if (str[index] == '-' || /*str[index] == '0' ||*/ !is_digit(str[index])) 
        {
            printf("Error : Bad value for %c (RGB)\n", "RGB"[i]);
            free_parsing2(parsing);
            return 1;
        }
         

        *values[i] = atoi(str + index);
        while (isdigit(str[index])) 
        {
            index++;
        }

 
        if (i < 2) // Vérifier le caractère de séparation sauf pour la dernière valeur
        {  
             
            if (str[index] != ',') 
            {
               
                printf("Error : Incorrect separator character after %c.\n", "RGB"[i]);
                free_parsing2(parsing);
                return 1;
            }
             
            index++;
           
        }
        i++;
       
    }
     
    if (str[index] == ' ' || str[index] == '\0') 
    {
        
            // Passer au caractère suivant après l'espace ou à la fin de la chaîne
            // Ignorer les espaces après la résolution
           
            while (str[index] == ' ')
                index++;
               
    } 
    
    else 
    {
         
            printf("Error : Non-numeric character found\n");
            free_parsing(parsing);

            return 1;
    }
    return 0;
}

int parsing_rgbs_sky(char **text_file, t_parsing *parsing)
{
    int line_index;// Initialisation de l'index
    
    line_index = 0;
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "C ", 2) == 0) 
        {                 
            int r;
            int g;
            int b;
            if (parse_rgb(text_file[line_index], &r, &g, &b, parsing) == 0) 
            {

               
                if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
                {
                    
                    // Les valeurs RGB sont valides
                    parsing->sky_value_1 = r;
                    parsing->sky_value_2 = g;
                    parsing->sky_value_3 = b;
		            parsing->ceiling_color = rgb_to_hex_sky(parsing);
                    
                    //printf("parsing->ceiling_color = %u\n", parsing->ceiling_color);
                    // printf("1s = %d\n", parsing->sky_value_1);
                    // printf("2s = %d\n", parsing->sky_value_2);
                    // printf("3s = %d\n", parsing->sky_value_3);
                    return 0;  // Valeurs RGB valides trouvées
                }
                
            }
        }
        line_index++;  // Incrément de l'index
    }
  
   // Si aucune valeur RGB valide n'a été trouvée
    printf("Error : sky values are incorrect\n");
    free_parsing(parsing);
    return 1;
}

int parsing_rgbs_floor(char **text_file, t_parsing *parsing)
{
    int line_index;// Initialisation de l'index
    
    line_index = 0;
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "F ", 2) == 0) 
        {
            int r;
            int g;
            int b;
            if (parse_rgb(text_file[line_index], &r, &g, &b, parsing) == 0) 
            {

                if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
                {
                    // Les valeurs RGB sont valides
                    parsing->floor_value_1 = r;
                    parsing->floor_value_2 = g;
                    parsing->floor_value_3 = b;
                    parsing->floor_color = rgb_to_hex_floor(parsing);
                    //printf("parsing->floor_color = %u\n", parsing->floor_color);
                    //printf("1f = %d\n", parsing->floor_value_1);
                    //printf("2f = %d\n", parsing->floor_value_2);
                    //printf("3f = %d\n", parsing->floor_value_3);
                    return 0;  // Valeurs RGB valides trouvées
                }
            }
        }
        line_index++;  // Incrément de l'index
    }
   // Si aucune valeur RGB valide n'a été trouvée
    printf("Error : floor values are incorrect\n");
    free_parsing(parsing);
    exit (1);
    return 1;
}


// int nbr_texture_value(t_parsing *parsing)
// {
//     int i = 0;
//     int already_present = 0;
//     while (parsing->config_elements[i] != NULL) 
//     {
//         if (strncmp(parsing->config_elements[i], "SO ", 2) == 0)
//         {  
//             if (already_present >= 1) 
//             {
//                 //printf("Error: Structure '%s' appears more than once\n", name_texture);
//                 printf("Error: Structure appears more than once\n");
//                 return 1;//exit(1);
//             }
//             already_present++;
//         }
//         i++;
//     }
// return 0;
// }

int nbr_texture_value(const char *prefix, t_parsing *parsing) 
{
    int i = 0;
    int count = 0;
    size_t prefix_length = strlen(prefix);
    while (parsing->config_elements[i] != NULL)
    {
        if (strncmp(parsing->config_elements[i], prefix, prefix_length) == 0) 
        {
            count++;
            if (count > 1) 
            {
                printf("Error: Structure '%s' appears more than once\n", prefix);
                free_parsing(parsing);
                return 1; // Structure trouvée plus d'une fois
            }
        }
        i++;
        
    }
    //printf("ici -------> %s\n", parsing->config_elements[i - 1]);
    // printf("ici2 -------> %s\n", parsing->config_elements[7]);
    return 0; // Structure unique
}


int parsing_rgbs(char **text_file, t_parsing *parsing) 
{
    // if (nbr_texture_value(parsing) == 1)
    //     return 1;
    if (nbr_texture_value("NO ", parsing) ||
        nbr_texture_value("SO ", parsing) || nbr_texture_value("WE ", parsing) 
    || nbr_texture_value("EA ", parsing) || nbr_texture_value("S ", parsing)
    || nbr_texture_value("F ", parsing) || nbr_texture_value("C ", parsing))
            return 1; 
    if (parsing_rgbs_floor(text_file, parsing) == 1)
        return 1;
    if (parsing_rgbs_sky(text_file, parsing) == 1)
        return 1;
return 0;
}

int parse_resolution(char *str, int *width, int *height, t_parsing *parsing) 
{
    int index = 2; // Ignorer les deux premiers caractères "R "
    int values[2] = {0, 0}; // Stocke la largeur et la hauteur
    int i = 0;

    while (str[index]) 
    {
        while (str[index] == ' ')
            index++;

        if (isdigit(str[index])) 
        {
            values[i] = atoi(str + index);
            i++;
            while (isdigit(str[index])) 
            {
               
                index++;
            }           
        } 
        else 
        {
            printf("Error : Non-numeric character found\n");
            free_parsing(parsing);
            return 1;
        }
        if (i > 2) 
        {
            printf("Error: Multiple resolutions in the file\n");
            free_parsing2(parsing);
            return 1; // Résolution invalide
        }
        if (str[index] == ' ' || str[index] == '\0') 
        {
            // Passer au caractère suivant après l'espace ou à la fin de la chaîne
            // Ignorer les espaces après la résolution
            while (str[index] == ' ')
                index++;
        } 
        else 
        {
            printf("Error : Non-numeric character found\n");
            free_parsing(parsing);
            return 1;
        }
    }
    *width = values[0];
    *height = values[1];
    // Résolution valide
    return 0;
}

int parsing_resolution(char **text_file, t_parsing *parsing) 
{
   int line_index;
   
    line_index = 0;  // Initialisation de l'index
    while (text_file[line_index] != NULL) 
    {
        if (strncmp(text_file[line_index], "R ", 2) == 0) 
        {
            int r_x;
            int r_y;
            if (parse_resolution(text_file[line_index], &r_x, &r_y, parsing) == 0) 
            {
               // printf("r_x1 = %d\n",  r_x);
               // printf("r_x2 = %d\n", r_y);

                if (r_x > 0 && r_y > 0 && r_x <= 2560 && r_y <= 1440) 
                {
                    // La résolution est valide
                    parsing->r_value_x = r_x;
                    parsing->r_value_y = r_y;
                  //  printf("r_x = %d\n",  parsing->r_value_x);
                  //  printf("r_x = %d\n", parsing->r_value_y);
                    return 0;  // Résolution valide trouvée
                }
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : Incorrect or undefined resolution\n");
    free_parsing2(parsing);
    return 1;
}

int extension_compare(const char *text_file, const char *extension) 
{
    int text_file_len = strlen(text_file);
    int ext_len = strlen(extension);
    int i = text_file_len - ext_len;
    //printf("ici%s\n", text_file[i]);
    // Trouver la position de l'extension ".xpm"
    while (i >= 0 && strncmp(text_file + i, extension, ext_len) != 0) 
    {
        i--;
        printf("i = %d\n", i);
    }

    if (i < 0) 
    {
        return 1;  // L'extension n'a pas été trouvée
    }
    // Ignorer les espaces en fin de chaîne
    int j = i + ext_len;
    while (j < text_file_len && isspace(text_file[j])) 
    {
        return 1;//j++;
    }
    
//  if (j == text_file_len)
//         return 0;
    return 0;
}

void free_texture(t_parsing *parsing)
{
    if (!parsing->so_texture_value)
        free(parsing->no_texture_value);//printf("y'a rien\n");
    else if (!parsing->we_texture_value)
    {
        free(parsing->no_texture_value);
        free(parsing->so_texture_value);
    }
    else if (!parsing->ea_texture_value)
    {
        printf("coucou");
        free(parsing->no_texture_value);
        free(parsing->so_texture_value);
        free(parsing->we_texture_value);
    }
}

int check_texture_value(char **text_file, char *name_texture, t_parsing *parsing) 
{
    // Vérifie si le nom du fichier se termine par l'extension ".xpm"
    if (extension_compare(*text_file, ".xpm") == 1) 
    {
        printf("Error: The file must have only the .xpm extension\n");
        free_parsing(parsing);
        exit(1);
    }
    (void)name_texture;
    // int i = 0;
    // while (text_file[i] != NULL) 
    // {
    //     if (strncmp(text_file[i], name_texture, 2) == 0) 
    //     {
    //         if (already_present == 1) 
    //         {
    //             printf("Error: Structure '%s' appears more than once\n", name_texture);
    //             exit(1);
    //         }
    //         already_present++;
    //     }
    //     i++;
    // }
    return 0;
}

int check_s_texture_value(char **text_file, t_parsing *parsing) 
{
    int line_index = 0;
   
    while (text_file[line_index] != NULL) 
    {
        int i = 0;
        int j = 0;

        // Sauter les espaces au début de la ligne
        while (text_file[line_index][i] == ' ')
            i++;

        while (text_file[line_index][i] != '\0') 
        {
             if (strncmp(&text_file[line_index][i], "S ", 2) == 0)
            {
                char *s = "S ";
                if (check_texture_value(&text_file[line_index], s, parsing) == 0) 
                {
                    i = i + 2;
                    
                    while (text_file[line_index][i] == ' ')
                    {
                        i++;
                        j++;
                    }
                    // i pointe maintenant au début du chemin de la texture
                    parsing->s_texture_value = strdup(&text_file[line_index][i]);
                    // Ajoutez le reste de votre logique ici (par exemple, vérification du chemin de texture)
                    return 0;
                }
            } 
            else 
            {
                i++;
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : S texture value is invalid\n");
    free_parsing(parsing);
    return 1;
}


int check_ea_texture_value(char **text_file, t_parsing *parsing) 
{
    int line_index = 0;
   
    while (text_file[line_index] != NULL) 
    {
        int i = 0;
        int j = 0;

        // Sauter les espaces au début de la ligne
        while (text_file[line_index][i] == ' ')
            i++;

        while (text_file[line_index][i] != '\0') 
        {
            if (strncmp(&text_file[line_index][i], "EA", 2) == 0) 
            {
                char *ea = "EA ";
                if (check_texture_value(&text_file[line_index], ea, parsing) == 0) 
                {
                    i = i + 2;
                    
                    
                    while (text_file[line_index][i] == ' ')
                    {
                        i++;
                        j++;
                    }
                    // i pointe maintenant au début du chemin de la texture
                    parsing->ea_texture_value = strdup(&text_file[line_index][i]);
                    // Ajoutez le reste de votre logique ici (par exemple, vérification du chemin de texture)
                    return 0;
                }
            } 
            else 
            {
                i++;
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : EA texture value is invalid\n");
    free_parsing2(parsing);
    return 1;
}

int check_we_texture_value(char **text_file, t_parsing *parsing) 
{
    int line_index = 0;
   
    while (text_file[line_index] != NULL) 
    {
        int i = 0;
        int j = 0;

        // Sauter les espaces au début de la ligne
        while (text_file[line_index][i] == ' ')
            i++;

        while (text_file[line_index][i] != '\0') 
        {
            if (strncmp(&text_file[line_index][i], "WE", 2) == 0) 
            {
                char *we = "WE ";
                if (check_texture_value(&text_file[line_index], we, parsing) == 0) 
                {
                    i = i + 2;
                    
                    
                    while (text_file[line_index][i] == ' ')
                    {
                        i++;
                        j++;
                    }
                    // i pointe maintenant au début du chemin de la texture
                    parsing->we_texture_value = strdup(&text_file[line_index][i]);
                    // Ajoutez le reste de votre logique ici (par exemple, vérification du chemin de texture)
                    return 0;
                }
            } 
            else 
            {
                i++;
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : WE texture value is invalid\n");
    free_parsing2(parsing);
    return 1;
}

int check_so_texture_value(char **text_file, t_parsing *parsing) 
{
    int line_index = 0;
   
    while (text_file[line_index] != NULL) 
    {
        int i = 0;
        int j = 0;

        // Sauter les espaces au début de la ligne
        while (text_file[line_index][i] == ' ')
            i++;

        // Recherche manuelle de la sous-chaîne "SO" en ignorant les espaces
        while (text_file[line_index][i] != '\0') 
        {
            if (strncmp(&text_file[line_index][i], "SO", 2) == 0) 
            {
                char *so = "SO ";
                if (check_texture_value(&text_file[line_index], so, parsing) == 0) 
                {
                    i = i + 2;
                    
                    
                    while (text_file[line_index][i] == ' ')
                    {
                        i++;
                        j++;
                    }
                    // i pointe maintenant au début du chemin de la texture
                    parsing->so_texture_value = strdup(&text_file[line_index][i]);
                    // Ajoutez le reste de votre logique ici (par exemple, vérification du chemin de texture)
                        //test
                    return 0;
                }
            } 
            else 
            {
                i++;
            }
        }
        line_index++;  // Incrément de l'index
    }
    // Si aucune résolution valide n'a été trouvée
    
    printf("Error : SO texture value is invalid\n");
    free_parsing2(parsing);
    return 1;
}

int check_no_texture_value(char **text_file, t_parsing *parsing) 
{
    int line_index = 0;
   
    while (text_file[line_index] != NULL) 
    {
        int i = 0;
        int j = 0;

        // Sauter les espaces au début de la ligne
        while (text_file[line_index][i] == ' ')
            i++;

        // Recherche manuelle de la sous-chaîne "NO" en ignorant les espaces
        while (text_file[line_index][i] != '\0') 
        {
            if (strncmp(&text_file[line_index][i], "NO", 2) == 0) 
            {
                char *no = "NO ";
                if (check_texture_value(&text_file[line_index], no, parsing) == 0) 
                {
                    i = i + 2; // Sauter "NO"
                    
                    // Compter les espaces après "NO"
                    while (text_file[line_index][i] == ' ')
                    {
                        i++;
                        j++;
                    }
                    // i pointe maintenant au début du chemin de la texture
                    parsing->no_texture_value = strdup(&text_file[line_index][i]);
                    // Ajoutez le reste de votre logique ici (par exemple, vérification du chemin de texture)
                    return 0;
                }
            } 
            else 
            {
                // Si ce n'est pas "NO", passer au caractère suivant
                i++;
            }
        }
        line_index++;  // Incrément de l'index
 
    }
    // Si aucune résolution valide n'a été trouvée
    printf("Error : NO texture value is invalid\n");
    free_parsing2(parsing);
    return 1;
}

int parsing_textures(char **text_file, t_parsing *parsing)
{
    if (check_no_texture_value(text_file, parsing) == 1)
		return (1);
    if (check_so_texture_value(text_file, parsing) == 1)
            return (1);
	if (check_we_texture_value(text_file, parsing) == 1)
		return (1);
    if (check_ea_texture_value(text_file, parsing) == 1)
		return (1);
	if (check_s_texture_value(text_file, parsing) == 1)
		return (1);
	return (0);
}

// manque prefixe s ??? -> fonction qui sert a rien finalement
// int check_map_prefixes(char **text_file) 
// {
//     int i = 0;
//     int found = 0;  // Utilisez une variable pour suivre si une correspondance a été trouvée
    
//     while (text_file[i]) 
//     {
//         //ne comprends pas les espaces, attention
//         if (strncmp(text_file[i], "NO", 2) == 0)
//             found++;
//         else if (strncmp(text_file[i], "SO", 2) == 0)
//             found++;
//         else if (strncmp(text_file[i], "WE", 2) == 0) 
//             found++;
//         else if (strncmp(text_file[i], "EA", 2) == 0) 
//             found++;
//         else if (strncmp(text_file[i], "S ", 2) == 0) 
//             found++;
//         else if (strncmp(text_file[i], "F ", 2) == 0) 
//             found++;
//          else if (strncmp(text_file[i], "C ", 2) == 0) 
//             found++;    
//         i++;
//     }
//     printf("ici = %d\n", found);
//     if (found == 7)
//             return 0;
//     else 
//     {
//         printf("Error : the map prefixes are not good\n");
//         return 1;
//     }
// }
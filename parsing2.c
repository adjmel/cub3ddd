#include "cub3d.h"

//parsing de la map
int parsing_map_elements(char **text_file, t_parsing *parsing)
{   
    (void)text_file;
        if (correct_number(parsing) == 1) //✅
           return 1;
        if (map_closed(parsing) == 1) 
            return 1;       
        if (map_less_3_lines(parsing) == 1) //✅
            return 1;
        if (check_nbr_player(parsing) == 1) //✅
            return 1;
        if (check_nbr_directions(parsing) == 1) //✅
            return 1;
        //if (put_map_in_struct(parsing) == 1) //inutile pour l'instant -> a revoir
            //return 1;
    return 0;
}

int check_config_elements(char **text_file, t_parsing *parsing)
{
        if (parsing_rgbs(text_file, parsing) == 1) //✅        
            {
                //free_parsing(parsing);
                return (1);
            }
        //if (parsing_resolution(text_file, parsing) == 1) //✅ car "R  1920 1080" n'est pas a mettre dans le fichier
          //  return (1);
                   printf("je seg ici\n");           
        if (parsing_textures(text_file, parsing) == 1) //✅
            {
                //free_parsing(parsing);
                return (1);
            }
        // if (check_map_prefixes(text_file) == 1)
        //     return (1);
    return 0;
}

//garder dans le prototype que t_parsing *parsing
int parsing_cub3d(char **text_file, t_parsing *parsing)
{
    (void)text_file;

    int i = 0;
    // Analyse les informations de configuration (résolution, textures, couleurs, etc.)
    if (check_config_elements(parsing->config_elements, parsing) == 1)
        return (1);
               
    parsing->map[parsing->map_count + parsing->start_map - 1] = NULL;

    //mettre la map dans une autre structure pour la traiter et que les deux
    //ne se melange pas

    if (parsing_map_elements(&parsing->map[i], parsing) == 1)
       return (1);
    

        //ree(parsing->so_texture_value);

return 0;
}
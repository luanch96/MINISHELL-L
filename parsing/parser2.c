/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:00:14 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/24 12:03:58 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_pars(t_general *general)
{
    char *temp;
    char *path;
    int j;

    j = 0;
    path = check_path(general->envp);
    general->paths = ft_split(path, ':');
    free(path);

    while(general->paths[j])
    {
        if(ft_strncmp(&general->paths[j][ft_strlen(general->paths[j]) - 1], "/", 1) != 0)
        {
            temp = ft_strjoin(general->paths[j], "/");
            free(general->paths[j]);
            general->paths[j] = temp;
        }
        j++;
    }
    return(EXIT_SUCCESS);
}

/*
The function's purpose is to parse the environment 
variable `envp` and manipulate its contents to create a list of paths.

Here's a step-by-step breakdown of what the function does:

1. It retrieves the value of the `envp` environment variable using the 
`find_path` function, which is not shown in this snippet.
2. It splits the retrieved path into individual directories using the 
`ft_split` function with a separator of `:`.
3. It iterates over each directory in the list and checks if it ends with 
a slash (`/`) character. If it does not end with a slash, it prepends an 
additional slash to the directory name.
4. After the iteration is complete, the modified list of directories is 
stored in the `tools->paths` field of the `t_tools` struct.

The purpose of this function seems to be to normalize the environment 
variable `envp` by removing any trailing slashes and prepending them to 
directories that are missing them. The final normalized list of paths is 
then likely used elsewhere in the program.

Some potential improvements or alternative approaches:

* Instead of using `ft_strjoin` and manually freeing memory, consider 
using a more modern C standard library function like `snprintf`.
* Consider adding additional error checking or handling for cases where 
`envp` is not set or contains invalid data.
* If the `tools->paths` field is dynamically allocated memory (e.g., using 
`malloc`), make sure to free it when no longer needed to avoid memory 
leaks.
*/


void add_comand_back(t_comands **lst, t_comands *new)
{
    t_comands *temp;

    temp = *lst;
    if(*lst == NULL)
    {
        *lst = new;
        return ;
    }
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new;
    new->prev = temp;
}

t_comands *start_cmds(t_parser_tools *tool)
{
    int j;
    int size_arg;
    char **string;
    t_lexer *temp;

    j = 0;
    remove_redir(tool);
    size_arg = arg_count(tool->lexer_list);
    string = ft_calloc(size_arg + 1, sizeof(char *));
    if(!string)
    {
        error_parsing(1, tool->tools, tool->lexer_list);
    }
    temp = tool->lexer_list;
    while(size_arg > 0)
    {
        if(temp->str)
        {
            string[j++] = ft_strdup(temp->str);
            ft_lexer_reset(&tool->lexer_list, temp->i);
            temp = tool->lexer_list;
        }
        size_arg--;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:16:41 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/21 12:54:34 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int look_pwd(t_general *general)
{
    int j;

    j = 0;
    while(general->envp[j])
    {
        if(!ft_strncmp(general->envp[j],"OLDPWD=", 7))
        {
            general->oldpwd = ft_substr(general->envp[j], 7, ft_strlen(general->envp[j]) - 7);
        }
        if(!ft_strncmp(general->envp[j], "PWD=", 4))
        {
            general->pwd = ft_substr(general->envp[j], 4, ft_strlen(general->envp[j]) - 4);
        }
        j++;
    }
}

void count_pipes(t_lexer *lexer_list, t_general *general)
{
    t_lexer *temp;

    temp = lexer_list;
    general->pipes = 0;
    while (temp)
    {
        if(temp->token == PIPE)
        {
            general->pipes++;
        }
        temp = temp->next;
    }
}

void ft_lexer_delfirst(t_lexer **lst)
{
    t_lexer *node;

    node = *lst;
    *lst = node->next;
    ft_lexer_delfirst(&node);
    if(*lst)
    {
        (*lst)->prev = NULL;
    }
}

void ft_lexer_reset (t_lexer **lst, int key)
{
    t_lexer *node;
    t_lexer *prev_node;
    t_lexer *start;

    start = *lst;
    node = start;
    if((*lst)->i == key)
    {
        ft_lexer_delfirst(lst);
        return ;
    }
    while(node && node->i != key)
    {
        prev_node = node;
        node = node->next;
    }
    if(node)
    {
        prev_node->next = node->next;
    }
    else
    {
        prev_node->next = NULL;
    }
    if(prev_node->next)
    {
        prev_node->next->prev = prev_node;
    }
    ft_lexer_delfirst(&node);
    *lst = start;
}

int handle_pipe_errors(t_general *general, t_tokens token)
{
    if(token == PIPE)
    {
        parser_token_error(general, general->lexer_list, general->lexer_list->token);
        return(EXIT_FAILURE);
    }
    if(!general->lexer_list)
    {
        error_parsing(0, general, general->lexer_list);
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

t_parser_tools start_parser(t_lexer *list, t_general *general)
{
    t_parser_tools tool;

    tool.lexer_list = list;
    tool.redirections = NULL;
    tool.num_redirections = 0;
    tool.tools = tool;
    return (tool);
}

void remove_redir(t_parser_tools *tool)
{
    t_lexer *temp;

    temp = tool->lexer_list;
    while (temp && temp->token == 0)
    {
        temp = temp->next;
    }
}

int arg_count(t_lexer *list)
{
    t_lexer *temp;
    int j;

    j = 0;
    temp = list;
    while(temp && temp->token != PIPE)
    {
        if(temp->i >= 0)
        {
            j++;
        }
        temp = temp->next;
    }
    return(j);
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

















int parser(t_general *general)
{
    t_comands *node;
    t_parser_tools parser_tools;

    general->cmds = NULL;
    count_pipes(general->lexer_list, general);
    if(general->lexer_list->token == PIPE)
    {
        return(parser_token_error(general, general->lexer_list, general->lexer_list->token));
    }
    while(general->lexer_list)
    {
        if(general->lexer_list && general->lexer_list->token == PIPE)
        {
            ft_lexer_reset(&general->lexer_list, general->lexer_list->i);
        }
        if(handle_pipe_errors(general, general->lexer_list->token))
        {
            return(EXIT_FAILURE);
        }
        parser_tools = start_parser(general->lexer_list, general);
        node = start_cmds(&parser_tools);
        if()
    }
}


/*is is a C function named `find_pwd` that appears to be part of a larger 
program. The purpose of the function is to parse and extract environment 
variables from a list (`envp`) stored in a struct (`tools`).

Specifically, it checks each environment variable (`envp[i]`) in the list 
and:

1. If the variable starts with "PWD=" (4 characters), it extracts the 
value starting from the 5th character (index 4) to the end of the string 
and stores it in the `pwd` field of the `tools` struct.
2. If the variable starts with "OLDPWD=" (7 characters), it extracts the 
value starting from the 8th character (index 7) to the end of the string 
and stores it in the `old_pwd` field of the `tools` struct.

The function iterates over each environment variable, performs these 
checks, and updates the corresponding fields of the `tools` struct. It 
returns an integer value of 1 if any environment variables are 
successfully parsed.

In summary, this function is used to extract and store the current working 
directory (`PWD`) and the previous working directory (`OLDPWD`) from a 
list of environment variables.
*/

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

char *check_path(char **env)
{
    int j;

    j = 0;
    while(env[j])
    {
        if(!ft_strncmp(env[j], "PATH=", 5))
        {
            return(ft_substr(env[j], 5, ft_strlen(env[j])) - 5);
        }
        j++;
    }
    return(ft_strdup("\0"));  //en caso de no encontrar Path, retorna String vacio.
}

/*The `find_path` function appears to be part of a custom string 
manipulation library, specifically designed for working with environment 
variables. Here's what it does:

1. It takes a pointer to an array of strings (`char **envp`) as input.
2. It iterates over each string in the array using a while loop.
3. For each string, it checks if the string starts with the prefix "PATH=" 
using `ft_strncmp`.
4. If the string matches the prefix, it extracts the path value by taking 
a substring starting from index 5 (since the prefix is 5 characters long) 
up to the end of the string.
5. The extracted path value is then returned as a new string using 
`ft_substr`.
6. If no matching "PATH=" prefix is found in the array, it returns a 
duplicate copy of an empty string (`"\0"`) using `ft_strdup`.

The purpose of this function seems to be to extract and return the value 
of the environment variable `PATH`, which typically contains a 
colon-separated list of directories where executable files are searched 
for.

Some observations about this implementation:

* The use of `ft_strncmp` with a fixed-length prefix is an efficient way 
to quickly identify the `PATH=` prefix.
* The `ft_substr` function is used to extract the path value, which 
suggests that this library provides a set of custom string manipulation 
functions.
* The return type of the function is `char *`, indicating that it returns 
a pointer to a dynamically allocated string.

Overall, this implementation appears to be designed for working with 
environment variables and provides a convenient way to extract the `PATH` 
value from an array of strings.*/

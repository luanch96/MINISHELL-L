/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:16:41 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/24 12:07:03 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*In summary, this function simply counts the number of pipes in a given linked list of tokens and stores the 
result in the `pipes` field of the `general` structure.
*/

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
    while(general->lexer_list) //parsing loop
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
        if(!node)
        {
            error_parsing(0, general, parser_tools.lexer_list);
        }
        if (!general->cmds)
        {
            general->cmds = node;
        }
        else
        {
            add_comand_back(&general->cmds, node);
        }
        general->lexer_list = parser_tools.lexer_list;
    }
    return(EXIT_SUCCESS);
}

/* **Function purpose:**
The `parser` function takes an argument `general`, which seems to represent the 
current state of the shell or interpreter, and parses a sequence of commands from a 
lexer.

**Initialization:**

1. It initializes the `cmds` field of the `general` structure to `NULL`.
2. It counts the number of pipes in the `lexer_list` using the `count_pipes` 
function.
3. If there's only one pipe, it returns an error code (`parser_token_error`) 
indicating that the input is invalid.

**Parsing loop:**

1. The function enters a loop that continues until all tokens in the `lexer_list` 
have been processed.
2. Inside the loop:
	* If the current token is a pipe (`PIPE`), it resets the lexer position using `ft_l
`ft_lexer_reset`.
	* It calls the `handle_pipe_errors` function to handle any errors related to pipes.
	* If an error occurs, the function returns an error code (`EXIT_FAILURE`) indicating 
failure.
	* The function calls `start_parser` to start parsing the next token in the lexer li
list, passing in the current lexer position and the `general` structure as arguments.
	* It stores the result of `start_parser` in a node variable named `node`.
	* If `node` is `NULL`, it returns an error code (`EXIT_FAILURE`) indicating that pa
parsing failed.
	* The function adds the new node to the beginning of the `cmds` list using `add_com
`add_comand_back`.

**Final step:**

1. After processing all tokens, the function updates the `lexer_list` field of the 
`general` structure with the lexer position passed as an argument in the 
`start_parser` call.
2. The function returns a success code (`EXIT_SUCCESS`) indicating that parsing was 
successful.*/


/*In summary, this function is responsible for parsing a sequence of commands from a 
lexer, handling errors related to pipes, and adding each parsed command to a linked 
list (`cmds`).
*/



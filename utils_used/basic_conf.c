/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_conf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:36:51 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/13 13:59:29 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int setstart_conf(t_general *general)
{
    general->pid = NULL;
    general->cmds = NULL;
    general->lexer_list = NULL;  //No entiendo, revisar.
    general->heredoc = false;
    general->reset = false;
    g_global.stop_heredoc = 0;
    g_global.in_cmd = 0;
    g_global.in_cmd = 0;
    env_pars(general);
    init_signals();
    return(1);
}

int reset_comands (t_general *general)
{
    comands_clear(&general->cmds);
    free(general->args);
    if(general->pid)
    {
        free(general->pid);
    }
    free_array(general->paths);
    setstart_conf(general);
    general->reset = true;
    loop(general);
    return (1);
}


int loop(t_general *general)
{
    char *space;

    general->args = readline(READLINE_MSG);
    space = ft_strtrim(general->args, " ");
    free(general->args);
    general->args = space;
    
    if(!general->args)
    {
        ft_putendl_fd("Exit", STDOUT_FILENO);
        exit(EXIT_SUCCESS);
    }
    if(general->args[0] == '\0')
        return(reset_comands(general));
    add_history(general->args);
    if(!count_quotes(general->args))
    {
        return(error(1, general));
    }
    parser(general);
    prepare_executor(general);
    reset_comands(general);
    return (1);
}

/*This function appears to be part of a shell implementation in C. It is the 
main loop of the shell, responsible for processing user input.

Here's a step-by-step breakdown of what the function does:

1. **Reads user input**: The function reads a line from standard input 
using `readline(READLINE_MSG)`. This line is stored in `tools->args`.

2. **Strips whitespace**: It removes any leading or trailing whitespace 
from the input string using `ft_strtrim(tools->args, " ")`, and stores the 
result back in `tools->args`.

3. **Freezes previous arguments**: The function frees the memory allocated 
to `tools->args` in a previous iteration.

4. **Checks for exit condition**: If `tools->args` is empty or only 
contains whitespace, it executes an "exit" command by printing "exit" and 
exiting the program with status code `EXIT_SUCCESS`.

5. **Adds history entry**: It adds the current input to the shell's 
history using `add_history(tools->args)`.

6. **Checks for quoting**: If the input string is not enclosed in quotes, 
it calls the `count_quotes` function (not shown here) to check if there 
are any quoted strings in the input. If not, it returns an error with code 
2.

7. **Processes tokens**: It calls the `token_reader(tools)` function (not 
shown here) to split the input string into individual tokens (words).

8. **Parses commands**: It calls the `parser(tools)` function (not shown 
here) to parse each token as a command.

9. **Prepares executor**: It calls the `prepare_executor(tools)` function 
(not shown here) to prepare the shell's executor for executing the parsed 
commands.

10. **Reset tools**: After processing all tokens, it resets the shell's 
tool state using `reset_tools(tools)`.

11. **Returns success**: If none of the above steps fail, the function 
returns 1 indicating success.

This function is likely part of a larger shell implementation, and other 
functions (`token_reader`, `parser`, `prepare_executor`) are not shown 
here but are essential to the overall functionality of the shell.
*/
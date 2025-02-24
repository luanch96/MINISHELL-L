/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:13:48 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/24 11:58:11 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_error(int error, t_general *general)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    if(error == 0)
    {
        ft_putstr_fd("syntax error near unexpected token 'newline'\n", STDERR_FILENO);
    }
    else if(error == 1)
    {
        ft_putstr_fd("memory: not able to asign memory\n", STDERR_FILENO);
    }
    else if(error == 2)
    {
        ft_putstr_fd("unable to find closing quote\n", STDERR_FILENO);
    }
    else if(error == 3)
    {
        ft_putstr_fd("Parser problem\n", STDERR_FILENO);
    }
    else if(error == 4)
    {
        ft_putstr_fd("Not able to create pipe\n", STDERR_FILENO);
    }
    else if (error == 5)
    {
        ft_putstr_fd("Failed to Fork\n", STDERR_FILENO);
    }
    else if (error == 6)
    {
        ft_putstr_fd("Outfile error\n", STDERR_FILENO);
    }
    else if (error == 7)
    {
        ft_putstr_fd("infile error: Not such file or directory\n", STDERR_FILENO);
    }
    else if (error == 8)
    {
        ft_putstr_fd("Path does not exist", STDERR_FILENO);
    }
    reset_comands(general);
    return(EXIT_FAILURE);
}

void error_parsing(int error, t_general *general, t_lexer *list)
{
    clear_lexer(&list);
    ft_error(error, general);
}

int parser_token_error(t_general *general, t_lexer *lexer_list, t_tokens token)
{
    ft_putstr_fd("minishell: syntax error unexpected token ", STDERR_FILENO);

    if(token == GREAT)
    {
        ft_putstr_fd("'>'\n", STDERR_FILENO);
    }
    else if(token == D_GREAT)
    {
        ft_putstr_fd("'>>'\n", STDERR_FILENO);
    }
    else if(token == PIPE)
    {
        ft_putstr_fd("'|'\n", STDERR_FILENO);
    }
    else if(token == LESS)
    {
        ft_putstr_fd("'<'\n", STDERR_FILENO);
    }
    else if(token == D_LESS)
    {
        ft_putstr_fd("'<<'\n", STDERR_FILENO);
    }
    else
    {
        ft_putstr_fd("\n", STDERR_FILENO);
    }
    clear_lexer(&lexer_list);
    reset_comands(general);
    return (EXIT_FAILURE);
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
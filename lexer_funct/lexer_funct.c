/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:05:02 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/26 13:16:16 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_tokens is_token(int c)
{
    int i;

    static int array_tokens[3][2] =
    {
        {'|', PIPE}, {'>', GREAT}, {'<', LESS}
    };
    
    i = 0;
    while(i < 3)
    {
        if(array_tokens[i][0] == c)
        {
            return(array_tokens[i][1]);
        }
        i++;
    }
    return(0);
}

int space(char x)
{
    return (x == ' ' || x == '\t' || 
        x == '\n' || x == '\v' || x == '\f' || x == '\r');
}

int ignore_space(char *s, int i)
{
    int j;

    j = 0;
    while (space(s[i + j]))
    {
        j++;
    }
    return(j);
}

int token_reader(t_general *general)
{
    int i;
    int j;
    
    int i = 0;
    int j = 0;
    while(general->args[i])
    {
        j = 0;
        i += ignore_space(general->args, i);
        if(is_token(general->args[i]))
        {
            j = token_manage(general->args, i, &general->lexer_list);
        }
        else
        {
            j = words_reader(i, general->args, &general->lexer_list);
        }
        if(j < 0)
        {
            return(0);
        }
        i += j;
    }
    return(1);
}
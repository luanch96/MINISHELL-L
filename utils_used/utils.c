/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:37:15 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/24 14:01:00 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function, `ft_arrdup`, is a duplicate of an array of strings. It 
takes a pointer to the first element of an array of strings as input and 
returns a new array of strings that contains identical copies of each 
string in the original array.

Here's a breakdown of what it does:

1. **Counting the number of elements**: The function counts the number of 
elements in the input array by iterating through each pointer (`arr[i]`) 
until it reaches `NULL`.
2. **Allocaion and initialization**: It allocates memory for a new array 
using `ft_calloc`, which is similar to `malloc` but allocates space for an 
array.
3. **Copying strings**: The function iterates through each string in the 
input array, duplicates it using `ft_strdup`, and assigns the duplicate to 
the corresponding position in the new array.
4. **Error handling**: If any of the duplicates fail to allocate memory 
(i.e., return `NULL`), the function frees the already allocated memory for 
that duplicate (using `free_arr`) and returns `NULL`.

The purpose of this function is to create a deep copy of an array of 
strings, which can be useful in situations where you need to ensure that 
changes made to one copy do not affect the original.
*/

char **ft_dupl_array(char **array)
{
    char **dupl;
    size_t i;

    i = 0;
    while(array[i] != NULL)
        i++;
    dupl = ft_calloc(sizeof(char *), i + 1);
    if (!dupl)
        return (NULL);
    i = 0;
    while(dupl[i] != NULL)
    {
        dupl[i] = ft_strdup(array[i]);
        if(dupl[i] == NULL)
        {
            free_array(dupl);
            return (dupl);
        }
        i++;
    }
    return(dupl);
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

int token_manage(char *s, t_lexer **list, int j)
{
    
}

void token_reader(t_general *general)
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
            j = han
        }
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:37:15 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/20 12:34:20 by luisfederic      ###   ########.fr       */
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


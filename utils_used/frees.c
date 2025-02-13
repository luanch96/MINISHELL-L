/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:52:57 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/13 13:03:10 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void free_array(char **split_array)
{
    int j;

    j = 0;
    while(split_array[j])
    {
        free(split_array[j++]);
    }
    free(split_array);
}

void clear_lexer(t_lexer **last)
{
    t_lexer *temp;
    
    if(!*last)
    {
        return ;
    }
    while(*last)
    {
        temp = (*last)->next;
        if((*last)->str)
            free((*last)->str);
        free(*last);
        *last = temp;
    }
    *last = NULL;
}

/*This function, `ft_lexerclear`, is a part of the lexical analysis component of a 
shell or compiler implementation. It appears to be responsible for clearing the 
linked list of tokens that are stored in memory.

Here's a step-by-step breakdown of what the function does:

1. **Checks if the list is empty**: The function checks if the `lst` pointer points 
to an invalid or null address by checking if `*lst` is zero. If it is, the function 
returns immediately without doing anything.

2. **Iterates through the linked list**: The function then enters a while loop that 
traverses the linked list of tokens from head to tail. In each iteration:
   - It temporarily stores the next token in the list in `tmp = (*lst)->next`.
   - If the current token's string buffer (`(*lst)->str`) is not null, it frees the 
memory allocated for that buffer using `free((*lst)->str)`.
   - It frees the memory allocated to the entire token structure (including its 
string buffer and any other data members) using `free(*lst)`.

3. **Updates the list pointer**: After freeing the current token's memory, the 
function updates the `*lst` pointer to point to the next token in the list (`tmp`).

4. **Sets the final node to null**: After iterating through all tokens and freeing 
their memory, the function sets the `*lst` pointer to null to indicate that there are 
no more tokens left in the list.

The purpose of this function is likely to release any allocated memory when a lexical 
analysis session is closed or completed. This prevents memory leaks and ensures that 
the shell or compiler can reuse the available memory for future sessions.

Example usage:

```c
t_lexer *tokens = NULL;

// Assume some tokens are added to the linked list

ft_lexerclear(&tokens);  // Frees all allocated memory for the tokens

if (tokens)
    ft_lexerclear(&tokens);
```

In this example, `ft_lexerclear` is called twice: once to clear the initial token 
list, and again when no more tokens are needed.
*/

void comands_clear(t_comands **last)
{
    t_comands *temp;
    t_lexer *redirection;

    if(!*last)
    {
        return ;
    }
    while (*last)
    {
        temp = (*last)->next;
        redirection = (*last)->redirections;
        clear_lexer(&redirection);
        if((*last)->str)
        {
            free_array((*last)->str);
        }
        if((*last)->hd_file_name)
        {
            free((*last)->hd_file_name);
        }
        free(*last);
        *last = temp;
    }
    *last = NULL;
}
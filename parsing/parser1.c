/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:14:51 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/24 12:01:50 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *lexer_clear(t_lexer **list)
{
    if((*list)->str)
    {
        free((*list)->str);
        (*list)->str = NULL;
    }
    free(*list);
    *list = NULL;
    return (NULL);
}
/*3. lexer_clear(t_lexer **list)

This function frees the memory allocated for a node and its string (str).
Step-by-Step Explanation:

    Free the Node's String:

        if((*list)->str): If the node has a string:

            free((*list)->str); frees the memory allocated for the string.

            (*list)->str = NULL; sets the string pointer to NULL.

    Free the Node Itself:

        free(*list); frees the memory allocated for the node.

    Set the Pointer to NULL:

        *list = NULL; sets the pointer to NULL to prevent accessing freed memory.

    Return NULL:

        return (NULL); returns NULL to indicate successful deallocation.
*/

void ft_lexer_delfirst(t_lexer **lst)
{
    t_lexer *node;

    node = *lst;
    *lst = node->next;
    lexer_clear(&node);
    if(*lst)
    {
        (*lst)->prev = NULL;
    }
}
/*This function removes the first node from the linked list.
Step-by-Step Explanation:

    Save the First Node:

        t_lexer *node; is declared to hold the first node.

        node = *lst; saves the first node.

    Update the List Head:

        *lst = node->next; moves the head of the list to the next node.

    Free the First Node's Memory:

        lexer_clear(&node); frees the memory allocated for the first node.

    Update Previous Pointer of the New First Node:

        if(*lst): If the list is not empty after removing the first node:

            (*lst)->prev = NULL; sets the prev pointer of the new first node to NULL.
*/

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
    lexer_clear(&node);
    *lst = start;
}

/*1. ft_lexer_reset(t_lexer **lst, int key)

This function is designed to remove a node from a doubly li
nked list based on a specific key value (key) stored in the node's i field.*/

/*Step-by-Step Explanation:

    Initialization:

        t_lexer *node;, t_lexer *prev_node;, and t_lexer *start; are declared to keep track of nodes during the traversal.

        start = *lst; and node = start; initialize start and node to the head of the list (*lst).

    Check if the First Node is the One to Delete:

        if((*lst)->i == key): If the first node's i value matches the key, it calls ft_lexer_delfirst(lst) to remove the first node and then returns from the function.

    Search for the Node to Delete:

        while(node && node->i != key): This loop continues until it finds a node with i equal to key or reaches the end of the list (node becomes NULL).

        Inside the loop:

            prev_node = node; saves the current node as the previous node.

            node = node->next; moves to the next node in the list.

    Update Pointers to Remove the Node:

        if(node): If a node with the matching key was found:

            prev_node->next = node->next; updates the next pointer of the previous node to skip the node to be deleted.

        else: If no node with the matching key was found (i.e., node is NULL):

            prev_node->next = NULL; sets the next pointer of the last node to NULL, indicating the end of the list.

    Update Previous Pointer of the Next Node:

        if(prev_node->next): If there is a next node after the one being deleted:

            prev_node->next->prev = prev_node; updates the prev pointer of the next node to point to the previous node.

    Free the Node's Memory:

        lexer_clear(&node); frees the memory allocated for the node to be deleted.

    Restore the List Head:

        *lst = start; restores the head of the list to its original value. However, this line is unnecessary if the first node was deleted, as the head would have already been updated.
*/


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

/*The `check_path` function appears to be part of a custom string 
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

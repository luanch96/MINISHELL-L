/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:52:57 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/03 00:07:33 by luisfederic      ###   ########.fr       */
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
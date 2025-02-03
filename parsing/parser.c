/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:16:41 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/03 00:58:17 by luisfederic      ###   ########.fr       */
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

    
    
}

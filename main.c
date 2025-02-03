/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:38:17 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/03 14:02:01 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    t_general general;

    if(argc != 1 || argv[1])
    {
        printf("Program does not allow any arguments\n");
        exit(0);
    }
    general.envp = ft_dupl_array(env);
    look_pwd(&general);
    setstart_conf(&general);
}


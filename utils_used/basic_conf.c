/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_conf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:36:51 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/03 14:02:35 by luisfederic      ###   ########.fr       */
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
    general->stop_heredoc = 0;
    general->in_cmd = 0;
    general->in_cmd = 0;
    env_pars(general);
    init_signals();
    return(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:37:54 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/03 14:09:27 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_general
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_simple_cmds	*cmds;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*oldpwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}		t_general;

typedef struct s_global
{
	int	error_num;
	int	stop_heredoc;
	int	in_cmd;
	int	in_heredoc;
}	t_global;

t_global	g_global;

int main(int argc, char **argv, char **envp);

char **ft_dupl_array(char **array);

void free_array(char **split_array);

int look_pwd(t_general *general);

int setstart_conf(t_general *general);

int env_pars(t_general *general);

char *check_path(char **env);

void init_signals(void);

int event(void);

void handler_sigint(int sig);

#endif
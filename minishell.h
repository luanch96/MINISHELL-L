/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:37:54 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/13 14:17:01 by luisfederic      ###   ########.fr       */
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

# define READLINE_MSG	"\033[1;36mminishell\033[34m$ \033[0m"

typedef struct s_general
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_comands		*cmds;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*oldpwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}		t_general;

typedef struct s_comands
{
	char					**str;
	int						(*builtin)(t_general *, struct s_comands *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_comands;


typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;

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

void clear_lexer(t_lexer **last);

void comands_clear(t_comands **last);

int reset_comands (t_general *general);

int loop(t_general *general);

char	**quotes_tokenizer(char *input);

char	**quotes_tokenizer_aux(char **tokens, char	*s, int start, int tok);

int	count_tokens(char *s, int i, int tokens);

#endif
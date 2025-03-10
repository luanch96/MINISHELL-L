/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:37:54 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/26 13:17:48 by luisfederic      ###   ########.fr       */
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
	D_GREAT,
	LESS,
	D_LESS,
}	t_tokens;

typedef struct s_parser_tools
{
	t_lexer			*lexer_list;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_tools	*tools;
}	t_parser_tools;

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

int tokens_count(char *line);
int look_quote(char *line, int i, int *num_prev, int num);


int token_reader(t_general *general);
int ignore_space(char *s, int i);
int space(char x);
t_tokens is_token(int c);

int parser_token_error(t_general *general, t_lexer *lexer_list, t_tokens token);
void clear_lexer(t_lexer **last);
int ft_error(int error, t_general *general);

void error_parsing(int error, t_general *general, t_lexer *list);
void ft_lexer_reset (t_lexer **lst, int key);

void ft_lexer_delfirst(t_lexer **lst);
int handle_pipe_errors(t_general *general, t_tokens token);
t_parser_tools start_parser(t_lexer *list, t_general *general);
void remove_redir(t_parser_tools *tool);
void arg_count(t_lexer *list);
int parser(t_general *general);
void add_comand_back(t_comands **lst, t_comands *new);
void *lexer_clear(t_lexer **list);
t_tokens token_check(int x);
int quotes_manage(int i, char *s, char c);
int token_manage(char *s, t_lexer **list, int j);
int words_reader(int i, char *s, t_lexer **list);

#endif
Main

1. char **ft_dupl_array(char **array);
1.1 void free_array(char **split_array);

2. int look_pwd(t_general *general);

3.int setstart_conf(t_general *general);
    3.1 int env_pars(t_general *general);
        3.1.1 char *check_path(char **env);
    3.2 void init_signals(void);
        3.2.0 int event(void)
        3.2.1 void handler_sigint
4. int loop (t_general *general);
    4.1 int reset_comands(t_tools *tools)
        4.1.1 void comands_clear(t_comands **last)
            4.1.1.1 void clear_lexer(t_lexer **last)
    4.2 int tokens_count(char *line);
        4.2.1 int look_quote(char *line, int i, int *num_prev, int num);
   
    4.3 int	token_reader(t_general *general)
        4.3.1 int ignore_space(char *s, int i);
            4.3.1.1 int space(char x);
        4.3.2 t_tokens is_token(int c);

        4.3.3 int token_manage(char *s, t_lexer **list, int j):
        4.3.3.1 int node_sum_empty(t_lexer **list, t_tokens tok, char *s);
        4.3.3.1.1 t_lexer *lex_new(char *s, int tok);
        4.3.3.1.2 void add_back(t_lexer **last, t_lexer *new);
    
        4.3.4 int words_reader(int i, char *s, t_lexer **list);
        4.3.4.1 int quotes_manage(int i, char *s, char c);

    4.3 int parser(t_general *general);
    4.3.1 void count_pipes(t_lexer *lexer_list, t_general *general);
    4.3.2 int parser_token_error(t_general *general, t_lexer *lexer_list, t_tokens token);
    4.3.3 void ft_lexer_reset (t_lexer **lst, int key);
    4.3.3.1 void ft_lexer_delfirst(t_lexer **lst);
    4.3.4 int handle_pipe_errors(t_general *general, t_tokens token);
    4.3.4.1 void error_parsing(int error, t_general *general, t_lexer *list);
    
    4.3.5 t_parser_tools start_parser(t_lexer *list, t_general *general)
    4.3.6 t_comands *start_cmds(t_parser_tools *tool);
    4.3.6.1 void remove_redir(t_parser_tools *tool);
    4.3.6.2 int arg_count(t_lexer *list);








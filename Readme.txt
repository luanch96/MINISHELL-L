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
    4.2 int	count_tokens(char *s, int i, int tokens)

    

        


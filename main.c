#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	t_tools	tools;

	if (argc != 1 || argv[1])
	{
		printf("Program does not allow arguments\n");
		exit(0);
	}
	tools.env = ft_arrdup(envp);
	find_pwd(&tools);
	implement_tools(&tools);
	printf("\n%s\n\n", WELCOME_MSG);
	minishell_loop(&tools);
	return (0);
}
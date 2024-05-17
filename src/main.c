
#include "minishell.h"



int	main()
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			return (ft_putendl_fd("error", 2), rl_clear_history(), EXIT_FAILURE);
		if (input[0] != '\0' && !ft_strisspace(input))
			add_history(input);
		free(input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

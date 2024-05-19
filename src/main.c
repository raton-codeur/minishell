
#include "minishell.h"


/*
ls -l|cat < infile >out
[ls -l] -> [|] -> [cat] -> [<] -> [infile] -> [>] -> [out]
commande pipe commande chevonsimplegauche fichier chevronsimpledroit fichier

dans une commande
1 nom de commande puis arguments
on peut avoir des redirections

chaine s : ls -l|cat < infile >out
trouver la position de toutes les separations
0, 5, 6, 7, 8, 9, 10

faire une liste des tokens

un token
type
contenu

type de token
commande



*/

// typedef enum e_state
// {
// 	STATE_GENERAL,
// 	STATE_QUOTE_SIMPLE,
// 	STATE_QUOTE_DOUBLE
// }	t_state;



t_list	*get_tokens(char *input)
{
	t_list	*result;

	result = NULL;
	list_add_back(&result, list_new(ft_strdup(input)));
	return (result);
}

void	print_as_string(void *p)
{
	ft_putendl_fd(p, 1);
}




typedef struct s_command
{
	char	**split;
	char	*pathname;
}	t_command;

void	free_cmd(t_command *command)
{
	if (command)
	{
		deep_free(command->split, get_length(command->split));
		free(command->pathname);
		free(command);
	}
}

char	*get_pathname(char *command, char **path)
{
	char	*result;

	result = NULL;
	while (*path)
	{
		free(result);
		result = ft_strjoin(*path, command);
		if (access(result, X_OK) == 0)
			return (result);
		path++;
	}
	free(result);
	return (NULL);
}

t_command	*get_cmd(char *command, char **path)
{
	t_command	*result;

	result = ft_calloc(1, sizeof(t_command));
	if (result == NULL)
		return (ft_putendl_fd("erreur a voir", 2), exit(1), NULL);
	result->split = ft_split_quote(command, ' ');
	if (result->split != NULL)
		result->pathname = get_pathname(result->split[0], path);
	if (result->split == NULL || result->pathname == NULL)
	{
		deep_free(result->split, get_length(result->split));
		result->split = NULL;
		ft_putstr_fd("command error for \"", 2);
		ft_putstr_fd(command, 2);
		ft_putendl_fd("\". execve will fail", 2);
	}
	return (result);
}







void	run_commands(t_list *tokens)
{
	
}




int	main()
{
	char	*input;
	t_list	*tokens;
	// char	*path;
	// char	**path_list;

	// path = getenv("PATH");
	// path_list = get_path_list(path);
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			ft_putendl_fd("error", 2);
		else
		{
			if (input[0] != '\0' && !ft_strisspace(input))
				add_history(input);
			tokens = get_tokens(input);
			free(input);
			list_print(tokens, print_as_string);
			run_commands(tokens);
		}
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

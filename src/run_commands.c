// typedef struct s_command
// {
// 	char	**split;
// 	char	*pathname;
// }	t_command;

// void	free_cmd(t_command *command)
// {
// 	if (command)
// 	{
// 		deep_free(command->split, get_length(command->split));
// 		free(command->pathname);
// 		free(command);
// 	}
// }

// char	*get_pathname(char *command, char **path)
// {
// 	char	*result;

// 	result = NULL;
// 	while (*path)
// 	{
// 		free(result);
// 		result = ft_strjoin(*path, command);
// 		if (access(result, X_OK) == 0)
// 			return (result);
// 		path++;
// 	}
// 	free(result);
// 	return (NULL);
// }

// t_command	*get_cmd(char *command, char **path)
// {
// 	t_command	*result;

// 	result = ft_calloc(1, sizeof(t_command));
// 	if (result == NULL)
// 		return (ft_putendl_fd("erreur a voir", 2), exit(1), NULL);
// 	result->split = ft_split_quote(command, ' ');
// 	if (result->split != NULL)
// 		result->pathname = get_pathname(result->split[0], path);
// 	if (result->split == NULL || result->pathname == NULL)
// 	{
// 		deep_free(result->split, get_length(result->split));
// 		result->split = NULL;
// 		ft_putstr_fd("command error for \"", 2);
// 		ft_putstr_fd(command, 2);
// 		ft_putendl_fd("\". execve will fail", 2);
// 	}
// 	return (result);
// }

// void	run_commands(t_list *tokens)
// {
// 	t_list			*current;
// 	t_command		*command;
// 	char			**path;
// 	pid_t			pid;

// 	pid = 0;
// 	path = get_path_list(getenv("PATH"));
// 	current = tokens;
// 	while (current)
// 	{
// 		command = get_cmd(current->content, path);
// 		if (command == NULL)
// 			return ;
// 		if (command->split != NULL)
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				execve(command->pathname, command->split, NULL);
// 				free_cmd(command);
// 				exit (1);
// 			}
// 			else if (pid > 0)
// 			{
// 				waitpid(pid, NULL, 0);
// 			}
// 			else
// 			{
// 				ft_putendl_fd("fork error", 2);
// 			}
// 		}
// 		current = current->next;
// 	}
// 	deep_free(path, get_length(path));
// }
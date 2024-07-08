/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:41:50 by jteste            #+#    #+#             */
/*   Updated: 2024/07/08 10:35:29 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_key(t_list *node)
{
	return (((t_kv *)node->content)->key);
}

char	*get_value(t_list *node)
{
	return (((t_kv *)node->content)->value);
}

char	**get_key_address(char *key, t_data *data)

char	*get_from_env(char *key, t_data *data)
{
	t_list	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strncmp(get_key(current), key, ft_strlen(get_key(current))))
			return (get_value(current));
		current = current->next;
	}
	return (NULL);
}

void	set_value(char *key, char *new_value, t_data *data)
{
	free(get_from_env(key, data));
	
}







static t_kv	*get_new_content(char *env_line)
{
	t_kv	*result;
	int		i;

	result = ft_calloc(1, sizeof(t_kv));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	result->key = ft_substr(env_line, 0, i);
	result->value = ft_substr(env_line, i + 1, ft_strlen(env_line) - i - 1);
	if (result->key == NULL || result->value == NULL)
		return (NULL);
	return (result);
}


/*free la valeur de SHLVL et ajoute une nouvelle valeur de 1*/
void	reset_SHLVL(t_data *data)
{
	char	*new_value;
	
	free(get_from_env("SHLVL", data));

}


// static int	needs_reset(t_data *data)
// {
// 	char	*value;

// 	value = get_from_env("SHLVL", data);
// 	if (value == NULL)
// 		return (1);
// 	if (!ft_strisdigit(value))
// 		return (1);
// 	if (ft_strlen(skip_zeros(value)) >= 3)
// 		return (1);
// 	if (ft_atoi(skip_zeros(value)) >= 999)
// 		return (1);
// 	return (0);
// }

/*si  SHLVL pas bon il faut le reset a 1
pas bon si pas que des chiffres, negatif, >= 999 */
void	check_SHLVL(t_data *data)
{
	t_kv	*new_content;
	t_list	*new_node;
	char	*value;

	value = get_from_env("SHLVL", data);
	if (value == NULL) // cree la variable et linit a 1
	else if (!is_good_SHLVL(value)) // remettre shlvl a 1
	else // incrementer shlvl
	
	// if ()
	// if (needs_reset(data))
	// {
	// 	new_content = get_new_content("SHLVL=1");
	// 	if (new_content == NULL)
	// 		return (error_exit(MALLOC, data));
	// 	new_node = list_new(new_content);
	// 	if (new_node == NULL)
	// 		return (free_kv(new_content), error_exit(MALLOC, data));
	// 	list_add_back(&data->env, new_node);
	// }
	// else /*incrementer shlvl*/
	// {
	// 	get_from_env("SHLVL", data)
	// 	new_content = get_new_content("SHLVL=");
	// 	if (new_content == NULL)
	// 		return (error_exit(MALLOC, data));
	// 	free(new_content->value);
	// 	new_content->value = ft_itoa(ft_atoi(get_from_env("SHLVL", data)) + 1);
	// 	if (new_content->value == NULL)
	// 		return (free_kv(new_content), error_exit(MALLOC, data));
	// 	new_node = list_new(new_content);
	// 	if (new_node == NULL)
	// 		return (free_kv(new_content), error_exit(MALLOC, data));
	// 	list_add_back(&data->env, new_node);
	// }
}

void	init_env(t_data *data, char **envp)
{
	int		i;
	t_kv	*new_content;
	t_list	*new_node;

	if (envp == NULL || envp[0] == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		new_content = get_new_content(envp[i]);
		if (new_content == NULL)
			return (error_exit(MALLOC, data));
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (free_kv(new_content), error_exit(MALLOC, data));
		list_add_back(&data->env, new_node);
		i++;
	}
	check_SHLVL(data);
}


// char	**env_double_array(t_list *envp, t_data *data)
// {
// 	char	**env;
// 	char	*tmp;
// 	t_list	*current;
// 	int		i;

// 	i = 0;
// 	current = envp;
// 	env = ft_calloc(list_size(envp) + 1, sizeof(char *));
// 	if (env == NULL)
// 		error_exit(MALLOC, data);
// 	env[list_size(envp)] = NULL;
// 	while (current)
// 	{
// 		tmp = ft_strjoin(((t_envp *)current->content)->key, "=");
// 		env[i] = ft_strjoin(tmp, ((t_envp *)current->content)->value);
// 		free(tmp);
// 		current = current->next;
// 		i++;
// 	}
// 	return (env);
// }

// void	env_(t_data *data, t_list **envp, int in_parent)
// {
// 	t_list	*current;
// 	char	*buff;
// 	char	*join;

// 	current = *envp;
// 	while (current)
// 	{
// 		if (((t_envp *)current->content)->value == NULL
// 			|| ft_strcmp(((t_envp *)current->content)->value, "") == 0)
// 		{
// 			current = current->next;
// 			continue ;
// 		}
// 		buff = ft_strjoin(((t_envp *)current->content)->key, "=");
// 		if (buff == NULL)
// 			return (error_exit(MALLOC, NULL));
// 		join = ft_strjoin(buff, ((t_envp *)current->content)->value);
// 		if (join == NULL)
// 			return (error_exit(MALLOC, NULL));
// 		free(buff);
// 		printf("%s\n", join);
// 		free(join);
// 		current = current->next;
// 	}
// 	if (!in_parent)
// 		return (free_all(data), exit(0));
// }

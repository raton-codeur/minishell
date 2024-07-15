/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:29:34 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/15 17:41:17 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_update_buffer_2(char **buffer)
{
	int	i;
	int	i_start;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\0' || (*buffer)[i + 1] == '\0')
	{
		free(*buffer);
		*buffer = NULL;
		return ;
	}
	i++;
	i_start = i;
	while ((*buffer)[i])
	{
		(*buffer)[i - i_start] = (*buffer)[i];
		i++;
	}
	(*buffer)[i - i_start] = '\0';
}

static char	*ft_get_line(char *buffer)
{
	char	*result;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	result = ft_calloc(i + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		result[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		result[i++] = '\n';
	result[i] = '\0';
	return (result);
}

static int	ft_init(char **buffer, char **to_add_to_buffer)
{
	if (*buffer == NULL)
		*buffer = ft_calloc(1, sizeof(char));
	*to_add_to_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (*buffer == NULL || *to_add_to_buffer == NULL)
		return (1);
	return (0);
}

static int	ft_update_buffer(char **buffer, int fd)
{
	char	*to_add_to_buffer;
	char	*new_buffer;
	int		n_read;

	if (ft_init(buffer, &to_add_to_buffer))
		return (1);
	n_read = 1;
	while (n_read > 0 && !ft_strchr(*buffer, '\n'))
	{
		n_read = read(fd, to_add_to_buffer, BUFFER_SIZE);
		if (n_read != -1)
		{
			to_add_to_buffer[n_read] = '\0';
			new_buffer = ft_strjoin(*buffer, to_add_to_buffer);
			if (new_buffer == NULL)
				return (free(to_add_to_buffer), 1);
			free(*buffer);
			*buffer = new_buffer;
		}
	}
	free(to_add_to_buffer);
	if (n_read == -1 || (n_read == 0 && ft_strlen(*buffer) == 0))
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_update_buffer(&buffer[fd], fd))
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	result = ft_get_line(buffer[fd]);
	ft_update_buffer_2(&buffer[fd]);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:26:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/01 18:02:59 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (code == MALLOC)
		ft_putendl_fd("memory allocation error", 2);
	else if (code == READLINE)
		ft_putendl_fd("readline failed", 2);
	else if (code == LEXING)
		ft_putendl_fd("lexical error", 2);
	else if (code == QUOTE)
		ft_putendl_fd("invalid quotes", 2);
	else if (code == PIPE)
		ft_putendl_fd("pipe failed", 2);
	else if (code == FORK)
		ft_putendl_fd("fork failed", 2);
	else if (code == ENV)
		ft_putendl_fd("cannot retriev env", 2);
}

void	error(int code, t_data *data)
{
	print_error(code);
	reset_input(data);
}

void	error_exit(int code, t_data *data)
{
	print_error(code);
	free_all(data);
	exit(1);
}

void	syntax_error(char *token, t_data *data)
{
	char	*message;
	char	*message_join;

	message = ft_strjoin("syntax error near unexpected token `", token);
	if (!message)
		error_exit(MALLOC, data);
	message_join = ft_strjoin(message, "'");
	free(message);
	if (!message_join)
		error_exit(MALLOC, data);
	ft_putendl_fd(message_join, 2);
	free(message_join);
	reset_input(data);
	data->exit_status = 2;
}

void	fd_error(char *file, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	free_all(data);
	exit(1);
}

void	cmd_pathname_error(char *cmd, t_data *data)
{
	char	*message;

	message = ft_strjoin(cmd, ": command not found");
	if (!message)
		error_exit(MALLOC, data);
	ft_putendl_fd(message, 2);
	free(message);
	free_all(data);
	exit(127);
}


/*
En bash, les codes de sortie (exit status) sont des entiers de 0 à 255, où 0 signifie généralement que la commande s'est exécutée avec succès et tout autre code indique une erreur ou un état particulier. Cependant, certaines conventions et standards existent pour les codes de sortie, laissant certains codes plus ou moins inutilisés ou réservés pour des cas spécifiques. Voici un aperçu :

    Code de sortie 0 : Indique que la commande s'est exécutée avec succès.
    Codes de sortie 1-2 : Souvent utilisés pour des erreurs générales.
    Codes de sortie 126 : Commande trouvée mais impossible à exécuter.
    Codes de sortie 127 : Commande non trouvée.
    Codes de sortie 128+n : La commande a été interrompue par le signal n (par exemple, 128+9 = 137 indique que la commande a été tuée par SIGKILL).
    Code de sortie 130 : La commande a été interrompue par Ctrl+C.
    Codes de sortie 255 : Souvent utilisé pour indiquer une erreur de sortie arbitraire.

Entre ces codes, certains sont moins communément utilisés et peuvent être considérés comme "inutilisés" dans des scripts bash ordinaires :

    Codes de sortie entre 3 et 125 : Bien qu'ils puissent être utilisés, ils ne sont pas spécifiquement réservés par bash ou POSIX et donc peuvent être choisis librement pour des erreurs spécifiques dans vos scripts.
    Codes de sortie au-delà de 255 : Techniquement, bash ne gère que les codes de sortie jusqu'à 255. Les codes au-delà seront modulés par 256 (par exemple, 256 deviendrait 0, 257 deviendrait 1, etc.).

En pratique, pour la gestion de scripts bash, il est généralement préférable d'utiliser des codes de sortie standardisés ou documentés clairement pour faciliter le débogage et la maintenance.
*/
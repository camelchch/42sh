/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_actions_each_bloc_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:30:02 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/29 17:23:47 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "twenty_one.h"

int		put2_str_fd_return(char *str1, char *str2, int fd, int return_value)
{
	put2_str_fd(str1, str2, fd);
	return (return_value);
}

void	put2_str_fd(char *str1, char *str2, int fd)
{
	if (str1 && str2)
	{
		write(fd, str1, ft_strlen(str1));
		write(fd, str2, ft_strlen(str2));
	}
}

int		valide_program(char **str, t_sh *table)
{
	char	*path;

	if (!str || !*str)
		return (0);
	if (is_buildin(*str))
		return (1);
	if (ft_strstr(*str, "/") && !access(*str, F_OK))
	{
		if (access(*str, X_OK))
			return (put2_str_fd_return(*str, " :permission denied.\n", 2, 0));
		return (1);
	}
	path = path_in_sh(*str, table);
	if (!path)
		return (put2_str_fd_return(*str, " :no such program.\n", 2, 0));
	if (access(path, X_OK))
		return (put2_str_fd_return(*str, " :permission denied.\n", 2, 0));
	return (1);
}

int		first_buildin_no_pipe(int nb_pipe, t_word *list)
{
	if (nb_pipe)
		return (0);
	while (list && !is_logic(list->type) && list->type != SEMI_DOT && \
			list->type != PIPE)
	{
		if (list->type == BUIDIN)
			return (1);
		list = list->next;
	}
	return (0);
}

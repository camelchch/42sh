/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:20:31 by saxiao            #+#    #+#             */
/*   Updated: 2018/07/01 14:42:59 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "twenty_one.h"

int			nb_str(char **paras)
{
	int		ct;

	ct = 0;
	while (*paras++)
		ct++;
	return (ct);
}

static char	**add_env(char ***env, char **paras)
{
	char	**cp;
	int		ct;
	int		i;
	char	*temp;
	char	**for_free;

	i = -1;
	ct = nb_str(*env) + 2;
	cp = *env;
	for_free = *env;
	*env = malloc(sizeof(char *) * ct);
	while (++i < ct - 2)
		(*env)[i] = ft_strdup(cp[i]);
	(*env)[i] = ft_strjoin(*paras, "=");
	paras++;
	temp = (*env)[i];
	(*env)[i] = ft_strjoin((*env)[i], *paras);
	free(temp);
	(*env)[++i] = NULL;
	ft_freestrstr(for_free);
	return (*env);
}

static char	**delet_env(char **env, int index)
{
	int		after;
	char	**temp;

	temp = env;
	free(temp[index]);
	while (index < nb_str(env) - 1)
	{
		after = index + 1;
		temp[index++] = temp[after];
	}
	temp[nb_str(env) - 1] = NULL;
	return (temp);
}

char		**set_env(char **paras, char ***env)
{
	char	**cp;
	char	*temp;

	cp = *env;
	paras++;
	if (!*paras || !*(paras + 1))
		return (*env);
	while (*cp && *paras && !(!ft_strncmp(*paras, *cp, ft_strlen(*paras)) &&\
				ft_strlen(*paras) < ft_strlen(*cp) && \
				(*cp)[ft_strlen(*paras)] == '='))
		cp++;
	if (*cp)
	{
		free(*cp);
		*cp = ft_strjoin(*paras++, "=");
		temp = *cp;
		*cp = ft_strjoin(*cp, *paras);
		free(temp);
	}
	else
		return (add_env(env, paras));
	return (*env);
}

char		**unset_env(char **paras, char **env)
{
	char	**cp;
	int		index;

	cp = env;
	index = 0;
	paras++;
	if (!*paras)
		return (env);
	while (*cp && !(!ft_strncmp(*paras, *cp, ft_strlen(*paras)) && \
				ft_strlen(*paras) < ft_strlen(*cp) && \
				(*cp)[ft_strlen(*paras)] == '='))
	{
		cp++;
		index++;
	}
	if (*cp)
		env = delet_env(env, index);
	else
		put2_str_fd(*paras, " :no such variable \n", 2);
	return (env);
}

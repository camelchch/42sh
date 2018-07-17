/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:39:10 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/29 15:44:56 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "twenty_one.h"

t_table			*malloc_add_sh(void)
{
	t_table		*add;

	add = (t_table *)malloc(sizeof(t_table));
	ft_bzero(add->name, NAME_MAX + 1);
	ft_bzero(add->path, PATH_MAX + 1);
	add->next = NULL;
	return (add);
}

int				replace_home(char *word, char **env)
{
	char	temp[MAX_BUF];
	char	*vari_value;

	ft_bzero(temp, MAX_BUF);
	if (*word && *word == '~')
	{
		vari_value = ft_getenv(env, "HOME");
		if (!vari_value)
			return (return_message("Undefined HOME variable\n", 1, 2));
		ft_strcpy(temp, word + 1);
		ft_bzero(word, MAX_BUF);
		ft_strcpy(word, vari_value);
		ft_strcat(word, temp);
		return (0);
	}
	return (0);
}

void			case_dquote_squote(t_helper *help, char *cp, char *word)
{
	if (cp[help->i] == '"')
		case_dquote(help, cp, word);
	else if (cp[help->i] == '\'')
		case_squote(help, cp, word);
}

void			put_strstr(char **str)
{
	while (*str)
		ft_printf("%s\n", *str++);
}

unsigned long	get_key(void)
{
	unsigned char	buff[6];

	ft_bzero(buff, 6);
	read(0, buff, 6);
	return (buff[0] + (buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24) + \
			((unsigned long)buff[4] << 32) + ((unsigned long)buff[5] << 40));
}

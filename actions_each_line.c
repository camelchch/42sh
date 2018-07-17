/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_each_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 22:55:00 by saxiao            #+#    #+#             */
/*   Updated: 2018/07/17 14:34:33 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

int			dslash_before(char *line, int index)
{
	int		i;
	int		j;

	i = 0;
	j = index - 1;
	while (j >= 0 && line[j] == '\\')
	{
		i++;
		j--;
	}
	if (!(i % 2))
		return (1);
	return (0);
}
/*
void		print_list_word(t_word *list)
{
	while (list)
	{
		ft_printf("%s ", list->word);
		list = list->next;
	}
}

static void	actions_blocs(t_word *list, char ***env, t_sh *table)
{
	t_word	*cp;

	cp = list;
	while (cp && !g_clc)
	{
		while (cp && !is_logic(cp->type) && cp->type != SEMI_DOT && !g_clc)
		{
			if (!remove_quoting_bloc(cp, *env))
				actions_each_bloc(cp, env, table);
			while (cp && !is_logic(cp->type) && cp->type != SEMI_DOT)
				cp = cp->next;
			if (cp && cp->type != SEMI_DOT)
				cp = cp->next;
		}
		if (cp)
			cp = cp->next;
	}
}

void		actions_each_line(char ***env, t_word *list, t_sh *table)
{
	if (!g_clc && !err_in_words(list))
		actions_blocs(list, env, table);
}
*/

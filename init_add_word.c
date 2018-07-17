/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_add_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 15:39:38 by saxiao            #+#    #+#             */
/*   Updated: 2018/07/01 15:33:49 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "twenty_one.h"

t_word		*malloc_add(void)
{
	t_word		*add;

	add = malloc(sizeof(t_word));
	add->next = NULL;
	add->pre = NULL;
	ft_bzero(add->word, MAX_BUF);
	return (add);
}

static void	init_vari_for_add_word(t_word **add, int *only_nb, int *j)
{
	g_open_dquote = -1;
	g_open_squote = -1;
	*add = NULL;
	*only_nb = 1;
	*j = 0;
}

static void	for_add_word(int only_nb, char *line, int *i, t_word *add)
{
	if (only_nb && (line[*i] == '<' || line[*i] == '>'))
		add->type = FD;
	else
		add->type = PROGRAM;
}

static void	change(char *line, int *i, int *only_nb)
{
	if (line[*i] < '0' || line[*i] > '9')
		*only_nb = 0;
	if (line[*i] == '"' && dslash_before(line, *i) && g_open_squote < 0)
		g_open_dquote = -g_open_dquote;
	if (line[*i] == '\'' && dslash_before(line, *i) && g_open_dquote < 0)
		g_open_squote = -g_open_squote;
}

t_word		*init_add_word(char *line, int *i, int *j)
{
	t_word	*add;
	int		only_nb;

	init_vari_for_add_word(&add, &only_nb, j);
	if (g_open_dquote < 0 && g_open_squote < 0 && *i < (int)ft_strlen(line) &&\
			is_seprator_w(line, *i))
		return (init_seprator(line, i));
	else
	{
		add = malloc_add();
		while ((g_open_dquote > 0 || g_open_squote > 0 ||\
					!is_seprator_w(line, *i)) && *i < (int)ft_strlen(line))
		{
			change(line, i, &only_nb);
			add->word[*j] = line[*i];
			*j = *j + 1;
			*i = *i + 1;
		}
		for_add_word(only_nb, line, i, add);
	}
	return (add);
}

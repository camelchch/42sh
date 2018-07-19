/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:43:37 by saxiao            #+#    #+#             */
/*   Updated: 2018/07/19 13:37:46 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

static	void	init_win(t_dir *list, int win_col, t_win *win)
{
	t_dir	*cp;

	cp = list;
	win->ct_lt = 0;
	win->max = 0;
	while (cp)
	{
		if (cp->na_len > win->max)
			win->max = cp->na_len;
		cp = cp->next;
	}
	win->max++;
	cp = list;
	while (cp)
	{
		(win->ct_lt)++;
		cp = cp->next;
	}
	win->col = win_col / win->max;
	if (!win->col)
		win_col = 1;
	win->line = win->ct_lt / win->col;
	if (win->ct_lt % win->col > 0)
		win->line++;
}

static	void	put_colum(t_dir *list, int win_col)
{
	t_dir	*cp;
	t_dir	*lt;
	t_ct	ct;
	t_win	w;

	ct.j = -1;
	init_win(list, win_col, &w);
	lt = list;
	while (++(ct.j) < w.line)
	{
		cp = lt;
		ct.i = -1;
		while (++(ct.i) < w.col && cp)
		{
			ct.ct = 0;
			if (cp)
				put_dirname(cp, w.max);
			while (cp && (ct.ct)++ < w.line)
				cp = cp->next;
		}
		ft_printf("\n");
		lt = lt->next;
	}
}

static	void	put_size_mm(t_dir *list, t_max max, t_index *index)
{
	ft_printf("%c%s", list->type, list->permi);
	if (index->hv_acl)
	{
		ft_printf("%c", list->long_f.aclatr);
		max.m_link--;
	}
	ft_printf("%*d", max.m_link, (list->buf).st_nlink);
	if (!ft_strchr(index->flags, 'g'))
		ft_printf("%*s", max.m_owner, (list->long_f).owner);
	ft_printf("%*s", max.m_group, list->long_f.group);
	if (list->type != 'c' && list->type != 'b')
		ft_printf("%*d", max.m_size, (list->buf).st_size);
	else
		ft_printf("%*d,%*d", max.m_maj, list->long_f.major, \
				max.m_min, list->long_f.minor);
	index->tm = list->long_f.change_tm + 3;
	if (!list->long_f.sixm)
		ft_printf("%.13s ", index->tm);
	else
	{
		ft_printf("%.7s ", index->tm);
		index->tm = list->long_f.change_tm + 20;
		ft_printf(" %.4s ", index->tm);
	}
}

static	void	put_lformat(t_dir *list, t_index *index)
{
	t_max	max;
	char	link[256];

	if (list)
	{
		init_lformat(list, &max, index->flags);
		index->hv_acl = inclu_acl(list);
		if (index->k)
			ft_printf("Total %d\n", max.total);
		index->k = 1;
	}
	while (list)
	{
		put_size_mm(list, max, index);
		put_dirname(list, ft_strlen(list->name));
		if (list->type == 'l')
		{
			ft_bzero(link, 256);
			index->ct = readlink(list->path, link, 256);
			link[index->ct] = '\0';
			ft_printf("-> %s", link);
		}
		ft_printf("\n");
		list = list->next;
	}
}

void			put_list(t_dir *list, t_index *index, int winsize)
{
	if (list)
	{
		if (ft_strchr(index->flags, 'l') || ft_strchr(index->flags, 'g'))
			put_lformat(list, index);
		else if (ft_strchr(index->flags, '1'))
			put_oneflag(list);
		else
			put_colum(list, winsize);
	}
}

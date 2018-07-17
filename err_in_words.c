/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_in_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:25:32 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/29 17:09:58 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one.h"

int					program_exit_before(t_word *li)
{
	while (li && li->type != PROGRAM && li->type != AND && \
			li->type != OR && li->type != PIPE && li->type != SEMI_DOT)
		li = li->pre;
	if (li && li->type == PROGRAM)
		return (1);
	return (0);
}

static int			program_exit_after(t_word *li)
{
	while (li && li->type != PROGRAM && li->type != AND && li->type != OR\
			&& li->type != PIPE && li->type != SEMI_DOT)
		li = li->next;
	if (li && li->type == PROGRAM)
		return (1);
	return (0);
}

static int			test_for_err_func(t_word *cp)
{
	if (cp->type == LESS || cp->type == GREAT || cp->type == GREATAND \
			|| cp->type == DGREAT)
	{
		if (!cp->next || (cp->next->type != FILES && cp->next->type != FD))
			return (1);
	}
	return (0);
}

int					err_in_words(t_word *cp)
{
	while (cp)
	{
		if (test_for_err_func(cp))
			return (return_message("\nMissing name for redirect.\n", 1, 2));
		if (cp->type == DLESS)
		{
			if (!cp->next || cp->next->type != HERE_DOC_MARK)
				return (return_message("\nMissing name for redirect.\n", 1, 2));
		}
		if (cp->type == LESSAND && (!cp->next || cp->next->type != FD))
			return (return_message("\nMissing file descriptor.\n", 1, 2));
		if (is_logic(cp->type) &&\
				(!program_exit_before(cp->pre) ||\
				!program_exit_after(cp->next)))
			return (return_message("\nInvalide null cmmand.\n", 1, 2));
		cp = cp->next;
	}
	return (0);
}

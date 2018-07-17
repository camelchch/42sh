/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_actions_each_bloc_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:28:56 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/30 01:50:32 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "twenty_one.h"

void		init_int_table(int *table, int len)
{
	int		i;

	i = -1;
	while (++i < len)
		table[i] = -1;
}

void		do_all_pipe(int *pipe_fd, int nb_pipe)
{
	int		i;

	i = 0;
	while (++i <= nb_pipe)
	{
		if (pipe(pipe_fd) < 0)
			ft_putendl_fd("pipe failed in  do all pipe", 2);
		pipe_fd = pipe_fd + 2;
	}
}

static int	redirection_for_here(t_word *list)
{
	int		res;

	res = 0;
	while (list && !is_logic(list->type) && \
			list->type != SEMI_DOT && list->type != PIPE)
	{
		if (list->type == GREAT)
			res = redi_great(list);
		else if (list->type == DGREAT)
			res = redi_dgreat(list);
		else if (list->type == GREATAND)
			res = redi_greatand(list);
		else if (list->type == GREATANDMINUS)
			res = redi_greatandminus(list);
		else if (list->type == LESSAND)
			res = redi_lessand(list);
		else if (list->type == LESSANDMINUS)
			res = redi_lessandminus(list);
		if (res < 0)
			return (-1);
		list = list->next;
	}
	return (0);
}

int			pro_is_buildin_no_pipe(t_word *list, char ***env, t_sh *table)
{
	char		**pro_args;
	t_save_fd	*recover;

	recover = NULL;
	pro_args = NULL;
	recover = fd_restorage(list, recover);
	pro_args = my_here_doc_word_init_pro_args(list);
	if (pro_args)
	{
		redirection_for_here(list);
		do_build(pro_args, env, table);
		recover_fd(recover);
		free_saver_fd(recover);
		free(pro_args);
	}
	return (0);
}

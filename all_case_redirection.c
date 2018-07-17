/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_case_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:07:16 by saxiao            #+#    #+#             */
/*   Updated: 2018/07/01 14:15:49 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "twenty_one.h"

int		redi_great(t_word *l)
{
	int		fd;
	int		tofd;

	if (l->pre && l->pre->type == FD)
		fd = ft_atoi(l->pre->word);
	else
		fd = 1;
	tofd = open(l->next->word, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	if (tofd != -1)
	{
		if (dup2(tofd, fd) < 0)
			return (return_message("dup2 failed\n", -1, 2));
		if (close(tofd) < 0)
			return (return_message("close file failed\n", -1, 2));
		return (0);
	}
	else
		return (err_open_file(l));
}

int		redi_dgreat(t_word *l)
{
	int		fd;
	int		tofd;

	if (l->pre && l->pre->type == FD)
		fd = ft_atoi(l->pre->word);
	else
		fd = 1;
	tofd = open(l->next->word, O_CREAT | O_APPEND | O_RDWR, S_IWUSR | S_IRUSR);
	if (tofd != -1)
	{
		if (dup2(tofd, fd) < 0)
			return (return_message("dup2 failed\n", -1, 2));
		if (close(tofd) < 0)
			return (return_message("close file failed\n", -1, 2));
		return (0);
	}
	else
		return (err_open_file(l));
}

int		redi_greatand(t_word *l)
{
	int		fd;
	int		t;

	fd = 1;
	if (l->pre && l->pre->type == FD)
		fd = ft_atoi(l->pre->word);
	if (l->next->type == FD)
		t = ft_atoi(l->next->word);
	else
		t = open(l->next->word, O_CREAT | O_APPEND | O_RDWR, S_IWUSR | S_IRUSR);
	if (t != -1)
	{
		if (dup2(t, fd) < 0)
			return (return_message("dup2 failed\n", -1, 2));
		if (close(t) < 0)
			return (return_message("close file failed\n", -1, 2));
		return (0);
	}
	else
	{
		if (l->next->type == FD)
			return (return_message("bad descriptor\n", -1, 2));
		else
			return (err_open_file(l));
	}
}

int		redi_greatandminus(t_word *list)
{
	int		fd;

	if (list->pre && list->pre->type == FD)
		fd = ft_atoi(list->pre->word);
	else
		fd = 1;
	if (close(fd) < 0)
		return (return_message("bad descriptor close failed\n", -1, 2));
	return (0);
}

int		all_case_redirection(t_word *list)
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
		else if (list->type == LESS)
			res = redi_less(list);
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

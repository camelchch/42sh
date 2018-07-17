/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bse_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 23:36:22 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/30 01:48:13 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "twenty_one.h"

static void	for_here_doc(int *temp_fd, t_line *doc_line)
{
	doc_line->here_end = 0;
	ft_bzero(doc_line->here_mark, MAX_BUF);
	*temp_fd = open(g_temp_file, O_CREAT | O_TRUNC | O_RDWR | O_APPEND,\
			S_IWUSR | S_IRUSR);
	if (temp_fd < 0)
		ft_putendl_fd("temp file failed to be opened", 2);
}

static int	write2_temp_file(char *word)
{
	int		i;
	int		temp_fd;
	t_line	doc;

	for_here_doc(&temp_fd, &doc);
	i = 1;
	while (g_inside_doc_quote)
	{
		ft_bzero(doc.here, MAX_BUF);
		i == 0 ? ft_printf("\n") : (i = 0);
		get_line("heredoc> ", (char *)doc.here, &doc);
		if (ft_strcmp(word, (char *)doc.here) && !g_clc && !g_dld)
		{
			if (write(temp_fd, doc.here, ft_strlen((char *)doc.here)) < 0)
				ft_putendl_fd("write into temp file failed", 2);
			write(temp_fd, "\n", 1);
		}
		else
			g_inside_doc_quote = 0;
	}
	if (g_with_termcap)
		ft_printf("\n");
	close(temp_fd);
	return (0);
}

char		**my_here_doc_word_init_pro_args(t_word *list)
{
	t_word		*cp;

	cp = list;
	while (list && !is_logic(list->type) && list->type != SEMI_DOT && \
			list->type != PIPE)
	{
		if (list->type == DLESS)
		{
			g_inside_doc_quote = 1;
			write2_temp_file(list->next->word);
			if (g_clc)
				return (NULL);
			list->type = LESS;
			list->next->type = FILES;
			ft_bzero(list->word, MAX_BUF);
			ft_strcpy(list->word, "<");
			ft_bzero(list->next->word, MAX_BUF);
			ft_strcpy(list->next->word, g_temp_file);
		}
		list = list->next;
	}
	return (args_each_exev(cp));
}

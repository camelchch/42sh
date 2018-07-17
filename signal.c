/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:25:25 by saxiao            #+#    #+#             */
/*   Updated: 2018/07/01 14:13:54 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "twenty_one.h"

void	signal_inh(int sign)
{
	if (sign == SIGINT)
	{
		if (!g_with_termcap)
		{
			g_clc = 1;
			ft_printf("\n$> ");
		}
		else
		{
			init_attr(SETOLD);
			ft_printf("\n");
			ft_bzero(g_new_line, MAX_BUF);
			init_line("$> ", &g_line);
			init_attr(SETNEW);
			g_clc = 1;
		}
	}
	if (sign == SIGQUIT && !g_with_termcap)
		exit(0);
}

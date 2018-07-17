#include <stdio.h>
#include "twenty_one.h"

static void	init_auto_start(int *i, int *find_start, int *res)
{
	*i = 0;
	*find_start = 0;
	*res = 0;
	g_open_dquote = -1;
	g_open_squote = -1;
}

int		auto_start(char *line)
{
	int		i;
	int		find_start;
	int		res;

	init_auto_start(&i, &find_start, &res);
	while (!find_start)
	{
		res = i;
		while (line[i] && !(g_open_squote < 0 && g_open_dquote < 0 && (line[i] == ' ' || line[i] == '\t')))
		{
			if (line[i] == '"' && dslash_before(line, i) && g_open_squote < 0)
				g_open_dquote = -g_open_dquote;
			if (line[i] == '\'' && dslash_before(line, i) && g_open_dquote < 0)
				g_open_squote = -g_open_squote;
			i++;
		}
		if (!line[i])
			find_start = 1;
		else
			i++;
	}
	return (res);
}

int		main()
{
	int i = auto_start("  'ls l ' l");
	printf(" i=%d\n", i);
	return (0);

}

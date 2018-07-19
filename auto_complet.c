#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
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

t_autolist	*add_one_list(t_autolist *list, t_autolist *add)
{
	t_autolist	*cp;

	cp = list;
	if (!cp)
		return (add);
	while (cp->next)
		cp = cp->next;
	cp->next = add;
	return (list);
}

t_autolist	*addlist_in_path(char *start, char **path, t_autolist *list)
{
	DIR				*dirp;
	struct dirent	*dir;
	t_autolist		*add;

	while (path && *path)
	{
		if ((dirp = opendir(*path)))
		{
			while ((dir = readdir(dirp)))
			{
				if (!ft_strncmp(start, dir->d_name, ft_strlen(start)))
				{
					add = malloc(sizeof(t_autolist));
					add->next = NULL;
					ft_bzero(add->name, MAX_BUF);
					ft_strcpy(add->name, dir->d_name);
					add->len = ft_strlen(add->name);
					list = add_one_list(list, add);
				}
			}
			closedir(dirp);
		}
		path++;
	}
	return (list);
}

char		*path_last_slash(char *start)
{
}
t_autolist	*addlist_no_path(char *start, t_autolist *list)
{
	DIR				*dirp;
	struct dirent	*dir;
	t_autolist		*add;

	if ((dirp = opendir(*path)))
	{
		while ((dir = readdir(dirp)))
		{
			if (!ft_strncmp(start, dir->d_name, ft_strlen(start)))
			{
				add = malloc(sizeof(t_autolist));
				add->next = NULL;
				ft_bzero(add->name, MAX_BUF);
				ft_strcpy(add->name, dir->d_name);
				add->len = ft_strlen(add->name);
				list = add_one_list(list, add);
			}
		}
		closedir(dirp);
	}
	return (list);
}

t_autolist	*get_autolist(char *start, char **env)
{
	t_autolist	*list;
	char		**all_path;

	list = NULL;
	all_path = path(env);
	if (!ft_strchr(start, '/'))
		list = addlist_in_path(start, all_path, list);
}

int		main()
{
	int i = auto_start("  'ls l ' l");
	printf(" i=%d\n", i);
	return (0);

}

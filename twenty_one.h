/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 00:15:00 by saxiao            #+#    #+#             */
/*   Updated: 2018/07/19 16:50:00 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_H
# define TWENTY_ONE_H
# include <limits.h>
# include <sys/types.h>
# include "libft/libft.h"

int		g_open_dquote;
int		g_open_squote;
int		g_open_backslash;
int		g_end_line;
int		g_with_termcap;
int		g_inside_doc_quote;
int		g_clc;
int		g_dld;

# define MAX_BUF 10000
# define SETNEW 1
# define SETOLD 0
# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define NB_KEY 21
# define ARROW_LEFT 4479771
# define ARROW_RIGHT 4414235
# define ARROW_UP 4283163
# define ARROW_DOWN 4348699
# define MY_DELECT 127
# define MY_HOME 4741915
# define MY_END 4610843
# define CT_SHIFT_LEFT 74999712013083
# define CONTRL_L 12
# define CONTRL_H 8
# define CONTRL_A 1
# define CONTRL_B 2
# define CONTRL_E 5
# define CONTRL_P 16
# define ALT_M 46530
# define CONTRL_PERCENT 29
# define ALT_S 40899
# define ALT_UP 1096489755
# define ALT_DOWN 1113266971
# define OPTION_SHIFT_U 43202
# define OPTION_SHIFT_D 36547
# define CONTRL_N 14
# define SHIFT_UP 71683997260571
# define SHIFT_DOWN 71683997260571
# define CONTRL_F 6
# define CONTRL_D 4
# define CONTRL_C 3
# define TAB_KEY 9
# define RETURN_KEY 10
# define DELETE_AT_POSITION 2117294875
# define BGYELLOW "\033[7;33m"
# define RESET "\033[0m"

typedef struct	s_table
{
	char			name[NAME_MAX + 1];
	char			path[PATH_MAX + 1];
	struct s_table	*next;
}				t_table;

typedef struct	s_shtable
{
	t_table		*sh_ta;
}				t_sh;

typedef struct	s_vari
{
	int		in;
	int		num_pipe;
	int		pipe_fd[2];
	int		ct;
	pid_t	pid;
}				t_vari;

typedef enum	e_type{
	PROGRAM,
	ARG,
	LESS,
	LESSAND,
	LESSANDMINUS,
	DLESS,
	AND,
	GREAT,
	GREATAND,
	GREATANDMINUS,
	DGREAT,
	OR,
	PIPE,
	SEMI_DOT,
	FILES,
	FD,
	HERE_DOC_MARK,
	BUIDIN,
}				t_type;

typedef struct	s_word{
	char			word[MAX_BUF];
	t_type			type;
	struct s_word	*next;
	struct s_word	*pre;
}				t_word;

typedef struct	s_save_fd{
	int					fd_2be_saved;
	int					fd_saved_in2;
	struct s_save_fd	*next;
}				t_save_fd;

typedef struct	s_history
{
	char				his[MAX_BUF];
	struct s_history	*next;
	struct s_history	*pre;
}				t_history;

t_history	*g_history;

typedef struct	s_autolist
{
	int					len;
	int					is_dic;
	int					ct;
	char				name[MAX_BUF];
	struct s_autolist	*next;
	struct s_autolist	*pre;
}				t_autolist;

typedef struct	s_win
{
	int		max;
	int		line;
	int		col;
	int		ct_lt;
}				t_win;

typedef struct	s_line
{
	int				pos;
	unsigned char	buf[MAX_BUF];
	unsigned char	cp[MAX_BUF];
	unsigned char	here_mark[MAX_BUF];
	unsigned char	here[MAX_BUF];
	unsigned char	ici_doc[MAX_BUF];
	int				buf_len;
	int				line_max;
	int				start_po;
	int				his_mostdown;
	int				his_mostup;
	int				up_indown;
	int				one_his;
	int				here_end;
	int				auto_ct;
	int				auto_is_dic;
	int				auto_current_dic;
	t_win			w;
	t_autolist		*auto_lt;
	t_history		*last_his;

	int				(*printable)(struct s_line *line, unsigned long a_key);
	int				(*move_left)(struct s_line *line);
	int				(*move_right)(struct s_line *line);
	int				(*delete_key)(struct s_line *line);
	int				(*move_nleft)(struct s_line *line);
	int				(*move_nright)(struct s_line *line);
	int				(*mv_left_word)(struct s_line *line);
	int				(*mv_right_word)(struct s_line *line);
	int				(*history_up)(struct s_line *line);
	int				(*history_down)(struct s_line *line);
	int				(*cp_all)(struct s_line *line);
	int				(*cp_begin)(struct s_line *line);
	int				(*cp_end)(struct s_line *line);
	int				(*cut_all)(struct s_line *line);
	int				(*cut_begin)(struct s_line *line);
	int				(*cut_end)(struct s_line *line);
	int				(*paste)(struct s_line *line);
	int				(*go_up)(struct s_line *line);
	int				(*go_down)(struct s_line *line);
	int				(*ctrl_d)(struct s_line *line);
	int				(*return_key)(struct s_line *line);
	int				(*delete_at_position)(struct s_line *line);
	int				(*my_tabkey)(struct s_line *line, char **env);
	int				(*engine)(struct s_line *line, unsigned long a_key, char **env);
}				t_line;
typedef struct	s_key
{
	unsigned long	a_key;
	int				(*func)(t_line *);
}				t_key;

char		g_new_line[MAX_BUF];
char		g_temp_file[MAX_BUF];
t_line		g_line;

char			*get_autoline(t_sh *table);
void			shell(int ac, char **av, char **env, t_sh *table);
void			each_cmdline(char *cmdline, char **env, t_sh *table);
void			pipes(char *cmdline, int nb_pipe, char ***env, t_sh *table);
int				no_pipe(char *cmdline);
int				init_attr(int mod);
int				my_putc(int c);
int				engine(t_line *line, unsigned long key, char **env);
int				move_left(t_line *line);
int				move_nleft(t_line *line);
int				mv_left_word(t_line *line);
int				mv_right_word(t_line *line);
int				move_right(t_line *line);
int				move_nright(t_line *line);
int				delete_key(t_line *line);
int				delete_all(t_line *line);
int				delete_at_position(t_line *line);
int				ctrl_d(t_line *line);
int				my_tabkey(t_line *line, char **env);
int				ctrl_c(char *new_line, t_line *line);
int				printable(t_line *line, unsigned long key);
void			put_a_key(t_line *line, unsigned long key);
int				history_up(t_line *line);
int				history_down(t_line *line);
int				cp_all(t_line *line);
int				cp_begin(t_line *line);
int				cp_end(t_line *line);
int				cut_all(t_line *line);
int				cut_begin(t_line *line);
int				cut_end(t_line *line);
int				paste(t_line *line);
int				go_up(t_line *line);
int				go_down(t_line *line);
int				return_key(t_line *line);
int				get_line(char *prompt, char *new_line, t_line *line, char **env);
void			init_line(char	*prompt, t_line *line);
int				prompt_open_quote(char *line, char **env);
int				prompt(char **env, t_sh *table);
char			*ft_getenv(char **env, char *name);
char			**path(char **env);
int				calcu_index(char *name);
void			init_shtable(t_sh *table, char **path);
void			update_shlvl(char ***env);
void			update_lastapp(char *lastcmd, char ***env);
int				nb_str(char **str);
char			**set_env(char **paras, char ***env);
char			**unset_env(char **paras, char **env);
int				is_buildin(char *app);
void			do_build(char **paras, char ***env, t_sh *table);
void			replace_home_cd(char *cp, char *home);
void			ft_exit(char ***env, t_sh *table);
int				cd(char **paras, char ***env);
int				put_env(char **env, char **paras, t_sh *table);

typedef struct	s_helper{
	int		i;
	int		j;
	int		k;
	int		index;
}				t_helper;

typedef struct	s_program {
	char	**pro_args;
}				t_program;

int				remove_quoting_word(char *word, char **env);
void			case_dquote(t_helper *help, char *cp, char *word);
void			case_squote(t_helper *help, char *cp, char *word);
void			change_part_str(char *ori, int start, int end, char *change);
void			dollor_sign(t_helper *help, char *cp, char *vari);
void			remove_quoting_list(t_word *list, char **env);
int				remove_quoting_bloc(t_word *list, char **env);
void			print_words_type(t_word *list);
int				err_in_words(t_word *list);
int				program_exit_before(t_word *li);
int				is_seprator_w(char *line, int index);
int				is_redirector(t_type type);
int				is_logic(t_type type);
t_word			*command_to_words(char *line);
t_word			*init_add_word(char *line, int *i, int *j);
t_word			*malloc_add(void);
t_word			*init_seprator(char *line, int *index);
t_word			*pipe_or_type(char *line, int *index);
t_word			*and_type(char *line, int *index);
t_word			*semidot_type(char *line, int *index);
int				return_message(char *message, int re_value, int fd);
void			my_here_doc(char *line);
int				inclu_heredoc(char *new_line);
char			**my_here_doc_word_init_pro_args(t_word *list, char **env);
int				all_case_redirection(t_word *list);
int				redi_great(t_word *list);
int				redi_dgreat(t_word *list);
int				redi_greatand(t_word *list);
int				redi_greatandminus(t_word *list);
int				redi_less(t_word *list);
int				redi_lessand(t_word *list);
int				redi_lessandminus(t_word *list);
int				err_open_file(t_word *list);
void			child_pro_bin(char **paras, char **env, t_sh *table);
void			do_child_pro(char **paras, char **env, t_sh *table);
char			*path_in_sh(char *app, t_sh *table);
int				dslash_before(char *line, int index);
void			print_list_word(t_word *list);
void			actions_each_line(char ***env, t_word *list, t_sh *table);
int				actions_each_bloc(t_word *list, char ***env, t_sh *table);
int				nb_pipe_eachbloc(t_word *list);
char			**args_each_exev(t_word *list);
int				close_all_pipe(int *pipe_fd, int nb_pipe, int nb_pro);
int				do_all_redirection(t_word *l, int *pp_fd, int nbpp, int nbpro);
void			init_int_table(int *table, int len);
void			do_all_pipe(int *pipe_fd, int nb_pipe);
int				pro_is_buildin_no_pipe(t_word *list, char ***env, t_sh *table);
int				first_buildin_no_pipe(int nb_pipe, t_word *list);
int				valide_program(char **str, t_sh *table);
int				put2_str_fd_return(char *str1, char *str2, int fd, int res);
void			put2_str_fd(char *str1, char *str2, int fd);
t_save_fd		*fd_restorage(t_word *list, t_save_fd *recover);
void			recover_fd(t_save_fd *recover);
void			free_saver_fd(t_save_fd *recover);
void			signal_inh(int sign);
void			ft_freestrstr(char **cp_env);
void			free_sh_table(t_sh *table, int index);
void			free_pro_args(t_program *pro, int index);
void			free_word_list(t_word *list);
t_table			*malloc_add_sh(void);
int				replace_home(char *word, char **env);
void			case_dquote_squote(t_helper *help, char *cp, char *word);
void			put_strstr(char **str);
unsigned long	get_key(void);


//auto_complet.c
t_autolist		*add_one_list(t_autolist *list, t_autolist *add);
int				nb_list(t_autolist *list);
void			free_auto_lt(t_line *line);

//sort_list.c
void			del_one_list(t_autolist **list, t_autolist *del);
void			sort_list(t_autolist **list);

//line_auto_color.c
void			bg_yellow(void);
void			color_reset(void);
#endif

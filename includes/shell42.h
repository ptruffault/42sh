/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell42.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:02:36 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 16:47:28 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL42_H
# define SHELL42_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <term.h>
# include <limits.h>
# include "structures.h"
# include "libft.h"
# include "tenvv.h"
# include "ft_printf.h"


void 		ft_link_process_to_term(t_process *p, t_shell *sh);
t_jobs		*ft_search_jobs(t_jobs *j, char *s);
void 		ft_update_status(t_process *p, unsigned int status);
int			ft_tcsetpgrp(int fd, pid_t pgrp);
pid_t		ft_tcgetpgrp(int fd);
void		set_son_signal(void);
int			ft_init_groups(t_shell *sh);
int			ft_signal_check(t_process *p);
void 		ft_add_jobs(t_process *p, t_shell *sh);
void		ft_remove_jobs(int pid, t_shell *sh);
t_jobs 		*ft_free_tjobs(t_jobs *j);

int			ft_fc(t_shell *sh, char **argv);
int			flags_gestion(char *flags, char **av, int x);
int			search_in_hist_parser(t_fc *fc, short i);
t_hist		*search_by_number_from_first(t_hist *first, int nb);
t_hist		*search_by_number_from_last(t_hist *first, int nb);
t_hist		*search_by_occurence(t_hist *first, char *to_search);
void		ft_fc_option_l(t_fc *fc);
void		ft_fc_option_e(t_fc *fc, int pos);
void		ft_fc_option_s(t_fc *fc, int pos);

void		ft_deload_hist_in_file(t_shell *sh);

void 		ft_setup_localenv(t_process *p, t_shell *sh, t_tree *t);
void		ft_get_envv_back(t_shell *sh, t_process *p, t_tree *t);
int			ft_quit(int exit_code, t_shell *sh);
void		ft_kill(t_process *p, int sig);
void 		ft_killgrp(t_process *p, int sig);
void		ft_sigcont(t_process *tmp);
void 		ft_wait_background(t_shell *sh);
int			ft_wait(t_process *p, t_shell *sh);
int 		ft_bg(t_shell *sh, char **argv);
int 		ft_fg(t_shell *sh, char **argv);
int			ft_hi(t_shell *sh);
void 		ft_process_tab_status(char *stat[6]);
void		ft_put_process(t_process *p);
void		ft_exit_son(t_shell *sh, int exit_code);
char		ft_parse_back(char c);
void		ft_execve_pip(t_process *p, t_shell *sh, t_tree *t, int mode);
void		ft_delete_char(t_eval *e);
t_redirect	*parse_heredoc(t_redirect *ret, t_word *w);
int			init_env(t_shell *sh, char **argv, char **envv);
t_word		*ft_deltword(t_word *prev, t_word *src);
t_hist		*ft_free_thist(t_hist *h);
t_redirect	*ft_free_redirection(t_redirect *r);
t_word		*ft_free_tword(t_word *w);
t_process	*ft_free_tprocess(t_process *p);
void		ft_free_tshell(t_shell *sh);
void		ft_disp(t_shell *sh);
int			get_input(char	**line);
char		**ft_twordto_arr(t_word *w);
t_word		*ft_expention(t_word *w);
char		*ft_get_cutted_value(char *parenth, t_shell *sh, char *val, int *i);
char		*ft_exp_var(char *ret, t_shell *sh);
int			get_content_size(char *s);
char		*ft_exp_param(char *ret, t_shell *sh, int *i);
char		*ft_get_secondvalue(char *src);
t_tree		*get_tree(char *input);
t_tree		*ft_free_tree(t_tree *t);
int			ft_redirect(t_tree *t);
int			ft_redirect_builtin(t_tree *t, t_process *p, t_shell *sh);
int			get_destination_fd(t_redirect *r);
void		ft_reset_fd(t_shell *sh);
int			fd_dup(int fd1, int fd2, t_process *p, int close);
t_shell		*ft_get_set_shell(t_shell *sh);
int			init_shell(t_shell *sh, char **envv, char **argv);
void		set_signals(void);
void		set_signals_ni(void);
void		ft_execve(t_process *p, t_shell *sh);
t_process	*ft_exec_process(t_process *p, t_shell *sh, t_tree *t);
int 		ft_get_pgid(int pgid, t_process *p, t_process *prev);
t_tree		*exec_pipe(t_tree *t, t_process *p, t_shell *sh);
int			run_builtin(t_tree *t, char **argv, t_shell *sh);
t_tree		*exec_tree(t_tree *t, t_shell *sh);
int			exec_file(char *path, t_shell *sh);
int			exec_fd(t_shell *sh, int fd);
t_tree		*ft_get_set_tree(t_tree *new_t);
int			new_process(t_process *new, t_tree *t, t_shell *sh);
void		ft_add_process(t_shell *sh, t_process *new);
int			kill_process(t_process *p, int sig, unsigned int status);
char		*search_in_envv(char *input, t_envv *envv);
char		*absolute_path(char *input, t_envv *envv);
char		*get_bin_path(char *input, t_envv *envv);
int			ft_check_ascii(char *input);
int			ft_isparenth(char c);
int			ft_setup_edit_term(t_shell *sh);
int			ft_set_old_term(t_shell *sh, int error);
void		ft_update_windows(t_edit *e);
int			init_termcaps(t_shell *sh);
int			check_builtin(char *input);
t_envv		*ft_cd(char **input, t_envv *envv);
t_envv		*change_dir(char *path, t_envv *envv, unsigned int opts);
int			ft_echo(char **input);
void		ft_exit(char *nbr, t_shell *sh);
t_envv		*ft_export(t_shell *sh, char **argv);
void		ft_alias(t_shell *sh, char **argv);
int			ft_jobs(t_shell *sh, char **argv);
int			ft_type(t_word *w);
int			putword(t_word *w, int t);
int			putfile(t_word *w, t_envv *env, int t);
int			putcmd(t_word *w, t_envv *env, int t);
int			putbuiltin(t_word *w, int t);
int			putalias(t_word *w, t_envv *alias, int t);
t_hist		*init_hist(char *hist);
int			ft_hist_len(t_hist *hist);
t_hist		*new_hist(void);
void		ft_lex_backslash(t_eval *e);
void		ft_lex_parenth(t_eval *e);
void		ft_lex_var(t_eval *e);
void		ft_lex_dquote(t_eval *e);
void		ft_lex_quote(t_eval *e);
t_word		*ft_check_alias(t_word *head, t_shell *sh);
t_word		*ft_addtword(t_word *head, t_word *new);
t_word		*get_redirections(t_tree *t, t_word *w);
t_tree		*new_tree(void);
t_redirect	*new_redirection(void);
t_tree		*add_newttree(t_tree *tree, t_word *w);
t_word		*ft_get_words(t_eval *e);
void		lexer(t_eval *e, char *src);
t_word		*eval_line(char *input);
t_word		*new_tword(void);
t_word 		*ft_arrto_tword(char **arr, t_shell *sh);
t_process	*init_process(t_tree *t, t_shell *sh);
t_process	*init_pipe_process(t_tree *t, t_shell *sh);
t_process 	*init_process_tmp_var(t_shell *sh, t_envv *head, char **arr);
char 		*ft_split_equal(char *str, char **aft);
int			init_intern(t_shell *sh);
void		retrieve_path(t_shell *sh);
char		*trim_path(char *path);
char		*try_cdpath(char *cdpath, char *path, bool *pwd_f, unsigned int *opts);
char		**check_line(int *max_len, int *total, t_edit *e);
int			add_to_tabl(char ***tabl, char *value, int j);
char		**get_binary(char **path, char *value, bool all, int *total);
char		**get_files(char *value, bool all, int *total);
void		ft_arrdel(char ***arr);
void		set_null_tabl(char **tabl, int len_env);
char		**get_environ_match(char *value, int *total, bool all);
int			check_exec(char *file, char *path);
void		ft_sort_table(char **tabl, int *max_len);
void		ft_others_prompt(t_shell *sh, const char *prompt_txt);
#endif

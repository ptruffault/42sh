/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell42.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:02:36 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/27 20:02:55 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL42_H
# define SHELL42_H

# include <stdbool.h>
# include <stddef.h>
# include <pwd.h>
# include "libft.h"
# include "structures.h"

/*
** autocompletion/binary_completion.c
*/
char			**get_binary(t_shell *sh, char *value, bool all, int *total);

/*
** autocompletion/check_line.c
*/
char			**check_line(int *max_len, int *total, t_edit *e);

/*
** autocompletion/environ_completion.c
*/
char			**get_environ_match(char *value, int *total, bool all);

/*
** autocompletion/files_completion.c
*/
char			**get_files(char *value, bool all, int *total);

/*
** autocompletion/tabl_handler.c
*/
int				add_to_tabl(char ***tabl, char *value, int j);
void			ft_sort_table(char **tabl, int *max_len);
int				check_exec(char *file, char *path);
void			set_null_tabl(char **tabl, int len_env);

/*
** autocompletion/utility_handler.c
*/
char			*check_tilde(char *value);
int				check_before(char *str, int pos);
void			ft_arrdel(char ***arr);

/*
** builtins/ft_fc/flags_lexer.c
*/
int				flags_gestion(char *flags, char **av, int x);

/*
** builtins/ft_fc/fc_fc.c
*/
int				ft_fc(t_shell *shell, char **argv);

/*
** builtins/ft_fc/ft_fc_option_e.c
*/
int				ft_fc_option_e(t_fc *fc, int pos);
int				read_from_add_hist(t_shell *sh, char *line, int x);

/*
** builtins/ft_fc/fc_free_editor.c
*/
int				fc_free_editor(char *editor);

/*
** builtins/ft_fc/fc_fc_option_l.c
*/
int				ft_fc_option_l(t_fc *fc);

/*
** builtins/ft_fc/fc_fc_option_s.c
*/
int				ft_fc_option_s(t_fc *fc, int pos);

/*
** builtins/ft_fc/fc_fc_search_hist.c
*/
t_hist			*search_by_occurence(t_hist *first, char *to_search);
t_hist			*search_by_number_from_last(t_hist *first, int nb);
t_hist			*search_by_number_from_first(t_hist *first, int nb);

/*
** builtins/ft_fc/fc_fc_search_hist_parser.c
*/
int				search_in_hist_parser(t_fc *fc, short i);

/*
** builtins/ft_hash/ft_hash.c
*/
int				builtin_htable(char **cmd, t_shell *sh);
int				cleaning_htable(t_shell *sh);
int				add_in_htable(const char *str, const char *path, t_shell *sh);
t_hash			*search_in_htable(const char *str, t_shell *sh);

/*
** builtins/ft_hash/hash_utility.c
*/
t_hash			**init_htable(void);
unsigned int	ft_hash(const char *str);
char			**check_options_hash(char **cmd, t_shell *sh, int *ret);

/*
** builtins/ft_test/ft_test.c
*/
int				ft_test(char **argv);

/*
** builtins/ft_test/test_utility.c
*/
int				check_integer_tab(char *argv);
int				return_fnc(const char *str, int ret);

/*
** builtins/jobs/fg_bg.c
*/
int				ft_fg(t_shell *sh, char **argv);
int				ft_bg(t_shell *sh, char **argv);

/*
** builtins/jobs/ft_jobs.c
*/
int				ft_jobs(t_shell *sh, char **argv);
void			ft_job_prompt(t_jobs *j, int opts);

/*
** builtins/jobs/hi.c
*/
int				ft_hi(t_shell *sh);
void			ft_put_process(t_process *p);
void			ft_process_tab_status(char *stat[6]);

/*
** builtins/check_builtins.c
*/
int				check_builtin(char *input);

/*
** builtins/ft_alias.c
*/
int				ft_alias(t_shell *sh, char **argv);

/*
** builtins/ft_cd.c
*/
int				ft_cd(char **input, t_shell *sh);

/*
** builtins/ft_cdpath.c
*/
char			*ft_strdup_path(char *src);
char			*trans_cdpath(char *p, t_shell *sh, bool *pw, t_opts *o);
char			*try_cdpath(char *cdp, char *p, bool *pw, t_opts *o);
char			*trim_path(char *path);

/*
** builtins/ft_echo.c
*/
int				ft_echo(char **input, t_process *p);

/*
** builtins/ft_exit.c
*/
int				ft_quit(int exit_code, t_shell *sh);
int				ft_exit(char **nbr, t_shell *sh);

/*
** builtins/ft_export.c
*/
int				ft_export(t_shell *sh, char **argv);
int				check_name(const char *name);

/*
** builtins/ft_type.c
*/
int				ft_type(t_word *w);

/*
** builtins/print_utility.c
*/
void			print_for_export_p(t_envv *node);
void			print_for_export(t_envv *node);
void			print_for_alias(t_envv *node);

/*
** builtins/run_builtin.c
*/
int				run_builtin(t_tree *t, t_process *p, t_shell *sh);

/*
** builtins/type_tools.c
*/
int				putalias(t_word *w, t_envv *alias, int t);
int				putbuiltin(t_word *w, int t);
int				putcmd(t_word *w, t_envv *env, int t);
int				putfile(t_word *w, t_envv *env, int t);
int				putword(t_word *w, int t);

/*
** eval/alias.c
*/
t_word			*ft_check_alias(t_word *head, t_shell *sh, int k);

/*
** eval/eval_tools.c
*/
void			ft_reset_alias(t_envv *alias);
char			*get_tenvv_val_alias(t_envv *envv, const char *name);
char			**ft_twordto_arr(t_word *w);
void			ft_delete_char(t_eval *e);

/*
** eval/get_instruction.c
*/
t_tree			*get_tree(char *input, t_shell *sh);
int				ft_check_grammar(t_word *w, t_shell *sh);

/*
** eval/heredoc_content.c
*/
t_redirect		*parse_heredoc(t_redirect *ret, t_word *w);

/*
** eval/lexer.c
*/
void			lexer(t_eval *e, char *src);

/*
** eval/lexer_tools.c
*/
int				ft_check_in_head(t_word *head, char *str);
void			ft_lex_quote(t_eval *e);
void			ft_lex_dquote(t_eval *e);
void			ft_lex_parenth(t_eval *e);
void			ft_lex_backslash(t_eval *e);

/*
** eval/redirect.c
*/
t_word			*get_redirections(t_tree *t, t_word *w);

/*
** eval/redirect_tools.c
*/
t_word			*ft_delete_redir_stuff(t_word *w);
char			*ft_get_redir_path(t_word *w);

/*
** eval/t_word_tools.c
*/
int				check_order_alias(t_word *w, int *doit, int i);
t_word			*ft_addtword(t_word *head, t_word *ret);
t_word			*ft_deltword(t_word *prev, t_word *src);
t_word			*new_tword(void);

/*
** eval/token.c
*/
t_word			*eval_line(char *input);
t_word			*ft_get_words(t_eval *e);

/*
** eval/tree_tools.c
*/
t_tree			*newttree(t_tree *tree, t_word *w);
t_redirect		*new_redirection(void);
t_tree			*new_tree(void);
int				ft_check_ascii(char *input);

/*
** eval/tword_to_string.c
*/
char			*tword_to_string(t_word *w);

/*
** exec/bin_search.c
*/
char			*get_bin_path(char *input, t_envv *envv);
char			*search_in_envv(char *input, t_envv *envv, int i);
char			*absolute_path(char *input, t_envv *envv);

/*
** exec/exec.c
*/
t_tree			*exec_tree(t_tree *t, t_shell *sh);

/*
** exec/exec_file.c
*/
int				exec_file(const char *path, t_shell *sh);
int				exec_fd(t_shell *sh, int fd);

/*
** exec/exec_pipe.c
*/
t_jobs			*exec_pipe(t_tree *t, t_process *p, t_shell *sh);

/*
** exec/ft_execve.c
*/
t_jobs			*ft_exec_process(t_process *p, t_shell *sh, t_tree *t);

/*
** exec/pipe_tools.c
*/
void			ft_groups_stuff(t_shell *sh, t_process *p);
void			ft_close_pipe(int pipe[2]);
int				ft_link_stdout(t_process *p);
int				ft_link_stdin(t_process *p);

/*
** exec/exec_tools.c
*/
int				check_exe(char *bin_path);
void			ft_exit_son(t_shell *sh, int exit_code, t_process *p);
void			ft_link_process_to_term(t_process *p, t_shell *sh);

/*
** exec/redirect_builtins.c
*/
void			ft_reset_fd(t_shell *sh);
int				ft_redirect_builtin(t_tree *t, t_process *p, t_shell *sh);

/*
** exec/redirection.c
*/
int				ft_isstd(int i);
int				get_destination_fd(t_redirect *r);
int				fd_dup(int fd1, int fd2, t_process *p);

/*
** expansion/cut_string.c
*/
char			*ft_cut_string(char *parenth, char *val, int *curr);

/*
** expansion/cut_glob.c
*/
char		*ft_cut_glob(char *val, char *pattern, char *op);

/*
** expansion/exp.c
*/
t_tree			*ft_expention(t_tree *t);
char			*ft_exp_var(char *ret, t_shell *sh, t_bool quoting);

/*
** expansion/expansion_tools.c
*/
int				delete_char_j(int j, char *ret);
int				checktilde(t_word *w);
char			*ft_get_varname(char *s);

/*
** expansion/exp_parenth.c
*/
char			*ft_exp_param(char *ret, char *ptr, t_shell *sh);

/*
** expansion/parenth_tools.c
*/
t_tree			*ft_word_paste(t_tree *t);
char			*ft_get_cutted_value(char *p, t_shell *sh, char *v, int *i);
int				get_cnt_size(char *s);
char			*ft_get_secondvalue(char *src);

/*
** expansion/exp_tools.c
*/
int				ft_match_begin(const char *s, const char *p, t_bool mode);
int				ft_match_end(const char *s, const char *p, t_bool mode);
char			*ft_get_len(char *value);
char			*ft_clear_quote(char *str);
char			*ft_clear_backslash(char *str);

/*
** get_input/cursor/arrow_move.c
*/
void			ft_home_key(t_edit *e);
void			curr_go_last(t_edit *e);
void			curr_move_left(t_edit *e);
void			curr_move_right(t_edit *e);

/*
** get_input/cursor/clear_and_all.c
*/
void			reset_tedit(t_edit *e);
void			just_exit(t_edit *e);
void			reset_get_input(t_edit *e);
void			gi_clear(t_edit *e);

/*
** get_input/cursor/curs_move.c
*/
void			curs_reset(t_edit *e);

/*
** get_input/cursor/ft_cop_pas.c
*/
void			ft_paste(t_edit *e);
void			ft_copy(t_edit *e);

/*
** get_input/cursor/ft_jump_line.c
*/
void			ft_select_line_down(t_edit *e);
void			ft_jump_line_down(t_edit *e);
void			ft_select_line_up(t_edit *e);
void			ft_jump_line_up(t_edit *e);

/*
** get_input/cursor/ft_jump_word.c
*/
void			ft_jp_word_left(t_edit *e);
void			ft_jp_word_right(t_edit *e);

/*
** get_input/cursor/ft_select.c
*/
void			ft_select_home(t_edit *e);
void			ft_select_end(t_edit *e);
void			ft_select_left(t_edit *e);
void			ft_select_right(t_edit *e);

/*
** get_input/history/ft_incr_search.c
*/
int				ft_incr_add(t_edit *e);
void			ft_incremental_search(t_edit *e);

/*
** get_input/history/hist_expanse.c
*/
int				check_for_hist_exp(t_edit *e);

/*
** get_input/history/history.c
*/
void			hist_move_up(t_edit *e);
void			hist_move_do(t_edit *e);

/*
** get_input/history/seek_n_replace.c
*/
int				seek_n_repl_nb(t_edit *e, size_t x, int nb, size_t size);
int				seek_n_repl_str(t_edit *e, size_t x, char *word, size_t i);

/*
** get_input/ft_tab.c
*/
int				tab_handle(t_edit *e);

/*
** get_input/get_input.c
*/
int				get_input(char **line);

/*
** get_input/handler_input.c
*/
int				handle_input(unsigned long buf, t_edit *e);
void			ft_incr_search(t_edit *e);

/*
** get_input/input_tools.c
*/
void			delete_on(t_edit *e);
void			delete_left(t_edit *e);
int				ft_add_char(char buf, t_edit *e);

/*
** get_input/print_line.c
*/
void			ft_print_line(t_edit *e);
void			ft_print_fast(t_edit *e);
void			ft_print_edited(t_edit *e);
void			ft_delete_line(t_edit *e);

/*
** get_input/prompt.c
*/
void			ft_disp(t_shell *sh);
void			ft_others_prompt(t_shell *sh, const char *prompt_txt);

/*
** get_input/setup.c
*/
int				init_tedit(t_shell *sh);
int				ft_get_hist_size(void);

/*
** get_input/gi_init_tab.c
*/
void			ft_init_inputs_kval(t_edit *e, int x);
void			ft_init_inputs_tab(t_edit *e, int x);
void			ft_init_print_modes(t_edit *e, int x);

/*
** get_input/term_settings.c
*/
int				ft_set_old_term(t_shell *sh, int error);
int				ft_setup_edit_term(t_shell *sh);
int				init_termcaps(t_shell *sh);
void			ft_update_windows(t_edit *e, bool print);

/*
** get_input/use_termcaps.c
*/
int				term_goto(char *cmd, int row, int col);
int				term_actions(const char *cmd);
char			*get_tgetstr(const char *id, char **area);

/*
** get_input/valid_line.c
*/
void			entry_key(t_edit *e);
int				check_eval(char *str);

/*
** history/deload_history.c
*/
void			ft_deload_hist_in_file(t_shell *sh);

/*
** history/get_history.c
*/
t_hist			*init_hist(char *hist);
t_hist			*new_hist(void);
int				ft_isparenth(char c);

/*
** process/ft_kill.c
*/
int				kill_process(t_process *p, int sig, unsigned int status);
void			ft_update_status(t_process *p, unsigned int status);

/*
** process/init_pipe.c
*/
t_process		*init_pipe_process(t_tree *t, t_shell *sh);

/*
** process/init_process.c
*/
t_process		*init_process(t_tree *t, t_shell *sh);

/*
** process/jobs_search.c
*/
t_jobs			*ft_search_jobs(t_jobs *j, char *s);
t_jobs			*ft_get_last_jobs(t_jobs *j, char last);
t_jobs			*ft_get_jobs_pid(t_jobs *j, int pid);

/*
** process/jobs_tools.c
*/
t_jobs			*ft_add_jobs(t_process *p, t_shell *sh);
t_jobs			*ft_remove_jobs(int pid, t_shell *sh);
int				ft_job_is_over(t_jobs *j);
t_jobs			*ft_get_lastp_jobs(t_jobs *j);

/*
** process/wait_process.c
*/
void			ft_wait_background(t_shell *sh);
int				ft_wait(t_process *p, t_jobs *j, t_shell *sh, t_bool fg);

/*
** setup_exit/free_tools.c
*/
t_process		*ft_free_tprocess(t_process *p);
t_hist			*ft_free_thist(t_hist *h);
t_tree			*ft_free_tree(t_tree *t);
t_redirect		*ft_free_redirection(t_redirect *r);
t_word			*ft_free_tword(t_word *w);

/*
** setup_exit/free_tools_shell.c
*/
void			ft_free_tshell(t_shell *sh);
t_jobs			*ft_free_tjobs(t_jobs *j);
void			pre_free_process(t_process *p);

/*
** setup_exit/init_envv.c
*/
int				init_env(t_shell *sh, char **argv, char **envv);

/*
** setup_exit/init_intern.c
*/
void			ft_init_builtins_tab(t_shell *sh);
void			retrieve_path(t_shell *sh);
int				init_intern(t_shell *sh);
char			*retrieve_home(struct passwd **usr, t_envv *envv);

/*
** setup_exit/init_shell.c
*/
int				init_shell(t_shell *sh, char **envv, char **argv);
int				ft_init_groups(t_shell *sh);
int				ft_tcsetpgrp(int fd, pid_t pgrp);
pid_t			ft_tcgetpgrp(int fd);

/*
** tenvv/ft_setenv.c
*/
t_envv			*ft_setenv(t_envv *envv, char **t, int mode, short status);
t_envv			*ft_new_envv_equ(t_envv *envv, char *eq, short status);
t_envv			*ft_new_envv(t_envv *e, const char *n, const char *v, short s);
t_envv			*ft_new_envv_int(t_envv *e, const char *n, int v, short s);
char			*ft_split_equal(char *str, char **aft);

/*
** tenvv/ft_unsetenv.c
*/
int				ft_unsetenv(t_shell *sh, char **t);
t_envv			*ft_del_envv(t_envv *envv, char *name);
t_envv			*ft_free_tenvv(t_envv *envv);
t_envv			*del_tenvv(t_envv *envv);
int				ft_unsetalias(t_shell *sh, char **t);

/*
** tenvv/tenvv_to_tab.c
*/
void			ft_setup_localenv(t_process *p, t_shell *sh, t_tree *t);
void			ft_get_envv_back(t_shell *sh, t_process *p, t_tree *t);
char			**tenvv_to_tab(t_envv *envv);

/*
** tenvv/tenvv_tools.c
*/
int				ft_puttenvv(t_envv *t, short status, int mode);
char			*get_tenvv_val(t_envv *envv, const char *name);
t_envv			*get_tenvv(t_envv *envv, const char *name);
t_envv			*new_tenvv(short status);
int				only_a(char *str);

/*
** tenvv/tenvv_tools_tmp.c
*/
t_envv			*ft_save_tenvv(t_envv *envv, t_envv *tmp);
t_envv			*ft_push_tenvv(t_envv *dest, const t_envv *src, short status);
t_envv			*ft_remove_tmp(t_envv *src);
t_envv			*ft_restore_tenvv(t_envv *dest, const t_envv *src);
t_envv			*ft_push_tmp_env(t_envv *dest, const t_envv *src, short status);

/*
** ft_get_set.c
*/
t_shell			*ft_get_set_shell(t_shell *sh);
t_tree			*ft_get_set_tree(t_tree *new_t);

/*
** signal.c
*/
void			sig_handler(int sig);
int				ft_signal_check(t_process *p);
void			ft_leave(int sig);

/*
** signal_handle.c
*/
void			set_signals(void);
void			set_son_signal(void);

#endif

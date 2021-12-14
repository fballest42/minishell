/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:07:06 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/10 12:09:57 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <term.h>
# include <termios.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/includes/libft.h"

# define READ_END 0
# define WRITE_END 1

typedef enum s_type
{
	ARGUMENT,
	PIPE,
	INDIRECTION,
	REDIRECTION,
	HERE_DOC,
	APPEND,
	FILE_NAME
}			t_type;

typedef struct s_here
{
	int		i;
	int		j;
	int		z;
	int		s_qoutes;
	int		d_quotes;
	int		comillas;
	int		fd;
	char	*str1;
	char	*str2;
}	t_here;

typedef struct s_pparse
{
	char	*aux;
	int		s_quotes;
	int		d_quotes;
	int		i;
	int		j;	
}	t_pparse;

typedef struct s_env
{
	char	**envp;
	char	*home;
	char	*user;
	char	*pwd;
	char	*oldpwd;
	char	**paths;
}	t_env;

typedef struct s_exe
{
	int		fd_in;
	char	*cmd;
	char	**args;
	int		fd_out;
}	t_exe;

typedef struct s_cmd_info
{
	int		return_code;
	int		no_pipes;
	char	*line;
	t_list	*command_list;
	t_exe	*exe;
}	t_cmd_info;

typedef struct s_node
{
	char	*prompts;
	t_type	types;
	int		comillas;
	int		fd_in;
	int		fd_out;
}	t_node;

typedef struct s_parser
{
	int		i;
	char	*word;
	char	*prompt;
}	t_parser;

/*
** MINISHELL.C
** OJO BORRAR LEAKS Y PRINT_LIST
*/
void		leaks(void);
void		print_list(t_cmd_info *cmd_info);
void		del(void *node);
char		*memory_main(int argc, char **argv);
int			main(int argc, char **argv, char **envp);

/*
** ENV/ENVIROMENTS.C
*/
char		*ft_strchr2(const char *str, char c);
char		**add_basic_envs(char **envp);
void		take_envs(char	**envp, t_env *env);

/*
** ENV/ENV_UTILS.C
*/
void		change_shlvl(t_env *env);
void		add_slash_to_path(t_env *env, char *envp);

/*
** ENV/FIND_INITIAL_ENVS.C
*/
int			find_initial_envs(char **envs);
int			find_oldpwd(char **envs);
int			find_pwd(char **envs);
int			find_shlvl(char **envs);

/*
** LEXER/LEXER.C
*/
void		set_next_char(t_parser *p, int *j);
int			check_dollar_to_print(t_parser *p);
int			parse_simple_chars(t_env *env, t_parser *p,
				t_cmd_info *cmd_info, int j);
void		lexer(t_env *env, t_cmd_info *cmd_info, char *prompt);

/*
** LEXER/WORDS.C
*/
void		word_analyzer(t_parser *p, t_env *env, t_cmd_info *cmd_info);
void		add_word_to_list(t_list **list, t_cmd_info *cmd_info, char *word,
				int comillas);

/*
** LEXER/QUOTES.C
*/
void		parse_quotes(t_env *env, t_parser *p, char c, t_cmd_info *cmd_info);
void		simple_quotes_after_char(t_parser *p, int *j);
void		double_quotes_after_char(t_parser *p, t_env *env,
				t_cmd_info *cmd_info, int *j);

/*
** LEXER/DOLLAR.C
*/
void		dollar_variables(t_parser *p, t_env *env, int *j);
void		expand_dollar_digit(t_parser *p, int *j);
void		expand_dollars(t_env *env, t_parser *p,
				int *j, t_cmd_info *cmd_info);

/*
** EXECUTER/EXECUTE.C
*/
int			count_arguments(t_list *tmp);
char		**assign_arguments_for_execve(t_list *tmp);
int			execute_paths(t_list *tmp, t_env *env);
void		execute(t_cmd_info *cmd_info, t_env *env);
char		*cmd_path2(char *cmd, char *tmp, int check_path, t_env *env);

/*
** EXECUTER/EXECUTE2.C
*/
char		*cmd_path(t_env *env, char *cmd);
int			execute_builtins(t_exe exe, t_env *env);

/*
** BUILTINS/CD.C
*/
int			cd_alone(t_env *env);
int			cd_guion(t_env *env);
int			cd_path(t_env *env, t_exe exe);
int			check_cddirectory(char *direct);
int			execute_cd(t_exe exe, t_env *env);

/*
** BUILTINS/CD_2.C
*/
void		ft_take_envs_free(t_env *env);
void		ft_change_env(t_env *env);

/*
** BUILTINS/ECHO.C
*/
void		print_after_know_flag(int n, t_exe exe, int jump);
int			flag_to_one(t_list **tmp);
int			execute_echo(t_exe exe);

/*
** BUILTINS/ENV.C
*/
int			execute_env(t_exe exe, t_env *env);

/*
** BUILTINS/EXIT.C
*/
int			alpha_in_string(char *str);
void		alpha_exit(char *alpha);
void		normal_exit(char *n);
int			execute_exit(t_exe exe);

/*
** BUILTINS/EXPORT.C
*/
char		**order_envs(char **envs);
void		print_envs_export(char **envs);
char		**add_string_to_array(t_env *env, char **arr, char *str);
int			execute_export(t_exe exe, t_env *env);

/*
** BUILTINS/PWD.C
*/
int			execute_pwd(void);

/*
** BUILTINS/UNSET.C
*/
int			execute_unset(t_exe exe, t_env *env);

/*
** BUILTINS/BUILTIN_UTILS.C
*/
void		ft_take_envs_free(t_env *env);
void		ft_change_env(t_env *env);
void		change_env_in_env_utils(char **newenv, t_env *env, int *i, int *j);
char		**remove_env(t_env *env, char *erased);
int			check_builtin(char *cmd);

/*
** SIGNAL/SIGNAL.C
*/
void		child_signal(void);
void		sig_init(void);
void		sig_int(int sig);
void		sig_quit(int sig);
void		negligent_parent(void);

/*
** REDIRECTIONS/REDIRECTION.C
*/
int			ft_append(char *filename, t_cmd_info *cmd_info);
int			ft_indirection(char *filename, t_cmd_info *cmd_info);
int			ft_redirection(char *filename, t_cmd_info *cmd_info);
int			check_directory(char *filename, t_cmd_info *cmd_info);
void		ft_manageredirections(t_cmd_info *cmd_info, t_env *env,
				t_node *node, t_type type);

/*
** REDIRECTIONS/HEREDOC.C
*/
char		*heredoc_expander(const char *file, char *tmp, t_env *env,
				t_here *h);
char		*heredoc_bucle_disclaimer(const char *file, char *tmp, t_env *env,
				t_here *h);
void		ft_heredoc_bucle_b(const char *file, char *tmp, t_env *env,
				t_here *h);
void		ft_heredoc_bucle(const char *file, t_env *env, int comillas,
				int fd);
int			ft_heredoc(char *file, t_cmd_info *cmd_info, t_env *env,
				int comillas);

/*
** REDIRECTIONS/HEREDOCEXPANDER.C
*/
char		*fill_env(char *dollar, t_env *env);
void		heredoc_expander_init(char *tmp, t_here *h);
void		heredoc_expander_dollar(char *tmp, t_env *env, t_here *h);
void		heredoc_expander_finish(char *tmp, t_here *h);
char		*heredoc_expander_free(char *tmp, t_here *h);

/*
** REDIRECTIONS/HEREDOCWRITE.C
*/
void		heredoc_writer(char *tmp, t_here *h);

/*
** PARSER/PARSER.C
*/
void		parser(t_cmd_info *cmd_info);

/*
** PARSER/PREPARSER.C
*/
char		*check_finish(char *prompt, t_cmd_info *cmd_info, t_pparse *pp);
void		check_doublequotes(char *prompt, t_pparse *pp);
void		check_addletter(char *prompt, t_pparse *pp);
char		*check_prompt_b(char *prompt, t_cmd_info *cmd_info, t_pparse *pp);
char		*check_prompt(char *prompt, t_cmd_info *cmd_info);

/*
** PARSER/PREPARSER_2.C
*/
char		*check_tmpmemory(char *prompt, char *tmp, int *z, int *y);
void		free_mayorminor(char *prompt, char *tmp, t_pparse *pp);
char		*expand_mayorminor_b(char *prompt, char *tmp, t_pparse *pp, int *z);
char		*expand_mayorminor(char *prompt, t_pparse *pp);
int			check_before_pipes(char *prompt, t_cmd_info *cmd_info, int len);

/*
** PARSER/PREPARSER_3.C
*/
int			expand_conditions(char *prompt, char *tmp, t_pparse *pp);
int			check_end_prompt(char *prompt, t_cmd_info *cmd_info, t_pparse *pp);
void		check_simplequotes(char *prompt, t_pparse *pp);

/*
** PARSER/ANALYZER.C
*/
void		analyze_prompt(t_cmd_info *cmd_info, t_env *env);

/*
** PARSER/ASSIGN_EXE.C
*/
void		assign_arguments_from_list(t_list *tmp, t_exe *exe, int n);
void		assign_cmd_from_argument(t_cmd_info *cmd_info, t_list *tmp,
				int *arg, int i);
void		assign_fd_from_list(t_list *tmp, t_exe *exe, int n);

/*
** EXECUTER/SIMPLE_COMMANDS.C
*/
int			execute_simple_commands(t_cmd_info *cmd_info, t_env *env);
char		**assign_arguments_with_cmd(t_exe exe);
//int			check_builtin(char *cmd);

/*
** EXECUTER/MANAGE_FDS.C
*/
void		restore_fds(int saved_stdin, int saved_stdout);
void		manage_fds(t_exe exe, int *fd_stdin, int *fd_stdout);
void		manage_read_fd(t_exe exe, int read_pipe);
void		manage_write_fd(t_exe exe, int write_pipe[2]);

/*
** EXECUTER/PIPES.C
*/
int			execute_pipes(t_cmd_info *cmd_info, t_env *env);

/*
** CLEAN/CLEANNING.C
*/
void		del(void *node);
void		free_exe(t_cmd_info *cmd_info);
void		reset_values(t_cmd_info *cmd_info);

/*
** EXECUTER/SIMPLE_COMMANDS_UTILS.C
*/
int			check_dir_error(char *path, int saved_stdin, int saved_stdout);
char		**assign_arguments_with_cmd(t_exe exe);

/*
** BUILTINS/ENVIRONMENTS_UTILS.C
*/
void		assign_path(t_env *env, char *str);
int			check_env(char *env, char **list);
char		**order_envs(char **envs);
#endif

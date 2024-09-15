/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:12:07 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 02:44:52 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <termios.h>
# include  "libft/libft.h"

# define IN_HEREDOC 1
# define OUT_HEREDOC 0

# define SET 0
# define GET 1
# define INT_MAX 2147483647

typedef struct s_node
{
	char			*value;
	char			*key;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_data
{
	char	**token;
	int		token_count;
	bool	is_pipe;
	bool	has_redirection;
	bool	is_heredoc;
	int		*input_file_fds;
	int		*output_file_fds;
	int		input_file_count;
	int		output_file_count;
	char	**command_paths;
	char	**command_arguments;
	int		**pipes;
	int		previous_pipe_fd[2];
	int		fd_output;
	int		fd_input;
	bool	has_input;
	int		original_stdin;
	int		heredoc_interrupted;
	int		last_command_exit_status;
	char	**envp;
	t_node	*env;
}	t_data;

// builtins:
void	builtins(t_data *data);
void	handle_export(t_data *data);
void	handle_unset(t_data *data, t_node **env);
void	handle_cd(t_data *data, t_node *env);
void	handle_echo(t_data *data);
void	handle_env(t_data *data, t_node *env);
void	handle_exit(t_data *data);
int		handle_pwd(t_data *data);

// executor:
void	execute_command(t_data *data, char **envp, int index);
bool	handle_commands(t_data *data, char **envp);
bool	execution(t_data *data);
bool	redirect_file_input(t_data *data);
bool	redirect_file_output(t_data *data);
char	*get_command_path(char *command_name, char **envp);
void	pipex(t_data *data);
void	close_pipe_fds(int fd[2]);
void	redirections(t_data *data);

// lexer:
char	*env_variable_check(char *input_str, t_node *env, t_data *data);
bool	lexer(char *input_str, t_data *data);
void	token_merge(t_data *data);
void	token_cleaner(t_data *data, int i);
bool	check_specials(char *token);

// parser:
bool	parse_command_arguments(t_data *data);
bool	parse_cmd_line(t_data *data, char **envp);
void	find_doc(t_data *data, int tk_i);
void	handle_the_doc(const char *delimiter, t_data *data);
char	*find_delimiter(t_data *data);
void	open_infile(t_data *data, int i);
void	open_outfile(t_data *data, int i, bool append);
bool	parser(t_data *data);
void	file_handling(t_data *data);

// signal:
void	signaling(void);
int		get_set_stop_flag(int get, int newvalue);

// utils:
void	reset_struct(t_data *data);
int		add_end(t_node **stack, char *str);
char	**env_list_to_array(t_node **env);
void	load_list(t_data *data, char **envp);
t_node	*find_last(t_node	*stack);
t_node	*parse_str(t_node *node, char *env_str);
int		stack_len(t_node *stack);
void	remove_node(t_node *node);
void	cleanup_and_handle_errors(t_data *data);
char	get_heredoc_status(void);
void	set_heredoc_status(char status);
void	free_array(char ***paths, int arc);
char	*free_char_array(char **array);
void	free_stuff(char **args, char *path);
void	free_line(char **paths, int arc);
void	free_args(char **argh);
void	clean_data(t_data *data);
void	clean_struct(t_data *data);
void	free_env(t_node	**env);
void	exiting(t_data *data, int i);
int		number_checker(char *argv);
void	setup_terminal(struct termios *original_termios);
void	restore_terminal(const struct termios *original_termios);

#endif
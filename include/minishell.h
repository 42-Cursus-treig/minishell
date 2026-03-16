#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define PROMPT "minishell$ "

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	char			*heredoc_file;
	char			*heredoc_delim;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**envp;
	int		last_status;
}	t_shell;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_exec_ctx
{
	int	*prev_pipe;
	int	*curr_pipe;
	int	is_last;
}	t_exec_ctx;

typedef struct s_pipe_ctx
{
	int		cmd_count;
	int		index;
	int		**pipes;
	pid_t	*pids;
	t_cmd	*cmd;
}	t_pipe_ctx;

// builtins/buitlins.c
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
// builtins
int		builtin_echo(char **argv);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_pwd(void);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
int		builtin_env(char **envp);
int		builtin_exit(char **argv, t_shell *shell);

// executor/execute_heredoc.c
int		handle_heredoc_with_content(char *delimiter, char **temp_file,
			char *content);
int		handle_heredoc(char *delimiter, char **temp_file);
// executor/execute_pipeline.c
int		**create_pipes(int n);
pid_t	launch_process(t_shell *shell, t_pipe_ctx *ctx);
void	close_and_free_pipes(int **pipes, int n);
int		execute_pipeline(t_cmd *cmd_list, t_shell *shell);
// executor/execute_simple_cmd.c
int		execute_simple_cmd(t_cmd *cmd, t_shell *shell);
// executor/executor.c
int		count_commands(t_cmd *cmd_list);
void	handle_command_not_found(t_cmd *cmd);
void	execute_piped_cmd(t_cmd *cmd, t_shell *shell, t_exec_ctx *ctx);
int		execute_line(t_cmd *cmd, t_shell *shell);
// executor/setup_redirections.c
int		setup_redirections(t_cmd *cmd);

// parser/expansion.c
char	*get_var_name(char *str);
char	*get_var_value(char *var_name, t_shell *shell);
char	*build_expanded_string(char *original, char *var_name, char *value,
			int dollar_pos);
char	*expand_variables(char *str, t_shell *shell);
// parser/fill_argv_from_tokens
char	**fill_argv_from_tokens(t_token *tokens, int word_count);
t_cmd	*parse_commands_from_tokens(t_token *tokens, t_shell *shell);
// parser/simple_cmd.c
t_cmd	*parse_simple_cmd(t_token **tokens, t_shell *shell);
// parser/parse_word.c
char	*parse_word(char **line_ptr);
// parser/parser.c
t_cmd	*parse_line(char *line, t_shell *shell);

// signals
void	setup_signals(void);

// tokens/handle_operator.c
t_token	*handle_operator(char **line);
// tokens/tokenize.c
t_token	*create_token(t_token_type type, char *value);
t_token	*tokenize(char *line);
// tokens/tokens_to_argv.c
char	**tokens_to_argv(t_token *tokens, t_shell *shell);

// utils/env_utils.c
int		count_env_vars(char **envp);
char	**dup_envp(char **envp);
int		find_env_var(char **envp, char *var);
char	*get_env_var(char **envp, char *var);
// utils/execute_utils.c
void	execute_external_command(t_cmd *cmd, t_shell *shell);
// utils/export_unset_utils.c
char	**set_env_var(char **envp, char *var, char *value);
char	**unset_env_var(char **envp, char *var);
// utitls/free_utils.c
void	free_envp(char **envp);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd_list);
void	free_tokens(t_token *tokens);
void	free_argv_temp(char **argv_temp);
// utils/heredoc_utils.c
char	*create_temp_filename(void);
char	*read_heredoc_line(void);
int		write_heredoc_to_temp(char *delimiter, int fd);
void	cleanup_heredoc_temp(char *temp_file);
// utils/parse_utils.c
int		is_separator(char c);
int		is_newline(char c);
int		is_special(char c);
void	set_redirection_field(char **field, char *value, int *append_flag,
			int append_value);
t_cmd	*create_empty_cmd(t_cmd *cmd);
// utils/path_utils.c
char	*find_command_path(char *cmd, char **envp);
// utils/token_utils.c
char	**expand_argv(char **argv, t_shell *shell);
char	*clean_protection_flags(char *str);
char	*expand_next_variable(char *str, t_shell *shell);
// utils/pipeline_utils.c
void	init_ctx(t_pipe_ctx *ctx, int cmd_count, int **pipes, pid_t *pids);
int		allocate_resources(int cmd_count, pid_t **pids, int ***pipes);
int		execute_command(t_shell *shell, t_pipe_ctx *ctx);
void	close_all_pipes(int **pipes, int count);
void	free_all_pipes(int **pipes, int count);

#endif
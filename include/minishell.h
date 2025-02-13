/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:14:31 by mpihur            #+#    #+#             */
/*   Updated: 2025/01/24 17:30:21 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <signal.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <errno.h>
# include <string.h>
# include "../ft_libft/headers/libft.h"

typedef enum e_nodes
{
	ERROR,
	CMD,
	CMD_CUST,
	IN_REDIR,
	HERE_DOC,
	OUT_REDIR,
	OUT_REDIR_APPEND,
	COMMENT,
	COMMENT_APPEND,
	FILE_STR,
	PIPE,
	AND,
	OR,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	STRING
}	t_node_type;

typedef enum e_redir_type
{
	I_INPUT,
	I_HEREDOC,
	O_OVERWR,
	O_APPENDF,
}	t_redir_type;

typedef enum e_err
{
	PIPE_ERR,
	FORK_ERR,
	DUP2_ERR,
	EXECVE_ERR,
	WAIT_ERR,
	CMD_NOT_FOUND,
	MALLOC,
	INPUT,
	ERROR
}	t_error;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

/*
* args[0] = File path for redirection,
* args[1] = delim or NULL
*/
typedef struct s_redir
{
	t_redir_type	type;
	char			*str;
	int				fd;
	struct s_redir	*next;
}	t_redir;

/* 
*   type - CMD | CUST_CMD
*   argv - command and arguments
*   full_path - exec path like "/bin/ls"
*/
typedef struct s_cmd
{
	// t_node_type		type;
	char			**argv;
	int				argc;
	int				pipe[2];
	pid_t			pid;
	// char			*full_path;
	struct s_redir	*inred;
	struct s_redir	*outred;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_string
{
	t_node_type		type;
	char			*string;
	struct s_string	*next;
	struct s_string	*prev;
}	t_string;

typedef struct s_ast
{
	t_node_type		type;
	char			*string;
	t_cmd			*cmd;
	bool			result;
	struct s_ast	*top;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_minish
{
	t_string		*tokens;
	struct s_ast	*leaf;
	struct s_cmd	*list;
	//char			**envv;
	t_list			*env;
}	t_minish;


char	*expand_line(char *line, t_minish *msh, int i);
/*Tokenize*/
/**
 * @brief Creates double linked list of tokens
 * @param line input line from readline
 * @return 
 */
t_string	*tokenize(char *line);
int	verify_pipes(t_string *tokens);

int	verify_quotes(char *line);

/**
 * @brief Processes the input string, expanding environment variables, handling
 * 	quotes, and resolving escape sequences.
 *
 * This function scans the input string for environment variable references
 * (e.g., `$USER`, `${USER}`), quotes (single and double), and escape sequences
 * (e.g., `\$` for a literal `$`), and generates a processed output string with
 * all substitutions and resolutions applied. The environment variable
 * values are retrieved from the provided linked list `lst`.
 *
 * @param input The input string containing potential environment variable
 * 	references, quotes, and escape sequences.
 * @param lst A linked list of environment variables, where each node
 * 	represents a name-value pair.
 * @return A dynamically allocated string containing the processed output with
 * 	all substitutions applied. The caller is responsible for freeing the
 *	returned string. Returns `NULL` if an error occurs, such as unsupported
 *	syntax or memory allocation failure.
 * @note This function supports both single quotes (which prevent variable
 * 	expansion) and double quotes (which allow variable expansion).
 * 	If unsupported syntax is encountered (e.g., nested variables 
 *	like `${$USER}`), the function returns `NULL`.
 * @example // Example usage:
 * t_list *env_list = initialize_env_list();
 * char *result = process_env("Hello, $USER!", env_list);
 * printf("%s\n", result); // Output: "Hello, ogrativ!" (assuming USER=ogrativ)
 * free(result);
 */
char	*process_env(const char *input, t_list *lst);

char	*get_env_value(const char *var_name, t_list *lst);

/**
 * @brief executes the line provided as argument (argv) input to minishell
 * 			For example, ./minishell ls || echo "fail"
 * @return head of the linked list with t_string * tokens
 */
t_string	*tokenize_oneline(char *final_str);

/**
 * @brief checks the token type ()
 */
t_node_type find_token_type(char *token);

/**
 * @brief Splits the line into tokens which 
 * influence the tree logic, including |, ||, &&, ()
 * @param line Input line
 * @param new allocated t_string
 * @return Head of the linked list, or NULL
 */
t_string	*split_logical(char **line, t_string *new);

/**
 * @brief Creates a cmd_node inside t_string of type CMD,
 * 		which prerares command for execution: splits redir, cmd, args 
 * 		and checks their validity
 *  
 */

/**
 * Frees (char *)string AND linked list (t_string *)tokens
 * @param tokens - head of double linked list 
 */
void		free_tokens(t_string *tokens);
// t_ast		*parse(t_string *tokens);
void		free_list(t_cmd **list);
// void   free_ast(t_ast **leaf)
void		free_split(char **str);

/**
* @brief Printing path of current working directory
* @return Return 0 if succes, -1 for error
*/

/**
 * @brief creates a linked list of cmds with outred and inred inside struct
 * 
 * @param tokens double-linked list of the tokens
 * @return double-linked list of commands
 */
t_cmd	*parse(t_string *tokens, int i);
t_redir	*create_inred_list(t_string *cmd_start);
t_redir	*create_outred_list(t_string *cmd_start);

int			printpwd(void);

/**
 * @brief Changes the current working directory
 * of the calling process to the directory specified in path
 * @param path Path to directory
 * @param user User enviroment variable
 * @return On succes return 0, on error -1
 */
int			ft_cd(char *path, t_list **lst);

// Enviroment variables

/**
 * @brief Add enviroment valiable to list
 * @param lst List of enviroment variables
 * @param env Enviroment variable to add
 */
int			ft_set_env(t_list **lst, char	*env);

/**
 * @brief Delete enviroment valiable from list
 * @param lst List of enviroment variables
 * @param env Enviroment variable to add
 */
void		ft_env_unset(t_list **lst, char *env);

/**
 * @brief Create list of enviroment variables
 * @param lst List of enviroment variables
 * @param env Current enviroment variables
 * @return Return 0 if succes, -1 for error
 */
int			init_env(t_list **lst, char *env[]);

/**
 * @brief Take a key and key_value of enviroment variable
 * @param env Enviroment variable to parce
 * @return Return a pointer to t_env or NULL for error
 */
t_env		*parce_env(char *env);

/**
 * @brief Search enviroment variable by key
 * @param lst List of enviroment variables
 * @param key Name of enviroment variable
 * @return Return a pointer to t_env.
 * Return NULL if enviroment variable with 'key' does not exist
 */
t_env		*ft_get_env(t_list *lst, char *key);
/**
 * @brief Search enviroment variable by key
 * @param lst List of enviroment variables
 * @param key Name of enviroment variable
 * @return Return a pointer to t_list.
 * Return NULL if enviroment variable with 'key' does not exist
 */
t_list		*ft_get_env_node(t_list *lst, char *key);

/**
 * @brief Print enviroment variables to standart output
 * @param lst List of enviroment variables
 */
void		print_env_list(t_list *lst);

/**
 * @brief Splits the value of an environment variable into parts
 * using a specified delimiter.
 * @param lst List of environment variables.
 * @param key Name of the environment variable to split.
 * @param c Delimiter character used for splitting.
 * @return Array of strings resulting from the split operation.
 */
char		**split_path(t_list *lst, char *key, char c);

/**
 * @brief Free allocate memory
 * @param env t_env pointer
 */
void		free_env(void *env);

/**
 * EXECUTION FUNCTIONS
 */

/**
 * 
 */
t_error		execute_cmds(t_minish **msh, t_cmd *list);
t_error		single_cmd(t_list *list, t_minish *msh);
t_error		pipe_cmd(t_cmd *list, t_minish *msh);

#endif
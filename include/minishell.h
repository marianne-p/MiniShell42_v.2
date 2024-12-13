/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:14:31 by mpihur            #+#    #+#             */
/*   Updated: 2024/12/13 15:57:19 by ogrativ          ###   ########.fr       */
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
	CMD,
	CUST_CMD,
	IN_REDIR,
	HERE_DOC,
	OUT_REDIR,
	OUT_REDIR_APPEND,
	COMMENT,
	COMMENT_APPEND,
	FILE_STR,
	PIPE,
	STRING,
	AND,
	OR,
	OPEN_BRACKET,
	CLOSE_BRACKET
}	t_node_type;

typedef enum e_err
{
	MALLOC,
	INPUT
}	t_error;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

/* 
*   type - CMD | CUST_CMD
*   argv - command and arguments
*   full_path - exec path like "/bin/ls"
*/
typedef struct s_cmd
{
	t_node_type	type;
	char		**argv;
	int			argc; //?
	char		*full_path;
	int			outfd;
	int			infd;
}	t_cmd;

/*
* args[0] = File path for redirection,
* args[1] = delim or NULL
*/
typedef struct s_redir
{
	t_node_type		type;
	char			**args;
	int				fd; //?
	struct s_redir	*next;
}	t_redir;

typedef struct s_node
{
	t_cmd			*cmd;
	t_redir			*redir;
	struct s_node	*next;
}	t_node;

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
	//t_node          *node;
	struct s_ast	*top;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_minish
{
	t_string		*tokens;
	struct s_ast	*leaf;
	//struct s_ev		*env;
	//char			**envv;
}	t_minish;


/*Tokenize*/
t_node_type	find_token_type(char *token);
t_string	*tokenize(char *line);
t_ast		*parse(t_string *tokens);

void		free_split(char **str);

/**
* @brief Printing path of current working directory
* @return Return 0 if succes, -1 for error
*/
int			printpwd(void);

/**
 * @brief Changes the current working directory
 * of the calling process to the directory specified in path
 * @param path Path to directory
 * @param user User enviroment variable
 * @return On succes return 0, on error -1
 */
int			ft_cd(char *path, t_env *user);

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

/*Built-ins*/
// void	exec_builtin(t_node *node, t_minish **msh_ptr);
// int		exec_exit(t_node *node, t_minish **msh_ptr);
// void	ft_pwd(void);
// int		ft_cd(char *path);
// int		ft_echo(char **cmd);
// void	ft_exit(char *str, t_minish **msh_ptr, int ret, void *temp);
// int		ft_export(char **av, t_envv **head);
// void	print_all_envv(t_envv *head);
// void	free_envv(t_envv **node);
// void	ft_addenvv(t_envv **env_ptr, char *sngl, t_envv *new);
// int		ft_unset(char *key, t_envv **head);
// void	ft_env(t_minish *minish);

#endif
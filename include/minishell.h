/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:14:31 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/25 19:05:25 by mpihur           ###   ########.fr       */
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
# include "../Libft_42/libft.h"

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

typedef struct s_ev
{
	char		*key;
	char		*value;
	struct s_ev	*next;	
}	t_envv;

/* 
*   type - CMD | CUST_CMD
*   argv - command and arguments
*   full_path - exec path like "/bin/ls"
*/
typedef struct s_cmd
{
    t_node_type type;
	char        **argv;
	int         argc; //?
	char        *full_path;
	int         outfd;
	int         infd;
}	t_cmd;

/*
* args[0] = File path for redirection,
* args[1] = delim or NULL
*/
typedef struct s_redir
{
    t_node_type         type;
    char                **args;
    int                 fd; //?
    struct s_redir      *next;
}	t_redir;

typedef struct s_node
{
	t_cmd			*cmd;
	t_redir			*redir;
	struct s_node	*next;
}	t_node;

typedef struct s_string
{
	t_node_type     type;
	char            *string;
	struct s_string *next;
	struct s_string *prev;
}	t_string;

typedef struct s_ast
{
	t_node_type     type;
	char            *string;
	//t_node          *node;
	struct s_ast    *top;
	struct s_ast    *left;
	struct s_ast    *right;
}	t_ast;

typedef struct s_minish
{
    t_string        *tokens;
	struct s_ast	*leaf;
	//struct s_ev		*env;
	//char			**envv;
}	t_minish;


/*Tokenize*/
t_node_type	find_token_type(char *token);
t_string	*tokenize(char *line);
t_ast   *parse(t_string *tokens);

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
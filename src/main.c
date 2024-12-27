#include "../include/minishell.h"

void   free_ast(t_ast **leaf)
{
    if (!*leaf)
        return ;
    if ((*leaf)->left)
        free_ast(&((*leaf)->left));
    if ((*leaf)->right)
        free_ast(&((*leaf)->right));
    free((*leaf)->string);
    free(*leaf);
    *leaf = NULL;
}

#include <stdio.h>
#include "../include/minishell.h"

static const char *token_type_to_str(t_node_type type)
{
    if (type == ERROR)
        return "(ERROR)";
    else if (type == CMD)
        return "(CMD)";
    else if (type == CMD_CUST)
        return "(CMD_CUST)";
    else if (type == IN_REDIR)
        return "(IN_REDIR)";
    else if (type == HERE_DOC)
        return "(HERE_DOC)";
    else if (type == OUT_REDIR)
        return "(OUT_REDIR)";
    else if (type == OUT_REDIR_APPEND)
        return "(OUT_REDIR_APPEND)";
    else if (type == COMMENT)
        return "(COMMENT)";
    else if (type == COMMENT_APPEND)
        return "(COMMENT_APPEND)";
    else if (type == FILE_STR)
        return "(FILE_STR)";
    else if (type == PIPE)
        return "(PIPE)";
    else if (type == AND)
        return "(AND)";
    else if (type == OR)
        return "(OR)";
    else if (type == OPEN_BRACKET)
        return "(OPEN_BRACKET)";
    else if (type == CLOSE_BRACKET)
        return "(CLOSE_BRACKET)";
    else if (type == STRING)
        return "(STRING)";
    else
        return "(UNKNOWN)";
}

void print_tokens(t_string *tokens)
{
    t_string *current = tokens;

    while (current)
    {
        if (current->string)
            fprintf(stderr, "%s %s", current->string, token_type_to_str(current->type));
        else
            fprintf(stderr, "(null) %s", token_type_to_str(current->type));

        if (current->next && current->next != tokens)
            fprintf(stderr, " -> ");
        current = current->next;
		if (current == tokens || current == NULL)
			break ;
    }
    fprintf(stderr, "\n");
}

void	handle_oneline(t_minish **msh)
{
	// printf("NO_TTY\n");
	(*msh)->tokens = tokenize_oneline();
	if ((*msh)->tokens != NULL)
	{
		print_tokens((*msh)->tokens);
		free_tokens((*msh)->tokens);
	}
	exit(0);
}

void    msh_loop(t_minish **msh)
{
    char    *line;
    char    *prompt;

    prompt = "minishell$ ";
    while (1)
    {
        line = readline(prompt);
        if (!line)
            break ;
        if (*line)
        {
            add_history(line);
			fprintf(stderr, "BEFORE: %s\n", line);
			line = expand_line(line, *msh, 0);
			fprintf(stderr, "AFTER: %s\n", line);
			/*TOKENS STAGE*/
    		// if ((*msh)->tokens != NULL)
			// {
			// 	print_tokens((*msh)->tokens);
			// 	free_tokens((*msh)->tokens);
			// }
			// (*msh)->tokens = tokenize(line);
			// free_tokens((*msh)->tokens);
			/*PARSING*/
            // msh->leaf = parse(msh->tokens);
            // exec_ast(msh->leaf, msh);
            // free_ast(&(msh->leaf));
        }
        free(line);
    }
}

int main(int argc, char **argv, char **env)
{
    t_minish *msh;

	(void)argc;
	(void)argv;
    msh = (t_minish *)malloc(sizeof(t_minish));
    if (!msh)
        return (1);
    msh->tokens = NULL;
    msh->leaf = NULL;
	if (init_env(&(msh->env), env) < 0)
		perror("Env initialization failed\n");
	if (!isatty(STDIN_FILENO))
		handle_oneline(&msh);
    msh_loop(&msh);
    free(msh);
    return (0);
}
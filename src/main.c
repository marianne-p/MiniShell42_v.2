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
	char    *final_str;
	char    *line;
	char    *temp;
	// t_string	*start;

	final_str = ft_strdup("");
	if (!final_str)
		return ;
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		// printf("line = '%s'\n", line);
		temp = final_str;
		final_str = ft_strjoin(temp, line);
		free(temp);
		free(line);
		if (!final_str)
			return ;
	}
	// fprintf(stderr, "BEFORE: %s\n", final_str);
	// line = expand_line(final_str, *msh, 0);
	// fprintf(stderr, "AFTER: %s\n", line);
	(*msh)->tokens = tokenize_oneline(final_str);
    if ((*msh)->tokens != NULL)
		print_tokens((*msh)->tokens);
    (*msh)->list = parse((*msh)->tokens, 0);
    if ((*msh)->tokens != NULL)
		free_tokens((*msh)->tokens);
	if ((*msh)->list != NULL)
		free_list(&((*msh)->list));
	exit(0);
}

void    msh_loop(t_minish **msh)
{
    char    *line;
    char    *prompt;

    prompt = "\nminishell$ ";
    while (1)
    {
        line = readline(prompt);
        if (!line)
            break ;
        if (*line)
        {
            add_history(line);
			/*TOKENS STAGE*/
			if (verify_quotes(line) > 0)
			{
				free (line);
				free (*msh);
				exit (1);
			}
			(*msh)->tokens = tokenize(line);
            if ((*msh)->tokens != NULL)
				print_tokens((*msh)->tokens);
			/*PARSING*/
			if (verify_pipes((*msh)->tokens) > 0)
			{
				free(line);
				free_tokens((*msh)->tokens);
				free(*msh);
				exit(1);
			}
            (*msh)->list = parse((*msh)->tokens, 0);
            if ((*msh)->tokens != NULL)
				free_tokens((*msh)->tokens);
			if ((*msh)->list != NULL)
				free_list(&((*msh)->list));
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
	(void)env;
    msh = (t_minish *)malloc(sizeof(t_minish));
    if (!msh)
        return (1);
    msh->tokens = NULL;
    msh->leaf = NULL;
	msh->env = NULL;
	// if (init_env(&(msh->env), env) < 0)
	// 	perror("Env initialization failed\n");
	if (!isatty(STDIN_FILENO))
		handle_oneline(&msh);
	else
		msh_loop(&msh);
    free(msh);
    return (0);
}
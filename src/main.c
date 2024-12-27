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

void    msh_loop(t_minish *msh)
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
			line = expand_line(line, msh, 0);
            msh->tokens = tokenize(line);
			free_tokens(msh->tokens);
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
	if (init_env(NULL, env) < 0)
		perror("Failed to initialize env\n");
    msh_loop(msh);
    free(msh);
    return (0);
}
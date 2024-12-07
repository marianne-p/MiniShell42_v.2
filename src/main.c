#include "../minishell.h"

t_string    *tokenize(char *line)
{
    t_string    *tokens;
    t_string    *new;
    char        *token;

    tokens = NULL;
    token = ft_split(line, " ");
    while (token)
    {
        new = (t_string *)malloc(sizeof(t_string));
        if (!new)
            return (NULL);
        new->string = ft_strdup(token);
        new->next = tokens;
        tokens = new;
        token = strtok(NULL, " ");
    }
    return (tokens);
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
            msh->tokens = tokenize(line);
            msh->leaf = parse(msh->tokens);
            exec_ast(msh->leaf, msh);
        }
        free(line);
    }
}

int main(void)
{
    t_minish *msh;

    msh = (t_minish *)malloc(sizeof(t_minish));
    if (!msh)
        return (1);
    msh->tokens = NULL;
    msh->leaf = NULL;
    msh_loop(msh);
    return (0);
}
#include "../include/minishell.h"

t_node_type find_token_type(char *token)
{
    if (!ft_strncmp(token, "(\0", 2))
        return (OPEN_BRACKET);
    else if (!ft_strncmp(token, ")\0", 2))
        return (CLOSE_BRACKET);
    else if (!ft_strncmp(token, "&&\0", 3))
        return (AND);
    else if (!ft_strncmp(token, "||\0", 3))
        return (OR);
    else if (!ft_strncmp(token, "|\0", 2))
        return (PIPE);
    // else if (!ft_strncmp(token, "<", 1))
    //     return (IN_REDIR);
    // else if (!ft_strncmp(token, "<<", 2))
    //     return (HERE_DOC);
    // else if (!ft_strncmp(token, ">", 1))
    //     return (OUT_REDIR);
    // else if (!ft_strcmp(token, ">>", 2))
    //     return (OUT_REDIR_APPEND);
    // else if (!ft_strcmp(token, "'", 1))
    //     return (COMMENT);
    // else if (!ft_strcmp(token, "\"", 1))
    //     return (COMMENT_APPEND);
    else
        return (STRING);
}

void    free_split(char **str)
{
    char    **tmp;

    tmp = str;
    while (tmp && *tmp)
    {
        free(*tmp);
        tmp++;
    }
    free(str);
}

/*
    * Tokenizes the input line

    * Split the line into tokens w/ ft_split -> store in a double linked list of t_string
    * Free the split string after use
    * 
    * Allocated memory: t_string *start (head of the linked list)
    * 
    * Return: t_string *start
*/

t_string    *tokenize(char *line)
{
    t_string    *start;
    t_string    *new;
    t_string    *tmp;
    char        **token_str;
    char        **tmp_str;

    start = NULL;
    tmp = NULL;
    token_str = ft_split(line, ' ');
    tmp_str = token_str;
    while (token_str && *token_str)
    {
        new = (t_string *)malloc(sizeof(t_string));
        if (!new)
            return (NULL);
        new->type = find_token_type(*token_str);
        new->string = ft_strdup(*token_str);
        new->next = NULL;
        if (!*(token_str + 1))
        {
            start->prev = new;
            new->next = start;
        }
        new->prev = tmp;
        if (tmp)
            tmp->next = new;
        tmp = new;
        if (!start)
            start = new;
        token_str++;
    }
    free_split(tmp_str);
    return (start);
}
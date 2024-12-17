#include "../include/minishell.h"

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
	char		*line_cpy;
	char		*line_start;

    start = NULL;
    tmp = NULL;
	line_cpy = ft_strdup(line);
	line_start = line_cpy;
    while (*line_cpy)
    {
        new = (t_string *)malloc(sizeof(t_string));
        if (!new)
            return (NULL);
		new = split_logical(&line_cpy, new);	
        // new->type = find_token_type(*token_str);
        // new->string = ft_strdup(*token_str);
        if (!*line_cpy)
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
	}
	free(line_start);
    // free_split(tmp_str);
    return (start);
}
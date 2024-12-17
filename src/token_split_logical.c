#include "../include/minishell.h"

t_node_type find_token_type(char *token)
{
    if (!ft_strncmp(token, "(", 1))
        return (OPEN_BRACKET);
    else if (!ft_strncmp(token, ")", 1))
        return (CLOSE_BRACKET);
    else if (!ft_strncmp(token, "&&", 2))
        return (AND);
    else if (!ft_strncmp(token, "||", 2))
        return (OR);
    else if (!ft_strncmp(token, "|", 1))
        return (PIPE);
    else
        return (STRING);
}

// void    free_split(char **str)
// {
//     char    **tmp;

//     tmp = str;
//     while (tmp && *tmp)
//     {
//         free(*tmp);
//         tmp++;
//     }
//     free(str);
// }

/*	copies quote to quote, including the quotes '/" 
*	moves the pointer through the string 'line' 
*/

char	*copy_str(char **line_start, char quote, char *str)
{
	int	i;

	i = 1;
	while ((*line_start)[i] != quote)
		i++;
	str = malloc(i + 2);
	if (str == NULL)
		return (NULL);
	while (**line_start != quote)
		*(str)++ = *(*line_start++);
	*str = quote;
	*str = '\0';
	return (str);
}

t_string	*find_expression(t_string *new, char **line)
{
	new->type = find_token_type(*line);
	if (new->type == AND || new->type == OR)
	{
		new->string = malloc(3);
		if (!new->string)
			return (NULL);
		if (new->type == AND)
			new->string = "&&\0";
		else
			new->string = "||\0";
		*line = *line + 2;
	}
	else
	{
		new->string = malloc(2);
		if (!new->string)
			return (NULL);
		new->string[0] = **line;
		new->string[1] = '\0';
		(*line)++;
	}
	return(new);

} 

void	skip_blanks(char **line)
{
	while (ft_isblank(**line))
		(*line)++;
}

char	*copy_line(char **line, int i, char *str)
{
	while ((*line)[i] != '\'' && (*line)[i] != '"'
			&& (*line)[i] != '|' && (*line)[i] !='(' 
			&& (*line)[i] != '&' && (*line)[i] != ')'
			&& (*line)[i] != '\0' && !ft_isblank((*line)[i]))
			i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (**line != '\'' && **line != '"'
			&& **line != '|' && **line !='(' 
			&& **line != '&' && **line != ')'
			&& **line != '\0' && !ft_isblank(**line))
		{
			str[i] = **line;
			i++;
			(*line)++;
		}
	str[i] = '\0';
	return (str);
}

t_string	*split_logical(char **line, t_string *new)
{
	if (**line == '\'' || **line == '"')
	{
		new->string = copy_str(line, '\'', NULL);
		new->type = COMMENT; 
	}
	else if (**line == '"')
	{
		new->string = copy_str(line, '"', NULL);
		new->type = COMMENT_APPEND;
	}
	else if (**line == '|' || **line == '(' || **line == '&' || **line == ')')
		new = find_expression(new, line);
	else
	{
		new->string = copy_line(line, 0, NULL);
		new->type = CMD_LINE;
	}
	if (ft_isblank(**line))
		skip_blanks(line);	
	new->next = NULL;
	return (new);
}
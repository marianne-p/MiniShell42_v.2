#include "../include/minishell.h"

void	skip_blanks(char **line)
{
	while (*line && **line && ft_isblank(**line))
		(*line)++;
}

t_node_type find_token_type(char *token)
{
	if (!token)
		return (ERROR);
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

char	*copy_quote(char **line_start, char quote, char *str)
{
	int	i;

	i = 1;
	while (*line_start && (*line_start)[i] && (*line_start)[i] != quote)
		i++;
	str = malloc(i);
	if (str == NULL)
		return (NULL);
	i = 0;
	(*line_start)++;
	while (*line_start && *(*line_start) && *(*line_start) != quote)
	{
		str[i++] = **line_start;
		(*line_start)++;
	}
	if (**line_start == quote)
		(*line_start)++;
	str[i] = '\0';
	return (str);
}

char	*copy_token(char **line, char *str)
{
	int	i;

	i = 0;
	if (ft_isblank(**line))
		skip_blanks(line);	
	while (*line && (*line)[i] && !ft_isblank((*line)[i]))
		i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*line && **line && !ft_isblank(**line))
	{
		str[i++] = **line;
		(*line)++;
	}
	str[i] = '\0';
	return (str);
}

t_string	*find_expression(t_string *new, char **line)
{
	new->type = find_token_type(*line);
	if (new && new->type && (new->type == AND || new->type == OR))
	{
		// new->string = malloc(3);
		// if (!new->string)
		// 	return (NULL);
		if (new->type == AND)
			new->string = ft_strdup("&&\0");
		else
			new->string = ft_strdup("||\0");
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

char	*copy_line(char **line, int i, char *str)
{
	while (*line && (*line)[i] && (*line)[i] != '\'' && (*line)[i] != '"'
			&& (*line)[i] != '|' && (*line)[i] !='(' 
			&& (*line)[i] != '&' && (*line)[i] != ')'
			&& (*line)[i] != '\0' && !ft_isblank((*line)[i]))
			i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*line && **line && **line != '\'' && **line != '"'
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

t_string	*create_outred_struct(char **line, t_string *new)
{
	if (*line && !ft_strncmp(*line, ">>", 2))
	{
		new->string = copy_token(line, NULL);
		new->type = OUT_REDIR_APPEND; 
	}
	else if (*line && **line && **line == '>')
	{
		new->string = copy_token(line, NULL);
		new->type = OUT_REDIR;
	}
	else
	{
		new->string = copy_token(line, NULL);
		new->type = COMMENT_APPEND;
	}
	return (new);
}

t_string	*create_string_struct(char **line, t_string *new)
{
	if (*line && **line && **line == '\'')
	{
		new->string = copy_quote(line, '\'', NULL);
		new->type = COMMENT; 
	}
	else if (*line && **line && **line == '"')
	{
		new->string = copy_quote(line, '"', NULL);
		new->type = COMMENT_APPEND;
	}
	else if (*line && **line && !ft_strncmp(*line, "<<", 2))
	{
		new->string = copy_token(line, NULL);
		new->type = HERE_DOC;
	}
	else if (*line && **line && **line == '<')
	{
		new->string = copy_token(line, NULL);
		new->type = IN_REDIR; 
	}
	else
		new = create_outred_struct(line, new);
	return (new);
}

t_string	*split_logical(char **line, t_string *new)
{
	if (*line && **line && ft_isblank(**line))
		skip_blanks(line);	
	if (*line && **line
			&& (**line == '|' || **line == '(' || **line == '&' || **line == ')'))
	{
		new = find_expression(new, line);
	}
	else
	{
		new = create_string_struct(line, new);	
	}
	new->next = NULL;
	new->prev = NULL;
	if (*line && **line && ft_isblank(**line))
		skip_blanks(line);	
	return (new);
}
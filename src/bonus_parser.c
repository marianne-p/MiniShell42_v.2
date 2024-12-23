#include "../include/minishell.h"

void    free_tokens(t_string *tokens)
{
	t_string    *tmp;
	t_string	*start;

	if (tokens->prev != NULL)
	{
		start = tokens->prev;
		while (tokens)
		{
			tmp = tokens;
			tokens = tmp->next;
			fprintf(stderr, "Deleting '%s'\n", tmp->string);
			free(tmp->string);
			free(tmp);
			tmp = NULL;
			if (tokens == start)
			{
				fprintf(stderr, "Deleting start '%s'\n", start->string);
				free (start->string);
				free (start);
				break ;
			}
		}
	}
	else
	{
		free(tokens->string);
		free(tokens);
	}
}

t_ast   *create_leaf(t_string *tokens, t_ast *new, t_ast *left, t_ast *right)
{
	if (!tokens)
		return (NULL);
	new = (t_ast *)malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = tokens->type;
	new->string = ft_strdup(tokens->string);
	new->top = NULL;
	new->left = left;
	if (new->left)
		new->left->top = new;
	new->right = right;
	if (new->right)
		new->right->top = new;
	printf("New leaf: %s, addr: %p, left: %p, right: %p\n", new->string, new, new->left, new->right);
	return (new);
}

/*	for count end to start: incr = CLOSE_BRACKET, decr = OPEN_BRACKET
*	for count start to end: incr = OPEN_BRACKET, decr = CLOSE_BRACKET
*/

t_string	*count_brackets(t_string *token, t_node_type incr, t_node_type decr, bool middle)
{
	t_string    *tmp;
	int         count;

	count = 0;
	tmp = token;
	if (incr == OPEN_BRACKET)
		token = token->prev;
	else
		token = token->next;	
	while (tmp != token)
	{
		if (tmp->type == incr)
			count++;
		else if (tmp->type == decr)
			count--;
		if (middle == false && count == 0 && tmp->type == decr)
			return (tmp);
		else if (middle == true && count == 0 && (tmp->type == AND || tmp->type == OR))
			return (tmp);
		if (incr == OPEN_BRACKET)
			tmp = tmp->next;
		else
			tmp = tmp->prev;
	}
	printf("Error: Invalid syntax, current token type: %s\n", token->string);
	return (NULL);
}

// t_string	*find_middle_token(t_string *start, t_string *end)
// {
// 	t_string    *tmp;
// 	int         count;

// 	count = 0;
// 	tmp = start;
// 	while (tmp != end)
// 	{
// 		if (tmp->type == OPEN_BRACKET)
// 			count++;
// 		else if (tmp->type == CLOSE_BRACKET)
// 			count--;
// 		if (count == 0)
// 		{
// 			printf("Middle token: %s\n", tmp->next->string);
// 			return (tmp->next);
// 		}
// 		tmp = tmp->next;
// 	}
// 	printf("Error: Invalid syntax, current token type: %s\n", tmp->string);
// 	return (NULL);
// }

t_ast    *find_heart(t_string *start, t_string *end, t_ast *left, t_ast *right)
{
	t_string    *tmp;

	tmp = NULL;
	if (!start || !end)
		return (NULL);

	if (start->type == STRING && end->type == STRING && start->next->next == end)
		return (create_leaf(start->next, NULL, 
					create_leaf(start, NULL, NULL, NULL), 
					create_leaf(end, NULL, NULL, NULL)));

	if (end->type == CLOSE_BRACKET && start->type == OPEN_BRACKET)
	{
		tmp = count_brackets(end, CLOSE_BRACKET, OPEN_BRACKET, false);
		right = find_heart(tmp->next, end->prev, NULL, NULL);
		tmp = count_brackets(start, OPEN_BRACKET, CLOSE_BRACKET, false);
		left = find_heart(start->next, tmp->prev, NULL, NULL);
		// printf("End: %s\n", end->string);
		tmp = count_brackets(start, OPEN_BRACKET, CLOSE_BRACKET, true);
		return(create_leaf(tmp, NULL, left, right));
	}
	else if (end->type == STRING && start->type == OPEN_BRACKET)
	{
		right = create_leaf(end, NULL, NULL, NULL);
		tmp = count_brackets(start, OPEN_BRACKET, CLOSE_BRACKET, false);
		left = find_heart(start->next, tmp->prev, NULL, NULL);
		// printf("End: %s\n", end->string);
		return (create_leaf(end->prev, NULL, left, right));
	}
	else if (end->type == CLOSE_BRACKET && start->type == STRING)
	{
		tmp = count_brackets(end, CLOSE_BRACKET, OPEN_BRACKET, false);
		right = find_heart(tmp->next, end->prev, NULL, NULL);
		left = create_leaf(start, NULL, NULL, NULL);
		// printf("Start: %s\n", start->string);
		return (create_leaf(start->next, NULL, left, right));
	}
	else
	{
		printf("Error: Invalid syntax, end token type: %s, start: %s\n", end->string, start->string);
		return (NULL);
	}
}

// t_ast   *find_left_leaf(t_string *tokens)
// {
// 	t_string    *tmp;

// 	tmp = tokens;
// 	if (!tokens)
// 		return (NULL);
// 	if (tmp->prev->type == STRING)
// 		return (create_leaf(tmp->prev, NULL, NULL, NULL));
// 	else if (tmp->prev->type == CLOSE_BRACKET)
	
// 	return (NULL);
// }

t_ast   *parse_advanced(t_string *tokens)
{
	t_ast   *ast;
	t_ast   *heart;
	t_string    *start;

	start = tokens;
	ast = NULL;
	if (!tokens)
		return (NULL);

	if (tokens->type == OPEN_BRACKET)
	{
		heart = find_heart(tokens->next, tokens->prev->prev, NULL, NULL);
		return (heart);
	}
	else if (tokens->type == STRING)
	{
		ast = create_leaf(tokens, ast, NULL, NULL);
	}
	else
	{
		printf("Error: Invalid syntax\n");
		return (NULL);
	}

	free_tokens(start);
	return (ast);
}
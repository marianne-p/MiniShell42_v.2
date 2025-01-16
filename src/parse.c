#include "../include/minishell.h"

int	find_cmd_end(t_string **tokens, t_string *head, int i)
{
	i = 0;
	while ((i == 0 || *tokens != NULL || *tokens != head) 
			&& (*tokens)->type != PIPE)
	{
		if ((*tokens)->type != OUT_REDIR && (*tokens)->type != OUT_REDIR_APPEND
			&& (*tokens)->type != HERE_DOC && (*tokens)->type != IN_REDIR)
			i++;
		*tokens = (*tokens)->next;
	}
	return (i);
}

void	populate_command(t_string *cmd_start, t_string *tokens, t_cmd **tmp)
{
	int	i;

	i = 0;
	while (i == 0 || (cmd_start != tokens && cmd_start->type != PIPE))
	{
		if (cmd_start->type != OUT_REDIR && cmd_start->type != OUT_REDIR_APPEND
			&& cmd_start->type != HERE_DOC && cmd_start->type != IN_REDIR)
		{
			((*tmp)->argv)[i++] = ft_strdup(cmd_start->string);
		}
		cmd_start = cmd_start->next;
	}
	(*tmp)->argv[i] = NULL;
}

void	print_red(t_redir *red)
{
	while (red != NULL)
	{
		printf("'%s' ", red->str);
		red = red->next;
	}
}

void	print_parsed(t_cmd *head, t_cmd *current, int i)
{
	current = head;
	while (i == 0 || current != NULL)
	{
		i = 0;
		fprintf(stderr, "cmd: '%s'	", current->argv[i]);
		while (current->argv[++i] != NULL)
			fprintf(stderr, "'%s' ", current->argv[i]);
		if (current->inred)
		{
			fprintf(stderr, "	inred: ");
			print_red(current->inred);
		}
		if (current->outred)
		{
			fprintf(stderr, "	outred: ");
			print_red(current->outred);
		}
		current = current->next;
	}
}

t_cmd	*parse(t_string *tokens, int i)
{
	t_string	*tok_head;
	t_string	*cmd_start;
	t_cmd		*head;
	t_cmd		*prev;
	t_cmd		*tmp;

	tok_head = tokens;
	head = NULL;
	prev = NULL;
	tmp = NULL; 
	while (i == 0 || tokens != tok_head)
	{
		if (tokens->type == PIPE)
			tokens = tokens->next;
		cmd_start = tokens;
		i = find_cmd_end(&tokens, tok_head, i);
		tmp = (t_cmd *)malloc(sizeof(t_cmd));
		tmp->argc = i + 1;
		tmp->argv = (char **)malloc(sizeof(char *) * (i + 1));
		populate_command(cmd_start, tokens, &tmp);
		tmp->inred = NULL;
		tmp->outred = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
		if (prev)
		{
			tmp->prev = prev;
			prev->next = tmp;
		}
		if (!head)
			head = tmp;
		if (tmp)
			prev = tmp;
	}	
	print_parsed(head, head, 0);
	return (head);
}


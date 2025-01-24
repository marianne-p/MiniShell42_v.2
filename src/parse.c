#include "../include/minishell.h"

int	find_cmd_end(t_string **tokens, t_string *head, int i)
{
	(void)head;
	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
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

	(void)tokens;
	i = 0;
	while (cmd_start && cmd_start->type != PIPE)
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
		fprintf(stderr, "'%s' ", red->str);
		red = red->next;
	}
}

void	print_parsed(t_cmd *head, t_cmd *current, int i)
{
	current = head;
	while (i == 0 || (current && current != head))
	{
		i = 1;
		fprintf(stderr, "\ncmd: '%s'	", current->argv[0]);
		while (current->argv && current->argv[i])
			fprintf(stderr, "'%s' ", current->argv[i++]);
		if (current->inred)
		{
			fprintf(stderr, "\n		inred: ");
			print_red(current->inred);
		}
		if (current->outred)
		{
			fprintf(stderr, "\n		outred: ");
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
	while (i == 0 || (tokens && tokens != tok_head))
	{
		if (tmp)
			prev = tmp;
		if (tokens->type == PIPE && prev)
			tokens = tokens->next;
		cmd_start = tokens;
		i = find_cmd_end(&tokens, tok_head, i);
		tmp = (t_cmd *)malloc(sizeof(t_cmd));
		tmp->inred = create_inred_list(cmd_start);
		tmp->outred = create_outred_list(cmd_start);
		tmp->prev = NULL;
		tmp->next = NULL;
		tmp->argc = i;
		tmp->argv = (char **)malloc(sizeof(char *) * (i + 1));
		populate_command(cmd_start, tokens, &tmp);
		if (prev)
		{
			tmp->prev = prev;
			prev->next = tmp;
		}
		if (!head)
			head = tmp;
	}	
	print_parsed(head, head, 0);
	return (head);
}


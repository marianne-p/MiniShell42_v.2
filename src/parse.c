#include "../include/minishell.h"

int	find_cmd_end(t_string **tokens, t_string *head, int i)
{
	while ((i == 0 || *tokens != head) && (*tokens)->type != PIPE)
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
	while (cmd_start != tokens->next || cmd_start->type != PIPE)
	{
		if (tokens->type != OUT_REDIR && tokens->type != OUT_REDIR_APPEND
			&& tokens->type != HERE_DOC && tokens->type != IN_REDIR)
		{
			((*tmp)->argv)[i++] = ft_strdup(cmd_start->string);
		}
		cmd_start = cmd_start->next;
	}
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
	while (i == 0 || current != head)
	{
		i = 0;
		printf("cmd: '%s'	", current->argv[i]);
		while (current->argv[++i] != NULL)
			printf("'%s' ", current->argv[i]);
		if (current->inred)
		{
			printf("	inred: ");
			print_red(current->inred);
		}
		if (current->outred)
		{
			printf("	outred: ");
			print_red(current->outred);
		}
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
	while (i == 0 || tokens != tok_head)
	{
		cmd_start = tokens;
		i = find_cmd_end(&tokens, tok_head, i);
		if (tmp)
			prev = tmp;
		tmp = malloc(sizeof(t_cmd));
		tmp->inred = NULL;
		tmp->outred = NULL;
		tmp->argc = i;
		tmp->argv = (char **)malloc(sizeof(char *) * (i + 1));
		if (!head)
			head = tmp;
		tmp->prev = tmp;
		populate_command(cmd_start, tokens, &tmp);
	}	
	print_parsed(head, head, 0);
	return (head);
}


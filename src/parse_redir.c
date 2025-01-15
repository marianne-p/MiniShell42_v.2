#include "../include/minishell.h"

t_redir	*create_red_list(t_string *cmd_start, t_node_type type1, t_node_type type2)
{
	t_redir	*head;
	t_redir	*tmp;
	t_redir	*prev;

	head = prev = tmp = NULL;
	while (cmd_start && cmd_start->type != PIPE)
	{
		if (cmd_start->type == type1 || cmd_start->type == type2)
		{
			tmp = (t_redir *)malloc(sizeof(t_redir));
			if (!tmp)
				return (head);
			if (cmd_start->type == IN_REDIR)
				tmp->type = I_INPUT;
			else if (cmd_start->type == HERE_DOC)
				tmp->type = I_HEREDOC;
			else if (cmd_start->type == OUT_REDIR)
				tmp->type = O_OVERWR;
			else
				tmp->type = O_APPENDF;
			tmp->str = ft_strdup(cmd_start->string);
			tmp->next = NULL;
			tmp->fd = -2;
			if (!head)
				head = tmp;
			if (prev)
				prev->next = tmp;
			prev = tmp;
		}
		cmd_start = cmd_start->next;
	}
	return (head);
}

t_redir	*create_inred_list(t_string *cmd_start)
{
	t_redir	*head;

	head = create_red_list(cmd_start, IN_REDIR, HERE_DOC); 
	return (head);
}

t_redir	*create_outred_list(t_string *cmd_start)
{
	t_redir	*head;

	head = create_red_list(cmd_start, OUT_REDIR_APPEND, OUT_REDIR);
	return (head);
}
#include "../include/minishell.h"

void   free_ast(t_ast **leaf)
{
    if (!*leaf)
        return ;
    if ((*leaf)->left)
        free_ast(&((*leaf)->left));
    if ((*leaf)->right)
        free_ast(&((*leaf)->right));
    free((*leaf)->string);
    free(*leaf);
    *leaf = NULL;
}

void	free_red(t_redir **red)
{
	t_redir	*tmp;

	while (*red)
	{
		tmp = (*red)->next;
		free((*red)->str);
		free(*red);
		*red = NULL;
		*red = tmp;
	}
}

void	free_list(t_cmd **list)
{
	t_cmd	*tmp;

	tmp = *list;
	while (*list)
	{
		tmp = (*list)->next;
		free_split((*list)->argv);
		if ((*list)->inred)
			free_red(&(*list)->inred);
		if ((*list)->outred)
			free_red(&(*list)->outred);
		free(*list);
		*list = NULL;
		*list = tmp;
	}
}
#include "../include/minishell.h"



// t_string	*split_cmd(t_string *big, int i)
// {
// 	char		*cmd_line;
// 	char		*cmd_start;
// 	t_string	*start;
// 	t_string	*new;
// 	t_string	*tmp;

// 	cmd_line = ft_strdup(big->string);
// 	while (*cmd_line)
// 	{
// 		new = create_string_struct();
// 		if (!new)
// 			return (NULL);
// 		if (!*cmd_line)
//         {
//             start->prev = new;
//             new->next = start;
//         }
//         new->prev = tmp;
//         if (tmp)
//             tmp->next = new;
//         tmp = new;
//         if (!start)
//             start = new;
// 	}
// 	free(cmd_start);
// 	return (start);
// }
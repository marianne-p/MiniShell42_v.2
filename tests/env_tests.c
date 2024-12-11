/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:35:46 by ogrativ           #+#    #+#             */
/*   Updated: 2024/12/11 12:08:51 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "ft_color_utils.h"
#include <stdbool.h>

bool	ft_lst_nodecmp(t_list *node1, t_list *node2)
{
	t_env	*env1;
	t_env	*env2;

	env1 = (t_env *)(node1->content);
	env2 = (t_env *)(node2->content);
	if (ft_strcmp(env1->key, env2->key) == 0
		&& ft_strcmp(env1->value, env2->value) == 0)
		return (true);
	return (false);
}

bool	ft_lstcmp(t_list *lst1, t_list *lst2)
{
	if (lst1 == NULL && lst2 == NULL)
		return (true);
	if (lst1 == NULL || lst2 == NULL)
		return (false);
	while (lst1 != NULL && lst2 != NULL)
	{
		if (!ft_lst_nodecmp(lst1, lst2))
			return (false);
		lst1 = lst1->next;
		lst2 = lst2->next;
	}
	if (lst2 == NULL && lst1 == NULL)
		return (true);
	return (false);
}

void	ft_clear(t_list **lst, char **env)
{
	ft_lstclear(lst, free_env);
	free_split(env);
}

// int	main(int argc, char *argv[], char *env[])
int	main(void)
{
	t_list	*lst = NULL;
	/*test 1: create list with 10 elements*/
	char	**env = ft_split("TEST1=65987 TEST2=65987 TEST3=65987 TEST4=65987 TEST5=65987 TEST6=65987 TEST7=65987 TEST8=65987 TEST9=65987 TEST10=65987", ' ');
	init_env(&lst, env);
	if (ft_lstsize(lst) == 10)
		printf("create list: " GRN "OK\n" RESET);
	else
		printf("create list: " RED "KO\n" RESET);
	/*test 2 add element to list*/
	ft_set_env(&lst, "TEST11=89657");
	if (ft_lstsize(lst) == 11)
		printf("add element: " GRN "OK\n" RESET);
	else
		printf("add element: " RED "KO\n" RESET);
	/*test 3 update element*/
	t_list *lst2 = NULL;
	char	**env2 = ft_split("TEST1=65987 TEST2=65987 TEST3=9 TEST4=65987 TEST5=65987 TEST6=65987 TEST7=65987 TEST8=65987 TEST9=65987 TEST10=65987 TEST11=89657", ' ');
	init_env(&lst2, env2);
	ft_set_env(&lst, "TEST3=9");
	if (ft_lstcmp(lst, lst2))
		printf("update element: " GRN "OK\n" RESET);
	else
		printf("update element: " RED "KO\n" RESET);
	ft_clear(&lst2, env2);
	/*test 4 delete element from middle of the list*/
	t_list *lst3 = NULL;
	char	**env3 = ft_split("TEST1=65987 TEST2=65987 TEST4=65987 TEST5=65987 TEST6=65987 TEST7=65987 TEST8=65987 TEST9=65987 TEST10=65987 TEST11=89657", ' ');
	init_env(&lst3, env3);
	ft_env_unset(&lst, "TEST3");
	if (ft_lstcmp(lst, lst3))
		printf("remove element: " GRN "OK\n" RESET);
	else
		printf("remove element: " RED "KO\n" RESET);
	ft_clear(&lst3, env3);
	/*test 5 delete first element*/
	t_list *lst4 = NULL;
	char	**env4 = ft_split("TEST2=65987 TEST4=65987 TEST5=65987 TEST6=65987 TEST7=65987 TEST8=65987 TEST9=65987 TEST10=65987 TEST11=89657", ' ');
	init_env(&lst4, env4);
	ft_env_unset(&lst, "TEST1");
	if (ft_lstcmp(lst, lst4))
		printf("remove first element: " GRN "OK\n" RESET);
	else
		printf("remove first element: " RED "KO\n" RESET);
	ft_clear(&lst4, env4);
	/*test 6 add variables without args and with*/
	t_list	*lst5 = NULL;
	char	**env5 = ft_split("TEST2=65987 TEST4=65987 TEST5=65987 TEST6=65987 TEST7=65987 TEST8=65987 TEST9=65987 TEST10=65987 TEST11=89657 TEST12=12 TEST13=13", ' ');
	init_env(&lst5, env5);
	ft_set_env(&lst, "TEST12=12 TEST TEST13=13 TEST98");
	if (ft_lstcmp(lst, lst5))
		printf("mix input: " GRN "OK\n" RESET);
	else
		printf("mix input: " RED "KO\n" RESET);
	ft_clear(&lst5, env5);
	ft_clear(&lst, env);
	return (0);
}

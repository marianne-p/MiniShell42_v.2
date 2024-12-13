/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:02:30 by ogrativ           #+#    #+#             */
/*   Updated: 2024/12/11 16:23:16 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "ft_color_utils.h"

int	main(int argc, char *argv[], char *env[])
{
	t_list	*lst = NULL;
	char	*str;
	char	**path_value;
	char	**split_path_value;
	size_t	i = 0;

	(void)argc;
	(void)argv;
	init_env(&lst, env);
	if (lst == NULL)
		return (EXIT_FAILURE);
	str = getenv("PATH");
	if (str == NULL)
		return (EXIT_FAILURE);
	path_value = ft_split(str, ':');
	if (path_value == NULL)
		return (ft_lstclear(&lst, free_env), EXIT_FAILURE);
	split_path_value = split_path(lst, "PATH", ':');
	if (split_path_value == NULL)
		return (free_split(path_value),
			ft_lstclear(&lst, free_env), EXIT_FAILURE);
	while (path_value[i] != NULL && split_path_value[i] != NULL)
	{
		if (ft_strcmp(path_value[i], split_path_value[i]) != 0)
		{
			printf("Split_path: " RED "KO\n" RESET);
			return (free_split(path_value), free_split(split_path_value),
				ft_lstclear(&lst, free_env), EXIT_FAILURE);
		}
		i++;
	}
	if (path_value[i] == NULL && split_path_value[i] == NULL)
		printf("Split_path: " GRN "OK\n" RESET);
	else
		printf("Split_path: " RED "KO\n" RESET);
	return (free_split(path_value), free_split(split_path_value),
		ft_lstclear(&lst, free_env), EXIT_SUCCESS);
}

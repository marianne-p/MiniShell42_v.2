/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:15:16 by ogrativ           #+#    #+#             */
/*   Updated: 2024/12/10 13:48:51 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	try_replace(t_list **lst, t_env *env)
{
	t_list	*tmp_node;

	if (*lst == NULL || env == NULL)
		return (-1);
	tmp_node = ft_get_env_node(*lst, env->key);
	if (tmp_node == NULL)
		return (0);
	free_env(tmp_node->content);
	tmp_node->content = env;
	return (1);
}

int	ft_set_env(t_list **lst, char	*env)
{
	t_env	*var;
	char	**tmp;
	size_t	i;

	i = 0;
	if (env == NULL)
		return (-1);
	tmp = ft_split(env, ' ');
	if (tmp == NULL)
		return (-1);
	while (tmp[i] != NULL)
	{
		var = parce_env(tmp[i]);
		if (var == NULL)
			return (-1);
		if (!try_replace(lst, var))
			ft_lstadd_back(lst, ft_lstnew(var));
		i++;
	}
	free_split(tmp);
	return (0);
}

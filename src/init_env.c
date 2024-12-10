/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:19:18 by ogrativ           #+#    #+#             */
/*   Updated: 2024/12/10 16:44:15 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*parce_env(char *env)
{
	t_env	*var;
	size_t	i;

	i = 0;
	if (env == NULL)
		return (NULL);
	var = malloc(sizeof(t_env));
	if (var == NULL)
		return (perror(strerror(ENOSPC)), NULL);
	while (env[i] != '=' && env[i] != '\0')
		i++;
	var->key = ft_substr(env, 0, i);
	if (var->key == NULL)
		return (free(var), NULL);
	var->value = ft_substr(env, ++i, ft_strlen(env));
	if (var->value == NULL || var->value[0] == '\0')
		return (free(var->key), free(var->value), free(var), NULL);
	return (var);
}

void	free_env(void *env)
{
	if (env == NULL)
		return ;
	if (((t_env *)env)->key != NULL)
		free(((t_env *)env)->key);
	if (((t_env *)env)->value != NULL)
		free(((t_env *)env)->value);
	free(env);
}

int	init_env(t_list **lst, char *env[])
{
	t_env	*var;
	int		i;

	i = 0;
	if (env == NULL)
		return (perror(strerror(EINVAL)), -1);
	while (env[i] != NULL)
	{
		var = parce_env(env[i]);
		if (var == NULL)
			continue ;
		else if (*lst == NULL)
			*lst = ft_lstnew(var);
		else
			ft_lstadd_back(lst, ft_lstnew(var));
		i++;
	}
	return (0);
}

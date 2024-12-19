/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:02:41 by ogrativ           #+#    #+#             */
/*   Updated: 2024/12/18 16:08:19 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_strjoin3(const char *dest, const char *str2, const char *str3)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dest == NULL || str2 == NULL || str3 == NULL)
		return (NULL);
	str = malloc(ft_strlen(dest) + ft_strlen(str2) + ft_strlen(str3));
	if (str == NULL)
		return (NULL);
	while (dest[i] != '\0')
		str[i++] = dest[j++];
	j = 0;
	while (str2[j] != '\0')
		str[i++] = str2[j++];
	j = 0;
	while (str3[j] != '\0')
		str[i++] = str3[j++];
	str[i] = '\0';
	return (str);
}

char	**env_list_to_str_arr(t_list *lst)
{
	char	**env;
	t_env	*env_node;
	size_t	size;

	env = NULL;
	if (lst == NULL)
		return (NULL);
	size = ft_lstsize(lst);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (env == NULL)
		return (NULL);
	size = 0;
	while (lst != NULL)
	{
		env_node = (t_env *)lst->content;
		env[size] = ft_strjoin3(env_node->key, "=", env_node->value);
		if (env[size] == NULL)
			return (free_split(env), NULL);
		lst = lst->next;
		size++;
	}
	return (env);
}

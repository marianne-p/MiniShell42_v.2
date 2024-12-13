/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:11:06 by ogrativ           #+#    #+#             */
/*   Updated: 2024/12/13 16:36:18 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	cd_error_handler(int cd_out)
{
	if (cd_out != -1)
		return (cd_out);
	if (errno == EACCES)
		return (perror("Can't accest to component of path"), cd_out);
	if (errno == EFAULT)
		return (perror("Path outside accessible address space"), cd_out);
	if (errno == ENOENT)
		return (perror("Directory does not exist"), cd_out);
	if (errno == ENOTDIR)
		return (perror("A component of path is not a directory"), cd_out);
	if (errno == ENAMETOOLONG)
		return (perror("Path is to long:"), cd_out);
	if (errno == EIO)
		return (ft_putstr_fd("An I/O error occurred", STDERR_FILENO), cd_out);
	if (errno == ENOMEM)
		return (perror("Insufficient kernel memory was available"), cd_out);
	if (errno == ELOOP)
	{
		ft_putstr("Too many symbolic links were encountered in resolving path",
			STDERR_FILENO);
		return (cd_out);
	}
	return (cd_out);
}

//todo: errors handle
int	ft_cd(char *path, t_env *user)
{
	char	*home_path;
	int		cd;

	if (user == NULL || user->value[0] == '\0')
		return (-1);
	if (path == NULL || path[0] == '~')
	{
		home_path = ft_strjoin("/home/", user->value);
		if (home_path == NULL)
			return (free(home_path), -1);
		if (path != NULL && ft_strcmp(path, "~") != 0)
		{
			while (*path != '/')
				path++;
			home_path = ft_join_and_free(home_path, path);
			if (home_path == NULL)
				return (-1);
		}
		cd = chdir(home_path);
		return (free(home_path), cd_error_handler(cd));
	}
	return (cd_error_handler(chdir(path)));
}

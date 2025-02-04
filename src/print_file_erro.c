/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file_erro.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:13:48 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/04 12:14:12 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_file_error(void)
{
	if (errno == ENOENT)
		perror("File does not exist\n");
	else if (errno == EEXIST)
		perror("File already exists\n");
	else if (errno == ENOTDIR)
		perror("A component of the path is not a directory\n");
	else if (errno == EISDIR)
		perror("Expected a file, but it's a directory\n");
	else if (errno == EMFILE)
		perror("Too many open files in the process\n");
	else if (errno == ENFILE)
		perror("Too many open files in the system\n");
	else if (errno == ELOOP)
		perror("Too many symbolic links encountered\n");
	else
		perror(strerror(errno));
}

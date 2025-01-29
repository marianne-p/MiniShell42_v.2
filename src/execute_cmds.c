#include "../include/minishell.h"

int	is_valid_cmd(char *token, char *full_line, t_minish *msh)
{
	char	**path;
	int		is_valid;
	int		i;

	if (token[0] == '/')
	{
		if (access(token, F_OK) == 0)
		{
			full_line = ft_strdup(token);
			return (full_line);
		}
	}
	i = 0;
	is_valid = 0;
	path = split_path(msh->env, "PATH", ':');
	if (!path)
		return (-1);
	is_valid = check_command(path, token, full_line);
	while (path[i])
		free(path[i++]);
	free(path);
	return (full_line);
}

int	check_command(char **path, char *token, char **full_line)
{
	int		i;
	char	*ptemp;
	char	*full_path;

	i = 0;
	while (path && path[i++])
	{
		ptemp = ft_strjoin(path[i], "/\0");
		full_path = ft_strjoin(ptemp, token);
		free(ptemp);
		if (!full_path)
			return (printf("MALL_ERR, check_command, cmd_create.c\n"),
				MALL_ERR);
		if (access(full_path, F_OK) == 0)
		{
			*full_line = full_path;
			return (true);
		}
		free(full_path);
	}
	return (false);
}

void	run_child(t_cmd *list)
{
	char	*exec_path;

	if (list->next && dup2(list->prev->pipe[1], STDOUT_FILENO) < 0)
		exit(DUP2_ERR);
	close(list->prev->pipe[1]);
	exec_path = ;
	execve(exec_path, list->argv, NULL);
	exit(EXECVE_ERR);
}

t_error	pipe_cmd(t_cmd *list)
{
	t_cmd	*head;

	head = list;
	while (list->next != NULL)
	{
		if (pipe(list->pipe) < 0)
			return (perror("Pipe setup error: "), PIPE_ERR);
	}
	list = head;
	while (list)
	{
		list->pid = fork(); 
		if (list->pid != 0)
			return (perror("Fork() call error: "), FORK_ERR);
		if (list->pid == 0)
			run_child(list);
	}
}

int	execute_cmds(t_minish **msh, t_cmd *list)
{
	if (!list->next)
		single_cmd(list, *msh);
	else
		pipe_cmd(list);
}
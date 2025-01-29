#include "../include/minishell.h"

void	run_single_cmd(t_cmd *list, t_minish *msh)
{
	char	*exec_path;

	exec_path = find_cmd_path(list->argv[0], NULL, msh);
	if (!exec_path)
		exit(CMD_NOT_FOUND);
	execve(exec_path, list->argv, NULL);
	exit(EXECVE_ERR);
}

t_error	single_cmd(t_cmd *list, t_minish *msh)
{
	list->pid = fork();
	if (list->pid == 0)
		run_single_child(*list, msh);
	else if (list->pid < 0)
		return (perror("Fork() failed"), FORK_ERR);
	waitpid(list->pid, NULL, 0);
	if (WIFEXITED(list->pid))
		return (WEXITSTATUS(list->pid));
	return (ERROR);
}
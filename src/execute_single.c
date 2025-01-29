#include "../include/minishell.h"

void    single_cmd(t_cmd *list, t_minish *msh)
{
    char    *exec_path;

    exec_path = find_cmd_path(list->argv[0], exec_path, msh);
    if (!exec_path)
        exit(1);
    if (execve(exec_path, list->argv, NULL) < 0)
        exit(EXECVE_ERR);
    exit(0);
}
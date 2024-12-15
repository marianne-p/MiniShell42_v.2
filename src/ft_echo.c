#include "../include/minishell.h"

static int	exec_echo(bool newline, char **str, int i, int j)
{
	while (str[i] && ft_strncmp(str[i], "", 1) != 0)
	{
		if (ft_strncmp(str[i], "#\0", 2) == 0)
		{
			i++;
			continue ;
		}
		if (str[i][j] == '"' || str[i][j] == '\'')
		{
			j++;
			while (str[i][j] && (str[i][j] != '\'' && str[i][j] != '"'))
				printf("%c", str[i][j++]);
			i++;
		}
		else
			printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
	if (newline == true)
		printf("\n");
	return (0);
}

bool	check_all_n(char *str, int i)
{
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		else
			i++;
	}
	return (true);
}

int	ft_echo(char **cmd)
{
	bool	newline;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
	{
		if (check_all_n(cmd[i] + 2, 0) == false)
			return (exec_echo(true, cmd, 1, 0));
		newline = false;
		while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			if (check_all_n(cmd[i] + 2, 0) == false)
				return (exec_echo(true, cmd, i, 0));
			i++;
		}
	}
	else
		newline = true;
	if (newline == true)
		return (exec_echo(newline, cmd, 1, 0));
	else
		return (exec_echo(newline, cmd, i, 0));
}
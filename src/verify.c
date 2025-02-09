#include "../include/minishell.h"

int	quote_helper(char *line, int *i)
{
	if (line[*i] && line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (line[*i] && line[*i] == '\'')
			(*i)++;
		else
		{
			ft_putstr_fd("The matching quote (') is missing", STDERR_FILENO);
			return (2);
		}
	}
	(*i)++;
	return (0);
}

int	verify_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i] && line[i] == '"')
				i++;
			else
			{
				ft_putstr_fd("The matching quote (\") is missing", STDERR_FILENO);
				return (1);
			}
		}
		if (quote_helper(line, &i) == 2)
			return (2);
	}
	return (0);
}

int	verify_pipes(t_string *tokens)
{
	int	cmd;
	int	pipe;
	// t_string	*tmp;

	cmd = 0;
	pipe = 0;
	while (tokens != NULL)
	{
		if (tokens->type != PIPE)
		{
			cmd++;
			if (cmd - pipe > 1 || pipe - cmd > 0)
			{
				ft_putstr_fd("Wrong pipe/command pattern\n", STDERR_FILENO);
				return (1);
			}
			while (tokens && tokens->type != PIPE)
				tokens = tokens->next;
		}
		if (tokens && tokens->type == PIPE)
		{
			pipe++;
			tokens = tokens->next;
			if (cmd - pipe > 1 || pipe - cmd > 0)
			{
				ft_putstr_fd("Wrong pipe/cmd pattern\n", STDERR_FILENO);
				return (2);
			}
		}
	}
	if (cmd - pipe != 1)
	{
		ft_putstr_fd("Wrong pipe/cmd number\n", STDERR_FILENO);
		return(3);
	}
	return (0);
}
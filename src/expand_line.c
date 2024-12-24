#include "minishell.h"

char	*copy_string(char *line, int *i, char *res)
{
	int	k;

	k = *i + 1;
	line[*i] = '\0';
	while (line[*i] != '\'')
		*i++;
	if (line[*i] == '\'')
		line[*i] = '\0';
	else 
	{
		
	}
	res = ft_strjoin(line, line + k);
	return (res);
}

char	*find_key(char *key_start)
{
	int		k;
	char	*ret;

	k = 0;
	while (!ft_isblank(key_start[k]))
		k++;
	ret = malloc (k + 1);
	k = 0;
	while (!ft_isblank(key_start[k]))
	{
		ret[k] = key_start[k];
		k++;
	}
	ret[k] = '\0';
	return (ret);
}

char	*find_value_from_node(t_env *envvar)
{
	return (envvar->value);
}

char	*expand_dbl_quote(char *line, int *i, t_minish *msh)
{
	char	*result;
	char	*str1;
	char	*str2;

	result = NULL;
	str1 = NULL;
	str2 = NULL;
	if (!str1)
		str1 = copy_first_str(NULL, line, line + *i); //if there is no start point for joining, line...line + i
	else
		str1 = copy_first_str(result, str1, line + *i); // joint + (no_change_str = line...line + i)
	str2 = find_value_from_node(ft_get_env(msh->env, find_key(line + *i + 1)));
	result = ft_strjoin(str1, str2);
	free(str1);
	str1 = str2 = NULL;
	free(str2);
	skip_key(line, &i);
	if (line[*i] != '"')
		str1 = line + *i;
}

char	*expand_line(char *line, t_minish *msh, size_t i)
{
	char	*result;

	result = NULL;
	while (line[i] != '\0')
	{
		//check that there are matching quotes ", ' before that
		if (line[i] == '\'')
			result = copy_string(line, &i, NULL);
		else if (line[i] == '"')
		{
			while (line[i] != '"')
			{
				if (line[i] == '$')
				{
					result = expand_dbl_quote(line, &i, msh);
				}
				else
					i++;
			}
		}
		else
			i++;
	}
}
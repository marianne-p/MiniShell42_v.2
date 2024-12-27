#include "minishell.h"

char	*copy_string(char *line, int *i, char *res)
{
	int	k;

	k = *i + 1;
	line[*i] = '\0';
	while (line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
		line[*i] = '\0';
	else 
	{
		printf("No matching quotes\n");	
	}
	res = ft_strjoin(line, line + k);
	return (res);
}

char	*copy_first_str(char *prev, char *start, char *end)
{
	int		i;
	char	*new;
	char	*res;

	i = 0;
	while (start + i != end)
		i++;
	new = malloc(i + 1);
	i = 0;
	while (start + i != end)
	{
		new[i] = start[i];
		i++;
	}
	new[i] = '\0';
	res = ft_strjoin(prev, new);
	if (prev != NULL)
		free(prev);
	free(new);
	return (res);
}

void	skip_key(char *line, int *i)
{
	while ((ft_isalnum(line[*i]) || line[*i] == '_') &&
		line[*i] != '\0' && line[*i] != '"' && !ft_isblank(line[*i]))
		(*i)++;
}

char	*find_key(char *key_start)
{
	int		k;
	char	*ret;

	k = 0;
	while ((ft_isalnum(key_start[k]) || key_start[k] == '_') &&
			key_start[k] && key_start[k] != '"' && !ft_isblank(key_start[k]))
		k++;
	ret = malloc (k + 1);
	k = 0;
	while ((ft_isalnum(key_start[k]) || key_start[k] == '_') &&
		key_start[k] && key_start[k] != '"' && !ft_isblank(key_start[k]))
	{
		ret[k] = key_start[k];
		k++;
	}
	ret[k] = '\0';
	return (ret);
}

char	*find_value_from_node(t_env *envvar)
{
	if (!envvar)
		return (NULL);
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
	while (line[*i] != '"' && line[*i] != '\0')
	{
		if (line[*i] == '$')
		{
			//if (!(ft_isalpha(line[*i + 1])) && line[*i + 1] != '_')
			if (!str1 && *i > 1)
				str1 = copy_first_str(NULL, line, line + *i); //if there is no start point for joining, line...line + i
			else if (*i > 1)
				str1 = copy_first_str(result, str1, line + *i); // joint + (no_change_str = line...line + i)
			str2 = find_value_from_node(ft_get_env(msh->env, find_key(line + *i + 1)));
			result = ft_strjoin(str1, str2);
			if (str1 != NULL)
				free(str1);
			if (str2 != NULL)
				free(str2);
			str1 = str2 = NULL;
			skip_key(line, i);
			if (line[*i] != '"')
				str1 = line + *i;
		}
		else
			(*i)++;
	}			
	return (result);
}

char	*expand_line(char *line, t_minish *msh, int i)
{
	char	*result;

	result = NULL;
	while (line[i] != '\0')
	{
		//check that there are matching quotes ", ' before that
		if (line[i] == '\'')
			result = copy_string(line, &i, NULL);
		else if (line[i] && line[i] == '"')
		{
			i++;
			result = expand_dbl_quote(line, &i, msh);
			i++;
		}
		else
			i++;
	}
	free (line);
	return (result);
}
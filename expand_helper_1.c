#include "minishell.h"

char	*lookup_variable(char *var_name, t_env *env_struct)
{
	t_env	*tmp;

	tmp = env_struct;
	while (tmp)
	{
		if (strcmp(var_name, tmp->key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

int	expand_fill(t_exp_helper *expand, t_token *tmp)
{
	expand->original = tmp->DATA;
	expand->expanded = malloc(strlen(expand->original) * 2 + 1);
	if (!expand->expanded)
		return (0);
	expand->i = 0;
	expand->j = 0;
	expand->quote_state = 0;
	return (1);
}

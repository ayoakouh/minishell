#include "minishell.h"
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	l;

	i = 0;
	if (s == NULL)
		return (NULL);
	l = strlen(s);
	if (start >= l)
		return (strdup(""));
	if (len > l - start)
		len = l - start;
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

int	is_valide_key(char *key)
{
    int i;

    i = 0;
    if(!key)
        return (0);
    if (!(key[0] >= 'a' && key[0] <= 'z') && key[0] != '_')
        return (0);
    while(key[i] != '\0')   // this must be checked;
    {
        if(!(key[i] >= 'a' && key[i] <= 'z') && key[i] != '_' && !(key[i] >= '0' && key[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}
void add_or_update(t_env **env, char *key, char *value) //add_environment;
{
	t_env	*tmp;
	t_env	*new = NULL;
	int flag = 0;

	tmp = *env;
	while(tmp != NULL)
	{
		if(strcmp(tmp->key, key) == 0)
		{

			free(tmp->value);
			if(value != NULL)
				tmp->value = strdup(value);
			else
				tmp->value = strdup(" ");
			flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if(!flag)
	{
		new = malloc(sizeof(t_env));
		if(!new)
			return ;
		new->key = strdup(key);
		if(value != NULL)
			new->value = strdup(value);
		else
			new->value = strdup("");
		new->next = NULL;

	ft_lstadd_back(env, new);
	}
}
int check_syntax_expo(char **str)
{
	int i = 0;
	int j = 0;
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if(str[i][j] == '+' && str[i][j+1] == '=')
				return (j);
			j++;
		}
		i++;
	}
	return (0);
}
int len_string(char *str)
{
	int i = 0;
	while(str[i] && str[i] != '=')
		i++;
	int j = 0;
	while(str[i])
	{
		i++;
		j++;
	}
	return (j);
}
void ft_export(char **str)
{
	t_env	*helper = NULL;
	char	**spliting_input;
	char	*key;
	char	*value;
	char	*old_value;
	char	*new_value;
	int		append_mode = 0;
	int		i;

	if (!str[2])
		return;

	// Check if the argument contains +=
	i = check_syntax_expo(str);
	if (i != 0)
	{
		append_mode = 1;
		key = ft_substr(str[2], 0, i);
		value = ft_substr(str[2], i + 2, strlen(str[2]) - (i + 2));
	}
	else
	{
		spliting_input = ft_split(str[2], '=');
		key = strdup(spliting_input[0]);
		value = spliting_input[1] ? strdup(spliting_input[1]) : NULL;
	}

	if (!is_valide_key(key))
	{
		free(key);
		if (value)
			free(value);
		return;
	}

	if (append_mode)
	{
		t_env *tmp = helper;
		while (tmp)
		{
			if (strcmp(tmp->key, key) == 0)
			{
				old_value = tmp->value ? tmp->value : strdup("");
				new_value = malloc(strlen(old_value) + strlen(value) + 1);
				if (new_value)
				{
					strcpy(new_value, old_value);
					strcat(new_value, value);
					free(tmp->value);
					tmp->value = new_value;
				}
				free(key);
				free(value);
				return;
			}
			tmp = tmp->next;
		}
		// If not found, just add as new
		add_or_update(&helper, key, value);
	}
	else
	{
		add_or_update(&helper, key, value);
	}

	free(key);
	if (value)
		free(value);
}

// void ft_export(char **str)
// {
//     char	**spliting_input;
//     t_env	*helper = NULL;
// 	char	*handel_plus;
// 	int		i;

// 	i = check_syntax_expo(str[2]);
//     if(i != 0)
// 	{
// 		handel_plus = ft_substr(str[2], 0, i);

// 	}
// 		// spliting_input = ft_split(str[2], '+=');
// 	else
// 		spliting_input = ft_split(str[2], '=');
//     if (!is_valide_key(spliting_input[0]))
// 	{
//         return ;
// 	}
// 	// t_env *node1;
// 	// node1 = malloc(sizeof(t_env));
// 	// node1->key = strdup("var");
// 	// node1->value = strdup("1111");
// 	// node1->next = NULL;
	
// 	// helper = node1;

// 	// t_env *node2 ;
// 	// node2 = malloc(sizeof(t_env));
// 	// node2->key = strdup("22222");
// 	// node2->value = strdup("222222");
// 	// node2->next = NULL;
// 	// node1->next = node2;

// 	// t_env *node3;
// 	// node3 = malloc(sizeof(t_env));
// 	// node3->key = strdup("3333333");
// 	// node3->value = strdup("333333");
// 	// node3->next = NULL;
// 	// node2->next = node3;

// 	// t_env *tmp;

// 	add_or_update(&helper, spliting_input[0], spliting_input[1]);
// 	// tmp = helper;
// 	// while(tmp)
// 	// {
// 	// 	printf("this is key ====%s\n", tmp->key);
// 	// 	printf("this is value ====%s\n", tmp->value);
// 	// 	tmp = tmp->next;
// 	// }
// }
int main(int ac, char **av)
{
	// int i = 0;
	if(ac < 1)
		return (0);
	// echo(av);
	// pwd(ac, av);
	// cd(av[2]);
	// if(strcmp(av[1], "export") == 0)
	// {
		
	t_env *helper;
	t_env *node1;
	node1 = malloc(sizeof(t_env));
	node1->key = strdup("var");
	node1->value = strdup("1111");
	node1->next = NULL;
	
	helper = node1;

	t_env *node2 ;
	node2 = malloc(sizeof(t_env));
	node2->key = strdup("22222");
	node2->value = strdup("222222");
	node2->next = NULL;
	node1->next = node2;

	t_env *node3;
	node3 = malloc(sizeof(t_env));
	node3->key = strdup("3333333");
	node3->value = strdup("333333");
	node3->next = NULL;
	node2->next = node3;

	t_env *tmp;
	tmp = helper;
	ft_export(av);
	while(tmp)
	{
		printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
	// }

}
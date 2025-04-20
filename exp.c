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
int	is_valid_key(char *key)
{
	int i;

	if (!key || (!((key[0] >= 'a' && key[0] <= 'z') || 
	               (key[0] >= 'A' && key[0] <= 'Z') || 
	               key[0] == '_')))
		return (1); // invalid key;;;;

	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!((key[i] >= 'a' && key[i] <= 'z') ||
		      (key[i] >= 'A' && key[i] <= 'Z') ||
		      (key[i] >= '0' && key[i] <= '9') ||
		      key[i] == '_') && key[i] == ' ')
			return (1);
		i++;
	}
	return (0); // valid;;;;
}

t_env *sort_env(t_env **head)
{
    t_env *helper = NULL;
    char *tmp_key;
    char *tmp_value;
    helper = *head;
    while(*head && (*head)->next != NULL)
    {
        if(ft_strcmp((*head)->key, (*head)->next->key) > 0)
        {
            tmp_key = (*head)->key;
            tmp_value = (*head)->value;
            (*head)->key = (*head)->next->key;
            (*head)->value = (*head)->next->value;
            (*head)->next->key = tmp_key;
            (*head)->next->value = tmp_value;
            *head = helper;
        }
        else
            *head = (*head)->next;
    }
    return (helper);
}

char *get_value(char *str) // spleted value;
{
    int i = 0;
    int tmp = 0;
    unsigned int len = 0;
    char *helper = NULL;
    while(str[i] && str[i] != '=' && str[i] != '+')
    i++;
    while(str[i] == '=' || str[i] == '+')
    i++;
    tmp = i;
    while(str[i])
    {
        len++;
        i++;
    }
    helper = ft_substr(str, tmp, len);
    if (!helper)
    return (NULL);
    return (helper);
}
char    *get_key(char *str)  // spleted key;
{
    unsigned int i = 0;
    while(str[i])
    {
        if(str[i] == '+' && str[i + 1] == '=')
        break ;
        if (str[i] == '=')
        break ;
        i++;
    }
    char *helper = ft_substr(str, 0, i);
    if(!helper)
    return (NULL);
    return (helper);
}

char *get_env_var(char *key, t_env **list) // this for searche varible of any key;;
{
    t_env   *tmp;
    
    tmp = *list;
    while(tmp)
    {
        if(ft_strcmp(tmp->key, key) == 0)
        return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void check_append(char *str, t_env **lst)
{
    int i = 0;
    t_env *tmp;

    tmp = *lst;
    while (str[i])
    {
        if (str[i] == '+' && str[i + 1] == '=')
        {
            tmp->operation = '+';
            return ;
        }
        else if (str[i] == '=')
        {
            tmp->operation = '=';
            return ;
        }
        i++;
    }
}

void    set_env(t_env **env, char *key, char *value)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if(ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
                tmp->value = ft_strjoin(tmp->value, value);
		}
		tmp = tmp->next;
	}
}

// void is_not_key_here(t_env **env, char *key, char *value)
// {
//     t_env *tmp;

//     tmp = *env;
// 	while(tmp)
// 	{
// 		if(ft_strcmp(tmp->key, key) == 0)
// 		{
// 			if (tmp->value)
//                 tmp->value = ft_strjoin(tmp->value, value);
// 			return (tmp->value);
// 		}
// 		tmp = tmp->next;
// 	}
// }
int ft_ex(char **str, t_env **lst)
{
    int i = 0;

    char *key = NULL;
    char *value = NULL;
    t_env *tmp;

    tmp = *lst;
    while(str[i])
    {
        key = get_key(str[i]);
        if(is_valid_key(key) == 1)
            return (1);
        value = get_value(str[i]);      
        check_append(str[i], lst);
        // printf("%d\n", tmp->operation);
        if(tmp->operation == '+')
        {
            set_env(lst, key, value);
            // retrun (0);
        }
        else
            updat_env(lst, key, value);
        i++;
    }
    return (0);
}
// void ft_ex(char **str, t_env **lst)
// {
//     int i = 0;

//     char *key = NULL;
//     char *value = NULL;
//     t_

//     while(str[i])
//     {
//         if(check_syntax_expo())
//         key = get_key(str[i]);
//         value = get_value(str[i]);      
//         updat_env(lst, key, value);
//         i++;
//     }
// }
void ft_export( char **str, t_env **env_list)
{
    *env_list = sort_env(env_list);
    if(!str[1])
    {
        t_env *tmp = *env_list;
        while(tmp)
        {
            printf("declare -x %s=%s\n", tmp->key, tmp->value);
            tmp = tmp->next;
        }
    }
    else
    {
        // if(is_valid_key(str[1]) == 1)
        // {
        //     printf("hehehehe\n");
        //     printf("minishell: export: %s : not valid identifier\n", str[1]);
        //     return ;
        // }
            if(ft_ex(str + 1, env_list) == 1)
            {
            // printf("hehehehe\n");
                printf("minishell: export: %s : not valid identifier\n", str[1]);
            return ;     
            }
    }
}


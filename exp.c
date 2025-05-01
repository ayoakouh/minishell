#include "minishell.h"

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
	return (0);
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


int check_append(char *str)
{
    int i = 0;
    
    while (str[i])
    {
        if (str[i] == '+' && str[i + 1] == '=')
        {
            return ('+');
        }
        else if (str[i] == '=')
        {
            return ('=');
        }
        i++;
    }
    return (0);
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
            tmp->operation = 0;
		}
		tmp = tmp->next;
	}
}

void  ft_handel_export(char **str, t_env **lst)
{
    int i = 0;
    
    char *key = NULL;
    char *value = NULL;

    while(str[i])
    {
        key = get_key(str[i]);
        if(is_valid_key(key) == 1)
            printf("minishell: export: %s : not valid identifier\n", str[1]);
        value = get_value(str[i]);
        int c = check_append(str[i]);
        if(c == '+')
        { 
            printf("00000\n");
            set_env(lst, key, value);
        }
        else if (c == '=')
        {
            printf("11111\n");
            updat_env(lst, key, value);
        }
        else
        {
            printf("333333\n");
            value_empty(lst, key, value);
        }
        i++;
    }
    
}

void ft_export(char **str, t_env **env_list)
{
    *env_list = sort_env(env_list);
    if(!str[1])
    {
        t_env *tmp = *env_list;
        while(tmp)
        {
            if(tmp->operation == 1)
            printf("declare -x %s\n", tmp->key);
            else
            {
                printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
            }
            tmp = tmp->next;
        }
    }
    else
    {
        ft_handel_export(str + 1, env_list);
        return;     
    }
}

                
// char *get_env_var(char *key, t_env **list) // this for searche varible of any key;;
// {
//     t_env   *tmp;
                    
//     tmp = *list;
//     while(tmp)
//     {
                //         if(ft_strcmp(tmp->key, key) == 0)
                //         return (tmp->value);
                //         tmp = tmp->next;
                //     }
                //     return (NULL);
                // }
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
int check_syntax_expo(char *str)
{
	int i = 0;

	while(str[i])
	{
        if(str[i] == '+' && str[i + 1] == '=')
            return (i);
        i++;
    }
    return(0);
}

// void add_or_update(t_env **env, char *key, char *value) //add_environment;
// {
// 	t_env	*tmp;
// 	t_env	*new = NULL;
// 	int flag = 0;

// 	tmp = *env;
// 	while(tmp != NULL)
// 	{
// 		if(strcmp(tmp->key, key) == 0)
// 		{

// 			free(tmp->value);
// 			if(value != NULL)
// 				tmp->value = strdup(value);
// 			else
// 				tmp->value = strdup(" ");
// 			flag = 1;
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if(!flag)
// 	{
// 		new = malloc(sizeof(t_env));
// 		if(!new)
// 			return ;
// 		new->key = strdup(key);
// 		if(value != NULL)
// 			new->value = strdup(value);
// 		else
// 			new->value = strdup("");
// 		new->next = NULL;

// 	ft_lstadd_back(env, new);
// 	}
// }
void add_or_update(t_env **env, char *key, char *value) //add_environment
{
    t_env *tmp;
    t_env *new = NULL;
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
                tmp->value = strdup(""); // Use empty string for consistency
            
            if(!tmp->value) // Check if strdup failed
                return; // Handle error appropriately
                
            flag = 1;
            break;
        }
        tmp = tmp->next;
    }
    if(!flag)
    {
        new = malloc(sizeof(t_env));
        if(!new)
            return;
            
        new->key = strdup(key);
        if(!new->key) {
            free(new);
            return;
        }
        
        if(value != NULL)
            new->value = strdup(value);
        else
            new->value = strdup("");
            
        if(!new->value) {
            free(new->key);
            free(new);
            return;
        }
        
        new->next = NULL;
        ft_lstadd_back(env, new);
    }
}
void ft_ex(char **str, t_env **lst)
{
    char **spliting_input;
    int  i = 0;
    char *key = NULL;
    char *value = NULL;

    if(!str[1])
        return;

    i = check_syntax_expo(str[1]);
    if (i != 0)
    {
        // Handle "+=" syntax
        key = ft_substr(str[1], 0, i);
        value = ft_substr(str[1], i + 2, strlen(str[1]) - (i + 2));
        
        if (!key || !value) {
            free(key);
            free(value);
            return;
        }
    }
    else
    {
        spliting_input = ft_split(str[1], '=');
        if (!spliting_input)
            return;

        if (!spliting_input[0]) {
            free(spliting_input);
            return;
        }
        
        // Make copies of the strings so we can free spliting_input safely
        key = strdup(spliting_input[0]);
        value = spliting_input[1] ? strdup(spliting_input[1]) : strdup("");
        
        // Free the split result
        int j = 0;
        while (spliting_input[j]) {
            free(spliting_input[j]);
            j++;
        }
        free(spliting_input);
        
        if (!key || !value) {
            free(key);
            free(value);
            return;
        }
    }
    
    if (!is_valide_key(key))
    {
        free(key);
        free(value);
        return;
    }
    
    add_or_update(lst, key, value);
    
    // Free our copies since add_or_update makes its own copies
    free(key);
    free(value);
}
// void ft_ex(char **str, t_env **lst)
// {
//     t_env   *helper;
//     char    **spliting_input;
//     int     i = 0;

//     helper = *lst;
//         printf("hehhdhdhdh\n");
//     if(!str[1])
//         return ;
//     i = check_syntax_expo(str[1]);
// 	if (i != 0)
// 	{
// 		helper->defined = 1;
// 		helper->key = ft_substr(str[1], 0, i);
// 		helper->value = ft_substr(str[1], i + 2, strlen(str[1]) - (i + 2));
// 	}
//     else
//     {
//         spliting_input = ft_split(str[1], '=');
// 		printf("%s\n", spliting_input[0]);
// 		// if(!spliting_input[0] || spliting_input[1] || !spliting_input)
// 		// {
// 		// 	free(spliting_input[0]);
// 		// 	free(spliting_input[1]);
// 		// 	free(spliting_input);
// 		// }
// 		// printf("%s\n", spliting_input[1]);
//         helper->key = spliting_input[0];
//         helper->value = spliting_input[1];
//     }
// 	// if (!is_valide_key(helper->key))
// 	// {
// 	// 	free(helper->key);
// 	// 	if (helper->value)
// 	// 		free(helper->value);
// 	// 	return ;
// 	// }
//     add_or_update(lst, helper->key, helper->value);
// }
void ft_export(char *env[], char **str, t_env **env_list)
{
    if(!str[1])
    {
        // Display sorted environment variables
        t_env *display_list = NULL;
        display_list = env_maker(env, &display_list);
        display_list = sort_env(&display_list);
        t_env *tmp = display_list;
        while(tmp)
        {
            printf("declare -x %s=%s\n", tmp->key, tmp->value);
            tmp = tmp->next;
        }
        // Free the temporary display list
        // ...
    }
    else
    {
        ft_ex(str, env_list);  // Pass the actual environment list
    }
}
// void ft_export(char *env[], char **str)
// {
//     t_env *list = NULL;
//     if(!str[1])
//     {
//         list = env_maker(env, &list);
//         list = sort_env(&list);
//         t_env *tmp = list;
//         while(tmp)
//         {
//             printf("declare -x %s=%s\n", tmp->key, tmp->value);
//             tmp = tmp->next;
//         }
//     }
// 	else
// 	{
// 		ft_ex(str, &list);
// 	}

// }





// void ft_export(t_env **list, )



// int start_with_export(char *str)
// {
//     int i = 0;

//     if(strcmp(str, "export"))
//         return (0);
//     else
//         return (1);
// }

// char **spliting_string(char *str)
// {
//     char **helper;
//     if(!strchr(str, '+'))
//         helper = ft_split(str, '=');
//     else
//     {
        
//     }

// }
// void handel_export(char **arg)
// {

// }





// int main(int ac, char **av)
// {
//     while(1)
//     {
//         char *input = readline("minishell$ ");
//         if(!input)
//             break;
//         if(input)
//             add_history(input);
//         if(!start_with_export(input))
//             handel_export(input);
//         free(input);
//     }

// }

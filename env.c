
#include "minishell.h"



int ft_strlen(const char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return i;
}
char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	int		s_len;
	char	*dup;

	i = 0;
	j = 0;
	s_len = ft_strlen(s);
	dup = (char *)malloc(s_len + 1);
	if (dup == NULL)
	{
		return (NULL);
	}
	while (s[i] != '\0')
	{
		dup[j] = s[i];
		j++;
		i++;
	}
	dup[j] = '\0';
	return (dup);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}


// static char	**free_split(char **split, size_t j)
// {
// 	while (j > 0)
// 		free(split[--j]);
// 	free(split);
// 	return (NULL);
// }

// static size_t	count_words(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	n;

// 	i = 0;
// 	n = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && (i == 0 || s[i - 1] == c))
// 			n++;
// 		i++;
// 	}
// 	return (n);
// }

// static char	**split_string(char const *s, char c, char **split, size_t n)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	start;
// 	size_t	len;

// 	i = 0;
// 	j = 0;
// 	while (s[i] && j < n)
// 	{
// 		while (s[i] == c)
// 			i++;
// 		start = i;
// 		while (s[i] && s[i] != c)
// 			i++;
// 		len = i - start;
// 		split[j] = (char *)malloc(len + 1);
// 		if (!split[j])
// 			return (free_split(split, j));
// 		ft_memcpy(split[j], &s[start], len);
// 		split[j][len] = '\0';
// 		j++;
// 	}
// 	split[j] = NULL;
// 	return (split);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t	n;
// 	char	**split;

// 	if (s == NULL)
// 		return (NULL);
// 	n = count_words(s, c);
// 	split = (char **)malloc((n + 1) * sizeof(char *));
// 	if (split == NULL)
// 		return (NULL);
// 	return (split_string(s, c, split, n));
// }


void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
		temp = *lst;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
}


t_env *env_node_maker(char *env[])
{
    t_env *env_node;

    env_node = malloc(sizeof(t_env));
    if (!env_node)
        return NULL;
        
    if (!env || !env[0])
        env_node->key = NULL;
    else
        env_node->key = ft_strdup(env[0]);
        
    if (!env || !env[1])
        env_node->value = NULL;
    else
        env_node->value = ft_strdup(env[1]);
        
    env_node->next = NULL;
    return env_node;

}

t_env *env_maker(char *env[], t_env **env_struct)
{
    // t_env *tmp;
    t_env *env_list = NULL;
    int i = 0;
    int j = -1;
    char **split;

    while (env[i])
    {
        j = -1;
        split = ft_split(env[i], '=');
        if (split)
        {
            ft_lstadd_back_env(&env_list,  env_node_maker(split));
            while (split[++j])
                free((split[j]));
            free(split);
        }
        i++;
    }
    *env_struct = env_list;
	return (*env_struct);
}
// int main(int argc, char *argv[], char *env[])
// {
// 	if(argc < 0 && argv == NULL)
// 		return 0;
		
//     t_env *env_struct = NULL;   //// add to the final main
//     t_env *tmp;
//     t_env *tmp2;

//     env_maker(env, &env_struct);    //// add to the final main
//     tmp = env_struct;
//     while (tmp)
//     {
//         if (tmp->key && tmp->value)
//             printf("%s=%s\n", tmp->key, tmp->value);
//         tmp = tmp->next;
//     }


//     tmp = env_struct;        /// make a func that do this 
//     while (tmp)
//     {
//         tmp2 = tmp->next;
//         if (tmp->key)
//             free(tmp->key);
//         if (tmp->value)
//             free(tmp->value);
//         free(tmp);
//         tmp = tmp2;
//     }  
// }



//******************>>>>>>>>>>><<<<<<<<<<<<*****************
// t_env *add_to_env(char **helper)
// {
//     t_env *head;
//     char **spliting;
//     t_env new_node;
//     int i =0;
//     if(!helper)
//         return (NULL);
//     head = malloc(sizeof(t_env));
//     if(!head)
//         return (NULL);
//     spliting = ft_split(helper[0], '=');
//     head->key = spliting[0];
//     head->value = spliting[1];
//     head ->next = NULL;
//     free(spliting);
//     i = 1;
//     while(helper[i])
//     {
//         spliting = ft_split(helper[i], '=');
//         if(!spliting)
//             return (NULL);
//         new_node = malloc(sizeof(t_env));
        
//     }

// }


    // t_env *helper = NULL;
    // ft_env(helper);

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
int check_syntax_expo(char *str)
{
	int i = 0;
	int j = 0;
	while(str[i])
	{
        if(str[i] == '+' && str[i + 1] == '=')
            return (i);
        i++;
    }
    return(0);
}
void add_or_update()
{
    
}
void ft_export(char **str)
{
    t_env   *helper = NULL;
    char    **spliting_input;
    int     i = 0;

    if(!str[2])
        return ;
    i = check_syntax_expo(str[2]);
	if (i != 0)
	{
		helper->defined = 1;
		helper->key = ft_substr(str[2], 0, i);
		helper->value = ft_substr(str[2], i + 2, strlen(str[2]) - (i + 2));
	}
    else
    {
        spliting_input = ft_split(str[2], '=');
        helper->key = strdup(spliting_input[0]);
        helper->value = strdup(spliting_input[1]);
    }
	if (!is_valide_key(helper->key))
	{
		free(helper->key);
		if (helper->value)
			free(helper->value);
		return;
	}
}

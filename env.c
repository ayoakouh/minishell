
#include "minishell.h"

// void    ft_env(t_env *h)
// {
//     while (h != NULL)
//     {
//         printf("%s=%s\n", h->key, h->value);
//         h = h->next;
//     }
// }
t_env *add_to_env(char **helper)
{
    t_env *head;
    char **spliting;
    t_env new_node;
    int i =0;
    if(!helper)
        return (NULL);
    head = malloc(sizeof(t_env));
    if(!head)
        return (NULL);
    spliting = ft_split(helper[0], '=');
    head->key = spliting[0];
    head->value = spliting[1];
    head ->next = NULL;
    free(spliting);
    i = 1;
    while(helper[i])
    {
        spliting = ft_split(helper[i], '=');
        if(!spliting)
            return (NULL);
        new_node = malloc(sizeof(t_env));
        
    }

}
int main(int ac, char **av, char **env)
{
    int i = 0;
    int j = 0;
    if(ac < 0)
        return (0);
    
    while(env[i])
    {
        printf("====%s\n", env[0]);
        i++;
    }
}

    // t_env *helper = NULL;
    // ft_env(helper);

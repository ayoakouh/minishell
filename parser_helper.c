#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

void *ft_memcpy_q(void *dest, const void *src, size_t n)
{
    unsigned char        *d;
    const unsigned char    *s;
    size_t                i;

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



static size_t count_words_q(char const *s, char c)
{
    size_t i;
    size_t n;
    int quote_state; /* 0: no quote, 1: single quote, 2: double quote */

    i = 0;
    n = 0;
    quote_state = 0;
    while (s[i])
    {
        while (s[i] == c && quote_state == 0)
            i++;
        if (s[i])
            n++;
        while (s[i])
        {
            if (s[i] == '\'')
            {
                if (quote_state == 0)
                    quote_state = 1;
                else if (quote_state == 1)
                    quote_state = 0;
            }
            else if (s[i] == '\"')
            {
                if (quote_state == 0)
                    quote_state = 2;
                else if (quote_state == 2)
                    quote_state = 0;
            }
            if (s[i] == c && quote_state == 0)
                break;
            i++;
        }
    }
    return (n);
}

static char **split_string_q(char const *s, char c, char **split, size_t n)
{
    size_t i = 0;
    size_t j = 0;
    size_t start;
    size_t len;
    int quote_state = 0; /* 0: no quote, 1: single quote, 2: double quote */

    while (s[i] && j < n)
    {
        while (s[i] == c && quote_state == 0)
            i++;
        start = i;
        
        /* Find end of word (considering quotes) */
        while (s[i])
        {
            /* Update quote state */
            if (s[i] == '\'')
            {
                if (quote_state == 0)
                    quote_state = 1;
                else if (quote_state == 1)
                    quote_state = 0;
            }
            else if (s[i] == '\"')
            {
                if (quote_state == 0)
                    quote_state = 2;
                else if (quote_state == 2)
                    quote_state = 0;
            }
            
            /* Break if we hit delimiter outside quotes */
            if (s[i] == c && quote_state == 0)
                break;
            i++;
        }
        
        len = i - start;
        if (len > 0) /* Ensure we have content to copy */
        {
            split[j] = (char *)malloc(len + 1);
            if (!split[j])
                return (free_split_q(split, j));
            ft_memcpy_q(split[j], &s[start], len);
            split[j][len] = '\0';
            j++;
        }
    }
    split[j] = NULL;
    return (split);
}

char **ft_split_q(char const *s, char c)
{
    size_t n;
    char **split;

    if (s == NULL)
        return (NULL);
    n = count_words_q(s, c);
    split = (char **)malloc((n + 1) * sizeof(char *));
    if (split == NULL)
        return (NULL);
    return (split_string_q(s, c, split, n));
}

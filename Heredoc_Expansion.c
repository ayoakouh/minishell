/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc_Expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:29:41 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/29 09:49:07 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_dir(int dir_size)
{
	char			**dir;

	dir = malloc(sizeof(char *) * (dir_size + 1));
	if (dir == NULL)
		return (NULL);
	dir[0] = ft_strdup("/mnt/homes/ayoakouh/");
	dir[1] = ft_strdup("/mnt/homes/ayoakouh/Pictures/");
	dir[2] = ft_strdup("/mnt/homes/ayoakouh/Library/Application Support/");
	dir[3] = ft_strdup("/tmp/");
	dir[4] = ft_strdup("/var/tmp/");
	dir[5] = ft_strdup("/Users/Shared/");
	dir[6] = ft_strdup("/mnt/homes/ayoakouh/Desktop/");
	dir[7] = ft_strdup("/mnt/homes/ayoakouh/Documents/");
	dir[8] = ft_strdup("/mnt/homes/ayoakouh/Downloads/");
	dir[9] = ft_strdup("/mnt/homes/ayoakouh/Library/");
	dir[10] = ft_strdup("/mnt/homes/ayoakouh/Library/Caches/");
	dir[11] = ft_strdup("/mnt/homes/ayoakouh/Library/Preferences/");
	dir[12] = ft_strdup("/mnt/homes/ayoakouh/Movies/");
	dir[13] = ft_strdup("/mnt/homes/ayoakouh/Music/");
	dir[14] = NULL;
	return (dir);
}

char	*open_urandom_failed(int dir_size, char **dir, unsigned char *raw_bytes)
{
	write(2, "Error opening /dev/urandom\n", 27);
	free_dir(0, dir_size, dir);
	free(dir);
	free(raw_bytes);
	return (NULL);
}

char	*read_urandom_failed(int fd, int dir_size,
			char **dir, unsigned char *raw_bytes)
{
	close(fd);
	free_dir(0, dir_size, dir);
	free(dir);
	free(raw_bytes);
	return (NULL);
}

void	clean_up(int fd, int dir_size, char **dir, unsigned char	*raw_bytes)
{
	close(fd);
	free_dir(0, dir_size, dir);
	free(dir);
	free(raw_bytes);
}

char	*random_dir(void)
{
	char			**dir;
	int				fd;
	unsigned char	*raw_bytes;
	char			*result;
	static int		i;

	raw_bytes = malloc(sizeof(unsigned char) * 5);
	if (raw_bytes == NULL)
		return (NULL);
	dir = init_dir(14);
	if (dir == NULL)
		return (free(raw_bytes), NULL);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (open_urandom_failed(14, dir, raw_bytes));
	if (read(fd, raw_bytes, 5) != 5)
		return (read_urandom_failed(fd, 14, dir, raw_bytes));
	result = ft_strdup(dir[raw_bytes[i] % 14]);
	i = (i + 1) % 5;
	clean_up(fd, 14, dir, raw_bytes);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melisportakal <melisportakal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:56:50 by atasyure          #+#    #+#             */
/*   Updated: 2023/12/21 19:10:09 by melisportak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_copy_to_repo(char *repo, char *buf)
{
	char	*result;

	result = 0;
	if (!repo && buf)
	{
		result = ft_strdup(buf);
		if (!result)
			return (NULL);
		return (result);
	}
	result = ft_strjoin(repo, buf);
	ft_free_repo(&repo, 0);
	return (result);
}

static int	newline_checkk(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i] != '\0')
		if (s[i] == '\n')
			return (1);
	return (0);
}

static char	*ft_extract_line(char *repo)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!repo)
		return (ft_free_repo(&repo, 0));
	while (repo[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (ft_free_repo(&line, 0));
	j = 0;
	while (j < i + 1)
	{
		line[j] = repo[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_recreate_repo(char *repo)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!repo)
		return (NULL);
	while (repo[i] != '\n')
		i++;
	if (repo[i + 1] == '\0')
		return (ft_free_repo(&repo, 0));
	res = ft_substr(repo, i + 1, ft_strlen(repo));
	if (!res)
	{
		ft_free_repo(&repo, 0);
		return (NULL);
	}
	ft_free_repo(&repo, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	long		check;
	static char	*repo = NULL;
	char		*line;

	line = 0;
	check = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_repo(&repo, 0));
	while (check > 0)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if ((check <= 0 && !repo) || check == -1)
			return (ft_free_repo(&repo, 0));
		buf[check] = '\0';
		repo = ft_copy_to_repo(repo, buf);
		if (newline_checkk(repo))
		{
			line = ft_extract_line(repo);
			if (!line)
				return (ft_free_repo(&repo, 0));
			return (repo = ft_recreate_repo(repo), line);
		}
	}
	return (ft_free_repo(&repo, 1));
}


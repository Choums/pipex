/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:51:30 by chaidel           #+#    #+#             */
/*   Updated: 2022/03/23 12:54:36 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (s && fd >= 0)
	{
		len = ft_strlen(s);
		write(fd, s, len);
		return (len);
	}
	return (len);
}

size_t	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (s && fd >= 0)
	{
		len = ft_putstr_fd(s, fd);
		write(fd, "\n", 1);
		return (len + 1);
	}
	return (len);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (dest[n])
		n++;
	while (src[i])
	{
		dest[n + i] = src[i];
		i++;
	}
	dest[n + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	return (str);
}

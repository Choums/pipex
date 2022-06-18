/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_sec_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:55:12 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/01 12:43:03 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(*to_find))
		return ((char *)(str));
	while (str[i] && i < len)
	{
		j = 0;
		while ((str[i + j] == to_find[j]) && (i + j) < len)
		{
			if (!to_find[j + 1] || j == len)
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		len = 0;
	else if ((size_t)start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size <= 0)
		return (src_len);
	if (src_len >= size)
		src_len = size - 1;
	ft_memcpy(dst, src, src_len);
	dst[src_len] = '\0';
	return (ft_strlen(src));
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*tmp_dst;
	char	*tmp_src;
	size_t	i;

	tmp_dst = (char *)dest;
	tmp_src = (char *)src;
	if (!tmp_dst && !tmp_src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (dest);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	i = 0;
	while ((tmp_s1[i] == tmp_s2[i]) && tmp_s1[i] && tmp_s2[i])
		i++;
	return (tmp_s1[i] - tmp_s2[i]);
}

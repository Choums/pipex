/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:25:07 by chaidel           #+#    #+#             */
/*   Updated: 2021/11/29 19:18:58 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_free_tab(char **split, size_t i)
{
	while (split[i])
	{
		free(split[i]);
		i--;
	}
	free(split);
	return (NULL);
}

static	size_t	ft_count_words(char *str, char sep)
{
	size_t	count;

	count = 0;
	while (*str == sep && *str)
		str++;
	while (*str)
	{
		count++;
		while (*str != sep && *str)
			str++;
		while (*str == sep && *str)
			str++;
	}
	return (count);
}

static	void	ft_get_to_next_word(char **str, char sep, size_t *len)
{
	*str = *str + *len;
	while (**str == sep && **str)
		(*str)++;
	*len = 0;
	while ((*str)[*len] != sep && (*str)[*len])
		(*len)++;
}

char	**ft_split(char const *s, char sep)
{
	char	**split;
	char	*tmp_s;
	size_t	word_len;
	size_t	num;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	word_len = 0;
	tmp_s = (char *)s;
	num = ft_count_words(tmp_s, sep);
	split = ft_calloc(num + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split[num] = NULL;
	while (i < num)
	{
		ft_get_to_next_word(&tmp_s, sep, &word_len);
		split[i] = (char *)ft_calloc(word_len + 1, sizeof(char));
		if (!split[i])
			return (ft_free_tab(split, i));
		ft_memcpy(split[i++], tmp_s, word_len);
	}
	return (split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:37:59 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:06:23 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cpy_next_word(const char *s, char c, char **tab_out, int i_word);

static int	ft_count_words(const char *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**tab_out;
	int		i_word;
	int		word_len;

	tab_out = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (tab_out == NULL)
		return (NULL);
	i_word = 0;
	while (*s)
	{
		if (*s == c)
		{	
			s++;
			continue ;
		}
		word_len = ft_cpy_next_word(s, c, tab_out, i_word);
		if (word_len == 0)
			return (NULL);
		i_word++;
		s += word_len;
	}
	tab_out[i_word] = NULL;
	return (tab_out);
}

static int	ft_cpy_next_word(const char *s, char c, char **tab_out, int i_word)
{	
	int	word_len;

	word_len = 0;
	while (s[word_len] && s[word_len] != c)
		word_len++;
	tab_out[i_word] = (char *)malloc(word_len + 1);
	if (tab_out[i_word] == NULL)
	{	
		while (i_word--)
			free(tab_out[i_word]);
		free(tab_out);
		return (0);
	}
	ft_strlcpy(tab_out[i_word], s, word_len + 1);
	return (word_len);
}

static int	ft_count_words(char const *s, char c)
{	
	int	flag_sep;
	int	n_word;

	flag_sep = 1;
	n_word = 0;
	while (*s)
	{
		if (*s == c)
		{	
			flag_sep = 1;
			s++;
			continue ;
		}
		if (flag_sep == 1)
			n_word++;
		flag_sep = 0;
		s++;
	}
	return (n_word);
}

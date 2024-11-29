/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:15:10 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/27 13:17:54 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	while (i < size && dst[i])
		i++;
	if (i < size)
		l = i + ft_strlen(src);
	else
		return (size + ft_strlen(src));
	j = 0;
	while (i + 1 < size && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (l);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (!size)
		return (srclen);
	i = size;
	while (--i && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (srclen);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	new = malloc(size * nmemb);
	if (!new)
		return (NULL);
	memset(new, 0, nmemb * size);
	return (new);
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*join;
	size_t	size;

	size = ft_strlen(str1) + ft_strlen(str2) + 1;
	join = ft_calloc(sizeof(char), size);
	if (!join)
		return (NULL);
	ft_strlcat(join, str1, size);
	ft_strlcat(join, str2, size);
	return (join);
}

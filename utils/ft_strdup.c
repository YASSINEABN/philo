/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:01:48 by yaboulan          #+#    #+#             */
/*   Updated: 2024/06/09 22:01:49 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		*d;
	int					i;

	if (dest == src)
		return (dest);
	i = 0;
	ptr = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (n == 0)
		return (d);
	if (n > 0)
	{
		while (n-- > 0)
		{
			d[i] = ptr[i];
			i++;
		}
		return ((char *)dest);
	}
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		n;
	char	*ptr;

	n = ft_strlen((char *)str);
	ptr = (char *)malloc(n + 1);
	if (ptr != NULL)
	{
		ft_memcpy(ptr, str, n);
		ptr[n] = '\0';
		return (ptr);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:01:33 by yaboulan          #+#    #+#             */
/*   Updated: 2024/06/09 22:01:37 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *pt)
{
	int			negative_sign;
	int			i;
	long long	result;

	result = 0;
	i = 0;
	negative_sign = 1;
	while (pt[i] && (pt[i] == ' ' || (pt[i] >= '\t' && pt[i] <= '\r')))
		i++;
	if (pt[i] == '-' || pt[i] == '+')
	{
		if (pt[i] == '-')
			negative_sign *= -1;
		i++;
	}
	while (pt[i] >= '0' && pt[i] <= '9')
	{
		result = result * 10 + pt[i] - 48;
		i++;
	}
	if (result > 9223372036854775807 && negative_sign == -1)
		return (-1);
	else if (result < -9223372036854775807 && negative_sign == 1)
		return (-1);
	return (negative_sign * result);
}

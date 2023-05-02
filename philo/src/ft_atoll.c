/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 14:43:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 01:02:23 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoll(const char *str)
{
	int			i;
	long long	res;
	int			flag;

	flag = 1;
	res = 0;
	i = 0;
	if (str[i] == '-')
	{
		i++;
		flag = -1;
	}
	while (('0' <= str[i] && str[i] <= '9') && str[i] != '\0')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * flag);
}

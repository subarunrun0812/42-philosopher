/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:34:32 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 00:58:40 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	arg_check(int argc, char **argv)
{
	if ((ft_atoll(argv[1]) <= 0 || INT_MAX < ft_atoll(argv[1])
			|| ft_atoll(argv[2]) <= 0 || INT_MAX < ft_atoll(argv[2])
			|| ft_atoll(argv[3]) <= 0 || INT_MAX < ft_atoll(argv[3])
			|| ft_atoll(argv[4]) <= 0 || INT_MAX < ft_atoll(argv[4])))
	{
		printf("\x1b[31mError: abnormal value\x1b[0m\n");
		return (false);
	}
	if (argc == 6)
	{
		if (ft_atoll(argv[5]) <= 0 || INT_MAX < ft_atoll(argv[5]))
		{
			printf("\x1b[31mError: abnormal value\x1b[0m\n");
			return (false);
		}
	}
	return (true);
}

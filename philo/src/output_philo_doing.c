/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_philo_doing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:34:36 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 01:02:44 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *str)
{
	if (philo->id == 0)
		printf("\x1b[41m");
	else if (philo->id == 1)
		printf("\x1b[42m");
	else if (philo->id == 2)
		printf("\x1b[43m");
	else if (philo->id == 3)
		printf("\x1b[44m");
	else if (philo->id == 4)
		printf("\x1b[45m");
	else if (philo->id == 5)
		printf("\x1b[46m");
	else if (philo->id == 6)
		printf("\x1b[47m");
	printf("%lld %d %s\x1b[0m\n", get_time_ms() - philo->table->start_time,
		philo->id + 1, str);
}

void	output_philo_doing(t_philo *philo, bool dead_f, char *message)
{
	if (check_dead_flag(philo->table) && !dead_f)
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	print_status(philo, message);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

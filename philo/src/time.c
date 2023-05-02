/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:34:41 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 01:49:28 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ms	get_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	wait_time_for_action(t_table *table, t_ms wait_time)
{
	t_ms	wake_up_time;

	wake_up_time = get_time_ms() + wait_time;
	while (get_time_ms() < wake_up_time)
	{
		pthread_mutex_lock(&table->dead_mutex);
		if (table->dead)
		{
			pthread_mutex_unlock(&table->dead_mutex);
			break ;
		}
		else
			pthread_mutex_unlock(&table->dead_mutex);
		usleep(10);
	}
}

void	wait_until_start_time(t_ms start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}

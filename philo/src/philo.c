/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:03:03 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 01:02:53 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mutexes[philo->fork[0]]);
	output_philo_doing(philo, false, TAKE_FORK1_MSG);
	wait_time_for_action(philo->table, philo->table->die_ms);
	output_philo_doing(philo, false, DEAD_MSG);
	pthread_mutex_unlock(&philo->table->fork_mutexes[philo->fork[0]]);
	return (NULL);
}

static void	philo_output_cycle(t_philo *philo)
{
	get_fork_and_eat_routine(philo);
	sleep_routine(philo);
}

void	*philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->limit_num_of_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->last_eat = philo->table->start_time;
	pthread_mutex_unlock(&philo->eat_time_mutex);
	wait_until_start_time(philo->table->start_time);
	if (philo->table->number_of_philos == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 1)
		think_routine(philo);
	while (check_dead_flag(philo->table) == false)
	{
		philo_output_cycle(philo);
		think_routine(philo);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_doing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:34:38 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 01:02:51 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think_routine(t_philo *philo)
{
	output_philo_doing(philo, false, THINKING_MSG);
	usleep(1000);
}

void	get_fork_and_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mutexes[philo->fork[0]]);
	output_philo_doing(philo, false, TAKE_FORK1_MSG);
	pthread_mutex_lock(&philo->table->fork_mutexes[philo->fork[1]]);
	output_philo_doing(philo, false, TAKE_FORK2_MSG);
	output_philo_doing(philo, false, EATING_MSG);
	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->last_eat = get_time_ms();
	philo->meal_count += 1;
	pthread_mutex_unlock(&philo->eat_time_mutex);
	wait_time_for_action(philo->table, philo->table->eat_ms);
	pthread_mutex_unlock(&philo->table->fork_mutexes[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_mutexes[philo->fork[0]]);
}

void	sleep_routine(t_philo *philo)
{
	output_philo_doing(philo, false, SLEEPING_MSG);
	wait_time_for_action(philo->table, philo->table->sleep_ms);
}

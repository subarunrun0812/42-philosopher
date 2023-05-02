/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:01:59 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 01:25:54 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_exist_dead(t_philo *philo)
{
	t_ms	current_time;
	t_ms	die_ms;

	pthread_mutex_lock(&philo->eat_time_mutex);
	current_time = get_time_ms();
	die_ms = philo->last_eat + philo->table->die_ms;
	pthread_mutex_unlock(&philo->eat_time_mutex);
	if (current_time >= die_ms)
		return (true);
	return (false);
}

static int	find_dead_philo_id(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		if (check_exist_dead(table->philos[i]))
			return (i);
		i++;
	}
	return (-1);
}

static bool	num_of_executions(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_mutex_lock(&table->philos[i]->eat_time_mutex);
		if (table->limit_num_of_eat != -1)
		{
			if (table->philos[i]->meal_count
				< (unsigned int)table->limit_num_of_eat)
			{
				pthread_mutex_unlock(&table->philos[i]->eat_time_mutex);
				return (false);
			}
		}
		pthread_mutex_unlock(&table->philos[i]->eat_time_mutex);
		i++;
	}
	return (true);
}

static void	dead_output(t_table *table, int dead_philo_id)
{
	dead_flag_on(table);
	if (table->limit_num_of_eat != -1 && !num_of_executions(table)
		&& table->number_of_philos > 1)
	{
		output_philo_doing(table->philos[dead_philo_id], true, DEAD_MSG);
	}
	else if (table->limit_num_of_eat == -1 && table->number_of_philos > 1)
	{
		output_philo_doing(table->philos[dead_philo_id], true, DEAD_MSG);
	}
}

void	*death_check(void *data)
{
	t_table	*table;
	int		dead_philo_id;

	table = (t_table *)data;
	wait_until_start_time(table->start_time);
	while (true)
	{
		dead_philo_id = find_dead_philo_id(table);
		if (dead_philo_id != -1)
		{
			dead_output(table, dead_philo_id);
			return (NULL);
		}
		if (table->limit_num_of_eat != -1)
		{
			if (num_of_executions(table))
			{
				dead_flag_on(table);
				return (NULL);
			}
		}
		usleep(100);
	}
}

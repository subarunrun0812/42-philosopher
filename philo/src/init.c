/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:34:27 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 16:25:49 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*create_forks_mutex(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = (pthread_mutex_t *)malloc(table->number_of_philos
			* sizeof(pthread_mutex_t));
	if (!forks)
		return (error(MALLOC_ERR, table));
	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

static bool	init_mutex(t_table *table)
{
	table->fork_mutexes = create_forks_mutex(table);
	if (!table->fork_mutexes)
		return (false);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->dead_mutex, NULL);
	return (true);
}

static void	init_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->number_of_philos;
		philo->fork[1] = philo->id;
	}
	else
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % philo->table->number_of_philos;
	}
}

static t_philo	**create_philo(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = (t_philo **)malloc(table->number_of_philos * sizeof(t_philo));
	if (!philos)
		return (error(MALLOC_ERR, table));
	i = 0;
	while (i < table->number_of_philos)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
			return (error(MALLOC_ERR, table));
		pthread_mutex_init(&philos[i]->eat_time_mutex, NULL);
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->meal_count = 0;
		init_forks(philos[i]);
		i++;
	}
	return (philos);
}

t_table	*init(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (error(MALLOC_ERR, NULL));
	table->number_of_philos = ft_atoll(argv[1]);
	table->die_ms = ft_atoll(argv[2]);
	table->eat_ms = ft_atoll(argv[3]);
	table->sleep_ms = ft_atoll(argv[4]);
	table->limit_num_of_eat = -1;
	if (argc == 6)
		table->limit_num_of_eat = ft_atoll(argv[5]);
	table->philos = create_philo(table);
	if (!table->philos)
		return (NULL);
	if (!init_mutex(table))
		return (NULL);
	table->dead = false;
	return (table);
}

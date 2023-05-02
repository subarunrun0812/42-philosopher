/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:34:28 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 01:02:21 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_mutex_destroy(&table->fork_mutexes[i]);
		pthread_mutex_destroy(&table->philos[i]->eat_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
}

void	*free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (NULL);
	destroy_mutexes(table);
	if (table->fork_mutexes != NULL)
		free(table->fork_mutexes);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->number_of_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return (NULL);
}

int	print_error(int err_num)
{
	if (err_num == ARG_ERR)
	{
		printf("\x1b[31mError: argument\x1b[0m\n");
		printf("1: number_of_philosophers\n");
		printf("2: time_to_die(ms)\n");
		printf("3: time_to_eat(ms)\n");
		printf("4: time_to_sleep(ms)\n");
		printf("option\n5: number_of_times_each_philosopher_must_eat\n");
	}
	else if (err_num == INT_ERR)
		printf("\x1b[31mError: out of range int range\x1b[0m\n");
	else if (err_num == THREAD_ERR)
		printf("\x1b[31mError: thread\x1b[0m\n");
	else if (err_num == MUTEX_ERR)
		printf("\x1b[31mError: mutex\x1b[0m\n");
	else if (err_num == MALLOC_ERR)
		printf("\x1b[31mError: malloc\x1b[0m\n");
	return (1);
}

void	*error(int err_num, t_table *table)
{
	if (table != NULL)
		free_table(table);
	print_error(err_num);
	return (NULL);
}

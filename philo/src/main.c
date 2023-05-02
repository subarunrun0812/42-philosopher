/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:34:34 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 01:02:38 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(table->death_check, NULL);
	free_table(table);
}

static bool	create_pthread(t_table *table)
{
	unsigned int	i;

	table->start_time = get_time_ms() + (table->number_of_philos * 30);
	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_create(&table->philos[i]->thread, NULL, &philo,
			table->philos[i]);
		i++;
	}
	pthread_create(&table->death_check, NULL, &death_check, table);
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 5 || 6 < argc)
	{
		print_error(ARG_ERR);
		return (1);
	}
	if (!arg_check(argc, argv))
		return (1);
	table = init(argc, argv);
	if (!table)
		return (1);
	if (!create_pthread(table))
		return (1);
	end_simulation(table);
	return (0);
}

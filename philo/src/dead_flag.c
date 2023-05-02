/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:34:43 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 00:53:46 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead_flag(t_table *table)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&table->dead_mutex);
	if (table->dead)
		res = true;
	pthread_mutex_unlock(&table->dead_mutex);
	return (res);
}

void	dead_flag_on(t_table *table)
{
	pthread_mutex_lock(&table->dead_mutex);
	table->dead = true;
	pthread_mutex_unlock(&table->dead_mutex);
}

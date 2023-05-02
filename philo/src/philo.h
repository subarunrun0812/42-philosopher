/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:49:23 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/10 01:51:41 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define DEAD_MSG "died"
# define EATING_MSG "is eating"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define TAKE_FORK1_MSG "has taken a fork"
# define TAKE_FORK2_MSG "has taken a fork"

# define INT_ERR 0
# define PHILO_RANGE_ERR 1
# define THREAD_ERR 2
# define MUTEX_ERR 3
# define MALLOC_ERR 4
# define ARG_ERR 5

typedef struct s_table	t_table;
typedef long long		t_ms;

typedef struct s_philo
{
	pthread_mutex_t		eat_time_mutex;
	unsigned int		id;
	unsigned int		fork[2];
	unsigned int		meal_count;
	t_ms				last_eat;
	pthread_t			thread;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	t_ms				start_time;
	unsigned int		number_of_philos;
	pthread_t			death_check;
	t_ms				die_ms;
	t_ms				eat_ms;
	t_ms				sleep_ms;
	int					limit_num_of_eat;
	bool				dead;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		*fork_mutexes;
	t_philo				**philos;
}						t_table;

t_table					*init(int argc, char **argv);
void					*free_table(t_table *table);
void					destroy_mutexes(t_table *table);
long long				ft_atoll(const char *str);
void					*death_check(void *data);
bool					arg_check(int argc, char **argv);
void					output_philo_doing(t_philo *philo, bool dead_f,
							char *message);
int						print_error(int err_num);
void					*error(int err_num, t_table *table);
void					think_routine(t_philo *philo);
void					get_fork_and_eat_routine(t_philo *philo);
void					sleep_routine(t_philo *philo);
void					*philo(void *data);
t_ms					get_time_ms(void);
void					wait_time_for_action(t_table *table, t_ms wait_time);
void					wait_until_start_time(t_ms start_time);
bool					check_dead_flag(t_table *table);
void					dead_flag_on(t_table *table);

#endif
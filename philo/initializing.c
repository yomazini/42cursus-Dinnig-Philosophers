/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 04:52:27 by ymazini           #+#    #+#             */
/*   Updated: 2025/06/03 20:21:13 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_fork_spliting(t_table **table, int num_philo)
{
	int	i;

	i = -1;
	while (++i < num_philo)
	{
		(*table)->philos[i].eating_count = 0;
		(*table)->philos[i].index = i + 1;
		(*table)->philos[i].left_fork = &(*table)->forks[i];
		(*table)->philos[i].last_time_eat = get_time();
		(*table)->philos[i].table = *table;
		if (i != num_philo - 1)
			(*table)->philos[i].right_fork = &(*table)->forks[i + 1];
		else
			(*table)->philos[i].right_fork = &(*table)->forks[0];
	}
	return (1);
}

int	initialize_table(t_table **table, char **av)
{
	int	last_av_exist;

	*table = malloc(sizeof(t_table));
	if (!*table)
		return (0);
	last_av_exist = 0;
	(*table)->nbr_philos = ft_atoi(av[1]);
	(*table)->time_to_eat = ft_atoi(av[3]);
	(*table)->time_to_die = ft_atoi(av[2]);
	(*table)->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		(*table)->nmr_time_must_eat = ft_atoi(av[5]);
		last_av_exist = 1;
	}
	else
		(*table)->nmr_time_must_eat = -1;
	if ((*table)->nbr_philos <= 0
		|| (*table)->nbr_philos >= MAX_PHILO
		|| (*table)->time_to_eat <= 0 || (*table)->time_to_eat < 60
		|| (*table)->time_to_sleep <= 0 || (*table)->time_to_sleep < 60
		|| (*table)->time_to_die <= 0 || (*table)->time_to_die < 60
		|| (last_av_exist && (*table)->nmr_time_must_eat < 0))
		return (0);
	return (1);
}

int	allocate_philos_forks(t_table **table)
{
	int	number_philo;

	number_philo = (*table)->nbr_philos;
	(*table)->forks = malloc(sizeof(pthread_mutex_t) * number_philo);
	if (!(*table)->forks)
		return (0);
	(*table)->philos = malloc(sizeof(t_philo) * number_philo);
	if (!(*table)->philos)
		return (0);
	return (1);
}

void	*routine(void *philos)
{
	t_philo	*phil;

	phil = (t_philo *)philos;
	if (phil->table->nmr_time_must_eat == 0)
		return (NULL);
	if (phil->index % 2 == 0)
		usleep(180);
	while (-2)
	{
		pthread_mutex_lock(phil->left_fork);
		print_fork_taken(phil);
		pthread_mutex_lock(phil->right_fork);
		print_fork_taken(phil);
		print_eating_stats(phil);
		update_status(&phil);
		ft_usleep(phil->table->time_to_eat);
		pthread_mutex_unlock(phil->left_fork);
		pthread_mutex_unlock(phil->right_fork);
		if (!eating_count_check(&phil))
			break ;
		print_sleep_stats(phil);
		ft_usleep(phil->table->time_to_sleep);
		print_thinking_stats(phil);
	}
	return (NULL);
}

void	monitor(t_table **table, int nmr_philos)
{
	int	i;

	i = 0;
	while (-1)
	{
		if (i == nmr_philos)
			i = 0;
		pthread_mutex_lock(&(*table)->last_time_eat_mutex);
		if ((*table)->all_eat <= 0)
		{
			pthread_mutex_unlock(&(*table)->last_time_eat_mutex);
			return ;
		}
		if (((get_time() - (*table)->philos[i].last_time_eat)
				> (*table)->time_to_die)
			&& (*table)->philos[i].eating_count != (*table)->nmr_time_must_eat)
		{
			print_death_status(*table, i);
			pthread_mutex_unlock(&(*table)->last_time_eat_mutex);
			return ;
		}
		pthread_mutex_unlock(&(*table)->last_time_eat_mutex);
		i++;
	}
}

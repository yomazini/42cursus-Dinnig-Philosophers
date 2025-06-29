/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:14:15 by ymazini           #+#    #+#             */
/*   Updated: 2025/06/02 21:55:01 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_status(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->table->last_time_eat_mutex);
	(*philo)->last_time_eat = get_time();
	(*philo)->eating_count++;
	pthread_mutex_unlock(&(*philo)->table->last_time_eat_mutex);
}

int	initialize_mutexes(t_table **table_ptr, int number_philo)
{
	t_table	*table;
	int		i;

	table = *table_ptr;
	i = -1;
	if (!allocate_philos_forks(table_ptr))
		return (0);
	if (pthread_mutex_init(&table->last_time_eat_mutex, NULL) != 0)
		return (free(table->philos), free(table->forks), 0);
	if (pthread_mutex_init(&table->writing_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->last_time_eat_mutex);
		return (free(table->philos), free(table->forks), 0);
	}
	while (++i < number_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(&table->writing_mutex);
			pthread_mutex_destroy(&table->last_time_eat_mutex);
			return (free(table->philos), free(table->forks), 0);
		}
	}
	return (ft_fork_spliting(&table, number_philo));
}

int	eating_count_check(t_philo **philo)
{
	if ((*philo)->eating_count == (*philo)->table->nmr_time_must_eat)
	{
		pthread_mutex_lock(&(*philo)->table->last_time_eat_mutex);
		(*philo)->table->all_eat--;
		pthread_mutex_unlock(&(*philo)->table->last_time_eat_mutex);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 04:52:17 by ymazini           #+#    #+#             */
/*   Updated: 2025/06/03 18:10:47 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death_status(t_table *table, int i)
{
	pthread_mutex_lock(&table->writing_mutex);
	printf("%ld %d died\n",
		get_time() - table->sim_start_time,
		table->philos[i].index);
}

void	detach_thread(t_table **table, int nmr_philos)
{
	int	i;

	i = 0;
	while (i < nmr_philos)
	{
		pthread_detach((*table)->philos[i].philo);
		i++;
	}
}

void	clean_all(t_table **table, int num_philos)
{
	int	i;

	i = 0;
	if ((*table) && (*table)->philos)
	{
		free((*table)->philos);
		(*table)->philos = NULL;
	}
	while ((*table) && i < num_philos && (*table)->forks)
	{
		pthread_mutex_destroy(&(*table)->forks[i]);
		i++;
	}
	if ((*table)->forks)
	{
		free((*table)->forks);
		(*table)->forks = NULL;
	}
	pthread_mutex_destroy(&(*table)->last_time_eat_mutex);
	if ((*table))
	{
		free((*table));
		(*table) = NULL;
	}
}

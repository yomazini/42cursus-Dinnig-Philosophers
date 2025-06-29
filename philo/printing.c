/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 04:52:36 by ymazini           #+#    #+#             */
/*   Updated: 2025/06/02 21:41:26 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork_taken(t_philo *phil)
{
	pthread_mutex_lock(&phil->table->writing_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - phil->table->sim_start_time,
		phil->index);
	pthread_mutex_unlock(&phil->table->writing_mutex);
}

void	print_eating_stats(t_philo *phil)
{
	pthread_mutex_lock(&phil->table->writing_mutex);
	printf("%ld %d is eating\n",
		get_time() - phil->table->sim_start_time,
		phil->index);
	pthread_mutex_unlock(&phil->table->writing_mutex);
}

void	print_sleep_stats(t_philo *phil)
{
	pthread_mutex_lock(&phil->table->writing_mutex);
	printf("%ld %d is sleeping\n",
		get_time() - phil->table->sim_start_time,
		phil->index);
	pthread_mutex_unlock(&phil->table->writing_mutex);
}

void	print_thinking_stats(t_philo *phil)
{
	pthread_mutex_lock(&phil->table->writing_mutex);
	printf("%ld %d is thinking\n",
		get_time() - phil->table->sim_start_time,
		phil->index);
	pthread_mutex_unlock(&phil->table->writing_mutex);
}

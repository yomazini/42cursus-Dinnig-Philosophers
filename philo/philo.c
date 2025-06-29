/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 04:52:32 by ymazini           #+#    #+#             */
/*   Updated: 2025/06/03 18:15:40 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_start_simulation(t_table **table_ptr)
{
	t_table	*table;
	int		i;
	int		number_philo;

	i = -1;
	table = *table_ptr;
	number_philo = table->nbr_philos;
	table->sim_start_time = get_time();
	if (table->nmr_time_must_eat == 0)
		table->all_eat = 0;
	else
		table->all_eat = number_philo;
	if (!initialize_mutexes(table_ptr, number_philo))
		return (0);
	while (++i < number_philo)
	{
		if (pthread_create(&table->philos[i].philo,
				NULL, routine, &table->philos[i]) != 0)
			return (clean_all(table_ptr, number_philo), 0);
	}
	detach_thread(table_ptr, number_philo);
	monitor(table_ptr, number_philo);
	return (clean_all(table_ptr, number_philo), 1);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if ((ac != 5 && ac != 6) || !input_validation(av, ac))
	{
		printf("Ops: Invalid Arguments\n");
		return (1);
	}
	if (!initialize_table(&table, av))
	{
		if (table)
			(free(table), table = NULL);
		printf("Ops: INVALID Arguments\n");
		return (1);
	}
	if (!philo_start_simulation(&table))
	{
		printf("Ops: Error IN Simulation\n");
		if (table)
			clean_all(&table, 0);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 04:52:29 by ymazini           #+#    #+#             */
/*   Updated: 2025/05/30 20:58:02 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_validation(char **av, int arguments)
{
	int	i;

	i = 1;
	while (i < arguments)
	{
		if (!ft_validating_the_arg(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_validating_the_arg(char *to_check)
{
	int	i;

	i = 0;
	while (to_check[i]
		&& (to_check[i] == ' ' || (to_check[i] >= '\t' && to_check[i] <= '\r')))
		i++;
	if (to_check[i] == '+')
		i++;
	if (!to_check[i] || !ft_isdigit(to_check[i]))
		return (0);
	while (to_check[i])
	{
		if (!ft_isdigit(to_check[i]))
			return (0);
		i++;
	}
	return (1);
}

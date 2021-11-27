/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluya <nluya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:10:34 by nluya             #+#    #+#             */
/*   Updated: 2021/11/27 17:21:36 by nluya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_output(t_phil_data *philo, char *str)
{
	pthread_mutex_lock(&philo->mutex->output);
	if (philo->args->flag == 0)
		printf("%ld\tThe philo %d %s\n", get_cur_time() - \
		philo->start_time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->mutex->output);
}

int	eating(t_phil_data *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_output(philo, YELLOW"has taken a right fork"RESET);
	pthread_mutex_lock(philo->l_fork);
	ft_output(philo, YELLOW"has taken a left fork"RESET);
	ft_output(philo, CYAN"is eating"RESET);
	philo->last_meal = get_cur_time();
	return (0);
}

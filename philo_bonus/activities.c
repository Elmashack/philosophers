/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluya <nluya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:10:34 by nluya             #+#    #+#             */
/*   Updated: 2021/11/27 16:49:47 by nluya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_output(t_phil_data *philo, char *str)
{
	sem_wait(philo->sems->output);
	if (philo->args->death_flag == 0)
		printf("%ld\tThe philo %d %s\n", get_cur_time() - philo->start_time, \
		philo->philo_id, str);
	sem_post(philo->sems->output);
}

int	eating(t_phil_data *philo)
{
	sem_wait(philo->sems->forks);
	ft_output(philo, YELLOW"has taken the forks"RESET);
	ft_output(philo, CYAN"is eating"RESET);
	philo->last_meal = get_cur_time();
	my_sleep(philo->args->time_eat);
	sem_post(philo->sems->forks);
	return (0);
}

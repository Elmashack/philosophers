/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluya <nluya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:54 by nluya             #+#    #+#             */
/*   Updated: 2021/11/17 18:01:56 by nluya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *err)
{
	write (1, "Error: ", 8);
	write(1, err, ft_strlen(err));
	return (1);
}

void	destroy_mutexes(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->args->phil_number)
		pthread_mutex_destroy(&all->mutexes->forks[i++]);
	pthread_mutex_destroy(&all->mutexes->output);
}

int	death_checker(t_phil_data *philos)
{
	long	hunger_time;

	hunger_time = get_cur_time() - philos->last_meal;
	if (philos->args->time_to_die < hunger_time)
	{
		ft_output(philos, "is dead");
		return (0);
	}
	return (1);
}

void	*check_dead(void *all_data)
{
	t_all	*all;
	int		i;
	int		meals_count;

	all = (t_all *)all_data;
	while (1)
	{
		i = 0;
		meals_count = 0;
		while (i < all->args->phil_number)
		{
			if (!death_checker(&all->philos[i]))
				return (NULL);
			meals_count += all->philos[i].eat_count;
			i++;
		}
		if (meals_count == 0)
		{
			pthread_mutex_lock(&all->mutexes->output);
			printf("The philos are full!\n");
			return (NULL);
		}
	}
}

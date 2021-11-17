/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluya <nluya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:38:33 by nluya             #+#    #+#             */
/*   Updated: 2021/11/17 17:58:14 by nluya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_act(void *ph_struct)
{
	t_phil_data	*philo;

	philo = (t_phil_data *)ph_struct;
	philo->last_meal = get_cur_time();
	while (1)
	{
		if (philo->eat_count != 0)
		{
			eating(philo);
			philo->eat_count--;
			my_sleep(philo->args->time_eat);
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			ft_output(philo, "is sleeping");
			my_sleep(philo->args->time_sleep);
			ft_output(philo, "is thinking");
		}
		else
			break ;
	}
	return (NULL);
}

void	ft_make_thread(t_all *all_info, int flag, int i)
{
	all_info->philos[i].start_time = get_cur_time();
	if (all_info->philos[i].philo_id % 2 == flag)
	{
		all_info->philos[i].mutex = malloc(sizeof(t_mutexes));
		if (!all_info->philos[i].mutex)
			return ;
		if (pthread_create(&all_info->philos[i].thread, NULL, &start_act, \
		 &all_info->philos[i]) != 0)
			ft_error("thread can't be created");
	}
	pthread_detach(all_info->philos[i].thread);
	usleep(10);
}

void	philo_thread(t_all *all_info)
{
	int	i;

	i = -1;
	while (++i < all_info->args->phil_number)
		ft_make_thread(all_info, 0, i);
	i = -1;
	while (++i < all_info->args->phil_number)
		ft_make_thread(all_info, 1, i);
	if (pthread_create(&all_info->dead, NULL, &check_dead, all_info) != 0)
		ft_error("thread can't be created");
	if (pthread_join(all_info->dead, NULL) != 0)
		ft_error("thread can't be joined");
}

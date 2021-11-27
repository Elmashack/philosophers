/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluya <nluya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:38:33 by nluya             #+#    #+#             */
/*   Updated: 2021/11/27 18:31:22 by nluya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_and_free(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->args->phil_number)
	{
		pthread_mutex_destroy(all->philos[i].l_fork);
		pthread_mutex_destroy(all->philos[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(&all->mutexes->output);
	free(all->mutexes);
	free(all->philos);
	free(all->args);
}

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
			philo->last_meal = get_cur_time();
			ft_output(philo, MAGENTA"is sleeping"RESET);
			my_sleep(philo->args->time_sleep);
			ft_output(philo, BLUE"is thinking"RESET);
		}
		else
			break ;
	}
	return (NULL);
}

int	ft_make_thread(t_all *all_info, int flag, int i)
{
	if (all_info->philos[i].philo_id % 2 == flag)
	{
		all_info->philos[i].start_time = all_info->args->time;
		all_info->philos[i].mutex = malloc(sizeof(t_mutexes));
		if (!all_info->philos[i].mutex)
			return (0);
		if (pthread_create(&all_info->philos[i].thread, NULL, &start_act, \
			&all_info->philos[i]) != 0)
			return (ft_error("thread can't be created"));
	}
	pthread_detach(all_info->philos[i].thread);
	usleep(30);
	return (0);
}

int	philo_thread(t_all *all_info)
{
	int	i;

	i = -1;
	all_info->args->time = get_cur_time();
	while (++i < all_info->args->phil_number)
		ft_make_thread(all_info, 0, i);
	i = -1;
	usleep(30);
	while (++i < all_info->args->phil_number)
		ft_make_thread(all_info, 1, i);
	if (pthread_create(&all_info->dead, NULL, &check_dead, all_info) != 0)
		return (ft_error("thread can't be created"));
	if (pthread_join(all_info->dead, NULL) != 0)
		return (ft_error("thread can't be joined"));
	destroy_and_free(all_info);
	return (0);
}

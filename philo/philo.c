/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluya <nluya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:46:23 by nluya             #+#    #+#             */
/*   Updated: 2021/11/27 18:24:37 by nluya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_phil(t_all *all_info)
{
	int	i;

	i = 0;
	all_info->philos = malloc(sizeof(t_phil_data) * \
	all_info->args->phil_number);
	if (all_info->philos == NULL)
		return (1);
	while (i < all_info->args->phil_number)
	{
		all_info->philos[i].philo_id = i + 1;
		all_info->philos[i].last_meal = 0;
		all_info->philos[i].eat_count = all_info->args->num_of_meals;
		all_info->philos[i].args = all_info->args;
		all_info->philos[i].r_fork = &all_info->mutexes->forks[i];
		if ((i + 1) == all_info->args->phil_number)
			all_info->philos[i].l_fork = &all_info->mutexes->forks[0];
		else
			all_info->philos[i].l_fork = &all_info->mutexes->forks[i + 1];
		i++;
	}
	return (0);
}

int	init_mutex(t_all *all_info)
{
	int	i;

	i = 0;
	all_info->mutexes = malloc(sizeof(t_mutexes));
	if (all_info->mutexes == NULL)
		return (1);
	if (!all_info->mutexes)
		return (ft_error("Can't allocate the memory"));
	all_info->mutexes->forks = malloc(sizeof(pthread_mutex_t) * \
	all_info->args->phil_number);
	if (pthread_mutex_init(&all_info->mutexes->output, NULL))
		return (ft_error("The mutex 'output' couldn't be init"));
	while (i < all_info->args->phil_number)
	{
		if (pthread_mutex_init(&all_info->mutexes->forks[i], NULL))
			return (ft_error("The mutex 'output' couldn't be init"));
		i++;
	}
	return (0);
}

int	ft_parse(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
			if (!ft_isdigit(argv[i][j++]) || ft_atoi(argv[i]) == -1)
				return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_all	all_info;

	all_info.args = malloc(sizeof(t_data));
	if (all_info.args == NULL)
		return (0);
	if ((argc != 5 && argc != 6) || argc == 1)
		return (ft_error("arguments error\n"));
	if (!ft_parse(argv))
		return (ft_error("Parse error\n"));
	all_info.args->phil_number = ft_atoi(argv[1]);
	all_info.args->time_to_die = ft_atoi(argv[2]);
	all_info.args->time_eat = ft_atoi(argv[3]);
	all_info.args->time_sleep = ft_atoi(argv[4]);
	all_info.args->num_of_meals = -1;
	all_info.args->flag = 0;
	if (argc > 5)
		all_info.args->num_of_meals = ft_atoi(argv[5]);
	if (init_mutex(&all_info))
		return (0);
	if (init_phil(&all_info))
		return (0);
	if (philo_thread(&all_info))
		return (0);
}

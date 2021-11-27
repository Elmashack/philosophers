/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluya <nluya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:46:23 by nluya             #+#    #+#             */
/*   Updated: 2021/11/27 16:41:28 by nluya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_phil(t_all *all)
{
	all->philos = malloc(sizeof(t_phil_data) * all->args->phil_num);
	if (all->philos == NULL)
		return (1);
	all->philos->pid = malloc(sizeof(pid_t) * all->args->phil_num);
	if (all->philos->pid == NULL)
		return (1);
	all->args->death_flag = 0;
	all->philos->eat_count = all->args->num_of_meals;
	all->philos->args = all->args;
	all->philos->sems = all->sems;
	return (0);
}

int	init_sems(t_all *all)
{
	all->sems = malloc(sizeof(t_sema));
	if (all->sems == NULL)
		return (ft_error("Memory couln't be allocated"));
	sem_unlink("output");
	all->sems->output = sem_open("output", O_CREAT, 0644, 1);
	if (all->sems->output == SEM_FAILED)
		return (ft_error("Semaphore 'output' failed to open"));
	sem_unlink("forks");
	all->sems->forks = sem_open("forks", O_CREAT, 0644, \
	all->args->phil_num / 2);
	if (all->sems->forks == SEM_FAILED)
		return (ft_error("Semaphore 'forks' failed to open"));
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
	all_info.args->phil_num = ft_atoi(argv[1]);
	all_info.args->time_to_die = ft_atoi(argv[2]);
	all_info.args->time_eat = ft_atoi(argv[3]);
	all_info.args->time_sleep = ft_atoi(argv[4]);
	all_info.args->num_of_meals = -1;
	if (argc > 5)
		all_info.args->num_of_meals = ft_atoi(argv[5]);
	if (init_sems(&all_info))
		return (0);
	if (init_phil(&all_info))
		return (0);
	if (init_process(&all_info))
		return (0);
	free_all(&all_info);
}

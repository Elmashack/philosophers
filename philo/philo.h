/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluya <nluya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:46:37 by nluya             #+#    #+#             */
/*   Updated: 2021/11/27 17:06:43 by nluya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
}			t_mutexes;
typedef struct s_data
{
	int	phil_number;
	int	time_sleep;
	int	time_eat;
	int	time_to_die;
	int	num_of_meals;
	int	flag;
}				t_data;

typedef struct s_phil_data
{
	int				philo_id;
	int				eat_count;
	long			start_time;
	long			last_meal;
	t_data			*args;
	t_mutexes		*mutex;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_phil_data;

typedef struct s_all
{
	pthread_t	dead;
	t_data		*args;
	t_mutexes	*mutexes;
	t_phil_data	*philos;
}				t_all;

//func
long	get_cur_time(void);
int		eating(t_phil_data *philo);
void	my_sleep(long time_to_wait);
int		philo_thread(t_all *all_info);
void	destroy_mutexes(t_all *all);
void	ft_output(t_phil_data *philo, char *str);
void	*check_dead(void *all_data);

//basic func
int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		ft_error(char *err);
int		ft_strlen(const char *s);

#endif
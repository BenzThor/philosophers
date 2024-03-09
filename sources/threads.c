/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:21:30 by thorben           #+#    #+#             */
/*   Updated: 2024/03/09 13:32:52 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	test_dead_output(t_vars *vars, t_phil *phil, int behaviour)
{
	pthread_mutex_lock(&vars->dead);
	if (!vars->finished)
	{
		pthread_mutex_unlock(&vars->dead);
		phil_output(behaviour, phil);
	}
	else
		pthread_mutex_unlock(&vars->dead);
}

void	one_phil(t_vars *vars)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(vars->time_die, vars);
	printf("%u 1 died\n", vars->time_die + 1);
	pthread_mutex_lock(&vars->dead);
	vars->finished = 1;
	pthread_mutex_unlock(&vars->dead);
}

void	check_death(t_vars *vars, t_phil *phil)
{
	int	i;

	while (!vars->finished_eating)
	{
		i = -1;
		pthread_mutex_lock(&vars->dead);
		while (++i < (int)vars->phil_num && !vars->finished)
		{
			pthread_mutex_unlock(&vars->dead);
			pthread_mutex_lock(&vars->phils[i].lock);
			if (phil[i].left_to_live < get_time())
				phil_output(DEAD, &vars->phils[i]);
			pthread_mutex_unlock(&vars->phils[i].lock);
			usleep(100);
			pthread_mutex_lock(&vars->dead);
		}
		if (vars->finished)
		{
			pthread_mutex_unlock(&vars->dead);
			break ;
		}
		pthread_mutex_unlock(&vars->dead);
		i = 0;
		while (vars->eat_req != -1 && i < (int)vars->phil_num
			&& (int)phil[i].eat_cnt >= vars->eat_req)
			i++;
		if (i == (int)vars->phil_num)
		{
			pthread_mutex_lock(&phil->vars->dead);
			vars->finished_eating = 1;
			pthread_mutex_unlock(&phil->vars->dead);
		}
	}
}

void	*ft_loop(void *phil_data)
{
	t_phil	*phil;

	phil = (t_phil *)phil_data;
	if (phil->vars->phil_num == 1)
		one_phil(phil->vars);
	if (phil->id % 2 == 0)
		ft_usleep(phil->vars->time_eat / 2, phil->vars);
	pthread_mutex_lock(&phil->vars->dead);
	while (!phil->vars->finished)
	{
		pthread_mutex_unlock(&phil->vars->dead);
		if (phil->vars->phil_num % 2 && phil->id == phil->vars->phil_num)
			ft_usleep(phil->vars->time_eat + 1, phil->vars);
		eat(phil);
		pthread_mutex_lock(&phil->vars->dead);
		if (phil->vars->finished_eating)
			break ;
		pthread_mutex_unlock(&phil->vars->dead);
		test_dead_output(phil->vars, phil, SLEEPING);
		ft_usleep(phil->vars->time_sleep, phil->vars);
		test_dead_output(phil->vars, phil, THINKING);
		if (phil->vars->phil_num % 2 && phil->id != phil->vars->phil_num)
			ft_usleep(phil->vars->time_eat + 1, phil->vars);
		pthread_mutex_lock(&phil->vars->dead);
	}
	pthread_mutex_unlock(&phil->vars->dead);
	return ((void *)0);
}

void	ft_threads(t_vars *vars)
{
	unsigned int	i;

	vars->start_time = get_time();
	i = -1;
	while (++i < vars->phil_num)
	{
		vars->phils[i].left_to_live = vars->time_die + get_time();
		if (pthread_create(&vars->tid[i], NULL, &ft_loop, &vars->phils[i]))
		{
			ft_error(vars, THREAD_ERR);
			return ;
		}
	}
	i = -1;
	check_death(vars, vars->phils);
	while (++i < vars->phil_num)
	{
		if (pthread_join(vars->tid[i], NULL))
		{
			ft_error(vars, JOIN_ERR);
			return ;
		}
	}
	ft_error(vars, OK);
}

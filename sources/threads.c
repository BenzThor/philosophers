/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:21:30 by thorben           #+#    #+#             */
/*   Updated: 2024/02/29 19:16:22 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	check_death(t_vars *vars, t_phil *phil)
{
	int	i;

	while (!vars->finished_eating)
	{
		i = -1;
		pthread_mutex_lock(&vars->meal);
		while (++i < (int)vars->phil_num && !vars->dead)
		{
			pthread_mutex_unlock(&vars->meal);
			pthread_mutex_lock(&vars->phils[i].lock);
			if (phil[i].left_to_live < get_time())
				phil_output(DEAD, &vars->phils[i]);
			pthread_mutex_unlock(&vars->phils[i].lock);
			usleep(100);
			pthread_mutex_lock(&vars->meal);
		}
		pthread_mutex_unlock(&vars->meal);
		if (vars->dead)
			break ;
		i = 0;
		while (vars->eat_req != -1 && i < (int)vars->phil_num
			&& (int)phil[i].eat_cnt >= vars->eat_req)
			i++;
		if (i == (int)vars->phil_num)
			vars->finished_eating = 1;
	}
}

void	*ft_loop(void *phil_data)
{
	t_phil	*phil;

	phil = (t_phil *)phil_data;
	// if (phil->id % 2)
	// 	usleep (15000);
	pthread_mutex_lock(&phil->vars->meal);
	while (!phil->vars->dead)
	{
		pthread_mutex_unlock(&phil->vars->meal);
		if (phil->id % 2 && phil->id == phil->vars->phil_num)
			ft_usleep(phil->vars->time_eat + 100, phil->vars);
		eat(phil);
		if (phil->vars->finished_eating)
			break ;
		pthread_mutex_lock(&phil->vars->meal);
		if (!phil->vars->dead)
		{
			pthread_mutex_unlock(&phil->vars->meal);
			phil_output(SLEEPING, phil);
		}
		ft_usleep(phil->vars->time_sleep, phil->vars);
		pthread_mutex_lock(&phil->vars->meal);
		if (!phil->vars->dead)
		{
			pthread_mutex_unlock(&phil->vars->meal);
			phil_output(THINKING, phil);
		}
		ft_usleep(100, phil->vars);
		pthread_mutex_lock(&phil->vars->meal);
	}
	pthread_mutex_unlock(&phil->vars->meal);
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

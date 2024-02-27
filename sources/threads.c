/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:21:30 by thorben           #+#    #+#             */
/*   Updated: 2024/02/27 13:41:53 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*ft_track_finished(void *phil_data)
{
	t_phil	*phil;

	phil = (t_phil *)phil_data;
	// pthread_mutex_lock(&phil->vars->write);
	while (!phil->vars->dead)
	{
		pthread_mutex_lock(&phil->lock);
		if (phil->vars->done >= phil->vars->phil_num)
			phil->vars->dead = 1;
		pthread_mutex_unlock(&phil->lock);
	}
	return ((void *)0);
}

void	*ft_executive(void *phil_data)
{
	t_phil	*phil;

	phil = (t_phil *)phil_data;
	while (phil->vars->dead)
	{
		pthread_mutex_lock(&phil->lock);
		if (get_time() > phil->left_to_live)
		{
			pthread_mutex_lock(&phil->vars->meal);
			phil->vars->done++;
			phil->eat_cnt++;
			pthread_mutex_unlock(&phil->vars->meal);
		}
		pthread_mutex_unlock(&phil->lock);
	}
	return ((void *)0);
}

void	*ft_loop(void *phil_data)
{
	t_phil	*phil;

	phil = (t_phil *)phil_data;
	phil->left_to_live = phil->vars->time_die + get_time();
	if (pthread_create(&phil->t, NULL, &ft_executive, (void *)phil))
		ft_error(phil->vars, THREAD_ERR);
	while (!phil->vars->dead)
	{
		eat(phil);
		phil_output(THINKING, phil);
	}
	if (pthread_join(phil->t, NULL))
		ft_error(phil->vars, THREAD_ERR);
	return ((void *)0);
}

void	ft_threads(t_vars *vars)
{
	pthread_t		monthr;
	unsigned int	i;

	vars->start_time = get_time();
	// if (vars->phil_num == 1)
	// 	ft_one_phil(vars);
	if (vars->eat_req > 0)
	{
		if (pthread_create(&monthr, NULL, &ft_track_finished, &vars->phils[0]))
			ft_error(vars, THREAD_ERR);
	}
	i = -1;
	while (++i < vars->phil_num)
	{
		if (pthread_create(&vars->tid[i], NULL, &ft_loop, &vars->phils[i]))
			ft_error(vars, THREAD_ERR);
	}
	i = -1;
	while (++i < vars->phil_num)
	{
		if (pthread_join(vars->tid[i], NULL))
			ft_error(vars, JOIN_ERR);
	}
	ft_error(vars, OK);
}

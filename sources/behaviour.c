/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:40:08 by thorben           #+#    #+#             */
/*   Updated: 2024/02/27 13:19:09 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	phil_output(int event, t_phil *phil)
{
	__uint64_t	time;

	pthread_mutex_lock(&phil->vars->write);
	time = (get_time() - phil->vars->start_time);
	printf("%lu %d", time, phil->id);
	if (event == DEAD && !phil->vars->dead)
	{
		printf(" has died 🪦\n");
		phil->vars->dead = 1;
	}
	else if (event == EATING && !phil->vars->dead)
		printf(" is eating 🍝\n");
	else if (event == THINKING && !phil->vars->dead)
		printf(" is thinking 🤯\n");
	else if (event == SLEEPING && !phil->vars->dead)
		printf(" is sleeping 💤\n");
	else if (event == GRAB_FORKS && !phil->vars->dead)
		printf(" has grabbed a fork 🍴\n");
	pthread_mutex_unlock(&phil->vars->write);
}

void	eat(t_phil *phil)
{
	pthread_mutex_lock(phil->r_fork);
	phil_output(GRAB_FORKS, phil);
	pthread_mutex_lock(phil->l_fork);
	phil_output(GRAB_FORKS, phil);
	pthread_mutex_lock(&phil->lock);
	phil->left_to_live = get_time() + phil->vars->time_die;
	phil_output(EATING, phil);
	phil->eat_cnt++;
	ft_usleep(phil->vars->time_eat);
	phil->eating = 0;
	pthread_mutex_unlock(&phil->lock);
	pthread_mutex_unlock(phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);
	phil_output(SLEEPING, phil);
	ft_usleep(phil->vars->time_sleep);
}

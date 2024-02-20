/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:40:08 by thorben           #+#    #+#             */
/*   Updated: 2024/02/20 15:38:13 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	phil_output(int event, t_phil *phil)
{
	__uint64_t	time;

	pthread_mutex_lock(&phil->vars->write);
	time = (get_time() - phil->vars->start_time);
	ft_putnbr_fd(time, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(phil->id, 1);
	if (event == DEAD && !phil->vars->dead)
	{
		ft_putstr_fd(" died\n", 1);
		ft_putstr_fd(" has died 🪦\n", 1);
		phil->vars->dead = 1;
	}
	else if (event == EATING && !phil->vars->dead)
	{
		ft_putstr_fd(" eating\n", 1);
		ft_putstr_fd(" is eating 🍝\n", 1);
	}
	else if (event == THINKING && !phil->vars->dead)
	{
		ft_putstr_fd(" thinking\n", 1);
		ft_putstr_fd(" is thinking 🤯\n", 1);
	}
	else if (event == SLEEPING && !phil->vars->dead)
	{
		ft_putstr_fd(" sleeping\n", 1);
		ft_putstr_fd(" is sleeping 💤\n", 1);
	}
	else if (event == GRAB_FORKS && !phil->vars->dead)
	{
		ft_putstr_fd(" grabbed a fork\n", 1);
		ft_putstr_fd(" has grabbed a fork 🍴\n", 1);
	}
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

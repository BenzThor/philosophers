/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:40:08 by thorben           #+#    #+#             */
/*   Updated: 2024/02/28 13:22:48 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	phil_output(int event, t_phil *phil)
{
	__uint64_t	time;

	pthread_mutex_lock(&phil->vars->write);
	time = (get_time() - phil->vars->start_time);
	printf("%llu ms %d", (unsigned long long)time, phil->id);
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

void	grab_forks(t_phil *philo)
{
	pthread_mutex_lock(philo->r_fork);
	phil_output(GRAB_FORKS, philo);
	pthread_mutex_lock(philo->l_fork);
	phil_output(GRAB_FORKS, philo);
}

void	let_go_forks(t_phil *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eat(t_phil *philo)
{
	grab_forks(philo);
	pthread_mutex_lock(&philo->vars->meal);
	philo->left_to_live = get_time() + philo->vars->time_die;
	phil_output(EATING, philo);
	pthread_mutex_unlock(&philo->vars->meal);
	philo->eat_cnt++;
	ft_usleep(philo->vars->time_eat);
	let_go_forks(philo);
}

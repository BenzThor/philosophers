/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:40:08 by thorben           #+#    #+#             */
/*   Updated: 2024/03/04 11:35:35 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	phil_output(int event, t_phil *phil)
{
	__uint64_t	time;

	pthread_mutex_lock(&phil->vars->write);
	time = (get_time() - phil->vars->start_time);
	printf("%llu %d", (unsigned long long)time, phil->id);
	if (event == DEAD && !phil->vars->finished)
	{
		printf(" died\n");
		pthread_mutex_lock(&phil->vars->dead);
		phil->vars->finished = 1;
		pthread_mutex_unlock(&phil->vars->dead);
	}
	else if (event == EATING && !phil->vars->finished)
		printf(" is eating\n");
	else if (event == THINKING && !phil->vars->finished)
		printf(" is thinking\n");
	else if (event == SLEEPING && !phil->vars->finished)
		printf(" is sleeping\n");
	else if (event == GRAB_FORKS && !phil->vars->finished)
		printf(" has taken a fork\n");
	pthread_mutex_unlock(&phil->vars->write);
}

void	grab_forks(t_phil *philo)
{
	if (philo->id != philo->vars->phil_num)
	{
		pthread_mutex_lock(philo->r_fork);
		test_dead_output(philo->vars, philo, GRAB_FORKS);
		pthread_mutex_lock(philo->l_fork);
		test_dead_output(philo->vars, philo, GRAB_FORKS);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		test_dead_output(philo->vars, philo, GRAB_FORKS);
		pthread_mutex_lock(philo->r_fork);
		test_dead_output(philo->vars, philo, GRAB_FORKS);
	}
}

void	let_go_forks(t_phil *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	eat(t_phil *philo)
{
	grab_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->left_to_live = get_time() + philo->vars->time_die;
	test_dead_output(philo->vars, philo, EATING);
	pthread_mutex_unlock(&philo->lock);
	philo->eat_cnt++;
	ft_usleep(philo->vars->time_eat, philo->vars);
	let_go_forks(philo);
}

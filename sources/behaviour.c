/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:40:08 by thorben           #+#    #+#             */
/*   Updated: 2024/03/12 10:33:03 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	phil_output(int event, t_phil *phil)
{
	unsigned long long int	time;
	int						ec;

	pthread_mutex_lock(&phil->vars->write);
	time = (unsigned long long)(get_time(phil->vars, &ec) - \
	phil->vars->start_time);
	if (event == DEAD && !phil_died(phil->vars, 0))
	{
		printf("%llu %d died\n", time, phil->id);
		phil_died(phil->vars, 1);
	}
	else if (event == EATING && !phil_died(phil->vars, 0))
		printf("%llu %d is eating\n", time, phil->id);
	else if (event == THINKING && !phil_died(phil->vars, 0))
		printf("%llu %d is thinking\n", time, phil->id);
	else if (event == SLEEPING && !phil_died(phil->vars, 0))
		printf("%llu %d is sleeping\n", time, phil->id);
	else if (event == GRAB_FORKS && !phil_died(phil->vars, 0))
		printf("%llu %d has taken a fork\n", time, phil->id);
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
	int	ec;

	grab_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->left_to_live = get_time(philo->vars, &ec) + philo->vars->time_die;
	if (ec)
	{
		pthread_mutex_unlock(&philo->lock);
		let_go_forks(philo);
		return ;
	}
	test_dead_output(philo->vars, philo, EATING);
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->vars->time_eat, philo->vars);
	let_go_forks(philo);
}

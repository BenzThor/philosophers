/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:21:30 by thorben           #+#    #+#             */
/*   Updated: 2024/03/11 13:54:28 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	phil_died(t_vars *vars)
{
	pthread_mutex_lock(&vars->dead);
	if (!vars->finished)
	{
		pthread_mutex_unlock(&vars->dead);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&vars->dead);
		return (1);
	}
}

void	test_dead_output(t_vars *vars, t_phil *phil, int behaviour)
{
	if (!phil_died(vars))
		phil_output(behaviour, phil);
}

void	one_phil(t_vars *vars)
{
	printf("0 1 has taken a fork\n");
	if (ft_usleep(vars->time_die, vars) == -1)
		return ;
	printf("%u 1 died\n", vars->time_die + 1);
	pthread_mutex_lock(&vars->dead);
	vars->finished = 1;
	pthread_mutex_unlock(&vars->dead);
}

void	check_death(t_vars *vars, t_phil *phil)
{
	int	i;
	int ec;

	while (!phil_died(vars))
	{
		i = -1;
		while (++i < (int)vars->phil_num && !phil_died(vars))
		{
			pthread_mutex_lock(&vars->phils[i].lock);
			if (phil[i].left_to_live < get_time(vars, &ec) && !ec)
				phil_output(DEAD, &vars->phils[i]);
			pthread_mutex_unlock(&vars->phils[i].lock);
			usleep(100);
		}
		if (phil_died(vars))
			break ;
		i = 0;
		while (vars->eat_req != -1 && i < (int)vars->phil_num
			&& (int)phil[i].eat_cnt >= vars->eat_req)
			i++;
		if (i == (int)vars->phil_num)
		{
			pthread_mutex_lock(&phil->vars->dead);
			vars->finished = 1;
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
	while (!phil_died(phil->vars))
	{
		if (phil->vars->phil_num % 2 && phil->id == phil->vars->phil_num)
			ft_usleep(phil->vars->time_eat + 1, phil->vars);
		eat(phil);
		if (phil_died(phil->vars))
			break ;
		test_dead_output(phil->vars, phil, SLEEPING);
		ft_usleep(phil->vars->time_sleep, phil->vars);
		test_dead_output(phil->vars, phil, THINKING);
		if (phil->vars->phil_num % 2 && phil->id != phil->vars->phil_num)
			ft_usleep(phil->vars->time_eat + 1, phil->vars);
	}
	return ((void *)0);
}

void	ft_threads(t_vars *vars)
{
	unsigned int	i;
	int 			ec;

	vars->start_time = get_time(vars, &ec);
	if (ec)
	{
		ft_error(vars, NOT_DEFINED);
		return ;
	}
	i = -1;
	while (++i < vars->phil_num)
	{
		vars->phils[i].left_to_live = vars->time_die + get_time(vars, &ec);
		if (ec)
			return ;
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

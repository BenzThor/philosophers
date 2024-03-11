/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:21:30 by thorben           #+#    #+#             */
/*   Updated: 2024/03/11 16:54:54 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	phil_died(t_vars *vars, int mode)
{
	pthread_mutex_lock(&vars->dead);
	if (mode)
	{
		vars->finished = 1;
		pthread_mutex_unlock(&vars->dead);
		return (0);
	}
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
	if (!phil_died(vars, 0))
		phil_output(behaviour, phil);
}

int	phil_fed(t_phil *phil)
{
	pthread_mutex_lock(&phil->lock);
	if ((int)phil->eat_cnt >= phil->vars->eat_req)
	{
		pthread_mutex_unlock(&phil->lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&phil->lock);
		return (0);
	}
}

void	one_phil(t_vars *vars)
{
	printf("0 1 has taken a fork\n");
	if (ft_usleep(vars->time_die, vars) == -1)
		return ;
	printf("%u 1 died\n", vars->time_die + 1);
	phil_died(vars, 1);
}

void	check_death(t_vars *vars, t_phil *phil)
{
	int	i;
	int	ec;

	while (!phil_died(vars, 0))
	{
		i = -1;
		while (++i < (int)vars->phil_num && !phil_died(vars, 0))
		{
			pthread_mutex_lock(&vars->phils[i].lock);
			if (phil[i].left_to_live < get_time(vars, &ec) && !ec)
				phil_output(DEAD, &vars->phils[i]);
			pthread_mutex_unlock(&vars->phils[i].lock);
			usleep(100);
		}
		if (phil_died(vars, 0))
			break ;
		i = 0;
		while (vars->eat_req != -1 && i < (int)vars->phil_num
			&& phil_fed(&phil[i]))
			i++;
		if (i == (int)vars->phil_num)
			phil_died(vars, 1);
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
	while (!phil_died(phil->vars, 0))
	{
		if (phil->vars->phil_num % 2 && phil->id == phil->vars->phil_num)
			ft_usleep(phil->vars->time_eat + 1, phil->vars);
		if (phil_died(phil->vars, 0))
			break ;
		eat(phil);
		if (phil_died(phil->vars, 0))
			break ;
		test_dead_output(phil->vars, phil, SLEEPING);
		ft_usleep(phil->vars->time_sleep, phil->vars);
		test_dead_output(phil->vars, phil, THINKING);
		if (phil->vars->phil_num % 2 && phil->id != phil->vars->phil_num
			&& !phil_died(phil->vars, 0))
			ft_usleep(phil->vars->time_eat + 1, phil->vars);
	}
	return ((void *)0);
}

void	ft_threads(t_vars *vars)
{
	unsigned int	i;
	int				ec;

	vars->start_time = get_time(vars, &ec);
	if (ec)
	{
		ft_error(vars, NOT_DEFINED);
		return ;
	}
	i = -1;
	pthread_mutex_lock(&vars->dead);
	while (++i < vars->phil_num)
	{
		vars->phils[i].left_to_live = vars->time_die + get_time(vars, &ec);
		if (ec)
			return ;
		if (pthread_create(&vars->tid[i], NULL, &ft_loop, &vars->phils[i]))
		{
			ft_putstr_fd("Error", 2);
			vars->finished = 1;
			vars->phil_num = i;
			break ;
		}
	}
	pthread_mutex_unlock(&vars->dead);
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

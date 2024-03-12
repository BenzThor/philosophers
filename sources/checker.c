/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:11:38 by tbenz             #+#    #+#             */
/*   Updated: 2024/03/12 11:04:54 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	phil_died(t_vars *vars, int mode)
{
	pthread_mutex_lock(&vars->dead);
	if (mode && !vars->finished)
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

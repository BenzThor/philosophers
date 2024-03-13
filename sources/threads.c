/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:21:30 by thorben           #+#    #+#             */
/*   Updated: 2024/03/13 15:35:45 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	one_phil(t_vars *vars)
{
	printf("0 1 has taken a fork\n");
	if (ft_usleep(vars->time_die, vars) == -1)
		return ;
	printf("%u 1 died\n", vars->time_die + 1);
	phil_died(vars, 1);
}

void	join_threads(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < (int)vars->phil_num)
	{
		if (pthread_join(vars->tid[i], NULL))
		{
			ft_error(vars, JOIN_ERR);
			return ;
		}
	}
}

void	*ft_loop(void *phil_data)
{
	t_phil	*phil;

	phil = (t_phil *)phil_data;
	if (phil->vars->one_phil)
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

void	create_threads(t_vars *vars, int *ec)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&vars->dead);
	while (++i < (int)vars->phil_num)
	{
		vars->phils[i].left_to_live = vars->time_die + get_time(vars, ec, 1);
		if (pthread_create(&vars->tid[i], NULL, &ft_loop, &vars->phils[i]))
		{
			ft_putstr_fd("An error occurred while creating the threads", 2);
			vars->finished = 1;
			vars->phil_num = i;
			break ;
		}
	}
	pthread_mutex_unlock(&vars->dead);
}

void	ft_threads(t_vars *vars)
{
	int				ec;

	vars->start_time = get_time(vars, &ec, 0);
	if (ec)
	{
		ft_error(vars, NOT_DEFINED);
		return ;
	}
	create_threads(vars, &ec);
	if (!vars->one_phil)
		check_death(vars, vars->phils);
	join_threads(vars);
	ft_error(vars, OK);
}

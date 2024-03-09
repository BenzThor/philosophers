/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:19:12 by thorben           #+#    #+#             */
/*   Updated: 2024/03/09 13:34:37 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philsinit(t_vars *vars)
{
	unsigned int	i;

	i = -1;
	while (++i < vars->phil_num)
	{
		vars->phils[i].vars = vars;
		vars->phils[i].id = i + 1;
		vars->time_die = vars->time_die;
		pthread_mutex_init(&vars->phils[i].lock, NULL);
	}
}

void	forkinit(t_vars *vars)
{
	unsigned int	i;

	i = -1;
	while (++i < vars->phil_num)
		pthread_mutex_init(&vars->forks[i], NULL);
	vars->phils[0].l_fork = &vars->forks[0];
	vars->phils[0].r_fork = &vars->forks[vars->phil_num - 1];
	i = 0;
	while (++i < vars->phil_num)
	{
		vars->phils[i].l_fork = &vars->forks[i];
		vars->phils[i].r_fork = &vars->forks[i - 1];
	}
}

void	mallocate(t_vars *vars)
{
	vars->tid = calloc(vars->phil_num, sizeof(pthread_t));
	vars->forks = calloc(vars->phil_num, sizeof(pthread_mutex_t));
	vars->phils = calloc(vars->phil_num, sizeof(t_phil));
	if (!vars->tid || !vars->forks || !vars->phils)
		ft_error(vars, MALLOC_ERR);
}

void	ft_init(t_vars *vars)
{
	pthread_mutex_init(&vars->write, NULL);
	pthread_mutex_init(&vars->dead, NULL);
	if (!vars->ec)
		mallocate(vars);
	if (!vars->ec)
		forkinit(vars);
	if (!vars->ec)
		philsinit(vars);
	vars->init_check = 1;
}

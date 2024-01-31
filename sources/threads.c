/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:21:30 by thorben           #+#    #+#             */
/*   Updated: 2024/01/31 12:14:36 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_one_phil(t_vars *vars)
{
	ft_exit(vars, OK);
}

void	ft_threads(t_vars *vars)
{
	int			i;
	pthread_t	monthr;

	vars->start_time = get_time();
	if (vars->phil_num == 1)
		ft_one_phil(vars);
	if (vars->eat_req > 0)
	{
		if (pthread_create(monthr, NULL, &monitor, &vars->phils[0]))
			ft_exit(vars, THREAD_ERR);
	}
	i = -1;
	while (++i < vars->phil_num)
	{
		if (pthread_create(vars->tid[i], NULL, &loop, &vars->phils[i]))
			ft_exit(vars, THREAD_ERR);
	}
}

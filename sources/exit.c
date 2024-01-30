/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:08:40 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/30 19:53:31 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_print_err(int err)
{
	if (err == ARGC_ERR)
		ft_putstr_fd("Go, check your arguments\n", 2);
	else if (err == MALLOC_ERR)
		ft_putstr_fd("There has been a malloc error\n", 2);
	else if (err == NUM_ERR)
		ft_putstr_fd("You should put digits or one + sign at the start\n", 2);
	else if (err == EXC_ERR)
	{
		ft_putstr_fd("One of your numbers is too long. The maximum is ", 2);
		ft_putnbr_fd(UINT_MAX, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (err == NEG_ERR)
		ft_putstr_fd("We can't travel in time and need one philo\n", 2);
}

void	clean_vars(t_vars *vars, int err)
{
	if (vars->tid)
		free(vars->tid);
	if (vars->forks)
		free(vars->forks);
	if (vars->phils)
		free(vars->phils);
	exit(err);
}

void	ft_exit(t_vars *vars, int ec)
{
	int	i;

	if (ec)
		ft_print_err(ec);
	i = 0;
	if (!OK)
		clean_vars(vars, ec);
	while (vars->phil_num && i < vars->phil_num)
	{
		pthread_mutex_destroy(&vars->forks[i]);
		pthread_mutex_destroy(&vars->phils[i].lock);
	}
	pthread_mutex_destroy(&vars->meal);
	pthread_mutex_destroy(&vars->write);
	clean_vars(vars, ec);
}

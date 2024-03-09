/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:08:40 by tbenz             #+#    #+#             */
/*   Updated: 2024/03/09 13:34:43 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_print_err(t_vars *vars, int ec)
{
	if (ec == ARGC1_ERR)
		ft_putstr_fd("You didn't put all the required arguments\n", 2);
	else if (ec == ARGC2_ERR)
		ft_putstr_fd("You put too many arguments\n", 2);
	else if (ec == MALLOC_ERR)
		ft_putstr_fd("There has been a malloc error\n", 2);
	else if (ec == NUM_ERR)
		ft_putstr_fd("You should put digits only (additional + sign " \
			"at the start is allowed)\n", 2);
	else if (ec == EXC_ERR)
	{
		ft_putstr_fd("One of your numbers is too long. The maximum is ", 2);
		ft_putnbr_fd(UINT_MAX, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (ec == NEG_ERR)
		ft_putstr_fd("We can't travel in time and need one philo\n", 2);
	else if (ec == THREAD_ERR)
		ft_putstr_fd("An error occured while creating the threads\n", 2);
	else if (ec == JOIN_ERR)
		ft_putstr_fd("An error occured while joining the threads\n", 2);
	vars->ec = ec;
}

void	clean_vars(t_vars *vars)
{
	if (vars->tid)
		free(vars->tid);
	if (vars->forks)
		free(vars->forks);
	if (vars->phils)
		free(vars->phils);
}

void	ft_error(t_vars *vars, int ec)
{
	unsigned int	i;

	if (ec)
		ft_print_err(vars, ec);
	if (ec != OK && ec != THREAD_ERR && ec != JOIN_ERR)
	{
		clean_vars(vars);
		return ;
	}
	if (vars->in_check)
	{
		pthread_mutex_destroy(&vars->dead);
		pthread_mutex_destroy(&vars->write);
		if (vars->init_check)
		{
			i = -1;
			while (vars->phil_num && ++i < vars->phil_num)
			{
				pthread_mutex_destroy(&vars->forks[i]);
				pthread_mutex_destroy(&vars->phils[i].lock);
			}
		}
	}
	clean_vars(vars);
}

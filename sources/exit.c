/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:08:40 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/29 17:07:54 by tbenz            ###   ########.fr       */
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
		ft_putstr_fd("Your input is too long. The maximum is ", 2);
		ft_putnbr_fd(UINT_MAX, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (err == NEG_ERR)
		ft_putstr_fd("We can't travel in time and need one philo\n", 2);
}

void	ft_exit(t_vars *vars, int err)
{
	if (err)
		ft_print_err(err);
	if (vars)
		;
	// free everything
	exit (err);
}

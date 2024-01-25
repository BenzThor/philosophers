/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:08:40 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/25 15:29:00 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_print_err(int err)
{
	if (ARGC_ERR)
		ft_putstr_fd("Go check your arguments, you put too many\n", 2);
	else if (MALLOC_ERR)
		ft_putstr_fd("There has been a malloc error\n", 2);
	else if (NUM_ERR)
		ft_putstr_fd("The arguments have to be digits\n", 2);
}

void	ft_exit(t_phil *phil, int err)
{
	if (err)
		ft_print_err(err);
	// free everything
}

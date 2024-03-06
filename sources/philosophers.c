/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:02:48 by tbenz             #+#    #+#             */
/*   Updated: 2024/03/06 16:14:15 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	one_phil(t_vars *vars)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(vars->time_die, vars);
	printf("%u 1 died\n", vars->time_die + 1);
	ft_error(vars, OK);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	ft_arg_check(&vars, argc, argv);
	if (!vars.ec)
		ft_init(&vars);
	if (!vars.ec && vars.phil_num == 1)
		one_phil(&vars);
	else if (!vars.ec)
		ft_threads(&vars);
}

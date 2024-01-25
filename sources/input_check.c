/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:06:31 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/25 15:31:12 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_arg_check(t_vars *vars, int argc, char **argv)
{
	int	i;
	int	j;

	if (argc > 6)
		ft_exit(vars, ARGC_ERR);
	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				ft_exit(vars, NUM_ERR);
			j++;
		}
		i++;
	}
	
}

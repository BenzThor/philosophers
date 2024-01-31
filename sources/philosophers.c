/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:02:48 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/31 10:41:26 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	ft_arg_check(&vars, argc, argv);
	ft_init(&vars);
	ft_threads(&vars);
}

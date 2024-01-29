/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:02:48 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/29 14:54:56 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	ft_arg_check(&vars, argc, argv);
}

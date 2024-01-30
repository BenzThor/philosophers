/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:02:48 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/30 18:18:51 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	ft_arg_check(&vars, argc, argv);
	ft_init(&vars);
}

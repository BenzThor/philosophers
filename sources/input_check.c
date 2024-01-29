/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:06:31 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/29 17:12:50 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


long long int	ft_atoi_ll(t_vars *vars, const char *str)
{
	long long int	sign;
	long long int	sum;

	sign = 1;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	sum = 0;
	while (*str > 47 && *str < 58)
	{
		if (sum > __LONG_LONG_MAX__ / 10
			|| (sum == __LONG_LONG_MAX__ / 10 && sign == 1 && *str > '7')
			|| (sum == __LONG_LONG_MAX__ / 10 && sign == -1 && *str > '8'))
			ft_exit(vars, EXC_ERR);
		sum *= 10;
		sum += (*str - '0');
		str++;
	}
	sum *= sign;
	if (sum < 0)
		ft_exit(vars, NEG_ERR);
	return (sum);
}

void	ft_save_num(t_vars *vars, char *str, int i)
{
	long long int	llint;
	unsigned int	uns;

	llint = ft_atoi_ll(vars, str);
	if (llint > UINT_MAX)
		ft_exit(vars, EXC_ERR);
	uns = (unsigned)llint;
	if (uns == 0 && i != 5)
		ft_exit(vars, NEG_ERR);
	vars->settings[i - 1] = uns;
}

void	ft_check_number(t_vars *vars, char *str)
{
	while (*str == ' ' || *str == '\n' || *str == '\t'
	|| *str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			ft_exit(vars, NUM_ERR);
		str++;
	}
}

void	ft_arg_check(t_vars *vars, int argc, char **argv)
{
	int	i;

	if (argc > 6 || argc < 5)
		ft_exit(vars, ARGC_ERR);
	i = 1;
	while (argv && argv[i])
	{
		ft_check_number(vars, argv[i]);
		ft_save_num(vars, argv[i], i);
		i++;
	}
}

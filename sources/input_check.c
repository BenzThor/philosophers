/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:06:31 by tbenz             #+#    #+#             */
/*   Updated: 2024/03/15 15:14:44 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long long int	ft_atoi_ll(t_vars *vars, const char *str)
{
	long long int	sum;

	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			ft_error(vars, NEG_ERR);
			return (-1);
		}
		str++;
	}
	sum = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (sum > __LONG_LONG_MAX__ / 10 || (sum == __LONG_LONG_MAX__ / 10
				&& *str > '7') || (sum == __LONG_LONG_MAX__ / 10 && *str > '8'))
		{
			ft_error(vars, EXC_ERR);
			return (1);
		}
		sum *= 10;
		sum += (*str - '0');
		str++;
	}
	return (sum);
}

void	ft_save_num(t_vars *vars, char *str, int i)
{
	long long int	llint;
	unsigned int	uns;

	llint = ft_atoi_ll(vars, str);
	if (llint < 0)
		return ;
	if (llint > UINT_MAX)
		ft_error(vars, EXC_ERR);
	uns = (unsigned)llint;
	if (!vars->ec && uns == 0 && i != 5)
		ft_error(vars, NEG_ERR);
	if (i == 1)
	{
		vars->phil_num = uns;
		if (uns == 1)
			vars->one_phil = 1;
	}
	else if (i == 2)
		vars->time_die = uns;
	else if (i == 3)
		vars->time_eat = uns;
	else if (i == 4)
		vars->time_sleep = uns;
	else if (i == 5)
		vars->eat_req = uns;
}

void	ft_check_number(t_vars *vars, char *str)
{
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r'
		|| *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			ft_error(vars, NUM_ERR);
			break ;
		}
		str++;
	}
}

void	ft_arg_check(t_vars *vars, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			ft_error(vars, ARGC1_ERR);
		else if (argc > 6)
			ft_error(vars, ARGC2_ERR);
		return ;
	}
	i = 1;
	while (argv && argv[i] && !vars->ec)
	{
		ft_check_number(vars, argv[i]);
		if (!vars->ec)
			ft_save_num(vars, argv[i], i);
		i++;
	}
	if (argc == 5 && !vars->ec)
		vars->eat_req = -1;
	vars->in_check = 1;
}

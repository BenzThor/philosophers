/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:52:41 by tbenz             #+#    #+#             */
/*   Updated: 2024/03/15 13:13:05 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allspc;
	size_t	total_size;

	total_size = nmemb * size;
	if (nmemb != 0 && size != 0 && nmemb > (total_size / size))
		return (NULL);
	allspc = malloc(total_size);
	if (allspc == NULL)
		return (NULL);
	ft_bzero(allspc, total_size);
	return (allspc);
}

__uint64_t	get_time(t_vars *vars, int *ec, int mode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		if (!mode && phil_died(vars, 0))
		{
			ft_putstr_fd("get_time() error\n", 2);
			phil_died(vars, 1);
			*ec = -1;
		}
		else if (mode)
		{
			ft_putstr_fd("get_time() error\n", 2);
			vars->finished = 1;
			*ec = -1;
		}
		return (1);
	}
	*ec = 0;
	return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(__useconds_t ms, t_vars *vars)
{
	__uint64_t	start;
	int			ec;

	start = get_time(vars, &ec, 0);
	while (!ec && (long long int)(get_time(vars, &ec, 0) - start) < ms)
	{
		if (!phil_died(vars, 0) && !ec)
		{
			if (usleep(100) == -1)
			{
				if (phil_died(vars, 0))
					ft_putstr_fd("usleep error\n", 2);
				phil_died(vars, 1);
				return (-1);
			}
		}
		else
			break ;
	}
	return (0);
}

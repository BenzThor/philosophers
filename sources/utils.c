/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:52:41 by tbenz             #+#    #+#             */
/*   Updated: 2024/02/27 18:07:21 by thorben          ###   ########.fr       */
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

__uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_putstr_fd("get_time() error\n", 2);
	return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(__useconds_t milliseconds)
{
	__uint64_t	start;

	start = get_time();
	while ((long long int)(get_time() - start) < milliseconds)
		usleep(milliseconds / 10);
	return (0);
}

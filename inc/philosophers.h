/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:50:22 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/29 17:03:19 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// included libraries
# include "macros_philosophers.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_vars
{
	unsigned int	settings[5];
}		t_vars;

void	ft_arg_check(t_vars *vars, int argc, char **argv);
void	ft_print_err(int err);
void	ft_exit(t_vars *vars, int err);
void	ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
void	ft_putnbr_fd(long n, int fd);
void	ft_putchar_fd(char c, int fd);

#endif

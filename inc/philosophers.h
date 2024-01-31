/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:50:22 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/31 12:01:32 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// included libraries
# include "macros_philosophers.h"
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// struct that stores then information of a single philosopher
typedef struct s_phil
{
	struct s_vars	*vars;
	int				id;
	int				eat_cnt;
	int				eating;
	unsigned int	left_to_live;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_phil;

// struct that stores all the main information
typedef struct s_vars
{
	pthread_t		*tid;
	unsigned int	phil_num;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	eat_req;
	__uint64_t		start_time;
	int				dead;
	int				done;
	int				in_check;
	int				init_check;
	t_phil			*phils;
	pthread_mutex_t	meal;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
}					t_vars;

/* exit */

// exits the program, providing an adequate error message and freeing memory
void				ft_exit(t_vars *vars, int err);
// prints an adequate error message
void				ft_print_err(int err);

/* init */

// initiates all the necesarry mutex and philosophers
void				ft_init(t_vars *vars);
// callocs all the needed elements:tids, forks and phils
void				mallocate(t_vars *vars);
// initiates the fork mutexes and gives each philosopher a left and right fork
void				forkinit(t_vars *vars);
// sets the philosophers variables to their respective inital values
void				philsinit(t_vars *vars);

/* input_check */

// checks the arguments for valid input
void				ft_arg_check(t_vars *vars, int argc, char **argv);
// checks whether the input is a valid number (can have leading + or - sign)
void				ft_check_number(t_vars *vars, char *str);
// saves the number given as input in the struct as parameters (max: uns. int)
void				ft_save_num(t_vars *vars, char *str, int i);
/* if possible, converts the input to long long int and returns it;
	otherwise exits */
long long int		ft_atoi_ll(t_vars *vars, const char *str);

/* utils_write */

// puts a char to the selected file descriptor
void				ft_putchar_fd(char c, int fd);
// puts a number to the selected file descriptor
void				ft_putnbr_fd(long n, int fd);
// puts a string to the selected file descriptor
void				ft_putstr_fd(char *s, int fd);

/* utils */

/* Sets the first n bytes of the area starting at s to zero (bytes containing
	aq\0aq). */
void				ft_bzero(void *s, size_t n);
// determines the length of a string s and returns its length
size_t				ft_strlen(const char *s);
/* Allocates memory for an array of nmemb elements of size bytes each and
	returns a pointer to the allocated memory. The memory is set to zero. If
	nmemb or size is 0, then calloc() returns either NULL, or a unique pointer
	value that can later be successfully passed to free().  */
void				*ft_calloc(size_t nmemb, size_t size);
// gets the time (starting from 1970) in microseconds and returns it
__uint64_t			get_time(void);
// usleep that uses get_time for more accuracy
int					ft_usleep(__suseconds_t microseconds);

#endif

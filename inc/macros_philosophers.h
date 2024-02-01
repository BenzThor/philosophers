/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_philosophers.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:52:29 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/01 16:19:19 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_PHILOSOPHERS_H
# define MACROS_PHILOSOPHERS_H

# define NOT_DEFINED 999

# define NOT_OK -1
# define OK 0
# define MALLOC_ERR 1000
# define ARGC_ERR 1100
# define NUM_ERR 1200
# define PHIL_ERR 1300
# define EXC_ERR 1400
# define NEG_ERR 1500
// # define TID_ALL_ERR 1600
// # define FORK_ALL_ERR 1700
// # define PHILS_ALL_ERR 1800
# define THREAD_ERR 1900
# define JOIN_ERR 2000

// behaviour
# define EATING 10000
# define SLEEPING 11000
# define THINKING 12000
# define DEAD 13000
# define GRAB_FORKS 14000

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:00:54 by mlangloi          #+#    #+#             */
/*   Updated: 2023/07/02 16:03:03 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_prog	t_prog;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pthread_t	tid;
	int			id;
	int			nb_repas;
	long long	der_repas;
	int			l_fork;
	int			r_fork;
	t_prog		*prog;
}	t_philo;

typedef struct s_prog
{
	t_philo			*philo;
	int				nb_philo;
	long long		time;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	int				max_eat;
	int				error;
	int				end_eat;
	int				loose;
	pthread_mutex_t	*fork;
	pthread_mutex_t	checker;
	pthread_mutex_t	write;
	int				write_die;
}	t_prog;

// philo_init.c
int			check_arg(int ac, char **av);
void		ft_init_prog(char **av, t_prog *prog);
void		ft_init_philo(t_prog	*prog);
void		check_number(char **av);
void		ft_free(t_prog *prog);

// philo_init2.c
t_prog		*ft_init_prog2(t_prog *prog, char **av);
t_prog		*ft_init_prog3(t_prog *prog);
void		ft_exit(t_prog *prog);

// utils.c 
int			ft_atoi(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			is_number(char *nb);

// philo_time.c
long long	ft_get_time(t_prog *prog);
void		ft_time(t_philo *philo, long long time);
long long	start_time(t_prog *prog);
void		ft_cata(t_prog *prog);
void		ft_cata2(t_prog *prog);

// philo_routine.c
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_eat(t_philo *philo);
void		*ft_routine(void *phi);
void		ft_print_mes(t_philo *philo, int nb, char *str);

#endif

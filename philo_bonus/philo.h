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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_prog	t_prog;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int			id;
	int			nb_repas;
	long long	der_repas;
	int			die;
	t_prog		*prog;
}	t_philo;

typedef struct s_prog
{
	int				nb_philo;
	long long		time;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	int				max_eat;
	int				*table;
	sem_t			*fork;
}	t_prog;

void		philo_fork(t_philo *philo);
void		ft_init_sem(t_prog *prog);
int			check_arg(int ac, char **av);
void		ft_init_prog(char **av, t_prog *prog);
void		check_number(char **av);
void		ft_free(t_prog *prog);
t_prog		*ft_init_prog2(t_prog *prog, char **av);
int			ft_atoi(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			is_number(char *nb);
long long	ft_get_time(void);
long long	ft_time(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_eat(t_philo *philo);
void		*ft_routine(t_philo *philo);
void		ft_print_mes(t_philo *philo, int nb, char *str);

#endif

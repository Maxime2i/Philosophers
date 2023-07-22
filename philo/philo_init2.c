/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:02:47 by mlangloi          #+#    #+#             */
/*   Updated: 2023/07/15 17:02:48 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_prog	*ft_init_prog2(t_prog *prog, char **av)
{
	prog->error = 0;
	prog->loose = 0;
	prog->end_eat = 0;
	prog->write_die = 0;
	prog->nb_philo = ft_atoi(av[1]);
	prog->t_die = ft_atoi(av[2]);
	prog->t_eat = ft_atoi(av[3]);
	prog->t_sleep = ft_atoi(av[4]);
	return (prog);
}

t_prog	*ft_init_prog3(t_prog *prog)
{
	int	i;
	int	res;

	i = -1;
	while (++i < prog->nb_philo)
	{
		res = pthread_mutex_init(&prog->fork[i], NULL);
		if (res != 0)
			ft_cata2(prog);
	}
	ft_init_philo(prog);
	prog->time = start_time(prog);
	return (prog);
}

void	ft_exit(t_prog *prog)
{
	if (prog->philo)
		free(prog->philo);
	if (prog)
		free(prog);
	exit(1);
}

void	ft_init_mutex(t_prog *prog)
{
	int	res;

	res = pthread_mutex_init(&prog->write, NULL);
	if (res != 0)
		ft_cata2(prog);
	res = pthread_mutex_init(&prog->checker, NULL);
	if (res != 0)
		ft_cata2(prog);
	res = pthread_mutex_init(&prog->loo, NULL);
	if (res != 0)
		ft_cata2(prog);
	res = pthread_mutex_init(&prog->eat_max, NULL);
	if (res != 0)
		ft_cata2(prog);
}

void	*ft_solitude(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	pthread_mutex_lock(&philo->prog->fork[philo->l_fork]);
	ft_print_mes(philo, philo->id, "has taken a fork");
	philo->der_repas = ft_get_time(philo->prog);
	usleep(philo->prog->t_die * 1000);
	ft_print_mes(philo, philo->id, "died");
	philo->prog->loose = 1;
	return (NULL);
}

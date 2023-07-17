/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:10:49 by mlangloi          #+#    #+#             */
/*   Updated: 2023/07/14 15:10:52 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_cata(t_prog *prog)
{
	printf("Erreur lors d'une fonction (gettimeofday, pthread_create)");
	prog->loose = 1;
	ft_free(prog);
	exit(1);
}

void	ft_cata2(t_prog *prog)
{
	int	i;

	printf("Erreur lors d'une fonction (pthread_mutex_init)");
	prog->loose = 1;
	i = prog->nb_philo;
	while (++i < prog->nb_philo)
	{
		if (&prog->fork[i])
			pthread_mutex_destroy(&prog->fork[i]);
	}
	if (&prog->write)
		pthread_mutex_destroy(&prog->write);
	if (&prog->checker)
		pthread_mutex_destroy(&prog->checker);
	free(prog->philo);
	free(prog->fork);
	free(prog);
	exit(1);
}

long long	ft_get_time(t_prog *prog)
{
	struct timeval	time;
	int				res;

	res = gettimeofday(&time, NULL);
	if (res == -1)
		ft_cata(prog);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - prog->time);
}

void	ft_time(t_philo *philo, long long time)
{
	long long	t;
	long long	diff;

	t = ft_get_time(philo->prog);
	while (1)
	{
		diff = ft_get_time(philo->prog) - t;
		if (diff >= time)
			break ;
		usleep(1000);
	}
}

long long	start_time(t_prog *prog)
{
	struct timeval	time;
	int				res;

	res = gettimeofday(&time, NULL);
	if (res == -1)
		ft_cata(prog);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

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

int	ft_loose(t_prog *prog)
{
	pthread_mutex_lock(&prog->loo);
	if (prog->loose == 0)
	{
		pthread_mutex_unlock(&prog->loo);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&prog->loo);
		return (1);
	}
}

void	ft_cata(t_prog *prog)
{
	int	i;

	i = prog->nb_philo;
	printf("Erreur lors d'une fonction (gettimeofday, pthread_create)\n");
	pthread_mutex_lock(&prog->loo);
	prog->loose = 1;
	pthread_mutex_unlock(&prog->loo);
	while (++i < prog->nb_philo)
		pthread_mutex_destroy(&prog->fork[i]);
	pthread_mutex_destroy(&prog->write);
	pthread_mutex_destroy(&prog->checker);
	pthread_mutex_destroy(&prog->loo);
	pthread_mutex_destroy(&prog->eat_max);
	free(prog->philo);
	free(prog->fork);
	free(prog);
	exit(1);
}

void	ft_cata2(t_prog *prog)
{
	int	i;

	printf("Erreur lors d'une fonction (pthread_mutex_init)\n");
	pthread_mutex_lock(&prog->loo);
	prog->loose = 1;
	pthread_mutex_unlock(&prog->loo);
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
	if (&prog->loo)
		pthread_mutex_destroy(&prog->loo);
	if (&prog->eat_max)
		pthread_mutex_destroy(&prog->eat_max);
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
	{
		pthread_mutex_lock(&prog->loo);
		prog->error = 1;
		prog->write_die = 1;
		pthread_mutex_unlock(&prog->loo);
		return (9223372036854775807);
	}
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - prog->time);
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

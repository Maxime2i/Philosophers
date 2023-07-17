/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:58:07 by mlangloi          #+#    #+#             */
/*   Updated: 2023/07/14 16:58:08 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philo_think(t_philo *philo)
{
	if (philo->prog->loose == 0)
	{
		pthread_mutex_lock(&philo->prog->write);
		if (philo->prog->write_die == 0)
			printf("%lld\t%d\t%s\n", ft_get_time(philo->prog),
				philo->id, "is thinking");
		pthread_mutex_unlock(&philo->prog->write);
	}
}

void	philo_sleep(t_philo *philo)
{
	if (philo->prog->loose == 0)
	{
		pthread_mutex_lock(&philo->prog->write);
		if (philo->prog->write_die == 0)
			printf("%lld\t%d\t%s\n", ft_get_time(philo->prog),
				philo->id, "is sleeping");
		pthread_mutex_unlock(&philo->prog->write);
		ft_time(philo, philo->prog->t_sleep);
	}
}

long long	timestampa(t_prog *input)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (((current.tv_sec * 1000) + (current.tv_usec / 1000)) - input->time);
}

void	philo_eat(t_philo *philo)
{
	if (philo->prog->loose == 0)
	{
		pthread_mutex_lock(&philo->prog->fork[philo->l_fork]);
		pthread_mutex_lock(&philo->prog->write);
		if (philo->prog->write_die == 0)
			printf("%lld\t%d\t%s\n", ft_get_time(philo->prog),
				philo->id, "has taken a fork");
		pthread_mutex_unlock(&philo->prog->write);
		pthread_mutex_lock(&philo->prog->fork[philo->r_fork]);
		pthread_mutex_lock(&philo->prog->write);
		if (philo->prog->write_die == 0)
			printf("%lld\t%d\t%s\n", ft_get_time(philo->prog),
				philo->id, "has taken a fork");
		pthread_mutex_unlock(&philo->prog->write);
		pthread_mutex_lock(&philo->prog->write);
		if (philo->prog->write_die == 0)
			printf("%lld\t%d\t%s\n", ft_get_time(philo->prog),
				philo->id, "is eating");
		pthread_mutex_unlock(&philo->prog->write);
		philo->der_repas = ft_get_time(philo->prog);
		philo->nb_repas++;
		ft_time(philo, philo->prog->t_eat);
		pthread_mutex_unlock(&philo->prog->fork[philo->l_fork]);
		pthread_mutex_unlock(&philo->prog->fork[philo->r_fork]);
	}
}

void	*ft_routine(void *phi)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)phi;
	prog = philo->prog;
	if (philo->id % 2)
		usleep(2000);
	while (prog->loose == 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

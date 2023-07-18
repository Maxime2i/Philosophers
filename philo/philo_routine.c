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

void	ft_print_mes(t_philo *philo, int nb, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->prog->write);
	time = ft_get_time(philo->prog);
	if (philo->prog->write_die == 0 && philo->prog->error == 0)
		printf("%lld\t%d\t%s\n", time, nb, str);
	pthread_mutex_unlock(&philo->prog->write);
}

void	philo_think(t_philo *philo)
{
	if (philo->prog->loose == 0)
	{
		ft_print_mes(philo, philo->id, "is thinking");
	}
}

void	philo_sleep(t_philo *philo)
{
	if (philo->prog->loose == 0)
	{
		ft_print_mes(philo, philo->id, "is sleeping");
		ft_time(philo, philo->prog->t_sleep);
	}
}

void	philo_eat(t_philo *philo)
{
	if (philo->prog->loose == 0)
	{
		pthread_mutex_lock(&philo->prog->fork[philo->l_fork]);
		ft_print_mes(philo, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->prog->fork[philo->r_fork]);
		ft_print_mes(philo, philo->id, "has taken a fork");
		ft_print_mes(philo, philo->id, "is eating");
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

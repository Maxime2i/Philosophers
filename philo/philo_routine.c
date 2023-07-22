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
	pthread_mutex_lock(&philo->prog->loo);
	if (philo->prog->write_die == 0 && philo->prog->error == 0)
		printf("%lld\t%d\t%s\n", time, nb, str);
	pthread_mutex_unlock(&philo->prog->loo);
	pthread_mutex_unlock(&philo->prog->write);
}

void	philo_think(t_philo *philo)
{
	if (ft_loose(philo->prog) == 0)
	{
		ft_print_mes(philo, philo->id, "is thinking");
	}
}

void	philo_sleep(t_philo *philo)
{
	if (ft_loose(philo->prog) == 0)
	{
		ft_print_mes(philo, philo->id, "is sleeping");
		usleep(philo->prog->t_sleep * 1000);
	}
}

void	philo_eat(t_philo *philo, int lf, int rf)
{
	if (ft_loose(philo->prog) == 0)
	{
		pthread_mutex_lock(&philo->prog->fork[lf]);
		ft_print_mes(philo, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->prog->fork[rf]);
		ft_print_mes(philo, philo->id, "has taken a fork");
		ft_print_mes(philo, philo->id, "is eating");
		pthread_mutex_lock(&philo->prog->eat_max);
		philo->der_repas = ft_get_time(philo->prog);
		philo->nb_repas++;
		pthread_mutex_unlock(&philo->prog->eat_max);
		usleep(philo->prog->t_eat * 1000);
		pthread_mutex_unlock(&philo->prog->fork[lf]);
		pthread_mutex_unlock(&philo->prog->fork[rf]);
	}
}

void	*ft_routine(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	if ((philo->id - 1) % 2)
		usleep((philo->prog->t_eat + 10) * 1000);
	while (ft_loose(philo->prog) == 0)
	{
		if ((philo->id - 1) % 2)
			philo_eat(philo, philo->l_fork, philo->r_fork);
		else
			philo_eat(philo, philo->r_fork, philo->l_fork);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

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
	if (philo->die == 0)
	{
		printf("%lld\t%d\t%s\n", ft_time(philo), nb, str);
	}
}

void	philo_think(t_philo *philo)
{
	ft_print_mes(philo, philo->id, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	ft_print_mes(philo, philo->id, "is sleeping");
	usleep(philo->prog->t_sleep * 1000);
}

void	philo_eat(t_philo *philo)
{
	ft_print_mes(philo, philo->id, "is eating");
	philo->der_repas = ft_get_time();
	philo->nb_repas++;
	usleep(philo->prog->t_eat * 1000);
	sem_post(philo->prog->fork);
	sem_post(philo->prog->fork);
	if (philo->nb_repas == philo->prog->max_eat)
		exit(0);
}

void	philo_fork(t_philo *philo)
{
	sem_wait(philo->prog->fork);
	ft_print_mes(philo, philo->id, "has taken a fork");
}

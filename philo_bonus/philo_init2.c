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
	prog->nb_philo = ft_atoi(av[1]);
	prog->t_die = ft_atoi(av[2]);
	prog->t_eat = ft_atoi(av[3]);
	prog->t_sleep = ft_atoi(av[4]);
	return (prog);
}

void	*ft_check(void	*arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if ((philo->der_repas + philo->prog->t_die) < ft_get_time())
		{
			ft_print_mes(philo, philo->id, "died");
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*ft_routine(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, ft_check, philo);
	while (1)
	{
		philo_fork(philo);
		philo_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_join(thread, NULL);
}

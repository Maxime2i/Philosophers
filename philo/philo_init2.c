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

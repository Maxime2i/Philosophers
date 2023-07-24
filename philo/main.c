/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:27:20 by mlangloi          #+#    #+#             */
/*   Updated: 2023/07/17 16:51:50 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_check_die(t_philo *philo)
{
	long long	diff;

	pthread_mutex_lock(&philo->prog->checker);
	pthread_mutex_lock(&philo->prog->eat_max);
	diff = ft_get_time(philo->prog) - philo->der_repas;
	pthread_mutex_unlock(&philo->prog->eat_max);
	if (diff >= philo->prog->t_die)
	{
		ft_print_mes(philo, philo->id, "died");
		pthread_mutex_lock(&philo->prog->loo);
		philo->prog->loose = 1;
		philo->prog->write_die = 1;
		pthread_mutex_unlock(&philo->prog->loo);
	}
	pthread_mutex_unlock(&philo->prog->checker);
}

void	ft_check_finish(t_prog *prog)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (i < prog->nb_philo)
	{
		pthread_mutex_lock(&prog->eat_max);
		if (prog->max_eat > 0
			&& prog->philo[i].nb_repas >= prog->max_eat)
			a++;
		pthread_mutex_unlock(&prog->eat_max);
		ft_check_die(&prog->philo[i]);
		i++;
		if (a == prog->nb_philo)
		{
			pthread_mutex_lock(&prog->loo);
			prog->loose = 1;
			pthread_mutex_unlock(&prog->loo);
		}
	}
	usleep(1500);
}

void	ft_create_2(t_prog *prog)
{
	int	res;
	int	i;

	i = -1;
	while (++i < prog->nb_philo)
	{
		res = pthread_create(&prog->philo[i].tid, NULL,
				&ft_routine, (void *) &prog->philo[i]);
		if (res != 0)
			ft_cata(prog);
	}
	while (ft_loose(prog) == 0)
	{
		ft_check_finish(prog);
		pthread_mutex_lock(&prog->loo);
		if (prog->error == 1)
		{
			printf("Error : fonction gettimeofday\n");
			pthread_mutex_unlock(&prog->loo);
			break ;
		}
		pthread_mutex_unlock(&prog->loo);
	}
}

void	ft_create(t_prog *prog)
{
	int	res;

	if (prog->nb_philo == 1)
	{
		res = pthread_create(&prog->philo[0].tid, NULL,
				&ft_solitude, (void *) &prog->philo[0]);
		if (res != 0)
			ft_cata(prog);
	}
	else
		ft_create_2(prog);
}

int	main(int ac, char **av)
{
	int		k;
	t_prog	*prog;

	prog = NULL;
	k = check_arg(ac, av);
	if (k != 0)
		return (1);
	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (1);
	ft_init_prog(av, prog);
	ft_create(prog);
	ft_free(prog);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:54:25 by mlangloi          #+#    #+#             */
/*   Updated: 2023/07/12 09:54:30 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	check_number(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_number(av[i]) != 0)
		{
			printf("Error : Entrez seulement des nombres positifs\n");
			exit(1);
		}
		i++;
	}
}

int	check_arg(int ac, char **av)
{
	int	i;
	int	res;

	if (ac != 5 && ac != 6)
	{
		printf("Error : nombre d'arguments\n");
		return (1);
	}
	check_number(av);
	i = 0;
	while (av[++i])
	{
		res = ft_atoi(av[i]);
		if (i == 1 && res > 200)
		{
			printf("Error : nombre de philosophe\n");
			return (1);
		}
		if (res <= 0)
		{
			printf("Error : 0 > time > 2147483648\n");
			return (1);
		}
	}
	return (0);
}

void	ft_init_philo(t_prog	*prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philo)
	{
		prog->philo[i].id = i + 1;
		prog->philo[i].nb_repas = 0;
		prog->philo[i].der_repas = 0;
		prog->philo[i].l_fork = i;
		prog->philo[i].r_fork = (i + 1) % prog->nb_philo;
		prog->philo[i].prog = prog;
		i++;
	}
}

void	ft_init_prog(char **av, t_prog *prog)
{
	prog = ft_init_prog2(prog, av);
	if (av[5])
		prog->max_eat = ft_atoi(av[5]);
	else
		prog->max_eat = 0;
	prog->philo = ft_calloc(prog->nb_philo, (sizeof(t_philo)));
	if (prog->philo == NULL)
		ft_exit(prog);
	prog->fork = ft_calloc(prog->nb_philo, (sizeof(pthread_mutex_t)));
	if (prog->fork == NULL)
		ft_exit(prog);
	ft_init_mutex(prog);
	prog = ft_init_prog3(prog);
}

void	ft_free(t_prog *prog)
{
	int	i;

	i = prog->nb_philo;
	while (--i >= 0)
		pthread_join(prog->philo[i].tid, NULL);
	while (++i < prog->nb_philo)
		pthread_mutex_destroy(&prog->fork[i]);
	pthread_mutex_destroy(&prog->write);
	pthread_mutex_destroy(&prog->checker);
	pthread_mutex_destroy(&prog->loo);
	pthread_mutex_destroy(&prog->eat_max);
	free(prog->philo);
	free(prog->fork);
	free(prog);
}

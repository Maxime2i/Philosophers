/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:27:20 by mlangloi          #+#    #+#             */
/*   Updated: 2023/07/16 16:51:08 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_check_die(t_philo *philo)
{
	long long	diff;

	pthread_mutex_lock(&philo->prog->checker);
	diff = ft_get_time(philo->prog) - philo->der_repas;
	if (diff >= philo->prog->t_die)
	{
		pthread_mutex_lock(&philo->prog->write);
		if (philo->prog->write_die == 0)
			printf("%lld\t%d\t%s\n", ft_get_time(philo->prog), philo->id, "died");
		pthread_mutex_unlock(&philo->prog->write);
		philo->prog->loose = 1;
		philo->prog->write_die = 1;
	}
	pthread_mutex_unlock(&philo->prog->checker);
}

void	*ft_solitude(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	pthread_mutex_lock(&philo->prog->fork[philo->l_fork]);
	pthread_mutex_lock(&philo->prog->write);
	if (philo->prog->write_die == 0)
		printf("%lld\t%d\t%s\n", ft_get_time(philo->prog),
			philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->prog->write);
	philo->der_repas = ft_get_time(philo->prog);
	ft_time(philo, philo->prog->t_die);
	pthread_mutex_lock(&philo->prog->write);
	if (philo->prog->write_die == 0)
		printf("%lld\t%d\t%s\n", ft_get_time(philo->prog), philo->id, "died");
	pthread_mutex_unlock(&philo->prog->write);
	philo->prog->loose = 1;
	return (NULL);
}

void	ft_check_finish(t_prog *prog)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (i < prog->nb_philo)
	{
		if (prog->max_eat > 0
			&& prog->philo[i].nb_repas == prog->max_eat)
			a++;
		ft_check_die(&prog->philo[i]);
		i++;
		if (a == prog->nb_philo)
			prog->loose = 1;
	}
	usleep(1500);
}

void	ft_create(t_prog *prog)
{
	int	i;
	int	res;

	i = -1;
	if (prog->nb_philo == 1)
		ft_solitude(prog->philo);
	else
	{
		while (++i < prog->nb_philo)
		{
			res = pthread_create(&prog->philo[i].tid, NULL,
					&ft_routine, (void *) &prog->philo[i]);
			if (res != 0)
				ft_cata(prog);
		}
		while (prog->loose == 0)
		{
			ft_check_finish(prog);
		}
	}
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

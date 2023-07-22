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

void	ft_init_philo(t_philo *philo, t_prog *prog)
{
	philo->nb_repas = 0;
	philo->der_repas = prog->time;
	philo->die = 0;
	philo->prog = prog;
}

void	ft_create(t_prog *prog)
{
	int		i;
	int		id;
	t_philo	*philo;

	philo = ft_calloc(prog->nb_philo, sizeof(t_philo));
	if (!philo)
		exit(1);
	i = 0;
	prog->time = ft_get_time();
	while (i < prog->nb_philo)
	{
		ft_init_philo(philo + i, prog);
		id = fork();
		if (id == 0)
		{
			philo[i].id = i + 1;
			ft_routine(philo + i);
		}
		else
			prog->table[i] = id;
		i++;
		usleep(100);
	}
	ft_free(prog);
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
	ft_init_sem(prog);
	ft_create(prog);
	return (0);
}

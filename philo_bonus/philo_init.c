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
			printf("Error : Entrez seulement des temps positifs\n");
			return (1);
		}
	}
	return (0);
}

void	ft_init_prog(char **av, t_prog *prog)
{
	prog = ft_init_prog2(prog, av);
	if (av[5])
		prog->max_eat = ft_atoi(av[5]);
	else
		prog->max_eat = 0;
	prog->table = ft_calloc(prog->nb_philo, sizeof(int));
	if (!prog->table)
		exit(1);
}

void	ft_init_sem(t_prog *prog)
{
	prog->fork = sem_open("forks", O_CREAT | O_EXCL, 0644, prog->nb_philo);
	if (prog->fork == SEM_FAILED || sem_unlink("forks"))
		printf("Error : semaphore\n");
}

void	ft_free(t_prog *prog)
{
	int	res;
	int	i;

	i = -1;
	while (++i < prog->nb_philo)
	{
		waitpid(-1, &res, 0);
		if (res != 0)
		{
			i = 0;
			while (i < prog->nb_philo)
				kill(prog->table[i++], 15);
			break ;
		}
	}
	sem_close(prog->fork);
	free(prog->table);
	free(prog);
}

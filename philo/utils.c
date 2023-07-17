/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:03:09 by mlangloi          #+#    #+#             */
/*   Updated: 2023/07/02 16:04:03 by mlangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_atoi(const char *nptr)
{
	int	rep;
	int	i;
	int	sign;

	i = 0;
	rep = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		rep = rep * 10 + (nptr[i] - '0');
		i++;
	}
	return (rep * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*dest;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_bzero((unsigned char *)dest, nmemb * size);
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_number(char *nb)
{
	int	i;

	i = 0;
	while (nb[i])
	{
		if (ft_isdigit(nb[i]) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}

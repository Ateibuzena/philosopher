/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:29:18 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/18 11:45:14 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

int	ft_atoi(const char *str)
{
	int i;
	int signe;
	long resultat;

	i = 0;
	signe = 1;
	resultat = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + (str[i] - '0');
		i++;
		if (resultat * signe > INT_MAX)
			return INT_MAX;
		if (resultat * signe < INT_MIN)
			return INT_MIN;
	}

	return (int)(resultat * signe);
}

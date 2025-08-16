/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                          :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:29:18 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/27 15:40:37 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>

static const char	*ft_skip_spaces(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\r' || *str == '\f' || *str == '\v')
		str++;
	return (str);
}

static int	ft_handle_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

static int	ft_base(const char **str, int base)
{
	if (base == 0)
	{
		if (**str == '0')
		{
			if (*(*str + 1) == 'x' || *(*str + 1) == 'X')
			{
				(*str) += 2;
				return (16);
			}
			else
			{
				(*str)++;
				return (8);
			}
		}
		return (10);
	}
	return (base);
}

static int	ft_check_overflow(long result, int digit, int base, int sign)
{
	if (sign == 1)
	{
		if (result > (LONG_MAX - digit) / base)
			return (1);
	}
	else
	{
		if (-result < (LONG_MIN + digit) / base)
			return (1);
	}
	return (0);
}

static long	ft_conversion(const char **str, int base, int *error, int sign)
{
	long	result;
	int		digit;
	int		has_digits;

	result = 0;
	has_digits = 0;
	while (**str)
	{
		if (**str >= '0' && **str <= '9')
			digit = **str - '0';
		else if (**str >= 'A' && **str <= 'Z')
			digit = **str - 'A' + 10;
		else if (**str >= 'a' && **str <= 'z')
			digit = **str - 'a' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		has_digits = 1;
		if (ft_check_overflow(result, digit, base, sign))
		{
			if (error != 0)
			{
				if (sign == 1)
					*error = 1;
				else
					*error = 2;
			}
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * base + digit;
		(*str)++;
	}
	if (!has_digits && error != 0)
		*error = 3;
	return (result);
}

long	ft_strtol(const char *str, char **endptr, int base, int *error)
{
	int		sign;
	long	result;

	if (error)
		*error = 0;
	if (!str)
	{
		if (error)
			*error = 4;
		if (endptr)
			*endptr = NULL;
		return (0);
	}
	str = ft_skip_spaces(str);
	sign = ft_handle_sign(&str);
	base = ft_base(&str, base);
	result = ft_conversion(&str, base, error, sign);
	if (*str != '\0' && error && *error == 0)
		*error = 5;
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

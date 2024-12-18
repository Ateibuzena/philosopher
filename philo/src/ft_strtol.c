/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:33:18 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/18 01:10:06 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static const char	*ft_skip_spaces(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\f' || *str == '\v')
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

static long int	ft_conversion(const char **str, int base)
{
	long int	result;
	int			digit;

	result = 0;
	digit = 0;
	while (**str)
	{
		if (**str >= '0' && **str <= '9')
			digit = **str - '0';
		else if ((**str >= 'A' && **str <= 'Z')
			|| (**str >= 'a' && **str <= 'z'))
			digit = (**str + 32) - 'a' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		result = result * base + digit;
		(*str)++;
	}
	return (result);
}

long int	ft_strtol(const char *str, char **endptr, int base)
{
	int			sign;
	long int	result;

	str = ft_skip_spaces(str);
	sign = ft_handle_sign(&str);
	base = ft_base(&str, base);
	result = ft_conversion(&str, base);
	*endptr = (char *)str;
	return (result * sign);
}

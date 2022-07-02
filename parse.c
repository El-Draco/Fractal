/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:11:12 by rriyas            #+#    #+#             */
/*   Updated: 2022/06/19 14:14:02 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

double	float_parser(char *s)
{
	int		i;
	int		neg;
	double	d;
	double	temp;

	i = 0;
	neg = 1;
	d = 0;
	if (s[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (s[i] && s[i] != '.')
		d = d * 10 + (s[i++] - '0');
	if (s[i] && s[i] == '.')
		i++;
	temp = 0.1;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		d += (s[i++] - '0') * temp;
		temp /= 10;
	}
	return (neg * d);
}

int	white_space(char ch)
{
	if (ch == ' ')
		return (1);
	if (ch >= 9 && ch <= 13)
		return (1);
	return (0);
}

int	extra_chars(char *str)
{
	int	i;
	int	m_count;
	int	d_count;
	int	p_count;

	i = 0;
	m_count = 0;
	d_count = 0;
	p_count = 0;
	while (str[i])
	{
		if (str[i] == '+')
			p_count++;
		else if (str[i] == '-')
			m_count++;
		else if (str[i] == '.')
			d_count ++;
		i++;
	}
	return (p_count <= 1 && d_count <= 1 && m_count <= 1);
}

int	find_invalid_chars(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (extra_chars(argv[i]) != 1)
			return (-1);
		while (argv[i][j])
		{
			if (!is_num(&argv[i][j]) && argv[i][j] != '+'
				&& argv[i][j] != '-' && argv[i][j] != '.')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate(int argc, char **argv, t_render *f)
{
	if (argc == 1 || !is_num(argv[1]) || find_invalid_chars(argv))
		return (-1);
	if (ft_strncmp("1", argv[1], 2) == 0
		|| ft_strncmp("3", argv[1], 2) == 0
		|| ft_strncmp("4", argv[1], 2) == 0)
	{
		if (argc > 2)
			return (-1);
	}
	else if (ft_strncmp(argv[1], "2", 2) == 0)
	{
		if (argc != 4)
			return (-1);
		f->c.x = float_parser(argv[2]);
		f->c.y = float_parser(argv[3]);
	}
	else
		return (-1);
	f->type = ft_atoi(argv[1]);
	return (0);
}

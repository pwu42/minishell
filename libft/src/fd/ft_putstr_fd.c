/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:05:49 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/28 15:22:15 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/fd.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (s[i] != 0)
	{
		ft_putchar_fd(s[i], fd);
		++i;
	}
}

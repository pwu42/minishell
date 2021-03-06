/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:15:56 by pwu               #+#    #+#             */
/*   Updated: 2022/04/07 14:08:09 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	find_size(char *s)
{
	int	quote;
	int	i;
	int	size;

	quote = 0;
	i = -1;
	size = 0;
	while (s[++i])
		if (!is_quote(s[i], &quote))
			size += 1;
	return (size);
}

void	quote_remove(t_tok *cur_tok, t_minishell *sh)
{
	int		size;
	char	*res;
	int		i;
	int		quote;
	int		j;

	size = find_size(cur_tok->content);
	res = ymalloc(sizeof(char) * (size + 1), sh);
	i = -1;
	j = -1;
	quote = 0;
	while (cur_tok->content[++i])
		if (!is_quote(cur_tok->content[i], &quote))
			res[++j] = cur_tok->content[i];
	res[j + 1] = 0;
	cur_tok->content = res;
}

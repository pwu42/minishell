/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:19:37 by pwu               #+#    #+#             */
/*   Updated: 2022/04/19 12:04:32 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	redir_one(t_elem *elem, t_command *cmd, t_redir *redir)
{
	if (redir->type == REDIR_IN)
	{
		if (cmd->fdin != cmd->here_doc)
			ft_close(&cmd->fdin);
		cmd->fdin = open(redir->var, O_RDONLY);
	}
	if (redir->type == REDIR_TRUNC)
	{
		ft_close(&cmd->fdout);
		cmd->fdout = open(redir->var, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (redir->type == REDIR_HEREDOC)
	{
		if (cmd->fdin != cmd->here_doc)
			ft_close(&cmd->fdin);
		cmd->fdin = cmd->here_doc;
	}
	if (redir->type == REDIR_APPEND)
	{
		ft_close(&cmd->fdout);
		cmd->fdout = open(redir->var, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	if (cmd->fdin == -1 || cmd->fdout == -1)
		return (perror(redir->var), exec_close_fds(elem), -1);
	return (0);
}

int	exec_redir(t_elem *elem, t_command *cmd)
{
	t_elem	*cur_elem;
	t_redir	*cur_redir;

	cur_elem = cmd->redir.head;
	while (cur_elem != NULL)
	{
		cur_redir = cur_elem->data;
		if (redir_one(elem, cmd, cur_redir) != 0)
			return (-1);
		cur_elem = cur_elem->next;
	}
	return (0);
}

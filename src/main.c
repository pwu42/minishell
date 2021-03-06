/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:52 by pwu               #+#    #+#             */
/*   Updated: 2022/04/19 14:59:00 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned char	g_exit_status = 0;

static void	minishell_read(t_line *cmdline, t_minishell *sh)
{
	signal_handler(HANDLER_RL, sh);
	cmdline->line = readline(PROMPT);
	if (!cmdline->line)
		return ;
	signal_handler(HANDLER_MAIN, sh);
	cmdline->len = ft_strlen(cmdline->line);
	if (cmdline->len > 0)
		add_history(cmdline->line);
	cmdline->i = 0;
}

static int	minishell_start(t_minishell *sh)
{
	int	err_code;

	err_code = lex(sh);
	if (err_code != 0)
		return (ft_dlist_destroy(&sh->dl_tok), err_code);
	parse(sh);
	make_cmds(sh);
	ft_dlist_destroy(&sh->dl_tok);
	err_code = make_heredocs(sh);
	if (err_code != 0)
		return (ft_dlist_destroy(&sh->dl_cmd), err_code);
	err_code = minishell_exec(sh);
	if (err_code != 0)
		return (ft_dlist_destroy(&sh->dl_cmd), err_code);
	ft_dlist_destroy(&sh->dl_cmd);
	return (0);
}

static int	minishell_init(t_minishell *sh, char **envp)
{
	signal_handler(HANDLER_MAIN, sh);
	ft_dlist_init(&sh->dl_cmd, cmd_destroy);
	ft_dlist_init(&sh->dl_env, free);
	ft_dlist_init(&sh->dl_tok, free);
	ft_dlist_init(&sh->dl_malloc, free);
	sh->cmdline.line = NULL;
	set_env(sh, envp);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	sh;

	(void)ac;
	(void)av;
	if (!isatty(0) || !isatty(1) || minishell_init(&sh, envp) != 0)
		return (EXIT_FAILURE);
	while (1)
	{
		minishell_read(&sh.cmdline, &sh);
		if (!sh.cmdline.line)
			break ;
		if (minishell_start(&sh) == -1)
			perror_exit("minishell", &sh);
		free(sh.cmdline.line);
	}
	ft_dlist_destroy(&sh.dl_env);
	ft_dlist_destroy(&sh.dl_malloc);
	rl_clear_history();
	return (g_exit_status);
}

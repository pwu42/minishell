/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:30:37 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/12 18:46:50 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handler_rl(int signo, siginfo_t *si, void *ignore)
{
	(void) ignore;
	(void) si;
	if (signo == SIGINT)
	{
		printf("^C");
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
	if (signo == SIGQUIT)
		return ;
}

void	handler_child(int signo, siginfo_t *si, void *ignore)
{
	(void) ignore;
	(void) si;
	if (signo == SIGINT)
	{
		printf("^C");
		exit(2);
	}
	if (signo == SIGQUIT)
		return ;
}

void	handler_parent(int signo, siginfo_t *si, void *ignore)
{
	(void) ignore;
	(void) si;
	if (signo == SIGINT)
	{
		printf("^C");
		exit(2); 
	}
	if (signo == SIGQUIT)
		return ;
}

void	signal_handler(int handler, t_minishell *sh)
{
	struct sigaction	sa;

	sa = sh->sa;

	echo_off();
	sigemptyset(&sa.sa_mask);
	if (handler == 0)
		sa.sa_handler = SIG_IGN;
	else if (handler == 1)
		sa.sa_sigaction = handler_rl;
	else if (handler == 2)
		sa.sa_sigaction = handler_parent;
	else if (handler == 3)
		sa.sa_sigaction = handler_child;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	echo_off(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
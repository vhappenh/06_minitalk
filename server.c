/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:59:39 by vhappenh          #+#    #+#             */
/*   Updated: 2023/02/09 10:03:29 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_out = 0;

static int	get_shifty(int signum, int reset)
{
	static int		count_char = 0;

	if (reset == 0)
	{
		count_char = 0;
		reset = 1;
	}
	if (signum == SIGUSR1)
		g_out = g_out << 1;
	else if (signum == SIGUSR2)
	{
		g_out = ~g_out;
		g_out = g_out << 1;
		g_out = ~g_out;
	}
	count_char ++;
	if (count_char == 8)
	{
		write(1, &g_out, 1);
		count_char = 0;
	}
	return (1);
}

static void	sighandler(int signum, siginfo_t *info, void *context)
{
	static int		reset;
	static pid_t	pid_c = 0;
	static pid_t	pid_compare = 0;

	(void)context;
	pid_c = info->si_pid;
	if (pid_compare == 0)
		pid_compare = pid_c;
	if (pid_c != pid_compare)
	{
		reset = 0;
		pid_compare = pid_c;
	}
	reset = get_shifty(signum, reset);
	usleep(50);
	kill(pid_c, SIGUSR1);
}

int	main(void)
{
	pid_t				pid_s;
	struct sigaction	sa;

	sa.sa_sigaction = sighandler;
	sa.sa_flags = SA_SIGINFO;
	pid_s = getpid();
	if (pid_s == -1)
		return (1);
	ft_printf("PID: %d\n", pid_s);
	ft_printf("waiting for instructions...\n");
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

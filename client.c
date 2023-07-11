/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:03:16 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/23 16:16:52 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handshake(int signum)
{
	(void)signum;
}

void	ft_sendsignals(pid_t pid_s, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
	{
		i = 7;
		while (i >= 0)
		{
			if ((str[j] >> i) & 1)
				kill(pid_s, SIGUSR2);
			else
				kill(pid_s, SIGUSR1);
			i--;
			pause();
		}
		j++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid_s;

	if (argc != 3)
		return (write(1, "Wrong number of arguments! [PID, string]\n", 41));
	pid_s = ft_atoi(argv[1]);
	i = 0;
	signal(SIGUSR1, handshake);
	ft_sendsignals(pid_s, argv[2]);
	return (0);
}

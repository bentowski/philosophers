/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:22:44 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/28 15:47:25 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_free_all(t_rules *r)
{
	if (r)
	{
		if (r->forks)
			free(r->forks);
		if (r->th_p)
			free(r->th_p);
		if (r->philos)
			free(r->philos);
		free(r);
	}
}

int	ft_error(int msg, t_rules *rules)
{
	ft_free_all(rules);
	if (msg == UND)
		printf("%s\n%s\n", "Error", "Error undefined" );
	if (msg == ARG)
		printf("%s\n%s\n", "Error", "bad, to much or missing arguments");
	if (msg == MEM)
		printf("%s\n%s\n", "Error", "bad memory allocations");
	if (msg == GTD)
		printf("%s\n%s\n", "Error", "gettimeofday crashed" );
	if (msg == MUT)
		printf("%s\n%s\n", "Error", "Mutex crashed" );
	if (msg == THC)
		printf("%s\n%s\n", "Error", "Thread create fail" );
	if (msg == TEST)
		printf("%s\n%s\n", "Error", "TEST ERROR OK" );
	return (-1);
}

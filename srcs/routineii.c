/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routineii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:23:26 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/28 15:23:26 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_usleep(unsigned long long t, t_philo *p)
{
	unsigned long long	x;

	x = get_now_timecaca(p->r);
	pthread_mutex_lock(&p->r->end_m);
	while (!p->r->end && (get_now_timecaca(p->r) - x) < t)
	{
		pthread_mutex_unlock(&p->r->end_m);
		usleep(10);
		pthread_mutex_lock(&p->r->end_m);
	}
	pthread_mutex_unlock(&p->r->end_m);
}

int	action(t_philo *p, char *m, int opt, unsigned long long t)
{
	get_now_timeph(p, p->r);
	pthread_mutex_lock(&p->r->end_m);
	pthread_mutex_lock(&p->lasteat_m);
	if (opt && !p->r->end)
	{
		p->lasteat = p->now_time;
	}
	pthread_mutex_unlock(&p->lasteat_m);
	pthread_mutex_unlock(&p->r->end_m);
	ft_write_p(p, m);
	ft_usleep(t, p);
	return (0);
}

void	*threadcreateerror(t_philo *p)
{
	pthread_mutex_lock(&p->r->end_m);
	p->r->end = 1;
	p->r->err = THC;
	pthread_mutex_unlock(&p->r->end_m);
	return (NULL);
}

void	ft_return(t_philo *p)
{
	char	*ret;

	pthread_join(p->is_dead, (void **) &ret);
}

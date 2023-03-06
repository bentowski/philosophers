/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:23:21 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/28 18:23:34 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	eat_timei(t_philo *p)
{
	pthread_mutex_lock(p->fl);
	action(p, "has taken a fork", 0, 0);
	if (p->fr == p->fl)
	{
		pthread_mutex_unlock(p->fl);
		usleep((p->r->ttd + 1) * 1000);
		return (1);
	}
	pthread_mutex_lock(p->fr);
	action(p, "has taken a fork", 0, 0);
	action(p, "is eating", 1, p->r->tte);
	pthread_mutex_unlock(p->fl);
	pthread_mutex_unlock(p->fr);
	usleep(950);
	return (0);
}

static int	eat_timep(t_philo *p)
{
	pthread_mutex_lock(p->fr);
	action(p, "has taken a fork", 0, 0);
	if (p->fl == p->fr)
	{
		pthread_mutex_unlock(p->fr);
		usleep((p->r->ttd + 1) * 1000);
		return (1);
	}
	pthread_mutex_lock(p->fl);
	action(p, "has taken a fork", 0, 0);
	action(p, "is eating", 1, p->r->tte);
	pthread_mutex_unlock(p->fr);
	pthread_mutex_unlock(p->fl);
	return (0);
}

static int	philo_routine_ii(t_philo *p)
{
	if (p->nb % 2)
		eat_timei(p);
	else
		eat_timep(p);
	action(p, "is sleeping", 0, p->r->tts);
	action(p, "is thinking", 0, 0);
	return (0);
}

static void	philo_routine_iii(t_philo *p)
{
	if (p->rounds > -1)
	{
		if (!p->rounds--)
		{
			pthread_mutex_lock(&p->r->end_m);
			pthread_mutex_lock(&p->r->finish_ph_m);
			if (p->r->finish_philos == p->r->nb_philos - 1)
				p->r->end = 1;
			p->r->finish_philos++;
			pthread_mutex_unlock(&p->r->finish_ph_m);
			pthread_mutex_unlock(&p->r->end_m);
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *) arg;
	pthread_mutex_lock(&p->r->goodtogo);
	pthread_mutex_unlock(&p->r->goodtogo);
	if (p->nb % 2)
		usleep(5000);
	if (pthread_create(&p->is_dead, NULL, is_it_alive, p))
		return (threadcreateerror(p));
	pthread_mutex_lock(&p->r->end_m);
	while (!p->r->end)
	{
		pthread_mutex_unlock(&p->r->end_m);
		philo_routine_ii(p);
		philo_routine_iii(p);
		pthread_mutex_lock(&p->r->end_m);
	}
	pthread_mutex_unlock(&p->r->end_m);
	ft_return(p);
	return (NULL);
}

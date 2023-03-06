/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:22:26 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/28 15:22:29 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	geterror(t_philo *p)
{
	pthread_mutex_lock(&p->r->end_m);
	p->r->end = 1;
	pthread_mutex_unlock(&p->r->end_m);
	pthread_mutex_lock(&p->r->mutex_write);
	printf("%s\n%s\n", "Error", "gettimeofday crashed");
	pthread_mutex_unlock(&p->r->mutex_write);
	return ;
}

static void	minibndistributeurdesourire(t_philo *p)
{
	if (!p->r->end)
		printf("%llu %d died\n", p->time_laps, p->nb);
}

static void	is_it_alive_iii(t_philo *p)
{
	pthread_mutex_lock(&p->r->end_m);
	pthread_mutex_lock(&p->lasteat_m);
	if (!p->r->end && (p->lasteat < p->time_laps)
		&& p->ttd <= p->time_laps - p->lasteat)
	{
		pthread_mutex_lock(&p->r->mutex_write);
		minibndistributeurdesourire(p);
		pthread_mutex_unlock(&p->r->mutex_write);
		p->r->end = 1;
	}
	pthread_mutex_unlock(&p->lasteat_m);
	pthread_mutex_unlock(&p->r->end_m);
}

static void	is_it_alive_ii(t_philo *p, struct timeval time)
{
	p->time_laps = (time.tv_sec * 1000 + time.tv_usec / 1000)
		- p->r->start_time;
}

void	*is_it_alive(void *arg)
{
	struct timeval	time;
	t_philo			*p;

	p = (t_philo *)arg;
	usleep(p->r->ttd * 1000 + 1);
	pthread_mutex_lock(&p->r->end_m);
	while (!p->r->end)
	{
		pthread_mutex_unlock(&p->r->end_m);
		if (gettimeofday(&time, NULL))
			geterror(p);
		is_it_alive_ii(p, time);
		is_it_alive_iii(p);
		usleep(5000);
		pthread_mutex_lock(&p->r->end_m);
	}
	pthread_mutex_unlock(&p->r->end_m);
	return (NULL);
}

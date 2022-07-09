/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfranco- <nfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:15:05 by lcouto            #+#    #+#             */
/*   Updated: 2022/07/09 19:19:49 by nfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	if (*philo->death == FALSE && is_philo_satiated(philo) == FALSE)
	{
		pthread_mutex_lock(philo->print_lock);
		output(timestamp(philo->session_start), philo->name, DROP_LEFT_FORK, 0);
		pthread_mutex_unlock(philo->print_lock);
	}
	pthread_mutex_unlock(philo->right_fork);
	if (*philo->death == FALSE && is_philo_satiated(philo) == FALSE)
	{
		pthread_mutex_lock(philo->print_lock);
		output(timestamp(philo->session_start), philo->name, DROP_RIGHT_FORK, 0);
		pthread_mutex_unlock(philo->print_lock);
	}
	philo->meals_eaten += 1;
}

void	pick_up_forks(t_philo *philo)
{
	if (*philo->death == FALSE && is_philo_satiated(philo) == FALSE)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->print_lock);
		output(timestamp(philo->session_start), philo->name, PICK_LEFT_FORK, 0);
		pthread_mutex_unlock(philo->print_lock);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->print_lock);
		output(timestamp(philo->session_start), philo->name, PICK_RIGHT_FORK, 0);
		pthread_mutex_unlock(philo->print_lock);
		philo->last_meal = timestamp(philo->session_start);
	}
}

int	thinking(t_philo *philo)
{
	if (*philo->death == TRUE || is_philo_satiated(philo) == TRUE)
		return (FALSE);
	else
	{
		pthread_mutex_lock(philo->print_lock);
		output(timestamp(philo->session_start), philo->name, THINKING, 0);
		pthread_mutex_unlock(philo->print_lock);
		return (TRUE);
	}
}

int	sleeping(t_philo *philo)
{
	if (*philo->death == TRUE || is_philo_satiated(philo) == TRUE)
		return (FALSE);
	else
	{
		pthread_mutex_lock(philo->print_lock);
		output(timestamp(philo->session_start), philo->name, SLEEPING, 0);
		pthread_mutex_unlock(philo->print_lock);
		wait_time_in_ms(philo->sleep_time);
		return (TRUE);
	}
}

int	eating(t_philo *philo)
{
	if (*philo->death == TRUE || is_philo_satiated(philo) == TRUE)
		return (FALSE);
	if ((timestamp(philo->session_start) - philo->last_meal)
		> philo->death_time && *philo->death == FALSE)
		return (FALSE);
	pick_up_forks(philo);
	pthread_mutex_lock(philo->print_lock);
	output(timestamp(philo->session_start), philo->name, EATING, 0);
	pthread_mutex_unlock(philo->print_lock);
	wait_time_in_ms(philo->eat_time);
	release_forks(philo);
	return (TRUE);
}

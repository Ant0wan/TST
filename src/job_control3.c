/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:42 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 18:58:24 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"

void	wait_for_job(t_job *j)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(pid, status) && !job_is_stopped(j)
			&& !job_is_completed(j))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}

void	format_job_info (t_job *j, const char *status)
{
	ft_dprintf(STDERR_FILENO, "%ld (%s): %s\n",
			(long)j->pgid, status, j->command);
}

void	do_job_notification(void)
{
	t_job	*j;
	t_job	*jlast;
	t_job	*jnext;

	update_status();
	jlast = NULL;
	j = first_job;
	while (j)
	{
		jnext = j->next;
		if (job_is_completed(j))
		{
			format_job_info(j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				first_job = jnext;
			free_job(j);
		}
		else if (job_is_stopped(j) && !j->notified)
		{
			format_job_info(j, "stopped");
			j->notified = 1;
			jlast = j;
		}
		else
			jlast = j;
		j = jnext;
	}
}

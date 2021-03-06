/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:32:58 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/14 17:19:54 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_errno.h"
#include "shell.h"
#include "builtins.h"

void		free_process(t_process *p)
{
	char	**wt;

	free_redirections(p->redir);
	if ((wt = p->argv))
	{
		while (*wt)
			free(*wt++);
	}
	free(p->argv);
	free(p);
	p = NULL;
}

static void	perf_redir(t_process *p)
{
	int ret;

	if (p->infile != STDIN_FILENO)
	{
		dup2(p->infile, STDIN_FILENO);
		close(p->infile);
	}
	if (p->outfile != STDOUT_FILENO)
	{
		dup2(p->outfile, STDOUT_FILENO);
		close(p->outfile);
	}
	if (p->errfile != STDERR_FILENO)
	{
		dup2(p->errfile, STDERR_FILENO);
		close(p->errfile);
	}
	if ((ret = do_redirection(p->redir)))
	{
		free_all_jobs();
		exit_clean(g_errordesc[ret].code);
	}
}

int			launch_process(t_process *p, pid_t pgid, int foreground)
{
	char		**envp;
	pid_t		pid;
	int			ret;

	g_noexit = 1;
	envp = get_env_tab();
	perf_redir(p);
	if (p->status)
		exit_clean(p->status);
	if (g_shell_is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (g_job_control_enabled && foreground)
			tcsetpgrp(g_shell_terminal, pgid);
		restore_procmask();
	}
	ret = execute_process(p->argv, envp, NULL, NULL);
	free_all_jobs();
	ft_tabdel(&envp);
	return (exit_clean(ret));
}

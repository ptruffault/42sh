
#include <shell42.h>

void ft_process_background(t_process *p)
{
	if (p->status == SUSPENDED)
		ft_kill(p, SIGCONT);
	if ((ioctl(0, TIOCSPGRP, &p->pid)) != 0)
	{
		error("can't set this process in background", p->cmd);
		ft_kill(p, SIGTSTP);
	}
	else
		p->status = RUNNING_BG;
}

void		ft_kill(t_process *p, int sig)
{
	if (p && p->pid > 0 && p->status != DONE && p->status != KILLED 
	&& 1 <= sig && sig <= 31)
	{
		if (sig == SIGTSTP || sig == SIGSTOP)
			p->status = SUSPENDED;
		else if (sig == SIGCONT)
			p->status = RUNNING_FG;
		else
			p->status = KILLED;
		ft_printf("kill(%i, %i); status = %i\n",p->pid, sig, p->status);
		if (p->builtins == FALSE && p->pid > 0)
		{
			if (sig == -1)
				ft_process_background(p);
			kill(p->pid, sig);
		}
	}
}

void	ft_killgrp(t_process *p, int sig)
{
	while (p)
	{
		ft_kill(p, sig);
		p = p->grp;
	}
}


int			kill_process(t_process *p, int sig, unsigned int status)
{
	int i;

	i = 0;
	while (p)
	{
		if (p->status == status)
		{
			ft_killgrp(p, sig);
			i++;
		}
		p = p->next;
	}
	return (i);
}

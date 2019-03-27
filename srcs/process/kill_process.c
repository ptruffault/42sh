
#include <shell42.h>

pid_t ft_tcgetpgrp(int fd)
{
 	int pgrp;

 	if (ioctl(fd, TIOCGPGRP, &pgrp) < 0)
		return -1 ;
	return pgrp ;
}

int ft_tcsetpgrp(int fd, pid_t pgrp)
{
 int pgrp_int = pgrp;
	 return (ioctl(fd, TIOCSPGRP, &pgrp_int));
}

void		ft_kill(t_process *p, int sig)
{
	if (p && p->pid > 0 && p->status != DONE && p->status != KILLED 
	&& 1 <= sig && sig <= 31)
	{
		p->sig = sig;
		if (sig == SIGTSTP || sig == SIGSTOP)
			p->status = SUSPENDED;
		else if (sig == SIGCONT)
			p->status = RUNNING_FG;
		else
			p->status = KILLED;
		ft_printf("kill(%i, %i); status = %i\n",p->pid, sig, p->status);
		if (p->builtins == FALSE && p->pid > 0)
			kill(p->pid, sig);
	}
}

void	ft_killgrp(t_process *p, int sig)
{
	while (p)
	{
		if (sig == -1)
		{
			
		}
		else
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

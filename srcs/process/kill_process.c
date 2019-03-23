
#include <shell42.h>


static t_process	*ft_get_process(t_process *p, unsigned int status)
{
	//t_process *tmp;

	while (p)
	{
		if (p->status == status && p->pid > 0 && p->builtins == FALSE)
			return (p);
		/*if (p->grp)
		{
			tmp = p->grp;
			while (tmp)
			{
				if (tmp->status == status && p->pid > 0)
					return (tmp);
				tmp = tmp->grp;
			}
		}*/
		p = p->next;
	}
	return (NULL);
}


//kill tout les process de p->status == status } avec sig , le status des process es changer 
// sig == -1 -> put in bg avec iotcl

void ft_process_background(t_process *p)
{
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
	if (sig == -1)
		ft_process_background(p);
	else
	{
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

void 		ft_killgrp(t_process *p, int sig)
{
	while (p)
	{
		ft_kill(p, sig);
		p = p->grp;
	}
}


int			kill_process(t_process *p, int sig, unsigned int status)
{
	t_process *tmp;
	int i;

	i = 0;
	while (p && (tmp = ft_get_process(p, status)))
	{
		i++;
		ft_killgrp(p, sig);
	}
	return (i);
}

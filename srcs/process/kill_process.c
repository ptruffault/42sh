
#include <shell42.h>


static t_process	*ft_get_process(t_process *p, unsigned int status)
{
	t_process *tmp;

	while (p)
	{
		if (p->status == status && p->pid > 0)
			return (p);
		if (p->grp)
		{
			tmp = p->grp;
			while (tmp)
			{
				if (tmp->status == status && p->pid > 0)
					return (tmp);
				tmp = tmp->grp;
			}
		}
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
		kill(p->pid, SIGTSTP);
		p->status = SUSPENDED;
	}
	else
	{
		ft_printf("\t{%i} running background %s\n", p->pid, p->cmd);
		p->status = RUNNING_BG;
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
		if (sig == SIGINT)
		{
			ft_printf("\t{%i} killed %s\n", tmp->pid, tmp->cmd);
			tmp->status = KILLED;
		}
		else if (sig == SIGTSTP)
		{
			ft_printf("\t{%i} suspended %s\n", tmp->pid, tmp->cmd);
			tmp->status = SUSPENDED;
		}
		else if (sig == SIGCONT)
		{
			ft_printf("\t{%i} continued %s\n", tmp->pid, tmp->cmd);
			tmp->status = RUNNING_FG;
		}
		if (sig == -1)
			ft_process_background(p);
		else
			killpg(tmp->pid, sig);
	}
	return (i);
}

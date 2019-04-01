#include "shell42.h"

void ft_update_status(t_process *p, unsigned int status)
{
	char *stat[6];

	ft_process_tab_status(stat);
	ft_printf("%i %s %s\n", p->pid, stat[status], p->cmd);
	while (p)
	{
		p->status = status; 
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
			if (p->pid > 0 && p->status != DONE && p->status != KILLED)
			{
				p->sig = sig;
				if (kill(-p->pid, sig) < 0)
					warning("kill fucked up", p->cmd);
				i++;
			}
		}
		p = p->next;
	}
	return (i);
}

#include <shell42.h>
#include "../includes/get_input.h"


void ft_process_tab_status(char *stat[6])
{
	stat[0] = "\033[00;31minitialised\033[00m";
	stat[1] = "\033[00;34mrunning fg\033[00m";
	stat[2] = "\033[00;34mrunning bg\033[00m";
	stat[3] = "\033[1;32mdone\033[00m";
	stat[4] = "\033[1;36msuspended\033[00m";
	stat[5] = "\033[00;31mkilled\033[00m";
}


void	ft_put_process(t_process *p, t_shell *sh)
{	
	char *stat[6];

	ft_process_tab_status(stat);
	ft_delete_line(&sh->e);
	ft_printf("\t{%i} \033[1;32m%s\033[00m  %s\n", 
		p->pid, stat[p->status], p->cmd);
	ft_putstr(sh->e.hist->s);
}



void	ft_sigcont(t_process *tmp)
{
	while (tmp)
	{
		if (tmp->status == SUSPENDED)
		{
			ft_printf("\t{%i} continued %s\n", tmp->pid, tmp->cmd);
			kill(tmp->pid, SIGCONT);
		}

		tmp = tmp->grp;
	}
}

void ft_set_background(t_process *p)
{
	if (p->status == INIT || p->status == SUSPENDED || p->status == RUNNING_FG)
	{
		if (p->status == SUSPENDED)
			ft_sigcont(p);
		ft_printf("\t{%i} running background %s\n", p->pid, p->cmd);
		p->status = RUNNING_BG;
	}
}

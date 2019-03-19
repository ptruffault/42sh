
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

int			kill_process(t_process *p, int sig, unsigned int status)
{
	t_process *tmp;
	int i;

	i = 0;
	while (p && (tmp = ft_get_process(p, status)))
	{
		i++;
		if (sig == SIGINT)
			tmp->status = KILLED;
		else if (sig == SIGTSTP)
		{
			ft_printf("{%i} suspended %s\n", tmp->pid, tmp->cmd);
			tmp->status = SUSPENDED;
		}
		kill(tmp->pid, sig);
	}
	return (i);
}

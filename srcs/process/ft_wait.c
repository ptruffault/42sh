#include <shell42.h>

int	ft_wait(t_process *p)
{
	int ret;

	ret = 0;
	while (p)
	{
		if (p->pid == 0 
			|| (p->status == RUNNING_FG && waitpid(p->pid, &p->ret, WUNTRACED) > 0)
			 || (p->status == RUNNING_BG && waitpid(p->pid, &p->ret, WUNTRACED | WNOHANG) > 0))
		{
			if (WIFCONTINUED(p->ret) && p->status == RUNNING_FG)
				ft_wait(p);
			if (WIFSIGNALED(p->ret) || p->background == TRUE || WIFSTOPPED(p->ret))
			{
				if (WIFSIGNALED(p->ret))
				{
					p->sig = WTERMSIG(p->ret);
					p->ret = p->ret + 128;
				}
				if (WIFSTOPPED(p->ret))
					p->status = SUSPENDED;
				else
					p->status = KILLED;
				ft_put_process(p);
			}
			else if (p->ret > 0 && WIFEXITED(p->ret))
			{
				p->ret =  WEXITSTATUS(p->ret);
				p->status = DONE;
			}
			else  if (p->status == RUNNING_BG || p->status == RUNNING_FG)
				p->status = DONE;
			ret = ret + p->ret;	
		}
		p = p->grp;
	}
	return (ret);
}

void ft_wait_background(t_shell *sh)
{
	t_process *tmp;

	tmp = sh->process;
	while (tmp)
	{
		if (tmp->status == RUNNING_BG)
			ft_wait(tmp);
		tmp = tmp->next;
	}
}


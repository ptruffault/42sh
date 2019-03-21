#include <shell42.h>

//| WCONTINUED
void	ft_wait(t_process *p, t_shell *sh)
{
	while (p)
	{
		if ((p->pid == 0
				|| (p->status == RUNNING_FG && waitpid(p->pid, &p->ret, WUNTRACED) > 0)
			 	|| (p->status == RUNNING_BG && waitpid(p->pid, &p->ret, WUNTRACED | WNOHANG) > 0))
				&& IS_RUNNING(p->status))
		{
			if (WIFSIGNALED(p->ret))
			{
				ft_printf("\n%s killed by signal %i\n", p->cmd, WTERMSIG(p->ret));
				if (WTERMSIG(p->ret) == SIGTSTP)
				{
					ft_printf("\t{%i} suspended %s\n", p->pid, p->cmd);
					p->status = SUSPENDED;
				}
				else
					p->status = KILLED;
			}
			else 
			{
				if (p->status == RUNNING_BG)
					ft_put_process(p, sh, DONE);
				if (WIFEXITED(p->ret))
					p->ret =  WEXITSTATUS(p->ret);
				p->status = DONE;
			}
		}
		p = p->grp;
	}
}

void ft_wait_background(t_shell *sh)
{
	t_process *tmp;

	tmp = sh->process;
	while (tmp)
	{
		if (tmp->status == RUNNING_BG)
			ft_wait(tmp, sh);
		tmp = tmp->next;
	}
}


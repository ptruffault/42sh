#include <shell42.h>

//| WCONTINUED
void	ft_wait(t_process *p, t_shell *sh)
{
	while (p)
	{
		if ((p->builtins == TRUE
		|| (p->status == RUNNING_FG &&  waitpid(p->pid, &p->ret, WUNTRACED ) > 0)
		|| (p->status == RUNNING_BG && waitpid(p->pid, &p->ret, WUNTRACED | WNOHANG) > 0))
		&& IS_RUNNING(p->status))
		{
			if (p->status == RUNNING_BG)
			{
				p->status = DONE;
				ft_put_process(p, sh);
			}
			p->status = DONE;
			if (WIFEXITED(p->ret))
				p->ret =  WEXITSTATUS(p->ret);
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


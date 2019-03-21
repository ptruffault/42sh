#include <shell42.h>

//| WCONTINUED


/*static const t_sig_msg	g_signal_msg[] = {
		{.sig = SIGHUP, .rtn = 129, .msg = "Hangup"},
		{.sig = SIGINT, .rtn = 1, .msg = ""},
		{.sig = SIGQUIT, .rtn = 131, .msg = "Quit"},
		{.sig = SIGILL, .rtn = 132, .msg = "Illegal instruction"},
		{.sig = SIGTRAP, .rtn = 133, .msg = "Trace/BPT trap"},
		{.sig = SIGABRT, .rtn = 134, .msg = "Abort"},
		{.sig = SIGFPE, .rtn = 136, .msg = "Floating exception"},
		{.sig = SIGKILL, .rtn = 137, .msg = "Killed"},
		{.sig = SIGBUS, .rtn = 138, .msg = "Bus error"},
		{.sig = SIGSEGV, .rtn = 139, .msg = "Segmentation fault"},
		{.sig = SIGSYS, .rtn = 140, .msg = "Bad system call"},
		{.sig = SIGPIPE, .rtn = 141, .msg = "Broken pipe"},
		{.sig = SIGALRM, .rtn = 142, .msg = "Alarm clock"},
		{.sig = SIGTERM, .rtn = 143, .msg = "Terminated"},
		{.sig = SIGURG, .rtn = 0, .msg = ""},
		{.sig = SIGXCPU, .rtn = 152, .msg = "Cputime limit exceeded"},
		{.sig = SIGXFSZ, .rtn = 153, .msg = "Filesize limit exceeded"},
		{.sig = SIGVTALRM, .rtn = 142, .msg = "Alarm clock"},
		{.sig = SIGPROF, .rtn = 155, .msg = "Profiling time alarm"},
		{.sig = SIGUSR1, .rtn = 158, .msg = "User signal 1"},
		{.sig = SIGUSR2, .rtn = 159, .msg = "User signal 2"},
		{.msg = NULL}
};
*/

static const t_sig_msg	g_signal_msg[] = {
		{.sig = SIGHUP, .rtn = 129, .msg = "Hangup"},
		{.sig = SIGINT, .rtn = 1, .msg = "Interupted"},
		{.sig = SIGQUIT, .rtn = 131, .msg = "Quit"},
		{.sig = SIGILL, .rtn = 132, .msg = "Illegal instruction"},
		{.sig = SIGTRAP, .rtn = 133, .msg = "Trace/BPT trap"},
		{.sig = SIGABRT, .rtn = 134, .msg = "Abort"},
		{.sig = SIGEMT, .rtn = 135, .msg = "emulate instruction executed"},
		{.sig = SIGFPE, .rtn = 136, .msg = "Floating exception"},
		{.sig = SIGKILL, .rtn = 137, .msg = "Killed"},
		{.sig = SIGBUS, .rtn = 138, .msg = "Bus error"},
		{.sig = SIGSEGV, .rtn = 139, .msg = "Segmentation fault"},
		{.sig = SIGSYS, .rtn = 140, .msg = "Bad system call"},
		{.sig = SIGPIPE, .rtn = 141, .msg = "Broken pipe"},
		{.sig = SIGALRM, .rtn = 142, .msg = "Alarm clock"},
		{.sig = SIGTERM, .rtn = 143, .msg = "Terminated"},
		{.sig = SIGURG, .rtn = 0, .msg = ""},
		{.sig = SIGSTOP, .rtn = 17, .msg = "Suspended"},
		{.sig = SIGTSTP, .rtn = 18, .msg = "Suspended"},
		{.sig = SIGCONT, .rtn = 19, .msg = "Continued"},
		{.sig = SIGCHLD, .rtn = 20, .msg = "Done"},
		{.sig = SIGTTIN, .rtn = 21, .msg = "background read attempted from control terminal"},
		{.sig = SIGTTOU, .rtn = 22, .msg = "background write attempted from control terminal"},
		{.sig = SIGIO, .rtn = 23, .msg = "I/O is possible on a descriptor"},
		{.sig = SIGXCPU, .rtn = 24, .msg = "Cputime limit exceeded"},
		{.sig = SIGXFSZ, .rtn = 25, .msg = "Filesize limit exceeded"},
		{.sig = SIGVTALRM, .rtn = 26, .msg = "Alarm clock"},
		{.sig = SIGPROF, .rtn = 27, .msg = "Profiling time alarm"},
		{.sig = SIGUSR1, .rtn = 30, .msg = "User signal 1"},
		{.sig = SIGUSR2, .rtn = 31, .msg = "User signal 2"},
		{.msg = NULL}
};

static void	ft_signal_check(t_process *p)
{
 	ft_printf("%s killed by signal %i \x1B[00;31m%s\x1B[00m\n", p->cmd, WTERMSIG(p->ret), g_signal_msg[WTERMSIG(p->ret) - 1].msg);
 	if (WIFSTOPPED(p->ret))
		p->status = SUSPENDED;
	else if (WIFCONTINUED(p->ret))
		p->status = KILLED;
}

void	ft_wait(t_process *p, t_shell *sh)
{
	int prompt;
	(void)sh;

	prompt = 0;
	while (p)
	{
		if ((p->pid == 0
				|| (p->status == RUNNING_FG && waitpid(p->pid, &p->ret, WUNTRACED) > 0)
			 	|| (p->status == RUNNING_BG && waitpid(p->pid, &p->ret, WUNTRACED | WNOHANG) > 0))
				&& IS_RUNNING(p->status))
		{
			printf("%s ret -> %i\n",p->cmd, p->ret );
			if (p->ret > 0 && WIFEXITED(p->ret))
			{
				p->ret =  WEXITSTATUS(p->ret);
				p->status = DONE;
			}
			else if (WIFSIGNALED(p->ret))
				ft_signal_check(p);
			else 
				p->status = DONE;
			if (prompt)
				ft_put_process(p);
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


#include <shell42.h>
#include "../includes/get_input.h"

static const t_sig_msg	g_signal_msg[] = {
		{.sig = SIGHUP, .rtn = 129, .msg = "Hangup"},
		{.sig = SIGINT, .rtn = 1, .msg = "Interupted"},
		{.sig = SIGQUIT, .rtn = 131, .msg = "Quit"},
		{.sig = SIGILL, .rtn = 132, .msg = "Illegal instruction"},
		{.sig = SIGTRAP, .rtn = 133, .msg = "Trace/BPT trap"},
		{.sig = SIGABRT, .rtn = 134, .msg = "Abort"},
		{.sig = SIGTRAP, .rtn = 135, .msg = "emulate instruction executed"},
		{.sig = SIGFPE, .rtn = 136, .msg = "Floating exception"},
		{.sig = SIGKILL, .rtn = 137, .msg = "Killed"},
		{.sig = SIGBUS, .rtn = 138, .msg = "Bus error"},
		{.sig = SIGSEGV, .rtn = 139, .msg = "Segmentation fault"},
		{.sig = SIGSYS, .rtn = 140, .msg = "Bad system call"},
		{.sig = SIGPIPE, .rtn = 141, .msg = "Broken pipe"},
		{.sig = SIGALRM, .rtn = 142, .msg = "Alarm clock"},
		{.sig = SIGTERM, .rtn = 143, .msg = "Terminated"},
		{.sig = SIGURG, .rtn = 0, .msg = ""},
		{.sig = SIGSTOP, .rtn = 0, .msg = "Suspended"},
		{.sig = SIGTSTP, .rtn = 0, .msg = "Suspended"},
		{.sig = SIGCONT, .rtn = 0, .msg = "Continued"},
		{.sig = SIGCHLD, .rtn = 0, .msg = "Done"},
		{.sig = SIGTTIN, .rtn = 0, .msg = "background read attempted from control terminal"},
		{.sig = SIGTTOU, .rtn = 0, .msg = "background write attempted from control terminal"},
		{.sig = SIGIO, .rtn = 0, .msg = "I/O is possible on a descriptor"},
		{.sig = SIGXCPU, .rtn = 152, .msg = "Cputime limit exceeded"},
		{.sig = SIGXFSZ, .rtn = 153, .msg = "Filesize limit exceeded"},
		{.sig = SIGVTALRM, .rtn = 142, .msg = "Alarm clock"},
		{.sig = SIGPROF, .rtn = 155, .msg = "Profiling time alarm"},
		{.sig = SIGUSR1, .rtn = 158, .msg = "User signal 1"},
		{.sig = SIGUSR2, .rtn = 159, .msg = "User signal 2"},
		{.msg = NULL}
};

void ft_process_tab_status(char *stat[6])
{
	stat[0] = "\x1b[1;34;41minitialised\x1B[00m";
	stat[1] = "\x1b[1;34;44mrunning fg \x1B[00m";
	stat[2] = "\x1b[1;34;44mrunning bg \x1B[00m";
	stat[3] = "\x1b[1;32;42m   done    \x1B[00m";
	stat[4] = "\x1b[1;36;46m suspended \x1B[00m";
	stat[5] = "\x1b[1;34;41m  killed   \x1B[00m";
}



static int	ft_signal_check(t_process *p)
{
	if (WIFSIGNALED(p->ret))
	{
	 	if (WIFSTOPPED(p->ret))
			p->status = SUSPENDED;
		else if (WIFCONTINUED(p->ret))
			p->status = RUNNING_FG;
		else
			p->status = KILLED;
		if (g_signal_msg[WTERMSIG(p->ret) - 1].msg)
			ft_printf("%s",  g_signal_msg[WTERMSIG(p->ret) - 1].msg);
		return (1);
	}
	return (0);
}

void update_grp_status(t_process *p, unsigned int to)
{
	char *stats[6];

	ft_process_tab_status(stats);
	while (p)
	{
		ft_printf("\t{%i} | %s -> %s |%s\n", 
			p->pid, stats[p->status], stats[to], p->cmd);
		p->status = to;
		p = p->grp;
	}
}


static void 	ft_putpid_ret(t_process *p)
{
	t_shell *sh;

	if (p->builtins == FALSE)
		ft_printf("{%i} ", p->pid);
	else if ((sh = ft_get_set_shell(NULL)))
		ft_printf("{\x1B[01;36m%i\x1B[00m} ", sh->pid);

	if (WIFSIGNALED(p->ret))
		ft_printf("\x1B[00;31m%- 4i  \x1B[00m", g_signal_msg[WTERMSIG(p->ret) - 1].rtn);
	else if (p->status == DONE || p->status == SUSPENDED || p->status == KILLED)
	{
		if (p->ret == 0)
			ft_printf("\x1b[1;32;42m%- 4i  \x1B[00m", p->ret);
		else
			ft_printf("\x1b[1;34;41m%- 4i  \x1B[00m", p->ret);
	}
	else
		ft_printf("       ");
}


void	ft_put_process(t_process *p)
{	
	char *stat[6];

	ft_process_tab_status(stat);
	ft_putpid_ret(p);
	ft_printf("%-25s", stat[p->status]);

	if (p->builtins == TRUE)
		ft_printf(" \x1B[1;36m%-17s\x1b[1;34;41m", p->cmd);
	else
		ft_printf(" %-17s", p->cmd);
	ft_signal_check(p);
	ft_putstr("\x1B[00m\n");
}

void ft_set_background(t_process *p)
{
	if (p->status == SUSPENDED)
		kill_process(p, SIGCONT, SUSPENDED);
	kill_process(p, -1, RUNNING_FG);
}


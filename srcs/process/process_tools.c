#include "shell42.h"
#include "../includes/get_input.h"

static const t_sig_msg	g_signal_msg[] = {
		{.sig = SIGHUP, .rtn = 129, .msg = "hanghup"},
		{.sig = SIGINT, .rtn = 130, .msg = "interupted"},
		{.sig = SIGQUIT, .rtn = 131, .msg = "quit"},
		{.sig = SIGILL, .rtn = 132, .msg = "illegal instruction"},
		{.sig = SIGTRAP, .rtn = 133, .msg = "trace/BPT trap"},
		{.sig = SIGABRT, .rtn = 134, .msg = "abort"},
		{.sig = SIGEMT, .rtn = 135, .msg = "emulate instruction executed"},
		{.sig = SIGFPE, .rtn = 136, .msg = "floating exception"},
		{.sig = SIGKILL, .rtn = 137, .msg = "killed"},
		{.sig = SIGBUS, .rtn = 138, .msg = "bus error"},
		{.sig = SIGSEGV, .rtn = 139, .msg = "segmentation fault"},
		{.sig = SIGSYS, .rtn = 140, .msg = "bad system call"},
		{.sig = SIGPIPE, .rtn = 141, .msg = "broken pipe"},
		{.sig = SIGALRM, .rtn = 142, .msg = "alarm clock"},
		{.sig = SIGTERM, .rtn = 143, .msg = "terminated"},
		{.sig = SIGURG, .rtn = 144, .msg = "SIGURP"},
		{.sig = SIGSTOP, .rtn = 145, .msg = "suspended"},
		{.sig = SIGTSTP, .rtn = 146, .msg = "suspended"},
		{.sig = SIGCONT, .rtn = 147, .msg = "continued"},
		{.sig = SIGCHLD, .rtn = 148, .msg = "SIGCHLD"},
		{.sig = SIGTTIN, .rtn = 149, .msg = "background read attempted from control terminal"},
		{.sig = SIGTTOU, .rtn = 150, .msg = "background write attempted from control terminal"},
		{.sig = SIGIO, .rtn = 151, .msg = "I/O is possible on a descriptor"},
		{.sig = SIGXCPU, .rtn = 152, .msg = "cpu time limit exceeded"},
		{.sig = SIGXFSZ, .rtn = 153, .msg = "file size limit exceeded"},
		{.sig = SIGPROF, .rtn = 154, .msg = "profiling time alarm"},
		{.sig = SIGVTALRM, .rtn = 155, .msg = "virtual time alarm"},
		{.sig = SIGUSR1, .rtn = 158, .msg = "user signal 1"},
		{.sig = SIGUSR2, .rtn = 159, .msg = "user signal 2"},
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
	int i;

	i = 0;
	if (p->sig <= 0)
		return (0);
	while (g_signal_msg[i].msg != NULL)
	{
		if (g_signal_msg[i].sig == p->sig)
		{
			ft_printf("%s",  g_signal_msg[i].msg);
			return (1);
		}
		i++;
	}
	return (0);
}

static void 	ft_putpid_ret(t_process *p)
{
	t_shell *sh;

	if (p->builtins == FALSE)
		ft_printf("{%i} ", p->pid);
	else if ((sh = ft_get_set_shell(NULL)))
		ft_printf("{\x1B[01;36m%i\x1B[00m} ", sh->pid);

	if (p->status == DONE || p->status == SUSPENDED || p->status == KILLED)
	{
		if (p->ret == 0)
			ft_printf("\x1b[1;32;42m  0  \x1B[00m ", p->ret);
		else
			ft_printf("\x1b[1;34;41m%-4i \x1B[00m ", p->ret);
	}
	else
		ft_printf("      ");
}


void	ft_put_process(t_process *p)
{	
	char *stat[6];

	ft_process_tab_status(stat);
	ft_putpid_ret(p);
	ft_printf("%-25s", stat[p->status]);

	if (p->builtins == TRUE)
		ft_printf(" \x1B[1;36m%-17s\x1B[00;31m", p->cmd);
	else
		ft_printf(" %-17s\x1B[00;31m", p->cmd);
	ft_signal_check(p);
	ft_putstr("\x1B[00m\n");
}

void ft_set_background(t_process *p)
{
	if (p->status == SUSPENDED)
		kill_process(p, SIGCONT, SUSPENDED);
	kill_process(p, -1, RUNNING_FG);
}


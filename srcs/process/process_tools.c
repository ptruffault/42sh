#include "shell42.h"
#include "get_input.h"

static const t_sig_msg	g_signal_msg[] = {
		{.sig = SIGHUP, .msg = "hanghup"},
		{.sig = SIGINT, .msg = "interupted"},
		{.sig = SIGQUIT, .msg = "quit"},
		{.sig = SIGILL,  .msg = "illegal instruction"},
		{.sig = SIGTRAP, .msg = "trace/BPT trap"},
		{.sig = SIGABRT, .msg = "abort"},
	//	{.sig = SIGEMT,  .msg = "emulate instruction executed"},
		{.sig = SIGFPE,  .msg = "floating exception"},
		{.sig = SIGKILL, .msg = "killed"},
		{.sig = SIGBUS,  .msg = "bus error"},
		{.sig = SIGSEGV, .msg = "segmentation fault"},
		{.sig = SIGSYS, .msg = "bad system call"},
		{.sig = SIGPIPE, .msg = "broken pipe"},
		{.sig = SIGALRM, .msg = "alarm clock"},
		{.sig = SIGTERM, .msg = "terminated"},
		{.sig = SIGURG, .msg = "SIGURP"},
		{.sig = SIGSTOP, .msg = "suspended"},
		{.sig = SIGTSTP, .msg = "suspended"},
		{.sig = SIGCONT, .msg = "continued"},
		{.sig = SIGCHLD, .msg = "SIGCHLD"},
		{.sig = SIGTTIN, .msg = "background read attempted from control terminal"},
		{.sig = SIGTTOU, .msg = "background write attempted from control terminal"},
		{.sig = SIGIO, .msg = "I/O is possible on a descriptor"},
		{.sig = SIGXCPU, .msg = "cpu time limit exceeded"},
		{.sig = SIGXFSZ, .msg = "file size limit exceeded"},
		{.sig = SIGPROF, .msg = "profiling time alarm"},
		{.sig = SIGVTALRM, .msg = "virtual time alarm"},
		{.sig = SIGUSR1, .msg = "user signal 1"},
		{.sig = SIGUSR2, .msg = "user signal 2"},
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
		ft_printf("\x1B[00;34m{\x1B[00m%i\x1B[00;34m}\x1B[00m ", p->pid);
	else if ((sh = ft_get_set_shell(NULL)))
		ft_printf("\x1B[00;34m{\x1B[01;36m%i\x1B[00m\x1B[00;34m}\x1B[00m ", sh->pid);

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

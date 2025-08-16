#include "../execute.h"

void pipe_sighandle(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void start_signals(void)
{
    signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

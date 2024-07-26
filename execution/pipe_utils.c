#include "../minishell.h"

int first_cmd(int fds[2])
{
    close(fds[0]);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
    {
        puts("error in dup");
        return (1);
    }
	close(fds[1]);
	// close(fds[0]);
    return (0);
}

int last_cmd(int fds[2])
{
    close(fds[1]);
	if (dup2(fds[0], STDIN_FILENO) == -1)
    {
        puts("error in dup");
        return (1);
    }
	close(fds[0]);
    return (0);
}

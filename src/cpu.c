#include "../includes/ftop.h"

bool    cpu_info(t_cpu *cpu)
{
    int     fd;
    ssize_t bytesRead;
    char    buffer[256];
    char    *targetStart;
    char    *targetEnd;

    // Opens the CPU sheet.
    fd = open("/proc/cpuinfo", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening \"/proc/cpuinfo\"\n");
        return (false);
    }

    // Reads and copies information from the CPU sheet.
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
    {
        buffer[bytesRead] = '\0';

        // CPU Model
        if ((targetStart = strstr(buffer, "model name")) != NULL)
        {
            if ((targetEnd = strchr(targetStart, '\n')) != NULL)
            {
                strncpy(cpu->model, strchr(targetStart, ':') + 2, targetEnd - (strchr(targetStart, ':') + 2));
                cpu->model[targetEnd - (strchr(targetStart, ':') + 2)] = '\0';
            }
        }

        // CPU Frequency (in MHz)
        if ((targetStart = strstr(buffer, "cpu MHz")) != NULL)
        {
            if ((targetEnd = strchr(targetStart, '\n')) != NULL)
            {
                cpu->frequency = strtol(strchr(targetStart, ':') + 2, NULL, 10);
            }
        }

        // CPU Threads
        if ((targetStart = strstr(buffer, "siblings")) != NULL)
        {
            if ((targetEnd = strchr(targetStart, '\n')) != NULL)
            {
                cpu->threads = strtol(strchr(targetStart, ':') + 2, NULL, 10);
            }
        }

        // Ends the loop once all information has been copied.
        if (cpu->model[0] != '\0' && cpu->frequency && cpu->threads)
            break ;
        else
            return (false);
    }

    if (bytesRead == -1)
    {
        perror("Error reading \"/proc/cpuinfo\"\n");
        close(fd);
        return (false);
    }
    close(fd);
    return (true);
}

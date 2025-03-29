#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

char* timedreadline (int timer)
{
    // dado salvo na memória mesmo dps da função retornar
    static char buffer[512];
    fd_set readfds;
    struct timeval timeout;
    int returnvalue;

    FB_ZERO(&readfds);
    // adiciona stdin ao conjunto de descritores de arquivo
    FD_SET(0, &readfds);

    timeout.tv_sec = timer;
    timeout.tv_usec = 0;

    returnvalue = select(1, &readfds, 0, 0, &timeout);
    // fd_isset para checar se readfds tem dados para serem lidos
    if(returnvalue && FD_ISSET(0, &readfds))
    {
        memset(buffer, 0, 512);
        returnvalue = read(0, buffer, 512);
        if(returnvalue = -1)
        {
            return 0;
        }
        // tirar \n do final
        buffer[returnvalue - 1] = 0;

        return buffer;
    }
    else
    {
        return 0;
    }
}

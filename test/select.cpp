#include <iostream>
#include <sys/select.h>
#include <unistd.h>

int main(){
    fd_set readfds;
    timeval timeout;

    FD_ZERO(&readfds);
    FD_SET(0,&readfds);

    return 0;
}
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    struct timeval timeout;

    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    // 设置超时为 5 秒
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    // 调用 select
    int ret = select(1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        std::cerr << "select() failed" << std::endl;
    } else if (ret == 0) {
        std::cout << "Timeout occurred! No data after 5 seconds." << std::endl;
    } else {
        std::cout<<ret<<std::endl;
        std::cout << "Data is available now." << std::endl;
    }

    return 0;
}

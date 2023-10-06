#include <iostream>
#include <poll.h>
#include <unistd.h>

int main() {
    struct pollfd fds[2];

    // 模拟两个文件描述符，这里用标准输入和标准输出
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;

    int timeout = 2000; // 超时时间为2000毫秒

    int ret = poll(fds, 2, timeout);

    if (ret == -1) {
        std::cerr << "poll() failed!" << std::endl;
        return 1;
    }

    if (fds[0].revents & POLLIN) {
        std::cout << "stdin is ready to read." << std::endl;
    }

    if (fds[1].revents & POLLOUT) {
        std::cout << "stdout is ready to write." << std::endl;
    }

    return 0;
}

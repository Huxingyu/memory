#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  // 创建一个socket
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);  // 监听8888端口
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 任何地址都可以连接

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));  // 绑定地址和端口

    listen(sockfd, 0);  // 开始监听

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);  // 接受客户端的连接

    char buffer[256] = {0};
    read(clientfd, buffer, 255);  // 读取客户端发送的消息
    std::cout << "Message from client: " << buffer << std::endl;  // 打印消息

    close(clientfd);  // 关闭客户端的连接
    close(sockfd);  // 关闭服务器的socket

    return 0;
}
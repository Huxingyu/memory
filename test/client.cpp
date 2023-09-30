#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){
    //socket->struct->connect->write
    int clientfd=socket(AF_INET,SOCK_STREAM,0);
    if(clientfd==-1){
        perror("socket");
        return -1;
    }
    //struct
    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8888);
    inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);

    //connect
    int ret=connect(clientfd,(sockaddr*)&addr,sizeof(addr));
    if(ret==-1){
        perror("connect");
        return -1;
    }

    char buffer[1024]={0};
    while(1){
        fgets(buffer,sizeof(buffer),stdin);
        //write
        write(clientfd,buffer,strlen(buffer)+1);
        int len=read(clientfd,buffer,sizeof(buffer));
        if(len<=0){
            perror("read");
        }else{
            printf("client re-data:%s\n",buffer);
        }
    }
    close(clientfd);
    return 0;
}
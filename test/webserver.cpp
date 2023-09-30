#include "webserver.h"
#include <sys/socket.h>
#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

webserver::webserver(){
    init();
}

bool webserver::init(){
    //socket->struct->bind->listen->struct-client->accept->read
    //init socket
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(socketfd==-1){
        perror("socket error");
        return -1;
    }
    //init mul
    int optval=1;
    setsockopt(socketfd,SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    //struct
    sockaddr_in saddr;
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=INADDR_ANY;
    saddr.sin_port=htons(8888);

    //bind
    int ret=bind(socketfd,(sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1){
        perror("bind");
        return -1;
    }

    //listen
    ret=listen(socketfd,0);
    if(ret==-1){
        perror("listen");
        return -1;
    }

    //client struct
    sockaddr_in client_addr;    
    socklen_t len=sizeof(client_addr);
    int clientfd=accept(socketfd,(sockaddr*)&client_addr,&len);
    if(clientfd==-1){
        perror("accept");
        return -1;
    }

    char buffer[1024]={0};
    while(1){
        int len=recv(clientfd,buffer,sizeof(buffer),0);
        if(len<0){
            perror("recv");
            return -1;
        }else if(len==0){
            perror("disconnect");
        }else{
            printf("server data:%s\n",buffer);
        }
        for(int i=0;i<len;i++){
            buffer[i]=toupper(buffer[i]);
        }
        ret=send(clientfd,buffer,strlen(buffer)+1,0);
        if(ret==-1){
            perror("send");
            return -1;
        }
    }

    close(clientfd);
    close(socketfd);
    return 0;
}


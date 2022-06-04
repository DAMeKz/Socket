#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void error_handling(char *message);

int main(int argc, char *argv[]){
    int server, client;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    server = socket(PF_INET, SOCK_STREAM,0);
    if(server == -1){
        error_handling("socket error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(server,(struct sockaddr *)&serv_addr, sizeof(serv_addr))==1){
        error_handling("bind error");
    }

    if(listen(server,5)==-1){
        error_handling("listen error");
    }

    clnt_addr_size = sizeof(clnt_addr);
    client = accept(server, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(client==-1){
        error_handling("accept error");
    }

    char msg[] = "Hello this is server!\n";
    write(client, msg, sizeof(msg));

    close(client);
    close(server);
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}
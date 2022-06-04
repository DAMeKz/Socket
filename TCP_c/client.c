#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void error_handling(char *message);

int main(int argc, char* argv[]){
    int client;
    struct sockaddr_in serv_addr;
    char message[1024]={0x00,};

    client = socket(PF_INET,SOCK_STREAM,0);
    if(client==-1){
        error_handling("socket error");
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(client, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1){
        error_handling("connect error");
    }

    if(read(client, message,sizeof(message)-1)==-1){
        error_handling("read_error");
    }

    printf("Message from server: %s\n",message);

    close(client);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}
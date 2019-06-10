#include "tcp_server.h"

void* TCP_server::Task(void *argv) {
    int n;
    int newsockfd = (long)argv;
    char msg[MAXPACKETSIZE];
    // ????
    pthread_detach(pthread_self());
    while (1) {
        n = recv(newsockfd, msg, MAXPACKETSIZE, 0);
        if (n==0) {
            close(newsockfd);
            break;
        }
        msg[n]=0;
        Message = std::string(msg);
    }
    return 0;
}
void TCP_server::setup(int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons((port));
    bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(sockfd, 5);
}

typedef int socklen_t;

std::string TCP_server::receive() {
    std::string str;
    while (1) {
        socklen_t sosize = sizeof(clientAddress);
        newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &sosize);
        str = inet_ntoa(clientAddress.sin_addr);
        pthread_create(&serverThread, NULL, &Task, (void*)newsockfd);
        std::cout << "!" << std:: endl;
    }
    return str;
}

std::string TCP_server::getMessage() {
    return Message;
}

void TCP_server::Send(std::string msg) {
    send(newsockfd, msg.c_str(), msg.length(), 0);
}
void TCP_server::clean() {
    Message = "";
    memset(msg, 0, MAXPACKETSIZE);
}
void TCP_server::detach() {
    close(sockfd);
    close(newsockfd);
}

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <winsock2.h>
#include <windows.h>
#include <pthread.h>
#include <mutex>

#define MAXPACKETSIZE 4096
extern std::mutex mtx;
class TCP_server
{
    public:
        int sockfd, newsockfd, n, pid;
        struct sockaddr_in serverAddress;
        struct sockaddr_in clientAddress;
        pthread_t serverThread;
        char msg[MAXPACKETSIZE];
        static std::string Message;

        void setup(int port);
        std::string receive();
        std::string getMessage();
        void Send(std::string msg);
        void detach();
        void clean();
    private:
        static void * Task(void* argv);
};
#endif // TCP_SERVER_H

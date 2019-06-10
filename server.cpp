#include <iostream>
#include "tcp_server.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <future>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <winsock2.h>
#include <windows.h>
#include <pthread.h>
#include <mutex>
#include <ws2tcpip.h>
#define msg_sec "Before server will stop remains "
#define MAXPACKETSIZE 4096
using namespace std;
extern std::mutex mtx;

std::string TCP_server::Message;

#include "tcp_server.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <future>

TCP_server tcp;
mutex mtx;

void * loop(void *m) {
    pthread_detach(pthread_self());
    int duration_server = 60;
    while (duration_server) {
        std::string str = tcp.getMessage();
        if (str !="") {
            std::cout << "The client message: " << str << std::endl;
            tcp.Send(" [text: "+str+"] ");
            tcp.clean();
        }
        //usleep(1000);
        this_thread::sleep_for(chrono::milliseconds(1000));
        if (duration_server%10==0) std::cout << msg_sec << duration_server << " sec" << std::endl;
        duration_server--;
    }
    tcp.detach();
}
int main()
{
    setlocale(LC_ALL, "ru");
    WSADATA wsdata;
    WSAStartup(0x0101,&wsdata);
    try {
        std::cout << "The server is launching. ID of the thread " << this_thread::get_id() <<  std::endl;
        pthread_t msg;
        tcp.setup(11999);
        if (pthread_create(&msg, NULL, loop, (void*)0) == 0 ) {
            //std::cout << this_thread::get_id() << std::endl;
            tcp.receive();
        }
    } catch (exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "Server done ok!" << std::endl;
    return 0;
}


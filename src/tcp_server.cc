#include "tcp.h"

TcpServer::TcpServer() {
    monitor_ = socket(AF_INET, SOCK_STREAM, 0);
}

void TcpServer::Listen(unsigned short port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(monitor_, (struct sockaddr*)&addr, sizeof(addr));
    listen(monitor_, 128);
}

TcpSocket* TcpServer::Accept(int timeout) {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int socket = accept(monitor_, (struct sockaddr*)&addr, &len);
    return new TcpSocket(socket);
}

TcpServer::~TcpServer() {
    close(monitor_);
}
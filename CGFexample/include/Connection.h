/* 
 * File:   Connection.h
 * Author: sidner
 *
 * Created on December 19, 2012, 7:46 PM
 */

#ifndef CONNECTION_H
#define	CONNECTION_H


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <errno.h>
#include <pwd.h>
#include <signal.h>

using namespace std;

#define PORT 5000
#define RECEIVE_SIZE 30

class Connection
{
public:
    Connection(string serverAddress, unsigned int port);
    Connection(string serverAddress);
    bool connect_server();
    bool disconnect_server();
    string speak(string message);
    bool isConnected(){return connected;};

private:
    char* serverAddress;
    int socket_fd;
    char* port;
    struct addrinfo hints, *address;
    bool connected;    
};
#endif	/* CONNECTION_H */

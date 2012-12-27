#include "Connection.h"


Connection::Connection (string serverAddress_, unsigned int port_)
{

    connected = false;
    
    cout << serverAddress_ << endl;
    
    strcpy(serverAddress,serverAddress_.c_str ());
    
    port = (char*) malloc (sizeof (unsigned int) * sizeof (char));

    sprintf (port, "%u", port_);

    memset (&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo (serverAddress, port, &hints, &address);

    if ((socket_fd = socket (address->ai_family, address->ai_socktype, address->ai_protocol)) < 0)
    {
        perror ("First socket()");
        connected = false;
    }
    else
    {
        cout << "Socket created\n";
    }
}

Connection::Connection (string serverAddress1)
{
    connected = false;
    
    serverAddress = (char*)malloc(sizeof(char)*serverAddress1.size());
    
    strcpy(serverAddress,serverAddress1.c_str ());
    
    port = (char*) malloc (sizeof (unsigned int) * sizeof (char));

    sprintf (port, "%d", PORT);
	
    memset (&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo (serverAddress, port, &hints, &address);

    if ((socket_fd = socket (address->ai_family, address->ai_socktype, address->ai_protocol)) < 0)
    {
        perror ("First socket()");
        connected = false;
    }
    else
    {
        cout << "Socket created\n";
    }
}

bool Connection::connect_server()
{
    if ((connect (socket_fd, address->ai_addr, address->ai_addrlen)) < 0)
    {
        perror ("connect() problem\n");
        return connected;
    }
    else
    {
        cout << "Connection stablished.\n";
        connected = true;
		speak("hello");
        return connected;
    }
}


string Connection::speak (string message)
{
    char* receive = (char*)malloc(sizeof(char)*RECEIVE_SIZE);
    string return_message;
    int res = 0;
	
	message.append(".\n");
	
    cout << "\nHere\n" << message.c_str () << "a." << endl;
    
    write(socket_fd,message.c_str (),strlen (message.c_str ()));

    res = read(socket_fd,receive,RECEIVE_SIZE);
    if (res < 0)
    {
        cout << "Server error in response\n";
        return NULL;
    }
    
    printf("Received: %s",receive);
    
    return_message = (string)receive;
    
    return return_message;
}

bool Connection::disconnect_server ()
{
    speak("disconnect");
    if(close(socket_fd) < 0)
    {
        return false;
    }
    
    return true;
}

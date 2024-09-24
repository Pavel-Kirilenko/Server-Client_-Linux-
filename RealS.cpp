#include"HeaderS.h"
#include<iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

#define MESSAGE_LENGTH 1024   // data buffer's max size
#define PORT 7777             // port's number

using namespace std;

void userReg(string& curName, string& curPassWord)   // // enter user's data while registaring or loggin in
{

    cout << "Type you name (less than 15 symbols including spaces): ";
    getline(cin, curName);
    cout << "Type your password: ";
    getline(cin, curPassWord);
}

void Chat::entrChat(bool& persPresence, string& curName, string& curPassWord)      // to log in the chat
{
    if (persArray.size())  // if the array is not empty
    {
        userReg(curName, curPassWord);   // to input user's data when logging in
        map <string, string>::iterator it = persArray.find(curName);
        if (it != persArray.end() && it->second == curPassWord) persPresence = true;  // successful logging in
        if (persPresence == false)
        {
            cout << "The user whith this name and password not found. Check the input" << endl;
        }
    }
    else
    {
        cout << "There are no users in the chat yet" << endl;
    }
}
void Chat::regChat(bool& nameInChatAlready, bool& persPresence, string& curName, string& curPassWord)    // to register in the chat
{
    userReg(curName, curPassWord);                                // enter user's data while registering
    map <string, string>::iterator it = persArray.find(curName);
    if (it != persArray.end() || curPassWord == "" || curName == "") nameInChatAlready = true;  // if the name is already in the chat of name or password is empty
    if (nameInChatAlready)                                                                      // registering denied
    {
        cout << "The user with this name is already in the chat or the data is not correct (empty name or password). Repeat the input" << endl;
        nameInChatAlready = false;
    }
    else
    {
        persArray.insert({ curName, curPassWord });               // to insert user's data into the array
        cout << "Welcome to the chat, " << curName << "!" << endl;
        persPresence = true;
    }
}

void Chat::sendMess(string curName)             // to send a message
{
    struct sockaddr_in serveraddress, client;
    socklen_t length;
    int sockert_file_descriptor, connection, bind_status, connection_status;
    char message[MESSAGE_LENGTH];
    string suffix = "_(" + curName + " is writing to you)";
    const char* suf = suffix.c_str();
    // create a socket
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == -1) {
        cout << "Socket creation failed.!" << endl;
        return;
    }
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // port's number for connection
    serveraddress.sin_port = htons(PORT);
    // using IPv4
    serveraddress.sin_family = AF_INET;
    // connect the socket
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
        sizeof(serveraddress));
    if (bind_status == -1) {
        cout << "Socket binding failed.!" << endl;
        return;
    }
    // make server to receive data 
    connection_status = listen(sockert_file_descriptor, 5);
    if (connection_status == -1) {
        cout << "Socket is unable to listen for new connections.!" << endl;
        return;
    }
    else {
        cout << "Server is listening for new connection: " << endl;
    }
    length = sizeof(client);
    connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);
    if (connection == -1) {
        cout << "Server is unable to accept the data from client.!" << endl;
        return;
    }

    // Communication Establishment
    while (1) {
        bzero(message, MESSAGE_LENGTH);

        read(connection, message, sizeof(message));
        if (strncmp("end", message, 3) == 0) {
            cout << "Client Exited." << endl;
            cout << "Server is Exiting..!" << endl;
            break;
        }
        cout << "Message: " << message << endl;
        bzero(message, MESSAGE_LENGTH);
        cout << "Enter the message: " << endl;
        cin.getline(message, MESSAGE_LENGTH - 37);
        strcat(message, suf);
        ssize_t bytes = write(connection, message, sizeof(message));
        // if >= 0  bytes transported, then transporting is successful
        if (bytes >= 0) {
            cout << "     ***     " << endl;
        }
    }
    // close the socket, stop the connection
    close(sockert_file_descriptor);
    return;
}

// 24.09.2024 by Pavel Kirilenko
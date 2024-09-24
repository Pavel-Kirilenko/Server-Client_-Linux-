#include"HeaderC.h"
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
    cout << "to quit the dialog type 'end'" << endl;
    int socket_file_descriptor, connection;
    struct sockaddr_in serveraddress, client;
    char message[MESSAGE_LENGTH];
    string suffix = "_(" + curName + " is writing to you)";
    const char* suf = suffix.c_str();
        // create a socket
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        cout << "Creation of Socket failed!" << endl;
        return;
    }

    // define server's address
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // define port's number
    serveraddress.sin_port = htons(PORT);
    // using IPv4
    serveraddress.sin_family = AF_INET;
    // connect the server
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        cout << "Connection with the server failed.!" << endl;
        return;
    }
    // interaction with the server
    while (1) {
        bzero(message, sizeof(message));
        cout << "Enter the message: " << endl;
        cin.getline(message, MESSAGE_LENGTH - 37);
        if ((strncmp(message, "end", 3)) == 0) {
            write(socket_file_descriptor, message, sizeof(message));
            cout << "Exit." << endl;
            break;
        }
        strcat(message, suf);
        ssize_t bytes = write(socket_file_descriptor, message, strlen(message));
        // if >= 0  bytes transported, then transporting is successful
        if (bytes >= 0) {
            cout << "     ***     " << endl;
        }
        bzero(message, sizeof(message));
        // wating for server's answer
        read(socket_file_descriptor, message, sizeof(message));
        cout << "Message: " << message << endl;
    }
    // close the socket, stop connection
    close(socket_file_descriptor);
    return;
}

// 24.09.2024 by Pavel Kirilenko
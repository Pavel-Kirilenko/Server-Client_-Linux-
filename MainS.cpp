#include <iostream>
#include "HeaderS.h"
#include <map>
#include <vector>

using namespace std;

int main()
{
	string curName;          //  current user's name
	string curPassWord;      //  current user's password
	int messNumber = 0;      //  current message's number (from zero in order to appearenses)
	bool persPresence = false;       //  if there is a user with this name and password
	bool nameInChatAlready = false;  //  if there is a user with this name already in the chat

	string contProcNumber = "0";     // action pointer, type 'string' is for program sustainability

	Chat presChat;


	while (true)
	{
		while (persPresence == false)  // while the user is not entered or loged in
		{
			while (contProcNumber != "1" && contProcNumber != "2" && contProcNumber != "3")  //  protection from incorrect input
			{
				cout << "Choose the action, please: 1 - to enter; 2 - to log in; 3 - exit." << endl;
				getline(cin, contProcNumber);
			}
			persPresence = false;
			if (contProcNumber == "1")
			{
				presChat.entrChat(persPresence, curName, curPassWord);      // to enter in the chat
				contProcNumber = "0";
			}

			if (contProcNumber == "2")
			{
				presChat.regChat(nameInChatAlready, persPresence, curName, curPassWord);    // to log in the chat
				contProcNumber = "0";
			}

			if (contProcNumber == "3") break;  //  exit from the cycle
		}
		if (contProcNumber == "3") break;      //  exit from the programme
		while (true)                       //  the cycle is continiuing unless the user exits from the profile or the programme
		{
			while (contProcNumber != "1" && contProcNumber != "2" && contProcNumber != "3")  //  protection from incorrect input
			{
				cout << "Choose the action, please: 1 - start the dialog (you have to wait for the message from the outside); 2 - quit the profile." << endl;
				getline(cin, contProcNumber);
			}
			if (contProcNumber == "2")     //  if exit chosen
			{
				cout << endl;
				persPresence = false;
				contProcNumber = "0";
				break;
			}
			if (contProcNumber == "1")      //  if sending a message is chosen
			{
				presChat.sendMess(curName);
				contProcNumber = "0";
			}
			if (contProcNumber == "2")      //  exit from programme
			{
				contProcNumber = "3";
				break;
			}
		}
		if (contProcNumber == "3") break;      //  exit from programme
	}
	return 0;
}

// 24.09.2024 by Pavel Kirilenko
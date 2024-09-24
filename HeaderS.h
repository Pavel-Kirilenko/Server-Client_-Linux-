#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

void userReg(string& curName, string& curPassWord);  // enter user's data while registaring or loggin in

class Chat
{
    map <string, string> persArray;               // array of user's data
public:
    void entrChat(bool& persPresence, string& curName, string& curPassWord);     // to log in chat
    void regChat(bool& nameInChatAlready, bool& persPresence, string& curName, string& curPassWord);    // to register in chat
    void sendMess(string curName);                // to send a message
};

// 24.09.2024 by Pavel Kirilenko
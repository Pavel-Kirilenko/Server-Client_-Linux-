#pragma once
#include <string>
#include <map>
#include <vector>

//using namespace std; // Без данной строчки код не компилируется

void userReg(std::string& curName, std::string& curPassWord);  // enter user's data while registеring or loggin in

class Chat
{
    std::map <std::string, std::string> persArray;               // array of user's data
public:
    void entrChat(bool& persPresence, std::string& curName, std::string& curPassWord);     // to log in chat
    void regChat(bool& nameInChatAlready, bool& persPresence, std::string& curName, std::string& curPassWord);    // to register in chat
    void sendMess(std::string curName);            // to send a message
};

// 24.09.2024 by Pavel Kirilenko

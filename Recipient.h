#include <iostream>
#include <vector>
#pragma once

using namespace std;


class Recipient
{

    int recipientId;
    int userId;
    string name;
    string surname;
    string telephone;
    string email;
    string addresss;

public:

    int getRecipientId();
    int getUserId();
    string getName();
    string getSurname();
    string getTelephone();
    string getEmail();
    string getAddress();

    void setRecipientId(int recipientId);
    void setUserId(int userId);
    void setName(string name);
    void setSurname(string surname);
    void setTelephone(string telephone);
    void setEmail(string email);
    void setAddress(string addresss);




};


#include <iostream>
#include <vector>
#pragma once



using namespace std;



class User
{


    int userId;
    string name;
    string password;

public:

    int getUserId();
    string getName();
    string getPassword();
    void setUserId(int userId);
    void setName(string name);
    void setPassword(string password);


};

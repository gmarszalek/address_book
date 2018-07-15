#include <iostream>
#include "User.h"


using namespace std;

int User::getUserId()
{
    return userId;
}
string User::getName()
{
    return name;
}
string User::getPassword()
{
    return password;
}

void User::setUserId(int userId)
{
    this -> userId = userId;
}

void User::setName(string name)
{
    this -> name = name;
}
void User::setPassword(string password)
{
    this -> password = password;
}


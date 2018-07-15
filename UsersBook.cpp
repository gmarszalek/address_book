#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "UsersBook.h"
#include "User.h"


using namespace std;


string UsersBook::convertIntToString(int number)
{
    ostringstream ss;
    ss << number;
    string str = ss.str();

    return str;
}

User UsersBook::getUserData(string dataOfSingleUserSeparatedByVerticalDashes)
{
    User user;
    string singleUserData = "";
    int numberOfSingleUserData = 1;

    for (int signPosition = 0; signPosition < dataOfSingleUserSeparatedByVerticalDashes.length(); signPosition++)
    {
        if (dataOfSingleUserSeparatedByVerticalDashes[signPosition] != '|')
        {
            singleUserData += dataOfSingleUserSeparatedByVerticalDashes[signPosition];
        }
        else
        {
            switch(numberOfSingleUserData)
            {
            case 1:
                user.setUserId(atoi(singleUserData.c_str()));
                break;
            case 2:
                user.setName(singleUserData);
                break;
            case 3:
                user.setPassword(singleUserData);
                break;
            }
            singleUserData = "";
            numberOfSingleUserData++;
        }
    }
    return user;
}

void UsersBook::loadUsersFromTextFile(vector <User> &users)
{
    User user;
    string dataOfSingleUserSeparatedByVerticalDashes = "";

    fstream textFile;
    textFile.open("Users.txt", ios::in);

    if (textFile.good() == true)
    {
        while (getline(textFile, dataOfSingleUserSeparatedByVerticalDashes))
        {
            user = getUserData(dataOfSingleUserSeparatedByVerticalDashes);

            users.push_back(user);
        }
        textFile.close();
    }
}

void UsersBook::addUserToTextFile (User user)
{
    fstream textFile;
    textFile.open("Users.txt", ios::out | ios::app);

    if (textFile.good() == true)
    {
        textFile << user.getUserId() << '|';
        textFile << user.getName() << '|';
        textFile << user.getPassword() << '|' << endl;

        textFile.close();

    }
    else
    {
        cout << "File could not be opened and the data stored in it." << endl;
        system("pause");
    }

}

void UsersBook::registration (vector <User> &users )
{
    User user;
    string newUserName = "";
    string password;

    system ("cls");
    cout << ">>> REGISTRATION<<<" << endl << endl;

    if (users.empty() == true)
    {
        user.setUserId(1);
    }
    else
    {
        user.setUserId(users.back().getUserId()+1);
    }


    cout << "Enter a new user name: ";
    cin >> newUserName;



    vector <User>::iterator itr = users.begin();

    while (itr < users.end())
    {
        if (itr -> User::getName() == newUserName)
        {
            cout << "This name exist, enter a new user name : ";
            cin >> newUserName;
            itr = users.begin();

        }
        else
        {
            itr ++;
        }

    }

    cout << "Enter the password: ";
    cin >> password;

    user.setPassword(password);

    user.setName(newUserName);


    users.push_back(user);

    addUserToTextFile(user);

    cout << "The account was created" << endl;
    Sleep(1500);

}

int UsersBook::logging (vector <User> &users, int idLoggedInUser )
{
    User user;

    if (!users.empty())
    {
        system ("cls");
        cout << ">>> LOGGING <<<" << endl << endl;

        string login = "";
        string password = "";
        cout << "Enter the login ";
        cin >> login;
        //uzytkownik.setName(login);

        vector <User>::iterator itr = users.begin();

        while (itr < users.end())
        {
            if ( itr -> User::getName() == login)
            {
                for (int attempt = 0; attempt < 3; attempt ++)
                {
                    cout << "Enter the password. There are " << 3-attempt << " attempts left: ";
                    cin >> password;
                    //uzytkownik.setPassword(password);
                    if (itr -> User::getPassword() == password)
                    {
                        cout << "Logged " << endl;
                        Sleep(1000);
                        return idLoggedInUser = itr -> User::getUserId();


                    }

                }
                cout << "You provided an incorrect password three times, Return to menu! " << endl;
                Sleep(2000);
                return 0;

            }
            itr ++;
        }
        cout << "User does not exist " << endl;
        Sleep(1500);
        return 0;

    }
    else
    {
        cout << "Recipient Book is empty." << endl << endl;
    }

    system("pause");
    return 0;


}

void UsersBook::saveAllUsersToTextFile(vector <User> &users)
{
    User user;
    fstream textFile;
    string lineWithUserData = "";


    textFile.open("Users.txt", ios::out);
    if (textFile.good())
    {
        for (vector <User>::iterator itr = users.begin(); itr != users.end(); itr++)
        {
            lineWithUserData += convertIntToString(itr -> User::getUserId()) + '|';
            lineWithUserData += itr -> User::getName()+ '|';
            lineWithUserData += itr -> User::getPassword() + '|';

            textFile << lineWithUserData << endl;
            lineWithUserData = "";
        }
        textFile.close();
    }
    else
    {
        cout << "File could not be opened" << endl;
    }
}

void UsersBook::passwordChange (vector <User> &users, int idLoggedInUser)
{
    //Uzytkownik uzytkownik;
    cout << ">>> PASSWORD CHANGE<<<" << endl << endl;
    string newPassword = "";

    for (vector <User>::iterator itr = users.begin(); itr != users.end(); itr++)
    {
        if (itr -> User::getUserId() == idLoggedInUser )
        {
            cout << "Enter new password: ";
            cin >>  newPassword;
            itr -> User::setPassword(newPassword);
            cout << endl << "Password was changed" << endl << endl;
            Sleep(1500);
            saveAllUsersToTextFile(users);

        }
    }

}

void logOff(vector <User> &users)
{
    users.clear();
}




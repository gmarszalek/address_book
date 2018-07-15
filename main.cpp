#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "UsersBook.h"
#include "RecipientsBook.h"

using namespace std;


int main()
{
    vector <User> users;
    vector <Recipient> recipients;

    int idLoggedInUser = 0;
    char choice;
    int idLastPerson = 0;

    UsersBook user;
    RecipientsBook recipient;


    user.loadUsersFromTextFile(users);
    Sleep(1500);
    while (true)
    {
        if (idLoggedInUser == 0)
        {
            system("cls");
            cout << ">>> ADDRESS BOOK<<<" << endl << endl;
            cout << "1. REGISTRATION" << endl;
            cout << "2. LOGGING" << endl;
            cout << "9. EXIT" << endl;
            cout << "Your choice: ";
            cin >> choice;

            switch(choice)
            {
            case '1':
                user.registration(users);
                break;
            case '2':
                idLoggedInUser = user.logging(users, idLoggedInUser);
                idLastPerson = recipient.loadRecipientsFromTextFile(recipients, idLoggedInUser);
                break;
            case '9':
                cout << "Exit the program"<< endl;
                Sleep(1500);
                exit(0);
                break;
            }

        }

        else
        {

            system("cls");
            cout << ">>> ADDRESS BOOK <<<" << endl << endl;
            cout << "1. Add recipient" << endl;
            cout << "2. Search by name" << endl;
            cout << "3. Search by surname" << endl;
            cout << "4. Display all recipients" << endl;
            cout << "5. Delete recipient" << endl;
            cout << "6. Edit recipient" << endl;
            cout << "7. Password change" << endl;
            cout << "8. Log Out" << endl;
            cout << "Your choice: ";
            cin >> choice;

            switch(choice)
            {
            case '1':
                idLastPerson = recipient.addRecipient(recipients, idLoggedInUser, idLastPerson);
                break;
            case '2':
                recipient.searchByName(recipients, idLoggedInUser);
                break;
            case '3':
                recipient.searchBySurname(recipients, idLoggedInUser);
                break;
            case '4':
                recipient.displayAllRecipient(recipients, idLoggedInUser);
                break;
            case '5':
                idLastPerson = recipient.deleteRecipient(recipients, idLoggedInUser, idLastPerson);
                break;
            case '6':
                idLastPerson = recipient.editRecipient(recipients, idLoggedInUser, idLastPerson);
                break;
            case '7':
                user.passwordChange(users, idLoggedInUser);
                break;
            case '8':
                recipient.logOff(recipients);
                idLoggedInUser = 0;
                break;
            }

        }

    }

    return 0;
}

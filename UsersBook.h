#include <iostream>
#include "User.h"
#include "RecipientsBook.h"



using namespace std;



class UsersBook
{

public:

    string convertIntToString(int number);
    User getUserData(string dataOfSingleUserSeparatedByVerticalDashes);
    void loadUsersFromTextFile(vector <User> &users);
    void addUserToTextFile (User User);
    void registration (vector <User> &users );
    int logging (vector <User> &users, int idLoggedInUser );
    void saveAllUsersToTextFile(vector <User> &users);
    void passwordChange (vector <User> &users, int idLoggedInUser);
    void logOff(vector <User> &users);





};

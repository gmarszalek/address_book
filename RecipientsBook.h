#include <iostream>
#include "Recipient.h"
#pragma once



using namespace std;

class RecipientsBook
{

public:

    Recipient getRecipientData(string dataOfSingleReciepientSeparatedByVerticalDashes, int idLoggedInUser);
    int loadRecipientsFromTextFile( vector <Recipient> &recipients, int idLoggedInUser);
    void addRecipientToTextFile(Recipient recipient,vector <Recipient> &recipients, int idLoggedInUser);
    int addRecipient(vector <Recipient> &recipients, int idLoggedInUser, int idLastPerson);
    void searchByName(vector <Recipient> &recipients, int idLoggedInUser);
    void searchBySurname(vector <Recipient> &recipients,  int idLoggedInUser);
    void displayAllRecipient(vector <Recipient> &recipients, int idLoggedInUser );
    void saveAllRecipientsToTextFile(vector <Recipient> &recipients);
    int deleteRecipient(vector <Recipient> &recipients, int idLoggedInUser, int idLastPerson);
    int  editRecipient(vector <Recipient> &recipients, int idLoggedInUser, int idLastPerson);
    void logOff(vector <Recipient> &recipients);
    string convertIntToString(int number);


};

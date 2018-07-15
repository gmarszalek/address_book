#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "RecipientsBook.h"
#include "Recipient.h"


using namespace std;


Recipient RecipientsBook::getRecipientData(string dataOfSingleReciepientsSeparatedByVerticalDashes, int idLoggedInUser)
{
    Recipient recipient;
    string singleRecipientData = "";
    int numberOfSingleRecipientData = 1;



    for (int signPosition = 0; signPosition < dataOfSingleReciepientsSeparatedByVerticalDashes.length(); signPosition++)
    {
        if (dataOfSingleReciepientsSeparatedByVerticalDashes[signPosition] != '|')
        {
            singleRecipientData += dataOfSingleReciepientsSeparatedByVerticalDashes[signPosition];
        }
        else
        {
            switch(numberOfSingleRecipientData)
            {
            case 1:
                recipient.setRecipientId(atoi(singleRecipientData.c_str()));
                break;
            case 2:
                recipient.setUserId(atoi(singleRecipientData.c_str()));
                break;
            case 3:
                recipient.setName(singleRecipientData);
                break;
            case 4:
                recipient.setSurname(singleRecipientData) ;
                break;
            case 5:
                recipient.setTelephone(singleRecipientData);
                break;
            case 6:
                recipient.setEmail(singleRecipientData) ;
                break;
            case 7:
                recipient.setAddress(singleRecipientData);
                break;
            }
            singleRecipientData = "";
            numberOfSingleRecipientData++;
        }
    }
    return recipient;


}

int RecipientsBook::loadRecipientsFromTextFile( vector <Recipient> &recipients, int idLoggedInUser)
{
    Recipient recipient;

    string dataOfSingleRecipientsSeparateByVerticalDashes = "";
    int idLastPerson = 0;
    int iloscLiniWPliku = 0;


    fstream textFile;
    textFile.open("Adresaci.txt", ios::in);


    if (textFile.good() == true)
    {

        while (getline(textFile, dataOfSingleRecipientsSeparateByVerticalDashes))
        {
            recipient = getRecipientData(dataOfSingleRecipientsSeparateByVerticalDashes, idLoggedInUser);

            if ( recipient.getUserId()  == idLoggedInUser)
            {
                recipients.push_back(recipient);

                idLastPerson = recipients.back().getRecipientId();

            }
            else
            {
                idLastPerson = recipient.getRecipientId();
            }

        }

        textFile.close();

    }


    return idLastPerson;

}

void RecipientsBook::addRecipientToTextFile(Recipient recipient,vector <Recipient> &recipients, int idLoggedInUser)
{
    fstream textFile;
    textFile.open("Adresaci.txt", ios::out | ios::app);

    if (textFile.good() == true)
    {
        textFile << recipient.getRecipientId() << '|';
        textFile << recipient.getUserId() << '|';
        textFile << recipient.getName()<< '|';
        textFile << recipient.getSurname() << '|';
        textFile << recipient.getTelephone()<< '|';
        textFile << recipient.getEmail() << '|';
        textFile << recipient.getAddress() << '|' << endl;
        textFile.close();

        cout << endl << "Adresat zostal dodany" << endl;
        system("pause");

    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }

}

int RecipientsBook::addRecipient(vector <Recipient> &recipients, int idLoggedInUser, int idLastPerson)
{
    Recipient recipient;
    string name;
    string surname;
    string telephone;
    string email;
    string address;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;

    if (recipients.empty() == true)
    {
        recipient.setRecipientId(1 + idLastPerson) ;

    }
    else
    {

        recipient.setRecipientId(idLastPerson +1);
    }

    recipient.setUserId(idLoggedInUser);



    cout << "Podaj imie: ";
    cin >> name;
    recipient.setName(name);

    cout << "Podaj nazwisko: ";
    cin >> surname;
    recipient.setSurname(surname);

    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, telephone);
    recipient.setTelephone(telephone);

    cout << "Podaj email: ";
    cin >> email;
    recipient.setEmail(email);

    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, address);
    recipient.setAddress(address);


    recipients.push_back(recipient);

    addRecipientToTextFile(recipient, recipients,idLoggedInUser);
    idLastPerson++;

    return idLastPerson;
}

void RecipientsBook::searchByName( vector <Recipient> &recipients, int idLoggedInUser)
{

    Recipient recipient;

    string nameOfSearchingRecipients = "";
    int numberRecipients = 0;



    system("cls");
    if (!recipients.empty())
    {
        cout << ">>> SEARCH RECIPIENTS BY NAME<<<" << endl << endl;

        cout << "Search recipients name: ";
        cin >> nameOfSearchingRecipients;

        for (vector <Recipient>::iterator  itr = recipients.begin(); itr != recipients.end(); itr++)
        {


            if ( itr -> Recipient::getName() == nameOfSearchingRecipients)
            {
                cout << endl;
                cout << "Id:                 " << itr -> Recipient::getRecipientId() << endl;
                cout << "Id loged in user:    " << itr -> Recipient::getUserId() << endl;
                cout << "NAme:               " << itr -> Recipient::getName() << endl;
                cout << "Surname:           " << itr -> Recipient::getSurname() << endl;
                cout << "Telephone:     " << itr -> Recipient::getTelephone() << endl;
                cout << "Email:           " << itr -> Recipient::getEmail() << endl;
                cout << "Address:              " << itr -> Recipient::getAddress() << endl;
                numberRecipients++;
            }
        }
        if (numberRecipients == 0)
        {
            cout << endl << "There are no addressees with this name in the address book" << endl;
        }
        else
        {
            cout << endl << "Number of recipients with this name: >>> " << nameOfSearchingRecipients << " <<<";
            cout << " in address book: " << numberRecipients << endl << endl;
        }
    }
    else
    {
        cout << "The address book is empty" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void RecipientsBook::searchBySurname(vector <Recipient> &recipients,  int idLoggedInUser)
{
    Recipient recipient;
    string surnameOfSearchingRecipient;
    int numberRecipients = 0;


    system("cls");
    if (!recipients.empty())
    {
        cout << ">>> SEARCH RECIPIENTS BY NAME <<<" << endl << endl;

        cout << "Search recipients surname: ";
        cin >> surnameOfSearchingRecipient;

        for (vector <Recipient>::iterator itr = recipients.begin(); itr != recipients.end(); itr++)
        {
            if (  itr -> Recipient::getSurname() == surnameOfSearchingRecipient)
            {
                cout << endl;
                cout << "Id:                 " << itr -> Recipient::getRecipientId() << endl;
                cout << "Id logged in user:    " << itr -> Recipient::getUserId() << endl;
                cout << "Name:               " << itr -> Recipient::getName() << endl;
                cout << "Surname:           " << itr -> Recipient::getSurname() << endl;
                cout << "Telephone:     " << itr -> Recipient::getTelephone() << endl;
                cout << "Email:           " << itr -> Recipient::getEmail() << endl;
                cout << "Address:              " << itr -> Recipient::getAddress() << endl;
                numberRecipients++;
            }
        }
        if (numberRecipients == 0)
        {
            cout << endl << "There are no addressees with this surname in the address book" << endl;
        }
        else
        {
            cout << endl << "Number of recipients with this name: >>> " << surnameOfSearchingRecipient << " <<<";
            cout << " in address book: " << numberRecipients << endl << endl;
        }
    }
    else
    {
        cout << "The address book is empty" << endl << endl;
    }
    cout << endl;
    system("pause");
}


void RecipientsBook::displayAllRecipient(vector <Recipient> &recipients, int idLoggedInUser )
{

    Recipient recipient;

    system("cls");

    int recipientsId = recipient.getUserId();
    if (!recipients.empty())
    {
        for (vector <Recipient> :: iterator itr = recipients.begin(); itr != recipients.end(); itr++)
        {

            cout << "Id:                 " << itr -> Recipient::getRecipientId() << endl;
            cout << "Id logged in user:    " << itr -> Recipient::getUserId() << endl;
            cout << "Name:               " << itr -> Recipient::getName() << endl;
            cout << "Surname:           " << itr -> Recipient::getSurname() << endl;
            cout << "Telephone:     " << itr -> Recipient::getTelephone() << endl;
            cout << "Email:           " << itr -> Recipient::getEmail() << endl;
            cout << "Address:              " << itr -> Recipient::getAddress() << endl;


        }
        cout << endl;
    }
    else
    {
        cout << "The address book is empty." << endl << endl;
    }

    system("pause");
}

void RecipientsBook::saveAllRecipientsToTextFile(vector <Recipient> &recipients)
{

    Recipient recipient;
    fstream textFile;
    string lineWithRecipientData = "";

    textFile.open("Adresaci.txt", ios::out);
    if (textFile.good())
    {
        for (vector <Recipient>::iterator itr = recipients.begin(); itr != recipients.end(); itr++)
        {
            lineWithRecipientData += convertIntToString(itr -> Recipient::getRecipientId() ) + '|';
            lineWithRecipientData += convertIntToString(itr -> Recipient::getUserId()) + '|';
            lineWithRecipientData += itr -> Recipient::getName() + '|';
            lineWithRecipientData += itr -> Recipient::getSurname() + '|';
            lineWithRecipientData += itr -> Recipient::getTelephone() + '|';
            lineWithRecipientData += itr -> Recipient::getEmail() + '|';
            lineWithRecipientData += itr -> Recipient::getAddress()+ '|';

            textFile << lineWithRecipientData << endl;
            lineWithRecipientData = "";
        }
        textFile.close();
    }
    else
    {
        cout << "The Address Book file can not be opened" << endl;
    }
}


int RecipientsBook::deleteRecipient(vector <Recipient> &recipients, int idLoggedInUser, int idLastPerson)
{

    int iddeletedRecipient = 0;
    char znak;
    bool czyIstnieje = false;


    system("cls");
    if (!recipients.empty())
    {
        cout << ">>> REMOVING A SELECTED PERSON <<<" << endl << endl;
        cout << "Enter the ID number of the recipient you want to DELETE: ";
        cin >> iddeletedRecipient;
        cout << endl;

        Recipient recipient;

        string dataOfSingleRecipientsSeparateByVerticalDashes = "";

        for (vector <Recipient>::iterator itr = recipients.begin(); itr != recipients.end(); itr++)
        {
            if (itr -> Recipient::getRecipientId() == iddeletedRecipient)
            {
                czyIstnieje = true;

                fstream textFile;
                textFile.open("Adresaci.txt", ios::in);

                if (textFile.good() == true)
                {

                    while (getline(textFile, dataOfSingleRecipientsSeparateByVerticalDashes))
                    {
                        recipient = getRecipientData(dataOfSingleRecipientsSeparateByVerticalDashes, idLoggedInUser);

                        if( ( recipient.getUserId()  != idLoggedInUser) || (recipient.getRecipientId() != iddeletedRecipient))
                        {
                            fstream plikTekstowy2;
                            plikTekstowy2.open("Adresaci_tymczasowo.txt", ios::out | ios::app);

                            if (plikTekstowy2.good() == true)
                            {
                                plikTekstowy2 << recipient.getRecipientId() << '|';
                                plikTekstowy2 << recipient.getUserId() << '|';
                                plikTekstowy2 << recipient.getName() << '|';
                                plikTekstowy2 << recipient.getSurname() << '|';
                                plikTekstowy2 << recipient.getTelephone() << '|';
                                plikTekstowy2 << recipient.getEmail() << '|';
                                plikTekstowy2 << recipient.getAddress() << '|' << endl;
                                plikTekstowy2.close();

                            }
                            else
                            {
                                cout << "It was not possible to open the file and save the data in it." << endl;
                                system("pause");
                            }

                            idLastPerson = recipient.getRecipientId();

                        }


                    }
                    cout << endl << "Confirm by pressing the key 't': ";
                    cin >> znak;
                    if (znak == 't')
                    {
                        cout << endl << endl << "Recipient has beed deleted" << endl << endl;
                        system("pause");
                    }


                    textFile.close();

                    remove("Adresaci.txt");
                    rename("Adresaci_tymczasowo.txt", "Adresaci.txt");

                }

            }

        }
        if (czyIstnieje == false)
        {
            cout << endl << "There is no recipient in the address book" << endl << endl;
            system("pause");
        }

    }
    else
    {
        cout << "The address book is empty" << endl << endl;
    }


    return idLastPerson;
}


int  RecipientsBook::editRecipient(vector <Recipient> &recipients, int idLoggedInUser, int idLastPerson)
{
    int idSelectedRecipient = 0;
    char choice;
    string name, surname, telephone, email, address;
    int userId, recipientId;
    bool czyIstniejeWybranyAdresat = false;

    system("cls");

    if (!recipients.empty())
    {
        cout << ">>> EDITION OF A CHOSEN ADDRESSE <<<" << endl << endl;
        cout << "Enter the ID number of the recipient where you want to change the data: ";
        cin >> idSelectedRecipient;
        cout << endl;


        Recipient recipient;

        string dataOfSingleRecipientsSeparateByVerticalDashes = "";

        for (vector <Recipient>::iterator itr = recipients.begin(); itr != recipients.end(); itr++)

        {
            if (itr -> Recipient::getRecipientId() == idSelectedRecipient)
            {
                fstream textFile;
                textFile.open("Adresaci.txt", ios::in);
                czyIstniejeWybranyAdresat = true;

                if (textFile.good() == true)
                {

                    while (getline(textFile, dataOfSingleRecipientsSeparateByVerticalDashes))
                    {
                        recipient = getRecipientData(dataOfSingleRecipientsSeparateByVerticalDashes, idLoggedInUser);

                        if( ( recipient.getUserId() != idLoggedInUser) || (recipient.getRecipientId() != idSelectedRecipient))
                        {

                            fstream plikTekstowy2;
                            plikTekstowy2.open("Adresaci_tymczasowo.txt", ios::out | ios::app);

                            if (plikTekstowy2.good() == true)
                            {
                                plikTekstowy2 << recipient.getRecipientId() << '|';
                                plikTekstowy2 << recipient.getUserId() << '|';
                                plikTekstowy2 << recipient.getName() << '|';
                                plikTekstowy2 << recipient.getSurname() << '|';
                                plikTekstowy2 << recipient.getTelephone() << '|';
                                plikTekstowy2 << recipient.getEmail() << '|';
                                plikTekstowy2 << recipient.getAddress() << '|' << endl;
                                plikTekstowy2.close();

                            }
                            else
                            {
                                cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
                                system("pause");
                            }

                        }
                        if ( ( recipient.getUserId()  == idLoggedInUser) & (recipient.getRecipientId() == idSelectedRecipient) )
                        {
                            recipient.setRecipientId(recipient.getRecipientId());
                            recipient.setUserId(idLoggedInUser);

                            cout << "Edytujesz kontakt o id rownym: " << idSelectedRecipient << endl << endl;
                            cout << endl << "-- MENU EDYCJI--" << endl;
                            cout << "------------------------ " << endl;
                            cout << "Ktore dane zaktualizowac: " << endl;
                            cout << "1 - Imie" << endl;
                            cout << "2 - Nazwisko" << endl;
                            cout << "3 - Numer telefonu" << endl;
                            cout << "4 - Email" << endl;
                            cout << "5 - Adres" << endl;
                            cout << "6 - Powrot " << endl;
                            cout << endl << "Twoj wybor: ";
                            cin >> choice;

                            switch (choice)
                            {
                            case '1':
                                cout << "Podaj zmienione imie: ";
                                cin >> name;
                                recipient.setName(name);
                                cout << endl << "Imie zostalo zmienione" << endl << endl;
                                Sleep(1500);
                                break;

                            case '2':
                                cout << "Podaj zmienione nazwisko: ";
                                cin >> surname;
                                recipient.setSurname(surname);
                                cout << endl << "Nazwisko zostalo zmienione" << endl << endl;
                                Sleep(1500);
                                break;

                            case '3':
                                cout << "Podaj zmieniony numer telefonu: ";
                                cin.sync();
                                getline(cin, telephone);
                                recipient.setTelephone(telephone);
                                cout << endl << "Numer telefonu zostal zmieniony" << endl << endl;
                                Sleep(1500);
                                break;

                            case '4':
                                cout << "Podaj zmieniony adres email: ";
                                cin >> email;
                                recipient.setEmail(email);
                                cout << endl << "Email zostal zmieniony" << endl << endl;
                                Sleep(1500);
                                break;

                            case '5':
                                cout << "Podaj zmieniony adres zamieszkania: ";
                                cin.sync();
                                getline(cin,address);
                                recipient.setAddress(address);
                                cout << endl << "Adres zostal zmieniony" << endl << endl;
                                Sleep(1500);
                                break;

                            case '6':
                                cout << endl << "Powrot do menu" << endl << endl;
                                Sleep(1500);

                            default:
                                cout << endl << "Nie ma takiej opcji w menu! Powrot do menu" << endl << endl;
                                Sleep(1500);
                                break;

                            }


                            fstream plikTekstowy3;
                            plikTekstowy3.open("Adresaci_tymczasowo.txt", ios::out | ios::app);

                            if (plikTekstowy3.good() == true)
                            {
                                plikTekstowy3 << recipient.getRecipientId() << '|';
                                plikTekstowy3 << recipient.getUserId() << '|';
                                plikTekstowy3 << recipient.getName() << '|';
                                plikTekstowy3 << recipient.getSurname() << '|';
                                plikTekstowy3 << recipient.getTelephone() << '|';
                                plikTekstowy3 << recipient.getEmail() << '|';
                                plikTekstowy3 << recipient.getAddress() << '|' << endl;
                                plikTekstowy3.close();

                            }
                        }

                    }
                    textFile.close();

                    remove("Adresaci.txt");
                    rename("Adresaci_tymczasowo.txt", "Adresaci.txt");

                }

            }


        }
        if (czyIstniejeWybranyAdresat == false)
        {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
            system("pause");
        }

    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    return idLastPerson;
}

void RecipientsBook::logOff(vector <Recipient> &recipients)
{
    recipients.clear();
}


string RecipientsBook::convertIntToString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}




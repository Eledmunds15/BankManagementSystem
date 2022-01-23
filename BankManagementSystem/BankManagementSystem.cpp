//Bank Management System

//Imports and namespace
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;

//creating class for accounts
class account {
    int acno; //Account number
    char name[50]; //Name
    int deposit; //Deposit
    char type; //Type of account

public:
    void create_account(); //Create account
    void show_account(); //Show account information
    void modify(); //Add new data to account
    void dep(int); //Accept amount and add balance
    void draw(int); //Accept amount and deduct from balance
    void report() const; //Show data in tabular formatl
    int retacno() const; //Return account number
    int retdeposit() const; //Return balance amount
    char rettype() const; //Return type of account
};

void account::create_account() {
    cout << "\n\tEnter Account No. : "; cin >> acno;

    cout << "\n\tEnter Name of Account Holder (Only alphabet characters): ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "\n\tEnter Account Type (C/S): "; cin >> type;
    type = toupper(type);

    cout << "\n\tEnter Initial Balance (>= 500 for Saving and >=1000 for Current) : "; cin >> deposit;

    cout << "\n\n\n\tAccount Created";
};

void account::show_account() {
    cout << "\n\tAccount no. : " << acno;
    cout << "\n\tAccount Holder Name : " << name;
    cout << "\n\tAccount Type : " << type;
    cout << "\n\tBalance Amount : " << deposit;
};

void account::modify() {
    cout << "\n\tEnter Account No. : "; cin >> acno;
    cout << "\n\tEnter Name of Account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n\tModify Account Type (C/S): "; cin >> type;
    type = toupper(type);
};

void account::dep(int x) {
    deposit += x;
};

void account::draw(int x) {
    deposit -= x;
};

void account::report() const {
    cout << setw(1) << acno << setw(5) << " " << setw(20) << name << setw(8) << " " << setw(1) << type << setw(6) << " " << deposit << endl;
};

int account::retacno() const {
    return acno;
};

int account::retdeposit() const {
    return deposit;
};

char account::rettype() const {
    return type;
}

//function decelerations
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

//Main function
int main()
{
    char ch;
    int num;
    intro();

    do {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. MODIFY AN ACCOUNT";
        cout << "\n\n\t07. CLOSE AN ACCOUNT";
        cout << "\n\n\t08. EXIT SYSTEM";

        cout << "\n\n\n\t"; cin >> ch;
        system("cls");

        switch (ch) {
        case '1':
            write_account();
            break;
        case '2':
            cout << "\n\n\tEnter account no. : "; cin >> num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            cout << "\n\n\tEnter account no. : "; cin >> num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            cout << "\n\n\tEnter account no. : "; cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout << "\n\n\tEnter account no. : "; cin >> num;
            modify_account(num);
            break;
        case '7':
            cout << "\n\n\tEnter account no. : "; cin >> num;
            delete_account(num);
            break;
        case '8':
            cout << "\n\n\tThanks for using Ethan's Bank Management System... Bye Bye!";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
};

//function to enter account information into file
void write_account() {
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
    outFile.close();
};

void display_sp(int n) {
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open!! Press any key ...";
        return;
    }

    cout << "\n\tBALANCE DETIALS\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))) {
        if (ac.retacno() == n) {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false) {
        cout << "\n\n\tRecord Not Found";
    }
};

//Function to modify account file
void modify_account(int n) {
    bool found = false;

    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open!! Press any key...";
        return;
    }

    while (!File.eof() && found == false) {
        File.read(reinterpret_cast <char*> (&ac), sizeof(account));
        if (ac.retacno() == n) {
            ac.show_account();
            cout << "\n\n\tEnter new details of the account" << endl;
            ac.modify();

            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\n\tRecord Updated";
            found = true;
        }
    }

    File.close();
    if (found == false) {
        cout << "\n\n\tRecord Not Found";
    }
};

void delete_account(int n) {
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open!! Press any key...";
        return;
    }

    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast <char*> (&ac), sizeof(account))) {
        if (ac.retacno() != n) {
            outFile.write(reinterpret_cast <char*> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord Deleted ...";
};

//Function to show all account currently in the system;
void display_all() {
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open!! Press any key";
        return;
    }
    cout << "\n\n\t\t ACCOUNT HOLDER LIST\n\n";
    cout << "================================================\n";
    cout << "A/c no.      NAME                Type    Balance\n";
    cout << "================================================\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))) {
        ac.report();
    }
    inFile.close();
};

void deposit_withdraw(int n, int option) {
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);

    if (!File) {
        cout << "File could not be open!! Press any key";
        return;
    }

    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if (ac.retacno() == n) {
            ac.show_account();
            if (option == 1) {
                cout << "\n\n\t    TO DEPOSIT AMOUNT";
                cout << "\n\n\tEnter amount to be deposited : "; cin >> amt;
                ac.dep(amt);
            }

            if (option == 2) {
                cout << "\n\n\t    TO WITHDRAW AMOUNT";
                cout << "\n\n\tEnter amount to be withdrawn : "; cin >> amt;
                int bal = ac.retdeposit() - amt;
                if ((bal < 500 && ac.rettype() == 'S') | (bal < 1000 && ac.rettype() == 'C')) {
                    cout << "\n\n\tInsufficient Balance";
                }
                else {
                    ac.draw(amt);
                }
            }

            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\tRecord Updated";
            found = true;
        }
    }

    File.close();
    if (found == false) {
        cout << "\n\n\tRecord Not Found";
    }
};

//Introduction function ... function that shows main menu;
void intro() {
    cout << "\n\n\n\t WELCOME TO ETHAN'S BANK MANAGEMENT SYSTEM";
    cout << "\n\n\n\n\tMADE BY : Ethan Edmunds";
    cout << "\n\n\tBEng Aerospace @ Uni of Sheffield";
    cout << "\n\n\n\tPress Enter to continue...";
    cin.get();
};
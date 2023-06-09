#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

fstream Registry;
int registrySize = 1;
fstream transactionHistory;

class BankSystem
{
protected:
    string uID;
    string password;
    double amountStored;
    bool isAmountUSD;
    long long int CNIC;
    int DoB[3];
    string address;
    long long int accNum;
    int pin;
    bool userFound;
    bool passwordCorrect;
    int startIndex;
    bool isCEOLogin;

public:
    BankSystem()
    {
        uID = "";
        password = "";
        amountStored = 0;
        isAmountUSD = false;
        CNIC = 0;
        DoB[0] = 0;
        DoB[1] = 0;
        DoB[2] = 0;
        address = "";
        accNum = 0;
        pin = 0;
        userFound = false;
        passwordCorrect = false;
        startIndex = 0;
        isCEOLogin = false;
    }
    ~BankSystem()
    {
        cout << "lol\n";
    }

    bool getUserFound()
    {
        return userFound;
    }

    bool getPasswordCorrect()
    {
        return passwordCorrect;
    }

    int getStartIndex()
    {
        return startIndex;
    }

    bool getIsAmountUSD()
    {
        return isAmountUSD;
    }

    void setIsAmountUSD(bool isAmountUSD)
    {
        this->isAmountUSD = isAmountUSD;
    }

    double getAmountStored()
    {
        return amountStored;
    }

    void setAmountStored(int x)
    {
        amountStored = amountStored + x;
    }

    void setAmountStored(double x)
    {
        amountStored = x;
    }

    bool getIsCEOLogin()
    {
        return isCEOLogin;
    }

    void setIsCEOLogin(bool isCEOLogin)
    {
        this->isCEOLogin = isCEOLogin;
    }

    string getUID()
    {
        return uID;
    }

    friend istream &operator>>(istream &in, BankSystem &x);
    friend istream &operator<<(istream &in, BankSystem &x);
};

template <class T>
class Sequence
{
    T amount;

public:
    void addAmount(BankSystem &login, T amount)
    {
        login.setAmountStored(login.getAmountStored() + amount);
        transactionHistory.open("Transaction_History.txt", ios::app);
        transactionHistory << login.getUID() << endl;
        transactionHistory << "Deposited ";
        transactionHistory << amount;
        if (login.getIsAmountUSD() == 1)
        {
            transactionHistory << " USD";
            transactionHistory << endl;
        }
        else
        {
            transactionHistory << " PKR";
            transactionHistory << endl;
        }
        transactionHistory.close();
    }
    void withdrawAmount(BankSystem &login, T amount)
    {
        if (login.getAmountStored() - amount < 0)
        {
            cout << "You do not have enough money to withdraw!\n";
            system("pause>nul");
        }
        else
        {
            login.setAmountStored(login.getAmountStored() - amount);
            transactionHistory.open("Transaction_History.txt", ios::app);
            transactionHistory << login.getUID() << endl;
            transactionHistory << "Withdrew ";
            transactionHistory << amount;
            if (login.getIsAmountUSD() == 1)
            {
                transactionHistory << " USD";
                transactionHistory << endl;
            }
            else
            {
                transactionHistory << " PKR";
                transactionHistory << endl;
            }
            transactionHistory.close();
        }
    }
};

void loginCode(BankSystem &login, bool &logout)
{
    if (logout == true)
    {
        cin << login;
    }
    logout = false;
    if (login.getUserFound() == true)
    {
        if (login.getPasswordCorrect() == true)
        {
            if (login.getIsCEOLogin() == true)
            {
                cout << "Welcome CEO\n";
            }
            else
            {
                Registry.open("Registry.txt", ios::in);
                vector<string> lines;
                string line;
                while (getline(Registry, line))
                {
                    lines.push_back(line);
                }
                Registry.close();
                system("cls");
                cout << "User name: " << lines[login.getStartIndex()] << endl;
                cout << "CNIC: " << lines[login.getStartIndex() + 2] << endl;
                cout << "Date of Birth: " << lines[login.getStartIndex() + 3] << endl;
                cout << "Address: " << lines[login.getStartIndex() + 4] << endl;
                cout << "Account Pin: " << lines[login.getStartIndex() + 5] << endl;
                if (login.getIsAmountUSD() == false)
                {
                    cout << "Amount Stored: " << stoi(lines[login.getStartIndex() + 6]) << " PKR" << endl;
                }
                else
                {
                    cout << "Amount Stored: $" << lines[login.getStartIndex() + 6] << endl;
                }
            }
        }
        else
        {
            cout << "Incorrect Password\n";
            system("pause>nul");
        }
    }
    else
    {
        cout << "User Not Found\n";
        system("pause>nul");
    }
}

istream &operator>>(istream &inp, BankSystem &x)
{
    cout << "Enter your user name: ";
    getline(inp, x.uID);

    cout << "Enter your password: ";
    getline(inp, x.password);

    cout << "Enter your CNIC: ";
    inp >> x.CNIC;

    cout << "You will now by entering your date of birth. You will be asked for Day, Month and Year seperately.\n";
    cout << "Enter the day on which you were born: ";
    inp >> x.DoB[0];
    cout << "Enter the month in which you were born: ";
    inp >> x.DoB[1];
    cout << "Enter the year in which you were born: ";
    inp >> x.DoB[2];

    cin.ignore();
    cout << "Enter your address: ";
    getline(inp, x.address);

    cout << "Enter your pin: ";
    inp >> x.pin;

    Registry.open("Registry.txt", ios::in);
    vector<string> lines;
    string line;
    while (getline(Registry, line))
    {
        lines.push_back(line);
    }
    Registry.close();
    Registry.open("Registry.txt", ios::out);
    for (int i = 0; i < lines.size(); i++)
    {
        if (i != 0)
        {
            Registry << lines[i] << endl;
        }
        else
        {
            Registry << registrySize << endl;
        }
    }
    Registry.close();
    Registry.open("Registry.txt", ios::app);
    Registry << endl;
    Registry << x.uID << endl;
    Registry << x.password << endl;
    Registry << x.CNIC << endl;
    Registry << x.DoB[0];
    Registry << "/";
    Registry << x.DoB[1];
    Registry << "/";
    Registry << x.DoB[2] << endl;
    Registry << x.address << endl;
    Registry << x.pin << endl;
    Registry << x.amountStored << endl;
    Registry << x.getIsAmountUSD() << endl;
    Registry.close();
    inp.ignore();
    system("cls");
    return inp;
}

istream &operator<<(istream &inp, BankSystem &x)
{
    cout << "Enter your user name: ";
    getline(inp, x.uID);
    cout << "Enter your password: ";
    getline(inp, x.password);
    if (x.uID == "CEO")
    {
        if (x.password == "12345678")
        {
            x.userFound = true;
            x.passwordCorrect = true;
            x.setIsCEOLogin(true);
        }
    }
    else
    {
        Registry.open("Registry.txt", ios::in);
        vector<string> lines;
        string line;
        while (getline(Registry, line))
        {
            lines.push_back(line);
        }
        Registry.close();
        for (int i = 2; i < lines.size(); i = i + 9)
        {
            if (lines[i] == x.uID)
            {
                x.userFound = true;
                if (lines[i + 1] == x.password)
                {
                    x.passwordCorrect = true;
                    x.startIndex = i;
                }
            }
        }
    }
    return inp;
}

Sequence<double> usdAdder;
Sequence<int> pkrAdder;

ostream &operator<<(ostream &out, BankSystem &x)
{
    return out;
}

int main()
{
    BankSystem login;
    bool logout = true;
    BankSystem *registry;
    do
    {
        system("cls");
        Registry.open("Registry.txt", ios::in);
        Registry >> registrySize;
        Registry.close();
        cout << "Do you want to login or register?\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        int ch = 0;
        do
        {
            cout << "Enter your choice: ";
            cin >> ch;
        } while (ch < 1 && ch > 2);
        cin.ignore();
        system("cls");
        if (ch == 1)
        {
            registry = new BankSystem[registrySize + 1];
            registrySize++;
            cin >> registry[0];
            logout = true;
        }
        else
        {
            loginCode(login, logout);
            Registry.open("Registry.txt", ios::in);
            vector<string> lines;
            string line;
            while (getline(Registry, line))
            {
                lines.push_back(line);
            }
            Registry.close();
            for (int i = 0; i < lines.size(); i++)
            {
                if (lines[i] == login.getUID())
                {
                    login.setAmountStored(stod(lines[i + 6]));
                    int booleanVal = stoi(lines[i + 7]);
                    login.setIsAmountUSD(booleanVal);
                }
            }
            system("cls");
            loginCode(login, logout);

            if (login.getPasswordCorrect() == false)
            {
                logout = true;
            }
            else
            {
                if (login.getIsCEOLogin() == true)
                {
                    do
                    {
                        cout << "\n1. See all registered users and their data\n";
                        cout << "2. See all user's transaction history\n";
                        cout << "3. Logout\n\n";
                        cout << "Your Choice: ";
                        int ceoChoice;
                        cin >> ceoChoice;
                        cout << endl;
                        if (ceoChoice == 1)
                        {
                            for (int i = 2; i < lines.size(); i++)
                            {
                                cout << lines[i] << endl;
                            }
                        }
                        else if (ceoChoice == 2)
                        {
                            transactionHistory.open("Transaction_History.txt", ios::in);
                            vector<string> transactionHistoryList;
                            string transactionLine;
                            while (getline(transactionHistory, transactionLine))
                            {
                                transactionHistoryList.push_back(transactionLine);
                            }
                            transactionHistory.close();
                            for (int i = 0; i < transactionHistoryList.size(); i = i + 2)
                            {
                                cout << transactionHistoryList[i] << " " << transactionHistoryList[i + 1] << endl;
                            }
                        }
                        else if (ceoChoice == 3)
                        {
                            logout = 1;
                        }
                    } while (logout != true);
                }
                else
                {
                    do
                    {
                        cout << "\n\n1. Would you like to add some amount to your account?\n";
                        cout << "2. Would you like to withdraw money from your account?\n";
                        cout << "3. View transaction history\n";
                        cout << "4. Logout\n";
                        cout << "Your Choice: ";
                        int choice = 0;
                        cin >> choice;
                        while (choice < 1 && choice > 4)
                        {
                            cout << "Incorrect Choice!\n";
                            cout << "Your Choice: ";
                            cin >> choice;
                        }
                        system("cls");
                        if (choice == 1)
                        {
                            if (login.getAmountStored() == 0)
                            {
                                int currencyPick = 0;
                                do
                                {
                                    cout << "1. Do you want to store amount in USD?\n";
                                    cout << "2. Do you want to store amount in PKR\n";
                                    cout << "Your choice: ";
                                    cin >> currencyPick;
                                } while (currencyPick < 1 && currencyPick > 2);
                                if (currencyPick == 1)
                                {
                                    login.setIsAmountUSD(1);
                                    double amount;
                                    cout << "How much would you like to add?: ";
                                    cin >> amount;
                                    usdAdder.addAmount(login, amount);

                                    Registry.open("Registry.txt", ios::out);
                                    for (int i = 0; i < lines.size(); i++)
                                    {
                                        if (login.getIsAmountUSD() == true)
                                        {
                                            lines[8] = to_string(stoi(lines[8]) + (static_cast<int>(login.getAmountStored())) * 286);
                                        }
                                        else
                                        {
                                            lines[8] = to_string(stoi(lines[8]) + login.getAmountStored());
                                        }
                                        if (lines[i] == login.getUID())
                                        {
                                            lines[i + 6] = to_string(login.getAmountStored());
                                            lines[i + 7] = to_string(login.getIsAmountUSD());
                                        }
                                        Registry << lines[i] << endl;
                                    }
                                    Registry.close();
                                    loginCode(login, logout);
                                }
                                else
                                {
                                    login.setIsAmountUSD(0);
                                    int amount;
                                    cout << "How much would you like to add?: ";
                                    cin >> amount;
                                    pkrAdder.addAmount(login, amount);
                                    Registry.open("Registry.txt", ios::out);
                                    for (int i = 0; i < lines.size(); i++)
                                    {
                                        if (login.getIsAmountUSD() == true)
                                        {
                                            lines[8] = to_string(stoi(lines[8]) + (static_cast<int>(login.getAmountStored())) * 286);
                                        }
                                        else
                                        {
                                            lines[8] = to_string(stoi(lines[8]) + login.getAmountStored());
                                        }

                                        if (lines[i] == login.getUID())
                                        {
                                            lines[i + 6] = to_string(static_cast<int>(login.getAmountStored()));
                                            lines[i + 7] = to_string(login.getIsAmountUSD());
                                        }
                                        Registry << lines[i] << endl;
                                    }
                                    Registry.close();
                                    loginCode(login, logout);
                                }
                            }
                            else
                            {
                                if (login.getIsAmountUSD() == 1)
                                {
                                    double amount;
                                    cout << "How much would you like to add?: ";
                                    cin >> amount;
                                    usdAdder.addAmount(login, amount);

                                    Registry.open("Registry.txt", ios::out);
                                    for (int i = 0; i < lines.size(); i++)
                                    {
                                        if (login.getIsAmountUSD() == true)
                                        {
                                            lines[8] = to_string(stoi(lines[8]) + (static_cast<int>(login.getAmountStored())) * 286);
                                        }
                                        else
                                        {
                                            lines[8] = to_string(stoi(lines[8]) + login.getAmountStored());
                                        }

                                        if (lines[i] == login.getUID())
                                        {
                                            lines[i + 6] = to_string(login.getAmountStored());
                                            lines[i + 7] = to_string(login.getIsAmountUSD());
                                        }
                                        Registry << lines[i] << endl;
                                    }
                                    Registry.close();
                                    loginCode(login, logout);
                                }
                                else
                                {
                                    int amount;
                                    cout << "How much would you like to add?: ";
                                    cin >> amount;
                                    pkrAdder.addAmount(login, amount);
                                    Registry.open("Registry.txt", ios::out);
                                    for (int i = 0; i < lines.size(); i++)
                                    {
                                        if (login.getIsAmountUSD() == true)
                                        {
                                            lines[8] = to_string(stoi(lines[8]) + (static_cast<int>(login.getAmountStored())) * 286);
                                        }
                                        else
                                        {
                                            lines[8] = to_string(stoi(lines[8]) + login.getAmountStored());
                                        }

                                        if (lines[i] == login.getUID())
                                        {
                                            lines[i + 6] = to_string(static_cast<int>(login.getAmountStored()));
                                            lines[i + 7] = to_string(login.getIsAmountUSD());
                                        }
                                        Registry << lines[i] << endl;
                                    }
                                    Registry.close();
                                    loginCode(login, logout);
                                }
                            }
                        }
                        else if (choice == 2)
                        {
                            if (login.getAmountStored() == 0)
                            {
                                cout << "You have no money stored in your account and therefore cannot withdraw\n";
                            }
                            else
                            {
                                if (login.getIsAmountUSD() == 1)
                                {
                                    double amount;
                                    cout << "How much would you like to withdraw?: ";
                                    cin >> amount;
                                    usdAdder.withdrawAmount(login, amount);

                                    Registry.open("Registry.txt", ios::out);
                                    for (int i = 0; i < lines.size(); i++)
                                    {
                                        if (login.getIsAmountUSD() == true)
                                        {
                                            lines[8] = to_string(stoi(lines[8]) - (static_cast<int>(login.getAmountStored())) * 286);
                                        }
                                        else
                                        {
                                            lines[8] = to_string(stoi(lines[8]) - login.getAmountStored());
                                        }
                                        if (lines[i] == login.getUID())
                                        {
                                            lines[i + 6] = to_string(login.getAmountStored());
                                            lines[i + 7] = to_string(login.getIsAmountUSD());
                                        }
                                        Registry << lines[i] << endl;
                                    }
                                    Registry.close();
                                    loginCode(login, logout);
                                }
                                else
                                {
                                    int amount;
                                    cout << "How much would you like to withdraw?: ";
                                    cin >> amount;
                                    pkrAdder.withdrawAmount(login, amount);
                                    Registry.open("Registry.txt", ios::out);
                                    for (int i = 0; i < lines.size(); i++)
                                    {
                                        if (login.getIsAmountUSD() == true)
                                        {
                                            lines[8] = to_string(stoi(lines[8]) - (static_cast<int>(login.getAmountStored())) * 286);
                                        }
                                        else
                                        {
                                            lines[8] = to_string(stoi(lines[8]) - login.getAmountStored());
                                        }
                                        if (lines[i] == login.getUID())
                                        {

                                            lines[i + 6] = to_string(static_cast<int>(login.getAmountStored()));
                                            lines[i + 7] = to_string(login.getIsAmountUSD());
                                        }
                                        Registry << lines[i] << endl;
                                    }
                                    Registry.close();
                                    loginCode(login, logout);
                                }
                            }
                        }
                        else if (choice == 3)
                        {
                            transactionHistory.open("Transaction_History.txt", ios::in);
                            vector<string> transactionHistoryList;
                            string transactionLine;
                            while (getline(transactionHistory, transactionLine))
                            {
                                transactionHistoryList.push_back(transactionLine);
                            }
                            transactionHistory.close();
                            for (int i = 0; i < transactionHistoryList.size(); i++)
                            {
                                if (transactionHistoryList[i] == login.getUID())
                                {
                                    cout << transactionHistoryList[i + 1] << endl;
                                }
                            }
                        }
                        else if (choice == 4)
                        {
                            logout = true;
                        }
                    } while (logout != true);
                }
            }
        }
    } while (logout == true);
    registry = nullptr;
    delete[] registry;
    return 0;
}
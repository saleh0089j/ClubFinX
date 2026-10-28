#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

enum class TransactionType
{
    INCOME,
    EXPENSE
};
struct Transaction
{
    int id;
    double amount;
    string category;
    string date;
    TransactionType type;
};

string getCurrentTimeStamp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm *localTime = std::localtime(&currentTime);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return std::string(buffer);
}

class Wallet
{
private:
    double balance = 0.00;

public:
    double getBalance() const
    {
        return balance;
    }
    void setBalance(double b)
    {
        balance = b;
    }
    double deposit(double amount)
    {
        if (amount > 0.0)
        {
            balance += amount;
            return balance;
        }
        else
        {
            balance = balance;
            return balance;
        }
    }

    double withdraw(double amount)
    {
        if (amount >= 0.0 && amount <= balance)
        {
            balance -= amount;
            return balance;
        }
        else
        {
            cout << "Insufficient funds." << endl;
            return balance;
        }
    }
};

class Ledger
{
public:
    vector<Transaction> transactions;

public:
    void addTransaction(const Transaction &t)
    {
        transactions.push_back(t);

        cout << "Your Transaction logged Successfully!!.." << endl;
    }
    void showHistory() const
    {
        for (const auto &t : transactions)
        {
            cout << "ID: " << t.id << endl;
            cout << "CATEGORY: " << t.category << endl;
            cout << "DATE: " << t.date << endl;
            cout << "AMOUNT: " << t.amount << endl;
        }
    }
    void loadFiles()
    {
        ifstream inFile("Fin_Records.txt");
        if (inFile.is_open())
        {
            transactions.clear();
            string line;

            while (std::getline(inFile, line))
            {
                if (line.empty())
                    continue;

                stringstream ss(line);
                string idStr, amountStr, category, date, typeStr;

                if (std::getline(ss, idStr, ',') && std::getline(ss, amountStr, ',') && std::getline(ss, category, ',') && std::getline(ss, date, ',') && std::getline(ss, typeStr, ','))
                {
                    Transaction t;
                    t.id = stoi(idStr);
                    t.amount = stod(amountStr);
                    t.category = category;
                    t.date = date;
                    t.type = static_cast<TransactionType>(stoi(typeStr));

                    transactions.push_back(t);
                }
            }
            inFile.close();
            cout << "Ledger records successfully restored from the archive.\n";
        }
        else
        {
            cout << "No previous records found. Starting with a clean slate.\n";
        }
    }
    void saveToFile() const
    {
        ofstream outFile("Fin_Records.txt");
        if (outFile.is_open())
        {
            for (const auto &t : transactions)
            {
                outFile << t.id << ","
                        << t.amount << ","
                        << t.category << ","
                        << t.date << ","
                        << static_cast<int>(t.type) << "\n";
            }
            outFile.close();
            cout << "Ledger records safely archived" << endl;
        }
        else
        {
            cout << "Error: Could not open the archive vault" << endl;
        }
    }
};
bool confirmExit()
{
    char choice;
    cout << "Are your sure, You want to Exit??" << endl;
    cout << "Y/N" << endl;
    cin >> choice;

    if (choice == 'n' || choice == 'N')
    {
        return false;
    }
    else if (choice == 'y' || choice == 'Y')
    {
        cout << "Exiting from CLUB FinX APP" << endl;
        return true;
    }
    return false;
}

int main()
{
    Wallet clubWallet;
    Ledger clubLedger;
    clubLedger.loadFiles();

    double restoredBalance = 0.00;
    for (const auto &t : clubLedger.transactions)
    {
        if (t.type == TransactionType::INCOME)
        {
            restoredBalance += t.amount;
        }
        else
        {
            restoredBalance -= t.amount;
        }
    }
    clubWallet.setBalance(restoredBalance);
    int choice;
    bool running = true;

    while (running)
    {
        cout << "\n--- ROYAL FENCING CENTER LEDGER ---\n";
        cout << "Current Balance: " << clubWallet.getBalance() << " BDT" << endl;
        cout << "1. Deposit Funds " << endl;
        cout << "2. Withdraw Funds " << endl;
        cout << "3. Transaction Histories" << endl;
        cout << "4. Exit" << endl;
        cout << endl;
        cout << "ENTER YOUR CHOICE" << endl;
        cin >> choice;

        if (choice == 1)
        {
            double amt;
            cout << "Enter your Deposit AMOUNT: " << endl;
            cin >> amt;
            if (clubWallet.deposit(amt))
            {
                cout << "Deposit Successful..!!" << " Current Balance: " << clubWallet.getBalance() << endl;

                // CREATE AND RECORD THE TRANSACTION HERE:
                Transaction t;
                t.id = clubLedger.transactions.empty() ? 1 : clubLedger.transactions.back().id + 1; // Auto unique ID
                t.amount = amt;
                t.category = "Deposit";
                t.date = getCurrentTimeStamp();   // Real-time timestamp
                t.type = TransactionType::INCOME; // Adjust based on your enum name

                clubLedger.transactions.push_back(t);
            }
            else
            {
                cout << "Invalid Deposit amount !!.." << endl;
            }
        }
        else if (choice == 2)
        {
            double amt;
            cout << "Enter Your Withdrawal Amount....: " << endl;
            cin >> amt;
            if (clubWallet.withdraw(amt))
            {
                cout << "Withdrawal Successful..!!"
                     << " Current Balance: " << clubWallet.getBalance() << endl;
                Transaction t;
                t.id = clubLedger.transactions.empty() ? 1 : clubLedger.transactions.back().id + 1; // Auto unique ID
                t.amount = amt;
                t.category = "Expense";
                t.date = getCurrentTimeStamp();    // Real-time timestamp
                t.type = TransactionType::EXPENSE; // Adjust based on your enum name

                clubLedger.transactions.push_back(t); // Add to vector
            }

            else
            {
                cout << "Invalid Deposit Amount..!!" << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Transaction Histories...." << endl;
            clubLedger.showHistory();
        }
        else if (choice == 4)
            if (confirmExit())
            {
                running = false;
                clubLedger.saveToFile();
            }
    }
}

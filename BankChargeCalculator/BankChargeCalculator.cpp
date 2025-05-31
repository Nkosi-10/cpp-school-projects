#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Standard charges for Capitec Bank
const double ADMIN_FEE = 5.00;
const double EXTRA_WITHDRAWAL_CHARGE = 22.50;
const int FREE_WITHDRAWALS = 4;
const double OVERDRAFT_PENALTY = 375.00;

// This class handles a customer's bank activities for the month
class BankTransaction {
private:
    string customerName;
    double openingBalance;
    double currentBal;
    bool overdraftAllowed;
    vector<double> withdrawalsList;
    double withdrawalCharges;
    double overdraftFee;

public:
    // Constructor sets up account details
    BankTransaction(string name, double start, bool overdraft)
        : customerName(name), openingBalance(start), currentBal(start), overdraftAllowed(overdraft),
          withdrawalCharges(0.0), overdraftFee(0.0) {}

    // Handles each withdrawal, if it makes sense
    void handleWithdrawal(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal must be more than zero." << endl;
            return;
        }

        if (currentBal >= amount) {
            currentBal -= amount;
            withdrawalsList.push_back(amount);
            cout << "Withdrawal of R" << fixed << setprecision(2) << amount << " completed." << endl;
        } else if (overdraftAllowed) {
            currentBal -= amount;
            withdrawalsList.push_back(amount);
            cout << "Withdrawal of R" << amount << " allowed with overdraft." << endl;
        } else {
            cout << "Insufficient funds for R" << amount << ". Transaction declined." << endl;
        }
    }

    // Calculates monthly fees and penalties
    void calculateCharges() {
        int totalWithdrawals = withdrawalsList.size();
        if (totalWithdrawals > FREE_WITHDRAWALS) {
            int extra = totalWithdrawals - FREE_WITHDRAWALS;
            withdrawalCharges = extra * EXTRA_WITHDRAWAL_CHARGE;
        }

        if (currentBal < 0 && overdraftAllowed) {
            overdraftFee = OVERDRAFT_PENALTY;
        }
    }

    // Final balance after all fees taken out
    double computeFinalBalance() const {
        return currentBal - ADMIN_FEE - withdrawalCharges - overdraftFee;
    }

    // Gives a detailed account report for the month
    void printSummary() const {
        cout << fixed << setprecision(2);
        cout << endl << "===== Capitec Monthly Account Report =====" << endl;
        cout << "Name: " << customerName << endl;
        cout << "Opening Balance: R" << openingBalance << endl;
        cout << "Overdraft Access: " << (overdraftAllowed ? "Yes" : "No") << endl;

        cout << endl << "--- Withdrawals ---" << endl;
        if (withdrawalsList.empty()) {
            cout << "You didn’t withdraw anything this month." << endl;
        } else {
            for (size_t i = 0; i < withdrawalsList.size(); ++i) {
                cout << "Withdrawal " << (i + 1) << ": R" << withdrawalsList[i] << endl;
            }
        }
        cout << "Total Withdrawals: " << withdrawalsList.size() << endl;

        cout << endl << "--- Charges ---" << endl;
        cout << "Admin Fee: R" << ADMIN_FEE << endl;
        cout << "Extra Withdrawal Charges: R" << withdrawalCharges << endl;
        cout << "Overdraft Penalty: R" << overdraftFee << endl;
        cout << "Total Deductions: R" << (ADMIN_FEE + withdrawalCharges + overdraftFee) << endl;

        cout << endl << "--- Final Balance ---" << endl;
        cout << "Balance Before Fees: R" << currentBal << endl;
        cout << "Final Balance After Fees: R" << computeFinalBalance() << endl;
        cout << "==========================================" << endl;
    }
};

// Main function that drives the program
int main() {
    string name;
    double balance;
    int overdraftInput;
    int numWithdrawals;

    cout << fixed << setprecision(2);
    cout << "Welcome to Capitec Monthly Charge Calculator" << endl;

    // Collect account holder details
    cout << "Please enter your full name: ";
    getline(cin, name);

    cout << "Enter your starting balance (R): ";
    while (!(cin >> balance) || balance < 0) {
        cout << "That balance ain't right. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Do you have overdraft enabled? (1 for Yes, 0 for No): ";
    while (!(cin >> overdraftInput) || (overdraftInput != 0 && overdraftInput != 1)) {
        cout << "Please enter 1 or 0 only: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool overdraftEnabled = (overdraftInput == 1);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Just to clear input buffer

    // Create account object
    BankTransaction account(name, balance, overdraftEnabled);

    // Get number of withdrawals
    cout << "How many withdrawals did you make this month? ";
    while (!(cin >> numWithdrawals) || numWithdrawals < 0) {
        cout << "Withdrawals must be a non-negative number. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Process withdrawals
    for (int i = 0; i < numWithdrawals; ++i) {
        double amount;
        cout << "Enter amount for withdrawal #" << (i + 1) << ": R";
        while (!(cin >> amount) || amount < 0) {
            cout << "Enter a valid positive amount: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        account.handleWithdrawal(amount);
    }

    // Process and print account summary
    account.calculateCharges();
    account.printSummary();

    return 0;
}

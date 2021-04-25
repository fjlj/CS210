// BankingThing.cpp : program to calculate annual interest with and without monthly contributions
//franklin lewis
//CS210

#include <iostream>
#include "invest.h"

using namespace std;
int main()
{
    auto userInvest = unique_ptr<Invest>(new Invest());
    double cinInput = 0.0;
    
    cout << "Initial Investment Amount: ";
    cin >> cinInput;
    userInvest->SetInitialInvestment(cinInput);

    cout << "Monthly Deposit: ";
    cin >> cinInput;
    userInvest->SetMonthlyDeposit(cinInput);

    cout << "Annual Interest: ";
    cin >> cinInput;
    userInvest->SetAnnualInterestRate(cinInput);

    cout << "Number of years: ";
    cin >> cinInput;
    userInvest->SetNumYears(cinInput);


    userInvest->PrintReport();
    cout << endl;
    userInvest->PrintReport(true);

    system("pause");
}


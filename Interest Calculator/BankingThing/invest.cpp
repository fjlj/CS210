#include "invest.h"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

//getters and setters
void Invest::SetInitialInvestment(double t_amount) { mInitialInvestment = t_amount; }

void Invest::SetMonthlyDeposit(double t_amount) { mMonthlyDeposit = t_amount; }

void Invest::SetAnnualInterestRate(double t_amount) { mAnnualInterestRate = t_amount / 100; }

void Invest::SetNumYears(double t_amount) { mNumYears = static_cast<unsigned int>(t_amount); }

double Invest::InitialInvestment() { return mInitialInvestment; }

double Invest::MonthlyDeposit() { return mMonthlyDeposit; }

double Invest::AnnualInterestRate() { return mAnnualInterestRate; }

unsigned int Invest::NumYears() { return mNumYears; }

//simple function to output yearly reports for interest compounding monthly (could not get the formula for summing a series to calculate accurately was alwaya a few cents off)
void compoundMonths(double principle, double deposit, double years, double iRate) {
	double totalInterest = 0.0;
	double interest = 0.0;
	int year = 1;

	//iterate through months calculate interest
	for (int i = 1; i <= years * 12; i++) {
		principle += deposit;
		interest = principle * (iRate / 12);
		principle += interest;
		totalInterest += interest;

		//output on the end of the year
		if (i % 12 == 0) {
			cout << setw(6) << year << setw(20) << principle << setw(28) << totalInterest << endl;
			year++;
		}
	}
}

//print the report
void Invest::PrintReport(bool withDeposits)
{
	string preposition = (withDeposits ? "With" : "Without");
	cout << setw(60) << "Balance and Interest Without Additional Monthly Deposits" << endl;
	cout << setw(65) << setfill('=') << " " << endl << setfill(' ');
	cout << setw(8) << "Year" << setw(24) << "Year End Balance" << setw(32) << "Year End Earned Interest" << endl;
	cout << setw(65) << setfill('-') << " " << endl << setfill(' ') << fixed << setprecision(2);

	double yearEndBalance = 0.0;
	double yearEndInterest = 0.0;

	if (withDeposits) {
		compoundMonths(this->mInitialInvestment, this->mMonthlyDeposit, this->mNumYears, this->mAnnualInterestRate);
	}
	else 
	{

		for (int i = 1; i <= static_cast<int>(this->mNumYears); ++i) {

			{
				yearEndBalance = this->mInitialInvestment * pow((1 + (this->mAnnualInterestRate / 12)), (12 * i));
				yearEndInterest = yearEndBalance - (this->mInitialInvestment * pow((1 + (this->mAnnualInterestRate / 12)), (12 * ((i - 1) % (i + 1)))));
				cout << setw(6) << i << setw(20) << yearEndBalance << setw(28) << yearEndInterest << endl;
			}

		}
	}
	cout << endl;
}




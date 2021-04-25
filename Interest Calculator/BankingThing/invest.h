#pragma once
#ifndef BANKINGTHING_INVEST_H_
#define BANKINGTHING_INVEST_H_
#include <string>

using namespace std;

class Invest {
private:
	double mInitialInvestment;
	double mMonthlyDeposit;
	double mAnnualInterestRate;
	unsigned int mNumYears;

public:
	void SetInitialInvestment(double t_amount);
	void SetMonthlyDeposit(double t_amount);
	void SetAnnualInterestRate(double t_amount);
	void SetNumYears(double t_amount);

	double InitialInvestment();
	double MonthlyDeposit();
	double AnnualInterestRate();
	unsigned int NumYears();
	void PrintReport(bool withDeposits = false);

};

#endif //BANKINGTHING_INVEST_H_
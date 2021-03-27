// ===================================================================================
//  Assignment: 2
//  Milestone : 2
// ===================================================================================
//  Student Name  : Nasim Khodapanah
//  Student ID    : 131929200
//  Student Email : nkhodapanah@myseneca.ca
//  Course Section: NGG
// ===================================================================================

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

typedef struct Demographic {
	int birthYear;
	double houseHoldIncome;
	char country[31];
}Demographic;

typedef struct UserLogin {
	char customerName[31];
	char userName[11];
	char password[9];

}UserLogin;

typedef struct Account {
	int accountNumber;
	char accountType;
	struct UserLogin name;
	struct Demographic log;

}Account;


void getAccount(Account* user);
void getUserLogin(UserLogin* login);
void getDemographic(Demographic* info);

void updateAccount(Account* update);
void updateUserLogin(UserLogin* user);
void updateDemographic(Demographic* demo);

void createPass(UserLogin* login);

#endif // !ACCOUNT_H_
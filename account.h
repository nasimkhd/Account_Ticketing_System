
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

//GetData
void   getAccount(Account* user);
void   getUserLogin(UserLogin* login);
void   getDemographic(Demographic* info);

//UpdateData
void   updateAccount(Account* update);
void   updateUserLogin(UserLogin* user);
void   updateDemographic(Demographic* demo);

void   createPass(UserLogin* login);

//FileData
int   loadAccounts(Account  account[], int ACCOUNT_SIZE);
void  accounts_arc(Account* removeaccount, int account_size);
int   recreateTheAccout(Account* account, int arrSize);
void  ViewArchivedAccounts(Account account[]);


#endif // !ACCOUNT_H_
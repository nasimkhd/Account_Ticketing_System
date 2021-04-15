

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include <ctype.h>
#include <string.h>
#include "commonHelpers.h"



void getAccount(Account* user) {
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	user->accountType = getCharOption("AC");

}
void createPass(UserLogin* login) {
	int i = 0, countDigit = 0, countUpper = 0, countLow = 0, countSym = 0;
	do {
		countDigit = 0, countUpper = 0, countLow = 0, countSym = 0;
		for (i = 0; login->password[i] != '\0'; i++) {
			if (isdigit(login->password[i])) {
				countDigit++;
			}
			else if (isupper(login->password[i])) {
				countUpper++;
			}
			else if (islower(login->password[i])) {
				countLow++;
			}
			else {
				if (login->password[i] != '(') {
					countSym++;
				}
			}
		}
		if (countDigit < 2 || countLow < 2 || countUpper < 2 || countSym < 2) {
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
			printf("Enter the password (must be 8 chars in length): ");
			scanf("%s", login->password);
		}

	} while ((countDigit < 2 || countLow < 2 || countUpper < 2 || countSym < 2));
}
void getUserLogin(UserLogin* login) {
	int i, countdigit = 0;
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter user login (10 chars max): ");
	getCString(login->userName, 1, 10);
	for (i = 0; login->userName[i] != '\0'; i++) {

		if (isblank(login->userName[i])) {
			countdigit++;
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
			printf("Enter user login (10 chars max): ");
			getCString(login->userName, 1, 10);
		}

	}
	printf("Enter the display name (30 chars max): ");
	getCString(login->customerName, 1, 30);
	printf("Enter the password (must be 8 chars in length): ");
	getCString(login->password, 8, 8);
	createPass(login);

}

void getDemographic(Demographic* info) {
	int i;
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter birth year (current age must be between 18 and 110): ");
	currentYear();
	info->birthYear = getIntFromRange(1911, 2003);
	printf("Enter the household Income: $");
	info->houseHoldIncome = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(info->country, 1, 30);
	for (i = 0; i < (int)strlen(info->country); i++)
		info->country[i] = toupper(info->country[i]);
}

void updateAccount(Account* update) {
	int account;
	do {
		printf("Account: %d - Update Options\n", update->accountNumber);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", update->accountType);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		account = getIntFromRange(0, 3);
		switch (account) {
		case 1: printf("\nEnter the account type (A=Agent | C=Customer): ");
			update->accountType = getCharOption("AC");
			break;
		case 2:
			updateUserLogin(&update->name);
			break;
		case 3:
			updateDemographic(&update->log);
			break;
		case 0: printf("\n"); break;
		}

	} while (account);
}

void updateUserLogin(UserLogin* user) {
	int select;
	do {
		printf("\nUser Login: %s - Update Options\n", user->userName);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", user->customerName);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		select = getIntFromRange(0, 2);
		switch (select) {
		case 1: printf("\nEnter the display name (30 chars max): ");
			getCString(user->customerName, 1, 30);
			break;
		case 2: printf("\nEnter the password (must be 8 chars in length): ");
			getCString(user->password, 8, 8);
			createPass(user);
			break;
		case 0: printf("\n"); break;
		}
	} while (select);
}
void updateDemographic(Demographic* demo) {
	int select, i = 0;
	do {
		printf("\nDemographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2f)\n", demo->houseHoldIncome);
		printf("2) Country (current value: %s)\n", demo->country);
		printf("0) Done\n");
		printf("Selection: ");
		select = getInteger();
		switch (select) {
		case 1: printf("\nEnter the household Income: $");
			demo->houseHoldIncome = getPositiveDouble();
			break;
		case 2: printf("\nEnter the country (30 chars max.): ");
			getCString(demo->country, 1, 30);
			for (i = 0; i < (int)strlen(demo->country); i++)
				demo->country[i] = toupper(demo->country[i]);
			break;
		case 0: printf("\n");
			break;
		}
	} while (select);
}

int loadAccounts(struct Account Account[], int ACCOUNT_SIZE) {
	int i = 0, flag = 1;
	FILE* fp = fopen("accounts.txt", "r");
	if (fp != NULL) {
		while (i <= ACCOUNT_SIZE && flag == 1)
		{
			fscanf(fp, "%d~%c~%[^~]~%[^~]~%[^~]~%d~%lf~%[^\n]",
				&Account[i].accountNumber,
				&Account[i].accountType,
				Account[i].name.customerName,
				Account[i].name.userName,
				Account[i].name.password,
				&Account[i].log.birthYear,
				&Account[i].log.houseHoldIncome,
				Account[i].log.country);
			if  (Account[i].accountNumber != 0)
				i++;
			else
				flag = 0;
		}
		fclose(fp);
		fp = NULL;
	}
	else printf("Failed to open the file accounts_arc.txt for writing\n");

	return i - 1;
}

void accounts_arc(Account* removeaccount, int account_size) {
	FILE* fp;
	fp = fopen("accounts_arc.txt", "a");
	if (fp != NULL) {
		fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n",
			removeaccount->accountNumber,       removeaccount->accountType,
			removeaccount->name.customerName,   removeaccount->name.password,
			removeaccount->name.userName,       removeaccount->log.birthYear,
			removeaccount->log.houseHoldIncome, removeaccount->log.country);
		fclose(fp);
		fp = NULL;
	}
	else printf("Failed to open the file accounts_arc.txt for writing.\n");

}

int recreateTheAccout(Account* account, int arrSize) {
	int i, numAccount = 0;
	FILE* fp = fopen("accounts.txt", "w");
	if (fp != NULL)
	{
		for (i = 0; i < arrSize; i++) {
			if (account[i].accountNumber != 0) {
				fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n",
					account[i].accountNumber,       account[i].accountType,   account[i].name.userName,
					account[i].name.customerName,   account[i].name.password, account[i].log.birthYear,
					account[i].log.houseHoldIncome, account[i].log.country);

				numAccount++;
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else
		printf("Failed to open the file accounts.txt for writing\n");
	return numAccount;
}

void ViewArchivedAccounts(Account account[]) {

	int i = 0, flag = 1, buffer = 0;
	char ch[1000];
	FILE* fp = fopen("accounts_arc.txt", "r");
	if (fp != NULL) {
		while (flag == 1)
		{
			fscanf(fp, "%d~%[^\n]", &buffer, ch);
			if (buffer != 0) {
				i++;
				buffer = 0;
			}
			else {
				fclose(fp);
				fp = NULL;
				flag = 0;
			}
		}
	}
	printf("There are %d account(s) currently archived.\n\n", i);
}
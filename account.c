
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "ticket.h"


void getAccount(Account* user) {
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	user->accountType = getCharOption("AC");
	putchar('\n');

}
void createPass(UserLogin* login) {
	int i = 0, countDigit = 0, countUpper = 0, countLow = 0, countSym = 0;
	do {
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
			else countSym++;
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
	int i , countdigit=0;
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter user login (10 chars max): ");
	getCString(login->userName, 1, 10);
	for (i = 0; login->userName[i] != '\0'; i++) {

		if (isblank(login->userName[i])) {
			countdigit++;
			printf("ERROR: The user login must NOT contain whitespace characters.\n");
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
	for (i = 0; i < strlen(info->country); i++)
		info->country[i] = toupper(info->country[i]);
}

void updateAccount(Account* update) {
	int account;
	do {

		printf("\nAccount: %d - Update Options\n", update->accountNumber);
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
		case 0:  break;
		}
	} while (select);
}
void updateDemographic(Demographic* demo) {
	int select;
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
			break;
		case 0: break;
		}
	} while (select);
}

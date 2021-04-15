
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "account.h"
#include "ticket.h"


//ApplicationStartUp
void applicationStartup(struct AccountTicketingData* account)
{
	int result;
	do
	{
		result = menuLogin(account->accounts, account->ACCOUNT_MAX_SIZE);
		if (result >= 0 && account->accounts[result].accountType != 'C')
		{
			printf("\n");
			menuAgent(account, &account->accounts[result]);
		}
		else if (result > -1 && account->accounts[result].accountType == 'C')
		{
			menuCustomer(account, &account->accounts[result]);
			printf("\n");
		}
	} while (result >= 0);
	printf("==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n");

}

//menu Login
int menuLogin(const struct Account accounts[], int arrSize)
{
	int attempts = 0, index, done = 0;
	char store = { 0 };
	do {
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n0) Exit application\n");
		printf("----------------------------------------------\n\nSelection: ");
		int customer_selection = getIntFromRange(0, 1);
		switch (customer_selection) {
		case 0:printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
			store = getCharOption("yYnN");
			if (toupper(store) == 'Y') {
				printf("\n");
				done = 1;
				index = -1;
			}
			break;
		case 1:
			while (checkAccount(accounts, arrSize, &index) && attempts < 2) {
				attempts++;
				printf("INVALID user login/password combination! [attempts remaining:%d]\n", 3 - attempts);
			}
			if (attempts >= 2) {
				attempts++;
				printf("INVALID user login/password combination! [attempts remaining:%d]\n", 3 - attempts);
				printf("\nERROR:  Login failed!\n\n");
				pauseExecution();
				printf("\n");
				attempts = 0;
			}
			else {
				done = 1;
			}
			break;
			printf("\n");
		}
	} while (!done);
	return index;
}
//meny agent
void viewmenuAgent(const struct Account* loggedDetail)
{
	printf("AGENT: %s (%d)\n", loggedDetail->name.customerName, loggedDetail->accountNumber);
	printf("==============================================\n");
	printf("Account Ticketing System - Agent Menu\n");
	printf("==============================================\n");
	printf(" 1) Add a new account\n");
	printf(" 2) Modify an existing account\n");
	printf(" 3) Remove an account\n");
	printf(" 4) List accounts: summary view\n");
	printf(" 5) List accounts: detailed view\n");
	printf("----------------------------------------------\n");
	printf(" 6) List new tickets\n");
	printf(" 7) List active tickets\n");
	printf(" 8) List closed tickets\n");
	printf(" 9) Manage a ticket\n");
	printf("10) Archive closed tickets\n");
	printf("----------------------------------------------\n");
	printf("11) View archived account statistics\n");
	printf("12) View archived tickets statistics\n");
	printf("----------------------------------------------\n");
	printf("0) Logout\n");
	printf("\nSelection: ");
}

//Menu Agent Data
void menuAgent(struct AccountTicketingData* agent, const struct Account* loggedDetail) {
	int index, account ,i=0;
	char acc, acc1;
	int account_saved, ticket_saved;
	do {
		viewmenuAgent(loggedDetail);
		account = getIntFromRange(0, 12);
		switch (account) {
		case 1:        newAccount(agent);
			break;
		case 2:        modifyAccount(agent);
			break;
		case 3:        removeAccount(agent, loggedDetail);
			break;
		case 4:        displayAllAccountSummaryRecords(agent->accounts, agent->ACCOUNT_MAX_SIZE);
			           pauseExecution();
			           printf("\n");
			break;
		case 5:        printf("\n");
			           displayAllAccountDetailRecords(agent->accounts, agent->ACCOUNT_MAX_SIZE);
			           pauseExecution();
			           printf("\n");
			break;
		case 6:        listMyTicket(agent->tickets);
			break;
		case 7:        listAllTickets(agent->tickets, 1);
			break;
		case 8:        listAllTickets(agent->tickets, 0);
			break;
		case 9:
			           printf("\nEnter ticket number: ");
			           int store = getPositiveInteger();
			           index = findTicketByNum(store, agent->tickets, 17);
			           printf("\n");
		          	   manageOneTicket(&agent->tickets[index], loggedDetail);
			break;
		case 10:      printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			          acc1 = getCharOption("YN");
			          if (acc1 == 'Y')
			       	  tickets_arc(agent->tickets, agent->TICKET_MAX_SIZE);
			break;
		case 11:      printf("\n");
			          ViewArchivedAccounts(agent->accounts);
                      pauseExecution();
			          printf("\n");
			break;
		case 12:      ViewArchivedTicket(agent->tickets, agent->TICKET_MAX_SIZE);
			          printf("\n");
			break;
		case 0:      printf("\n");
			         account_saved = recreateTheAccout(agent->accounts, agent->ACCOUNT_MAX_SIZE);
			         ticket_saved = recreateTicket(agent->tickets, agent->TICKET_MAX_SIZE);

			         printf("Saving session modifications...\n");
			         printf("   %d account saved.\n", account_saved);
			         printf("   %d tickets saved.\n", ticket_saved);
			         printf("### LOGGED OUT ###\n");
			         printf("\n");
			break;
		}
	} while (account);
}
//menuCustomer
void viewmenuCustomer(const struct Account *loggedDetail) 
{
	printf("\nCUSTOMER: %s (%d)\n", loggedDetail->name.customerName, loggedDetail->accountNumber);
	printf("==============================================\n");
	printf("Customer Main Menu\n");
	printf("==============================================\n");
	printf("1) View your account detail\n");
	printf("2) Create a new ticket\n");
	printf("3) Modify an active ticket\n");
	printf("4) List my tickets\n");
	printf("----------------------------------------------\n");
	printf("0) Logout\n\n");
	printf("Selection: ");
}

//MenucustomerData
void menuCustomer(struct AccountTicketingData* tickets, const struct Account* loggedDetail) {
	int account = 0, index, ticketNumber, ticket_saved;
	do {
		viewmenuCustomer(loggedDetail);
		account = getIntFromRange(0, 5);
		switch (account) {
		case 1:
			        printf("\n");
			        displayAccountDetailHeader();
			        displayAccountDetailRecord(loggedDetail);
			        printf("\n\n");
			        pauseExecution();
			break;
		case 2:     newTicket(tickets, loggedDetail);
			break;
		case 3:     modifyTicket(tickets, loggedDetail);
			break;
		case 4:
			        printf("\n");
			        displayAllTickets_forAccounts(tickets, loggedDetail);
			break;
		case 0:     printf("\nSaving session modifications...\n");
			        ticket_saved = recreateTheTicket(tickets->tickets, tickets->TICKET_MAX_SIZE);
			        printf("   %d tickets saved.", ticket_saved);
			        printf("\n### LOGGED OUT ###\n");
			break;
		}
	} while (account);
}

void newAccount(struct AccountTicketingData* agent) {
	int index;
	index = findAccountIndexByAcctNum(0, agent->accounts, agent->ACCOUNT_MAX_SIZE, 0);
	int i = 0, highest = agent->accounts[i].accountNumber;
	for (i = 0; i < agent->ACCOUNT_MAX_SIZE; i++) {
		if (highest < agent->accounts[i].accountNumber)
			highest = agent->accounts[i].accountNumber;
	}
	if (index < 0) {
		printf("\nERROR: Account listing is FULL, call ITS Support!\n");
		printf("\n");
	}
	else {
		printf("\nNew Account Data (Account#:%d)\n", highest + 1);
		agent->accounts[index].accountNumber = highest + 1;
		getAccount(&agent->accounts[index]);
		printf("\n");
		getUserLogin(&agent->accounts[index].name);
		printf("\n");
		getDemographic(&agent->accounts[index].log);
		printf("\n*** New account added! ***\n\n");
	}
	pauseExecution();
	printf("\n");
}
void modifyAccount(struct AccountTicketingData* agent) {
	int index, account;
	printf("\nEnter the account#: ");
	account = getPositiveInteger();
	printf("\n");
	index = findAccountIndexByAcctNum(account, agent->accounts, agent->ACCOUNT_MAX_SIZE, 0);
	if (index < 0) {
		printf("ERROR: Access Denied.\n");
		pauseExecution();
		printf("\n");
	}
	else {
		updateAccount(&agent->accounts[index]);
	}
}
void removeAccount(struct AccountTicketingData* agent, const struct Account* loggedDetail) {
	int index, account, i = 0;
	char acc;
	printf("\nEnter the account#: ");
	account = getPositiveInteger();
	index = findAccountIndexByAcctNum(account, agent->accounts, agent->ACCOUNT_MAX_SIZE, 0);
	int index2 = findAccountIndexByAcctNum(loggedDetail->accountNumber, agent->accounts, agent->ACCOUNT_MAX_SIZE, 0);

	if (index == -1)
		printf("\nAccount not founded! \n\n");
	if (index == index2) {
		printf("\n");
		printf("ERROR: You can't remove your own account!\n");
		printf("\n");
		pauseExecution();
	}
	else
	{
		if (index != -1) {
			displayAccountDetailHeader();
			displayAccountDetailRecord(&agent->accounts[index]);
			printf("\n\n");
			printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
			acc = getCharOption("YN");
			printf("\n");
			if (acc == 'Y' || acc == 'y') {
				for (i = 0; i < agent->TICKET_MAX_SIZE; i++) {
					if (agent->tickets[i].customerAccountNum == agent->accounts[index].accountNumber && agent->tickets[i].ticketNumber > 0) {
						agent->tickets[i].ticketNumber = 0;
					}
				}
				accounts_arc(&agent->accounts[index], agent->ACCOUNT_MAX_SIZE);
				agent->accounts[index].accountNumber = 0;
				printf("*** Account Removed! ***\n\n");
			}
			pauseExecution();
			printf("\n");
		}
		else {
			printf("*** No changes made! ***\n\n");
			pauseExecution();
			printf("\n");
		}
	}
}
void newTicket(struct AccountTicketingData* tickets, const struct Account* loggedDetail) {
	printf("\n");
	int index;
	index = findFreeTicket(tickets->tickets, tickets->TICKET_MAX_SIZE);
	int i = 0, highest = tickets->tickets[i].ticketNumber;
	for (i = 0; i < tickets->TICKET_MAX_SIZE; i++) {
		if (highest < tickets->tickets[i].ticketNumber)
			highest = tickets->tickets[i].ticketNumber;
	}
	if (index != 10) {
		printf("New Ticket (Ticket#:0%d)\n", highest + 1);
		tickets->tickets[index].ticketNumber = highest + 1;
		printf("----------------------------------------\n");

		tickets->tickets[index].customerAccountNum = loggedDetail->accountNumber;
		tickets->tickets[index].Status = 1;

		printf("Enter the ticket SUBJECT (30 chars. maximum): ");
		getCString(tickets->tickets[index].subjectLine, 1, 30);
		tickets->tickets[index].counter = 1;
		tickets->tickets[index].mesage[0].accountType = 'C';
		strcpy(tickets->tickets[index].mesage[0].displayName, loggedDetail->name.customerName);
		printf("\n");
		printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
		getCString(tickets->tickets[index].mesage->messageDetail, 1, 150);
		printf("\n*** New ticket created! ***\n");
	}
	printf("\n");
	pauseExecution();
}
void modifyTicket(struct AccountTicketingData* tickets, const struct Account* loggedDetail) {
	int ticketNumber, index;
	printf("\n");
	printf("Enter ticket number: ");
	ticketNumber = getPositiveInteger();
	printf("\n");
	index = findTicketByNum(ticketNumber, tickets->tickets, tickets->TICKET_MAX_SIZE);
	if (tickets->tickets[index].customerAccountNum == loggedDetail->accountNumber) {
		if (tickets->tickets[index].Status == 0)
			printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
		else
			modifyAccount(&tickets->tickets[index], loggedDetail);
	}
	else {
		printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
	}
	pauseExecution();
	printf("\n");
}
void displayoneTicketHeader() {
	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}
void displayoneTicketRecord(const Ticket* ticket) {
	char status[7];
	if (ticket->Status == 1)
		strcpy(status, "ACTIVE");
	else
		strcpy(status, "CLOSED");
	printf("%06d %-6s %-30s %5d\n", ticket->ticketNumber, status,
		ticket->subjectLine, ticket->counter);
}

void displayAllTickets_forAccounts(const AccountTicketingData* data, const struct Account* logged) {
	int i, j, b = 0, ticketNum = 0, goOn = 1;
	char agentAccountType[] = "AGENT";
	char customerAccountType[] = "CUSTOMER";
	do {

		displayoneTicketHeader();
		for (i = 0; i < data->TICKET_MAX_SIZE; i++) {
			if (data->tickets[i].customerAccountNum == logged->accountNumber)
				displayoneTicketRecord(&data->tickets[i]);
		}
		printf("------ ------ ------------------------------ --------\n");
		printf("\nEnter the ticket number to view the messages or\n0 to return to previous menu: ");
		ticketNum = getPositiveInteger();
		int index = findTicketByNum(ticketNum, data->tickets, data->TICKET_MAX_SIZE);

		if (index >= 0 && data->tickets[index].customerAccountNum == logged->accountNumber) {

			printf("\n================================================================================\n");
			printf("%06d (%s) Re: %s\n", ticketNum, data->tickets[index].Status ? "ACTIVE" : "CLOSED", data->tickets[index].subjectLine);
			printf("================================================================================\n");
			for (j = 0; j < data->tickets[index].counter; j++) {
				if (b % 5 == 0 && b != 0) {
					pauseExecution();
					printf("\n");
				}
				if (data->tickets[index].mesage[j].accountType == 'C') {
					printf("%s (%s):\n   %s\n\n", customerAccountType,
						data->tickets[index].mesage[j].displayName, data->tickets[index].mesage[j].messageDetail);
				}
				else {
					printf("%s (%s):\n   %s\n\n", agentAccountType,
						data->tickets[index].mesage[j].displayName, data->tickets[index].mesage[j].messageDetail);
				}
				b++;
			}
			b = 0;
			pauseExecution();
			printf("\n");
			i = 0;
		}
		else if (ticketNum == 0) {
			goOn = 0;
			i = 0;
			break;
		}
		else {
			printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n\n");
			pauseExecution();
			printf("\n");
		}

	} while (goOn);
}
void listMyTicketHeader() {
	printf("\n------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}
void listMyTicket(Ticket* tickets) {
	int i, goOn = 1;
	do {
		listMyTicketHeader();
		int output = -1;
		for (i = 0; i < 17; i++) {

			if (tickets[i].counter == 1) {

				printf("%06d %05d %-15s %-7s%-30s %5d", tickets[i].ticketNumber,
					tickets[i].customerAccountNum, tickets[i].mesage->displayName,
					tickets[i].Status == 1 ? "ACTIVE" : "CLOSED", tickets[i].subjectLine,
					tickets[i].counter);
				printf("\n");

			}
		}
		output = listItems(tickets);
		if (output != 0) {
			goOn = 0;
			break;
		}

	} while (goOn);
}

void listAllTickets(const Ticket* tickets, int status) {
	int i;
	int goOn = 1, output = -1;
	do {
		listMyTicketHeader();
		for (i = 0; i < 17; i++) {
			if (tickets[i].Status == status && tickets[i].ticketNumber != 0) {
				printf("%06d %05d %-15s %-7s%-30s %5d\n", tickets[i].ticketNumber, tickets[i].customerAccountNum, tickets[i].mesage->displayName,
					tickets[i].Status == 1 ? "ACTIVE" : "CLOSED", tickets[i].subjectLine, tickets[i].counter);
			}
		}
		output = listItems(tickets);
		if (output != -1) {
			goOn = 1;
		}
		else goOn = 0;

	} while (goOn);
}
int listItems(const struct Ticket* tickets) {
	int ticketNum, i, j, goOn = 0, b = 0;
	char agentAccountType[] = "AGENT";
	char customerAccountType[] = "CUSTOMER";
	do {
		printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
		ticketNum = getPositiveInteger();
		for (i = 0; i < 17; i++) {
			if (ticketNum == tickets[i].ticketNumber && tickets[i].ticketNumber != 0) {

				printf("\n================================================================================\n");
				printf("%06d (%s) Re: %s\n", ticketNum, tickets[i].Status ? "ACTIVE" : "CLOSED", tickets[i].subjectLine);
				printf("================================================================================\n");

				for (j = 0; j < tickets[i].counter; j++) {
					if (b % 5 == 0 && b != 0) {
						pauseExecution();
						printf("\n");
					}
					if (tickets[i].mesage[j].accountType == 'C') {
						printf("%s (%s):\n   %s\n\n", customerAccountType,
							tickets[i].mesage[j].displayName, tickets[i].mesage[j].messageDetail);
					}
					else {
						printf("%s (%s):\n   %s\n\n", agentAccountType,
							tickets[i].mesage[j].displayName, tickets[i].mesage[j].messageDetail);
					}
					b++;
				}
				pauseExecution();
				break;
			}
			else if (ticketNum == 0) {
				goOn = 0;
				i = -1;
				printf("\n");
				break;
			}
		}
		if (i == 10) {
			printf("\nERROR: Invalid ticket number.\n\n");
			pauseExecution();
		}
	} while (goOn);
	return i;
}
void displayAccountSummaryHeader() {
	printf("\nAcct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

void  displayAccountDetailHeader() {
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* name) {

	char agentAccountType[] = "AGENT";
	char customerAccountType[] = "CUSTOMER";

	if (name->accountType == 'A') {
		printf("%05d %-9s %5d",
			name->accountNumber, agentAccountType,
			name->log.birthYear);
	}
	else {
		printf("%05d %-9s %5d",
			name->accountNumber, customerAccountType,
			name->log.birthYear);

	}
	putchar('\n');
}
void displayAccountDetailRecord(const struct Account* record) {
	char password[50] = { 0 };
	int i;

	for (i = 0; record->name.password[i] != '\0'; i++)
	{
		if (i % 2) {
			password[i] = '*';
		}
		else
			password[i] = record->name.password[i];
	}
	char agentAccountType[] = "AGENT";
	char customerAccountType[] = "CUSTOMER";

	if (record->accountType == 'A') {
		printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s",

			record->accountNumber, agentAccountType,
			record->log.birthYear,
			record->log.houseHoldIncome,
			record->log.country,
			record->name.customerName,
			record->name.userName,
			password);
	}
	else {
		printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s",
			record->accountNumber, customerAccountType,
			record->log.birthYear,
			record->log.houseHoldIncome,
			record->log.country,
			record->name.customerName,
			record->name.userName,
			password);
	}
}

int findAccountIndexByAcctNum(int accountNum, const struct Account account[], int maxSize, int prompt) {
	int i, index = -1;
	if (prompt) {
		printf("Enter your account#: ");
		accountNum = getPositiveInteger();
	}
	for (i = 0; i < maxSize; i++) {
		if (account[i].accountNumber == accountNum) {

			index = i;
			break;
		}
		else index = -1;
	}
	return index;
}

void displayAllAccountSummaryRecords(const struct Account summary[], int maxSize) {
	int i = 0;
	displayAccountSummaryHeader();
	while (i < maxSize) {
		if (summary[i].accountNumber != '\0') {
			displayAccountSummaryRecord(&summary[i]);
		}
		i++;
	}
	printf('\n');
}
void displayAllAccountDetailRecords(const struct Account summary[], int maxSize) {
	int i = 0;
	displayAccountDetailHeader();
	while (i < maxSize) {
		if (summary[i].accountNumber != '\0') {
			displayAccountDetailRecord(&summary[i]);
			putchar('\n');
		}
		i++;
	}
	putchar('\n');
}

void pauseExecution() {
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
}

int checkAccount(const struct Account* user, int size, int* index) {
	int accNum, badReturn_val = 0;
	char line[100];
	printf("\nEnter the account#: ");
	accNum = getPositiveInteger();
	*index = findAccountIndexByAcctNum(accNum, user, size, 0);
	if (*index < 0)
		badReturn_val = 1;
	printf("User Login    : ");
	getCString(line, 1, 99);
	if (*index >= 0)
		if (strcmp(line, user[*index].name.userName))
			badReturn_val = 1;
	printf("Password      : ");
	getCString(line, 1, 99);
	if (*index >= 0)
		if (strcmp(line, user[*index].name.password))
			badReturn_val = 1;

	return badReturn_val;
}

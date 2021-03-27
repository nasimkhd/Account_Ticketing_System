// ===================================================================================
//  Assignment: 2
//  Milestone : 2
// ===================================================================================
//  Student Name  : Nasim Khodapanah
//  Student ID    : 131929200
//  Student Email : nkhodapanah@myseneca.ca
//  Course Section: NGG
// ===================================================================================
#include "ticket.h"
#include "account.h"

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_


typedef struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array
}AccountTicketingData;

void displayAccountSummaryHeader();
void displayAccountSummaryRecord(const struct Account* name);
void displayAccountDetailHeader();
void displayAccountDetailRecord(const struct Account* record);
void applicationStartup(struct AccountTicketingData* account);
int menuLogin(const struct Account accounts[], int arrSize);
void menuAgent(struct AccountTicketingData* agent, const struct Account* loggedDetail);
int findAccountIndexByAcctNum(int accountNum, const struct Account account[], int maxSize, int zeroOrNot);
int checkAccount(const struct Account* user, int size, int* index);
void displayAllAccountSummaryRecords(const struct Account summary[], int maxSize);
void displayAllAccountDetailRecords(const struct Account summary[], int maxSize);
void pauseExecution();
void menuCustomer(struct AccountTicketingData* tickets, const struct Account* loggedDetail);
void displayoneTicketHeader();
void displayoneTicketRecord(const Ticket* ticket);
void displayAllTickets_forAccounts(const AccountTicketingData* data, int accNumber);
void listMyTicketHeader();
void listMyTicket(Ticket* tickets);
void listAllTickets(const Ticket* tickets);

int listItems(const struct Ticket* tickets);

#endif // !ACCOUNT_TICKETING_UI_H_
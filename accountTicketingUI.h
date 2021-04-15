// ===================================================================================
//  Assignment: 2
//  Milestone : 4
// ===================================================================================
//  Student Name  : Nasim Khodapanah
//  Student ID    : 131929200
//  Student Email : nkhodapanah@myseneca.ca
//  Course Section: NGG
// ===================================================================================


#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#include "ticket.h"
#include "account.h"


void   displayAccountSummaryHeader();
void   displayAccountSummaryRecord(const struct Account* name);
void   displayAccountDetailHeader();
void   displayAccountDetailRecord(const struct Account* record);
void   applicationStartup(struct AccountTicketingData* account);
int    menuLogin(const struct Account accounts[], int arrSize);
void   menuAgent(struct AccountTicketingData* agent, const struct Account* loggedDetail);
int    findAccountIndexByAcctNum(int accountNum, const struct Account account[], int maxSize, int prompt);
int    checkAccount(const struct Account* user, int size, int* index);
void   displayAllAccountSummaryRecords(const struct Account summary[], int maxSize);
void   displayAllAccountDetailRecords(const struct Account summary[], int maxSize);
void   pauseExecution();
void   menuCustomer(struct AccountTicketingData* tickets, const struct Account* loggedDetail);
void   displayoneTicketHeader();
void   displayoneTicketRecord(const Ticket* ticket);
void   displayAllTickets_forAccounts(const AccountTicketingData* data, const struct Account* logged);
int    findTicketByNum(int ticketNo, Ticket* tickets, int sizeOfTicketArray);
void   listMyTicketHeader();
void   listMyTicket(Ticket* tickets);
void   listAllTickets(const Ticket* tickets, int status);
int    listItems(const struct Ticket* tickets);


#endif // !ACCOUNT_TICKETING_UI_H_
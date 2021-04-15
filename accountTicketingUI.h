

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#include "ticket.h"
#include "account.h"

//displayRecordswithHeader
void   displayAccountSummaryHeader();
void   displayAccountSummaryRecord(const struct Account* name);
void   displayAccountDetailHeader();
void   displayAccountDetailRecord(const struct Account* record);
void   displayoneTicketHeader();
void   displayoneTicketRecord(const Ticket* ticket);
void   displayAllTickets_forAccounts(const AccountTicketingData* data, const struct Account* logged);
void   displayAllAccountSummaryRecords(const struct Account summary[], int maxSize);
void   displayAllAccountDetailRecords(const struct Account summary[], int maxSize);

//ApplicationStartUp
void   applicationStartup(struct AccountTicketingData* account);

//Menu Agent
int    menuLogin(const struct Account accounts[], int arrSize);
void   viewmenuAgent(const struct Account* loggedDetail);
void   menuAgent(struct AccountTicketingData* agent, const struct Account* loggedDetail);
//cases
void   newAccount(struct AccountTicketingData* agent);
void   modifyAccount(struct AccountTicketingData* agent);
void   removeAccount(struct AccountTicketingData* agent, const struct Account* loggedDetail);


//menu Customer
void   viewmenuCustomer(const struct Account* loggedDetail);
void   menuCustomer(struct AccountTicketingData* tickets, const struct Account* loggedDetail);
//cases
void newTicket(struct AccountTicketingData* tickets, const struct Account* loggedDetail);
void modifyTicket(struct AccountTicketingData* tickets, const struct Account* loggedDetail);


int    findAccountIndexByAcctNum(int accountNum, const struct Account account[], int maxSize, int prompt);
int    checkAccount(const struct Account* user, int size, int* index);

void   pauseExecution();


void   listMyTicketHeader();
void   listMyTicket(Ticket* tickets);
void   listAllTickets(const Ticket* tickets, int status);
int    listItems(const struct Ticket* tickets);


#endif // !ACCOUNT_TICKETING_UI_H_
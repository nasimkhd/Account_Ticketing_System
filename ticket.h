
#ifndef TICKET_H_
#define TICKET_H_

#include "account.h"

typedef struct	Message {
	char accountType;
	char displayName[30];
	char messageDetail[150];

}Message;

typedef struct Ticket {
	int ticketNumber;
	int customerAccountNum;
	int Status;
	char subjectLine[35];
	int counter;
	struct Message mesage[21];
}Ticket;


typedef struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array

}AccountTicketingData;

int    findTicketByNum(int ticketNo, Ticket* tickets, int sizeOfTicketArray);
int    findFreeTicket(Ticket data[], int max_size);

//manage one ticket
void   viewManageTicket(Ticket* ticket);
void   manageOneTicket(Ticket* ticket, const Account* loggedData);

//modify
void   viewModifyAccount(Ticket* ticket);
void   modifyAccountMenu(Ticket* ticket, const Account* loggedData);
//cases
void   closeTicket(Ticket* ticket, const Account* loggedData);
void   getMessage(Ticket* ticket, const Account* loggedData);

int    findFreeMessage(Ticket* data, int max_size, int flag);


int    loadTickets(Ticket ticket[], int TICKET_SIZE);
int    recreateTheTicket(Ticket* ticket, int arrSize);
void   tickets_arc(Ticket* ticket, int arraySize);
void   ViewArchivedTicket(Ticket ticket[], int arrSize);
int    recreateTicket(Ticket* ticket, int arrSize);


#endif // !TICKET_H_
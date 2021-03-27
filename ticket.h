// ===================================================================================
//  Assignment: 2
//  Milestone : 2
// ===================================================================================
//  Student Name  : Nasim Khodapanah
//  Student ID    : 131929200
//  Student Email : nkhodapanah@myseneca.ca
//  Course Section: NGG
// ===================================================================================

#ifndef TICKET_H_
#define TICKET_H_

typedef struct	Message {
	char accountType;
	char displayName[30];
	char messageDetail[150];

}Message;

typedef struct Ticket {
	int ticketNumber;
	int customerAccountNum;
	int Status;
	char subjectLine[30];
	int counter;
	struct Message mesage[21];
}Ticket;



#endif // !TICKET_H_
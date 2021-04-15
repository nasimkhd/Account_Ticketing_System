

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "accountTicketingUI.h"
#include "commonHelpers.h"

//view modify account header
void viewModifyAccount(Ticket* ticket) {
	printf("----------------------------------------\n");
	printf("Ticket %06d - Update Options\n", ticket->ticketNumber);
	printf("----------------------------------------\n");
	printf("Status  : %s\n", (ticket->Status ? "ACTIVE" : "CLOSED"));
	printf("Subject : %s\n", ticket->subjectLine);
	printf("----------------------------------------\n");
	printf("1) Modify the subject\n");
	printf("2) Add a message\n");
	printf("3) Close ticket\n");
	printf("0) Done\n");
	printf("Selection: ");
}

//Modify Account
void modifyAccountMenu(Ticket* ticket, const Account* loggedData) {
	int selection, index, store = 0;
	do {
		viewModifyAccount(ticket);
		selection = getIntFromRange(0, 3);
		switch (selection) {
		case 1:      printf("\nEnter the revised ticket SUBJECT (%d chars. maximum): ", 30);
			         getCString(ticket->subjectLine, 1, 31);
			         printf("\n");
			break;
		case 2:      getMessage(ticket, loggedData);
			         printf("\n");
			break;
		case 3:      closeTicket(ticket, loggedData);
			         selection = !selection;
		    break;
		case 0:      printf("\n");
			break;
		}
	} while (selection);
}

//view Manage One Ticket Header
void viewManageTicket(Ticket* ticket) {
	printf("----------------------------------------\n");
	printf("Ticket 0%d - Update Options\n", ticket->ticketNumber);
	printf("----------------------------------------\n");
	printf("Status  : %s\n", ticket->Status == 1 ? "ACTIVE" : "CLOSED");
	printf("Subject : %s\n", ticket->subjectLine);
	printf("Acct#   : %05d\n", ticket->customerAccountNum);
	printf("Customer: %s\n", ticket->mesage[0].displayName);
	printf("----------------------------------------\n");
	printf("1) Add a message\n");
	printf("2) Close ticket\n");
	printf("3) Re-open ticket\n");
	printf("0) Done\n");
	printf("Selection: ");
}
//manage One Ticket
void manageOneTicket(Ticket* ticket, const Account* loggedData) {
	int selection = 1, index = 0;
	char store;
	do {
		viewManageTicket(ticket);
		selection = getIntFromRange(0, 3);
		switch (selection) {

		case 1:
			       getMessage(ticket, loggedData);
			       printf("\n");
			break;
		case 2:
			if (ticket->Status == 0) {
				printf("\nERROR: Ticket is already closed!\n\n");
			}
			else {
				printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				store = getCharOption("yYnN");
				if (toupper(store) == 'Y') {
					printf("\n");

					if (ticket->counter != 19 && ticket->counter != 20) {
						printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
						store = getCharOption("YN");
						if (toupper(store) == 'Y') {
							getMessage(ticket, loggedData);
							ticket->Status = 0;
							printf("\n*** Ticket closed! ***\n\n");
						}
						else {
							ticket->Status = 0;
							printf("\n*** Ticket closed! ***\n\n");
						}
					}
					if (ticket->counter == 19 || ticket->counter == 20) {
						ticket->Status = 0;
						printf("*** Ticket closed! ***\n\n");
					}
				}
				else {
					printf("\n");
					ticket->Status = 1;
				}
			}
			break;
		case 3: index = findTicketByNum(ticket->ticketNumber, ticket, 20);
			if (ticket[index].Status == 0) {
				printf("\nAre you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				store = getCharOption("YN");
				if (store == 'Y') {
					ticket->Status = 1;
					printf("\n*** Ticket re-opened! ***\n");
				}
				printf("\n");
			}
			else
				printf("\nERROR: Ticket is already active!\n\n");
			break;
		case 0: selection = 0;
			printf("\n");
			break;
		}
	} while (selection);
}
void closeTicket(Ticket* ticket, const Account* loggedData) {
	int index, store = 0;
	index = findFreeMessage(ticket, 20, 1);
	if (ticket->Status == 1) {
		printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
		store = getCharOption("yYnN");
		if (toupper(store) == 'Y') {

			if (index != 20) {
				printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
				store = getCharOption("yYnN");
				if (toupper(store) == 'Y') {
					getMessage(ticket, loggedData);
				}

			}
			printf("\n");
			printf("*** Ticket closed! ***");
			printf("\n\n");
			ticket->Status = 0;
		}
		else printf("Ticket was not closed!\n");
	}
	else printf("\nERROR: Ticket is already closed!\n\n");
}
int findTicketByNum(int ticketNo, Ticket* tickets, int sizeOfTicketArray)
{
	int i = 0;
	int found = 0;
	//int returnValue = -1;
	while (tickets != NULL && 0 == found && i < sizeOfTicketArray)
	{
		if (tickets[i].ticketNumber == ticketNo)
		{
			found = 1;
		}
		else i++;
	}
	//returnValue = (found == 1) ? i : -1;
	return i;
}
int findFreeTicket(Ticket data[], int max_size) {
	int i = 0;
	while (data[i].ticketNumber != 0 && i != max_size) {
		i++;
	}
	if (i >= max_size) {
		printf("ERROR: Ticket listing is FULL, call ITS Support!\n");
		return 10;
	}
	else
		return i;
}

int findFreeMessage(Ticket* data, int max_size, int flag) {
	int i = 0;

	while (data->mesage[i].messageDetail[0] != 0)
		i++;
	if (i > max_size && flag == 0) {
		printf("\nERROR: Message limit has been reached, call ITS Support!\n");
		return -1;
	}
	else {
		if (i > max_size) {
			return -1;
		}
		else
			return i;
	}
}

void getMessage(Ticket* ticket, const Account* loggedData) {
	int index = -1;
	index = findFreeMessage(ticket, 19, 0);
	if (index >= 0 && ticket->Status != 0) {
		printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
		getCString(ticket->mesage[index].messageDetail, 1, 150);
		ticket->counter++;
		ticket->mesage[index].accountType = loggedData->accountType;
		strcpy(ticket->mesage[index].displayName, loggedData->name.customerName);
	}
	if (index != -1 && ticket->Status == 0)
		printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
}

int loadTickets(struct Ticket ticket[], int TICKET_SIZE) {

	int i = 0, b = 0, c = 0, flag = 1;
	char ch[2000];
	char* result = NULL;
	FILE* fp = fopen("tickets.txt", "r");

	if (fp != NULL) {
		while (i < TICKET_SIZE && flag == 1)
		{
			b = 0;
			fscanf(fp, "%d|%d|%d|%[^|]|%d|%[^\n]", &ticket[i].ticketNumber,
				&ticket[i].customerAccountNum, &ticket[i].Status,
				ticket[i].subjectLine, &ticket[i].counter, ch);

			result = strtok(ch, "|");
			while (result != NULL)
			{
				while (result != NULL)
				{
					if (c == 0)
						ticket[i].mesage[b].accountType = result[0];
					if (c == 1)
						strcpy(ticket[i].mesage[b].displayName, result);
					if (c == 2)
						strcpy(ticket[i].mesage[b].messageDetail, result);
					c++;

					if (c == 3 && b < ticket[i].counter)
					{
						c = 0;
						b++;
					}

					result = strtok(NULL, "|");
				}
				fflush(stdin);
			}
			if (ticket[i].ticketNumber != 0)
				i++;
			else
				flag = 0;
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("Failed to open the file accounts_arc.txt for writing\n");

	}
	return i;
}

int recreateTheTicket(Ticket* ticket, int arrSize) {
	int i, j, numTicket = 0;
	FILE* fp;
	fp = fopen("tickets.txt", "w");
	if (fp != NULL) {
		for (i = 0; i < arrSize; i++) {
			if (ticket[i].ticketNumber != 0) {
				fprintf(fp, "%d|%d|%d|%s|%d|", ticket[i].ticketNumber, ticket[i].customerAccountNum,
					ticket[i].Status, ticket[i].subjectLine, ticket[i].counter);
				for (j = 0; j < ticket[i].counter; j++)
					fprintf(fp, "%c|%s|%s|",
						ticket[i].mesage[j].accountType,
						ticket[i].mesage[j].displayName,
						ticket[i].mesage[j].messageDetail);
				fprintf(fp, "\n");
				numTicket++;
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else printf("Failed to open the file\n");
	return numTicket;
}

int recreateTicket(Ticket* ticket, int arrSize) {
	int i, j, numTicket = 0;
	FILE* fp;
	fp = fopen("tickets.txt", "w");
	if (fp != NULL) {
		for (i = 0; i < arrSize; i++) {
			if (ticket[i].ticketNumber != 0) {
				if (ticket[i].Status == 1) {
					fprintf(fp, "%d|%d|%d|%s|%d|", ticket[i].ticketNumber, ticket[i].customerAccountNum,
						ticket[i].Status, ticket[i].subjectLine, ticket[i].counter);
					for (j = 0; j < ticket[i].counter; j++)
						fprintf(fp, "%c|%s|%s|",
							ticket[i].mesage[j].accountType,
							ticket[i].mesage[j].displayName,
							ticket[i].mesage[j].messageDetail);
					fprintf(fp, "\n");
					numTicket++;
				}
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else printf("Failed to open the file\n");
	return numTicket;
}
void tickets_arc(Ticket* ticket, int arraySize) {
	int i, j, count = 0;
	FILE* fp = NULL;
	fp = fopen("tickets_arc.txt", "a");
	if (fp == NULL) {
		printf("ERROR, CANT READ TICKETS_ARC.\n");
		exit(1);
	}
	for (i = 0; i < arraySize; i++) {
		if (ticket[i].ticketNumber != 0) {
			if (ticket[i].Status == 0) {
				count++;
				fprintf(fp, "%d|%d|%d|%s|%d|",
					ticket[i].ticketNumber,
					ticket[i].customerAccountNum,
					ticket[i].Status,
					ticket[i].subjectLine,
					ticket[i].counter);
				for (j = 0; j < ticket[i].counter; j++) {
					fprintf(fp, "%c|%s|%s|",
						ticket[i].mesage[j].accountType,
						ticket[i].mesage[j].displayName,
						ticket[i].mesage[j].messageDetail);
				}
				fprintf(fp, "\n");
				ticket[i].ticketNumber = 0;
			}
		}
	}
	fclose(fp);
	printf("\n*** %d tickets archived ***\n\n", count);
	pauseExecution();
	printf("\n");
}


void ViewArchivedTicket(Ticket ticket[], int arrSize)
{
	FILE* fp;
	fp = fopen("tickets_arc.txt", "r+");
	int i = 0, j, messages = 0;
	char pipe, pipe1, pipe2, pipe3;


	if (fp != NULL)
	{
		while (i < arrSize && fscanf(fp, "%d|%d|%d|%30[^|]%c%d%c",
			&ticket[i].ticketNumber, &ticket[i].customerAccountNum,
			&ticket[i].Status, ticket[i].subjectLine, &pipe,
			&ticket[i].counter, &pipe1) == 7)
		{
			if (pipe != '|' || pipe1 != '|')
			{
				while (fgetc(fp) != '|');
			}
			j = 0;
			while (j < ticket[i].counter &&
				fscanf(fp, "%c|%30[^|]%c%150[^|]%c",
					&ticket[i].mesage[j].accountType,
					ticket[i].mesage[j].displayName, &pipe2,
					ticket[i].mesage[j].messageDetail, &pipe3) == 5)
			{
				if (pipe2 != '|' || pipe3 != '|')
				{
					while (fgetc(fp) != '|');
				}
				j++;
			}

			messages = messages + ticket[i].counter;

			i++;
		}
		fclose(fp);
		fp = NULL;
	}
	if (i == 5)
		printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n\n", i + 1, messages + 4);
	else printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n\n", i, messages);

	pauseExecution();
}
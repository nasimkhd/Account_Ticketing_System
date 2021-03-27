// ===================================================================================
//  Assignment: 2
//  Milestone : 2
// ===================================================================================
//  Student Name  : Nasim Khodapanah
//  Student ID    : 131929200
//  Student Email : nkhodapanah@myseneca.ca
//  Course Section: NGG
// ===================================================================================


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "ticket.h"
#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"

void displayoneTicketHeader() {
    printf("------ ------ ------------------------------ --------\n");
    printf("Ticket Status Subject                        Messages\n");
    printf("------ ------ ------------------------------ --------\n");
}
void displayoneTicketRecord(const Ticket* ticket) {
    char status[7];
    if (ticket->Status == 1)
        strcpy(status, "OPEN");
    else
        strcpy(status, "CLOSED");
    printf("%06d %-6s %-30s %5d\n", ticket->ticketNumber, status,
        ticket->subjectLine, ticket->counter);
}
void displayAllTickets_forAccounts(const AccountTicketingData* data, int accNumber) {
    int i,j, ticketNum, goOn = 1;;
    char status[7];
    char agentAccountType[] = "AGENT";
    char customerAccountType[] = "CUSTOMER";
    do {
        
        displayoneTicketHeader();
        for (i = 0; i < data->ACCOUNT_MAX_SIZE; i++) {
            if (data->tickets[i].customerAccountNum == accNumber)
                displayoneTicketRecord(&data->tickets[i]);
        }
        printf("------ ------ ------------------------------ --------\n");
        printf("\nEnter the ticket number to view the messages or\n0 to return to previous menu: ");
        ticketNum = getPositiveInteger();
        for (i = 0; i < 5; i++) {
            
            if (ticketNum == data->tickets[i].ticketNumber) {
                if (data->tickets[i].Status == 1)
                    strcpy(status, "OPEN");
                else
                    strcpy(status, "CLOSED");
                printf("\n================================================================================\n");
                printf("%06d (%s) Re: %s\n", ticketNum, status, data->tickets[i].subjectLine);
                printf("================================================================================\n");
                for (j = 0; j < data->tickets[i].counter; j++) {
                    if (data->tickets[i].mesage[j].accountType == 'C') {
                        printf("%s (%s):\n   %s\n\n", customerAccountType,
                            data->tickets[i].mesage[j].displayName, data->tickets[i].mesage[j].messageDetail);
                    }
                    else {
                        printf("%s (%s):\n   %s\n\n", agentAccountType,
                            data->tickets[i].mesage[j].displayName, data->tickets[i].mesage[j].messageDetail);
                    }
                }
                pauseExecution();
                printf("\n");
                i = 0;
                break;
            }
            else if (ticketNum == 0) {
                goOn = 0;
                i = 0;
                break;
            }
        }
        if (i == 5) {
            printf("\nERROR: Invalid ticket number.\n\n");
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
    char status[7];
    int i, goOn = 1;
    do {
        if (tickets->Status == 1)
            strcpy(status, "OPEN");
        else
            strcpy(status, "CLOSED");
        int output = -1;
        for (i = 0; i < 10; i++) {
            
            if (tickets[i].counter == 1) {
                listMyTicketHeader();
                printf("%06d %05d %-15s %-7s%-30s %5d", tickets[i].ticketNumber, tickets[i].customerAccountNum, tickets[i].mesage->displayName,
                    status, tickets[i].subjectLine, tickets[i].counter);
                printf("\n");
                output = listItems(tickets);
                if (output == 0)
                    break;
                else i = 0;
                }
        }
        goOn = 0;
    } while (goOn);
}

void listAllTickets(const Ticket *tickets) {
    int i;
    char status[7];
    int goOn = 1, output = -1;
    do {
        if (tickets->Status == 1)
            strcpy(status, "OPEN");
        
        listMyTicketHeader();
        for (i = 0; tickets[i].ticketNumber != 0; i++) {
            if (tickets[i].Status == 1) {
                printf("%06d %05d %-15s %-7s%-30s %5d\n", tickets[i].ticketNumber, tickets[i].customerAccountNum, tickets[i].mesage->displayName,
                    status, tickets[i].subjectLine, tickets[i].counter);
            }
        }
        output = listItems(tickets);
        if (output == 0)
            break;
        else i = 0;
    } while (goOn);
}
int listItems(const struct Ticket* tickets) {
    int ticketNum, i,j, goOn = 0;
    char status[7];
    char agentAccountType[] = "AGENT";
    char customerAccountType[] = "CUSTOMER";
    do {
        printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
        printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
        ticketNum = getPositiveInteger();
        for (i = 0; i < 5; i++) {
            if (ticketNum == tickets[i].ticketNumber) {
                if (tickets[i].Status == 1)
                    strcpy(status, "OPEN");
                else
                    strcpy(status, "CLOSED");
                printf("\n================================================================================\n");
                printf("%06d (%s) Re: %s\n", ticketNum, status, tickets[i].subjectLine);
                printf("================================================================================\n");

                for (j = 0; j < tickets[i].counter; j++) {
                    if (tickets[i].mesage[j].accountType == 'C') {
                        printf("%s (%s):\n   %s\n\n", customerAccountType,
                            tickets[i].mesage[j].displayName, tickets[i].mesage[j].messageDetail);
                    }
                    else {
                        printf("%s (%s):\n   %s\n\n", agentAccountType,
                            tickets[i].mesage[j].displayName, tickets[i].mesage[j].messageDetail);
                    }
                }
                pauseExecution();
                break;
            }
            else if (ticketNum == 0) {
                goOn = 0;
                i = 0;
                printf("\n");
                break;
            }
        }
        if (i == 5) {
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
void menuCustomer(struct AccountTicketingData* tickets, const struct Account* loggedDetail) {
    int account;
    do {
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
        account = getIntFromRange(0, 5);
        switch (account) {
        case 1:
            printf("\n");
            displayAccountDetailHeader();
            displayAccountDetailRecord(loggedDetail);
            printf("\n\n");
            pauseExecution();
            break;
        case 2: printf("Feature #2 currently unavailable!\n");
            pauseExecution();
            printf("\n");
            break;
        case 3: printf("Feature #3 currently unavailable!\n");
            pauseExecution();
            printf("\n");
            break;
        case 4:
            printf("\n");
            displayAllTickets_forAccounts(tickets, loggedDetail->accountNumber);
            break;
        case 0: printf("\n### LOGGED OUT ###\n");
            break;
        }
    } while (account);
}
int menuLogin(const struct Account accounts[], int arrSize)
{
    int attempts = 0, index, done = 0;
    char store ;
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
            if (toupper(store) == 'Y' ) {
                printf("\n");
                done = 1;
                index = -1;
            }
            break;
        case 1:
            while (checkAccount(accounts, arrSize, &index) && attempts < 2) {
                attempts++;
                printf("INVALID user login/password combination! [attempts remaining:%d]\n" , 3-attempts);
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


void menuAgent(struct AccountTicketingData* agent, const struct Account* loggedDetail) {
    int index, account;
    char acc;
    do {
        printf("AGENT: %s (%d)\n", loggedDetail->name.customerName, loggedDetail->accountNumber);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf("1) Add a new account\n");
        printf("2) Modify an existing account\n");
        printf("3) Remove an account\n");
        printf("4) List accounts: summary view\n");
        printf("5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf("6) List new tickets\n");
        printf("7) List active tickets\n");
        printf("8) Manage a ticket\n");
        printf("9) Archive closed tickets\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\nSelection: ");
        account = getIntFromRange(0, 9);
        switch (account) {
        case 1:
            index = findAccountIndexByAcctNum(0, agent->accounts, agent->ACCOUNT_MAX_SIZE, 0);
            int i = 0, highest = agent->accounts[i].accountNumber;
            for (i = 0; i < agent->ACCOUNT_MAX_SIZE; i++) {
                if (highest < agent->accounts[i].accountNumber)
                    highest = agent->accounts[i].accountNumber;
            }
            if (index < 0) {
                printf("ERROR: Account listing is FULL, call ITS Support!\n");
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
            break;
        case 2:
            printf("\nEnter the account#: ");
            account = getPositiveInteger();
            index = findAccountIndexByAcctNum(account, agent->accounts, agent->ACCOUNT_MAX_SIZE, 0);
            if (index < 0) {
                printf("ERROR: Access Denied.\n");
                pauseExecution();
                printf("\n");
            }
            else {
                updateAccount(&agent->accounts[index]);
            }
            break;
        case 3:  printf("\nEnter the account#: ");
            account = getPositiveInteger();
            index = findAccountIndexByAcctNum(account, agent->accounts, agent->ACCOUNT_MAX_SIZE, 0);

            if (index > 0 && agent->accounts[index].accountNumber == loggedDetail->accountNumber)
            {
                printf("\nERROR: You can't remove your own account!\n\n");
                pauseExecution();
                printf("\n");
                break;
            }
            else if (index > -1)
            {
                displayAccountDetailHeader();
                displayAccountDetailRecord(&agent->accounts[index]);
                printf("\n\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
                acc = getCharOption("YN");
                if (acc == 'Y')
                {
                    agent->accounts[index].accountNumber = 0;
                    printf("\n*** Account Removed! ***\n\n");
                    pauseExecution();
                    printf("\n");
                }
                else
                {
                    printf("\n*** No changes made! ***\n\n");
                    pauseExecution();
                    printf("\n");
                }
            }
            else
            {
                printf("\nERROR:  Access Denied.\n\n");
                pauseExecution();
            }
            break;
        case 4: displayAllAccountSummaryRecords(agent->accounts, agent->ACCOUNT_MAX_SIZE);
            pauseExecution();
            printf("\n");
            break;
        case 5: printf("\n");
            displayAllAccountDetailRecords(agent->accounts, agent->ACCOUNT_MAX_SIZE);
            pauseExecution();
            printf("\n");
            break;
        case 6:
            listMyTicket(agent->tickets);
            break;
        case 7:
            listAllTickets(agent->tickets);
            break;
        case 8: printf("Feature #8 currently unavailable!");
            pauseExecution();
            break;
        case 9: printf("Feature #9 currently unavailable!");
            pauseExecution();
            break;
        case 0: printf("\n### LOGGED OUT ###\n");
            printf("\n");
            break;
        }
    } while (account);
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
    putchar('\n');
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

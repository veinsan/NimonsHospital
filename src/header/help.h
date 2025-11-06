#ifndef HELP_H
#define HELP_H

#include "data.h"
#include "user-management.h"

void help();
void tampilkanMenuHelp(const char *role);
FiturHelp* createLinkedList(const char *features[], int featureCount);
void displayLinkedList(FiturHelp *head);
void deleteLinkedList(FiturHelp *head);

#endif
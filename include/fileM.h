
// Group Name Date Username Password
#ifndef PASSWORDMANAGER_FILEM_H
#define PASSWORDMANAGER_FILEM_H
#include <stdio.h>
#include "types.h"

int write_entry(char filename[], FileEntry entry);
int show_entry_by_name(char filename[], char p_name[], FileEntry *entry);
int show_entry_by_group(char filename[], char p_group[], FileEntry *arr, int *len);

#endif //PASSWORDMANAGER_FILEM_H

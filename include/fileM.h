
// Group Name Date Username Password
#ifndef PASSWORDMANAGER_FILEM_H
#define PASSWORDMANAGER_FILEM_H

#include <stdio.h>
#include <stdint.h>
#include <stdint.h>

#include "types.h"

int write_entry(char filename[], FileEntry entry);
int show_entry_by_name(char filename[], char p_name[], FileEntry *entry);
FileEntry *show_entry_by_group(char filename[], char p_group[], int *len);
int change_group(char filename[], char groupName[], char newGroupName[], uint8_t del);

#endif //PASSWORDMANAGER_FILEM_H

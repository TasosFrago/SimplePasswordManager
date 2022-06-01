
// Group Name Date Username Password
#ifndef PASSWORDMANAGER_FILEM_H
#define PASSWORDMANAGER_FILEM_H
#include <stdio.h>
#include "types.h"

int write_entry(char filename[], FileEntry entry);

FileEntry *show_entry_by_name(char filename[], char p_name[]);

#endif //PASSWORDMANAGER_FILEM_H

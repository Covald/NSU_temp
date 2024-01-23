//
// Created by covald on 23.01.24.
//

#ifndef STRUCTURE_PROGRAMMING_PROJECT_AUTH_USER_H
#define STRUCTURE_PROGRAMMING_PROJECT_AUTH_USER_H

#endif //STRUCTURE_PROGRAMMING_PROJECT_AUTH_USER_H

#include "dynamic_string.h"
#include "hash.h"
#include "settings.h"
typedef struct User {
    char *login;
    char *password_hash;
} User;

User *user_create(char *login, char *hash);

User *user_create_by_cli();

void user_change_password(User *user);

int user_comparison(User *user1, User *user2);

void user_print(User *user);

void user_free(User *user);
//
// Created by covald on 23.01.24.
//

#include "user.h"

User *user_create(char *login, char *hash) {
    User *new_user = malloc(sizeof(User));
    new_user->login = login;
    new_user->password_hash = hash;
    return new_user;
}

User *user_create_by_cli() {
    system(cls);
    printf("Enter login: ");
    char *login = read_string();
    printf("Enter password: ");
    char *password = read_string();
    char *hash = NULL;
    hash_md5(password, hash);
    free(password);
    return user_create(login, hash);
}

void user_change_password(User *user) {
    system(cls);
    printf("Enter new password: ");
    char *password = read_string();
    char *hash = malloc(sizeof(char)*33);
    hash_md5(password, hash);
    free(password);
    free(user->password_hash);
    user->password_hash = hash;
}

int user_comparison(User *user1, User *user2) {
    /* Function for compare users by login
     * Returns:
     * * -1 if user1 < user2
     * * 0 if users are equal
     * * 1 if user1 > user2
     * */
    int login_comparison = strcmp(user1->login, user2->login);
    if (login_comparison > 0) { return 1; }
    else if (login_comparison < 0) { return -1; }
    return 0;
}

void user_print(User *user) {
    printf("Login: %s\n", user->login);
}

void user_free(User *user) {
    free(user->login);
    free(user->password_hash);
    free(user);
}
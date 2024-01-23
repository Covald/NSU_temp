//
// Created by covald on 23.01.24.
//
#include "menu.h"

void print_break() {
    printf("------------------------------------------------------------------------------------------------\n");
}

void print_incorrect_choice() {
    printf("You enter the incorrect choice.\n");
    print_break();
}

int confirm_choice(char *text) {
    int flag = 0;
    while (1) {
        system(cls);
        print_break();
        printf("Do you really want to '%s'?\n", text);
        print_break();
        if (flag) { print_incorrect_choice(); }
        printf("1. Yes.\n");
        printf("2. No.\n");
        printf("Enter your choice: ");
        int choice;
        get_choice(&choice);
        switch (choice) {
            case 1:
                return 1;
            case 2:
                return 0;
            default:
                flag = 1;
        }
    }
}

void user_main_menu(AVL *avl, User *user) {
    int incorrect_choice = 0;
    while (1) {
        print_break();
        system(cls);
        printf("User - %s\n", user->login);
        print_break();
        if (incorrect_choice) { print_incorrect_choice(); }
        printf("Menu:\n");
        printf("0. Logout.\n");
        printf("1. Change password.\n");
        printf("2. Delete me.\n");
        printf("Enter your choice: ");
        int choice;
        get_choice(&choice);
        switch (choice) {
            case 0:
                return;
            case 1:
                user_change_password(user);
                continue;
            case 2:
                if (confirm_choice("detele your account")) {
                    avl_delete(avl, user);
                    return;
                } else { continue; }
            default:
                incorrect_choice = 1;
                continue;
        }
    }
}

void sign_in(AVL *avl) {
    int is_password_correct = 1;
    int is_user_exist = 1;
    char *login;
    while (1) {
        system(cls);
        print_break();
        printf("SIGN IN.\n");
        printf("At any stage, type 'exit' to exit to the main menu.\n");
        print_break();
        if (!is_user_exist) {
            printf("User '%s' isn't exists.\n", login);
            print_break();
        }
        if (!is_password_correct) {
            printf("Incorrect password\n");
            print_break();
        }
        printf("Enter nickname: ");
        login = read_string();
        if (strcmp(login, "exit") == 0) { break; }
        Node *node = avl_search(avl, login);
        if (node == NULL) {
            is_user_exist = 0;
            is_password_correct = 1;
            continue;
        }
        printf("Enter password: ");
        char *password = read_string();
        if (strcmp(password, "exit") == 0) { break; }
        char *hash = malloc(sizeof(char)*33);
        hash_md5(password, hash);
        free(password);
        if (strcmp(hash, node->user->password_hash) == 0) {
            user_main_menu(avl, node->user);
            break;
        } else {
            is_user_exist = 1;
            is_password_correct = 0;
            continue;
        }
    }
}

void sign_up(AVL *avl) {
    int is_user_exist = 0;
    char *login;
    while (1) {
        system(cls);
        print_break();
        printf("SIGN UP\n");
        printf("At any stage, type 'exit' for go back to the main menu.\n");
        print_break();
        if (is_user_exist) {
            printf("User '%s' already exists.\n", login);
            print_break();
        }
        printf("Enter nickname: ");
        login = read_string();
        if (strcmp(login, "exit") == 0) { return; }
        Node *temp = avl_search(avl, login);
        if (temp) {
            is_user_exist = 1;
            continue;
        } else { break; }
    }
    printf("Enter password: ");
    char *password = read_string();
    if (strcmp(password, "exit") == 0) { return; }
    char *hash = malloc(sizeof(char)*33);
    hash_md5(password, hash);
    free(password);
    User *user = user_create(login, hash);
    avl_insert(avl, user);
    user_main_menu(avl, user);
}

void show_list_of_users(AVL *avl) {
    int is_incorrect_choice = 0;
    while (1) {
        system(cls);
        print_break();
        printf("List of users.\n");
        print_break();
        avl_print_users(avl);
        print_break();
        if (is_incorrect_choice) { print_incorrect_choice(); }
        printf("Menu:\n");
        printf("0. Go back.\n");
        printf("Enter your choice: ");
        int choice;
        get_choice(&choice);
        switch (choice) {
            case 0:
                return;
            default:
                is_incorrect_choice = 1;
                continue;
        }
    }
}

void main_menu(AVL *avl) {

    int flag = 0;
    while (1) {
        system(cls);
        print_break();
        printf("Welcome to the admin panel of our new SuperMegaGigaAuthSystem\n");
        print_break();
        if (flag) { print_incorrect_choice(); }
        printf("Menu:\n");
        printf("0. Exit.\n");
        printf("1. Sign in.\n");
        printf("2. Sign up.\n");
        printf("3. Show list of users.\n");
        printf("Enter your choice: ");
        int choice;
        get_choice(&choice);
        switch (choice) {
            case 0:
                exit(1);
                break;
            case 1:
                sign_in(avl);
                flag = 0;
                continue;
            case 2:
                sign_up(avl);
                flag = 0;
                continue;
            case 3:
                show_list_of_users(avl);
                flag = 0;
                continue;
            default:
                flag = 1;
                continue;
        }
    }
}
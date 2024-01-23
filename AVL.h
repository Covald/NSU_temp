//
// Created by covald on 23.01.24.
//

#ifndef STRUCTURE_PROGRAMMING_PROJECT_AUTH_BST_H
#define STRUCTURE_PROGRAMMING_PROJECT_AUTH_BST_H

#endif //STRUCTURE_PROGRAMMING_PROJECT_AUTH_BST_H

#include "user.h"

typedef struct Node {
    User *user;
    struct Node *left;
    struct Node *right;
    int height;

} Node;

typedef struct AVL {
    Node *root;
} AVL;

AVL *avl_create();

Node *avl_insert(AVL *avl, User* user);

Node *avl_delete(AVL *avl, User* user);

Node *avl_search(AVL *avl, char *login);

void avl_inorder(AVL *avl, void (*foreach_func)(Node *node));

void avl_print_users(AVL *avl);

void avl_free(AVL *avl);


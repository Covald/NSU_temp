//
// Created by covald on 23.01.24.
//

#include "AVL.h"

int balance_factor(Node *root) {
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->height;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->height;
    return lh - rh;
}

int height(Node *root) {
    int lh, rh;
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->height;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->height;

    if (lh > rh)
        return (lh);
    return (rh);
}

Node *node_rotate_left(Node *root) {
    Node *right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;

    // update the heights of the nodes
    root->height = height(root);
    right_child->height = height(right_child);

    // return the new node after rotation
    return right_child;
}

Node *node_rotate_right(Node *root) {
    Node *left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    // update the heights of the nodes
    root->height = height(root);
    left_child->height = height(left_child);

    // return the new node after rotation
    return left_child;
}

Node *node_create(User *user) {
    Node *new_node = (Node *) malloc(sizeof(Node));

    // if a memory error has occurred
    if (new_node == NULL) {
        printf("\nMemory can't be allocated\n");
        return NULL;
    }
    new_node->user = user;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 0;
    return new_node;
}

Node *node_insert(Node *root, User *user) {
    if (root == NULL) {
        Node *new_node = node_create(user);
        if (new_node == NULL) {
            return NULL;
        }
        return new_node;
    } else {
        //strcmp return >0 if s1>s2 and <0 if s1<s2
        int login_comparison = strcmp(user->login, root->user->login);
        if (login_comparison > 0) {
            // insert the new node to the right
            root->right = node_insert(root->right, user);
            // tree is unbalanced, then rotate it
            if (balance_factor(root) == -2) {
                login_comparison = strcmp(user->login, root->right->user->login);
                if (login_comparison > 0) {
                    root = node_rotate_left(root);
                } else {
                    root->right = node_rotate_right(root->right);
                    root = node_rotate_left(root);
                }
            }
        } else if (login_comparison < 0) {
            // insert the new node to the left
            root->left = node_insert(root->left, user);

            // tree is unbalanced, then rotate it
            if (balance_factor(root) == 2) {
                login_comparison = strcmp(user->login, root->left->user->login);
                if (login_comparison < 0) {
                    root = node_rotate_right(root);
                } else {
                    root->left = node_rotate_left(root->left);
                    root = node_rotate_right(root);
                }
            }
        }
    }
    // update the heights of the nodes
    root->height = height(root);
    return root;
}

Node *node_delete(Node *root, User *user) {
    Node *temp = NULL;

    if (root == NULL) {
        return NULL;
    }

    int login_comparison = strcmp(user->login, root->user->login);

    if (login_comparison > 0) {
        root->right = node_delete(root->right, user);
        if (balance_factor(root) == 2) {
            if (balance_factor(root->left) >= 0) {
                root = node_rotate_right(root);
            } else {
                root->left = node_rotate_left(root->left);
                root = node_rotate_right(root);
            }
        }
    } else if (login_comparison < 0) {
        root->left = node_delete(root->left, user);
        if (balance_factor(root) == -2) {
            if (balance_factor(root->right) <= 0) {
                root = node_rotate_left(root);
            } else {
                root->right = node_rotate_right(root->right);
                root = node_rotate_left(root);
            }
        }
    } else {
        if (root->left == NULL && root->right == NULL) {
            user_free(root->user);
            free(root);
            return NULL;
        }

        if (root->left == NULL) { return root->right; }
        if (root->right == NULL) { return root->left; }

        temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        user_free(root->user);
        root->user = temp->user;

        root->right = node_delete(root->right, temp->user);

        if (balance_factor(root) == 2) {
            if (balance_factor(root->left) >= 0) {
                root = node_rotate_right(root);
            } else {
                root->left = node_rotate_left(root->left);
                root = node_rotate_right(root);
            }
        }
    }
    root->height = height(root);
    return root;
}

Node *node_search(Node *root, char *login) {
    if (root == NULL) {
        return NULL;
    }

    int login_comparison = strcmp(login, root->user->login);

    if (login_comparison == 0) {
        return root;
    }

    if (login_comparison > 0) {
        return node_search(root->right, login);
    } else {
        return node_search(root->left, login);
    }
}

void node_inorder(Node *root, void (*foreach_func)(Node *node)) {
    if (root == NULL) { return; }
    node_inorder(root->left, foreach_func);
    foreach_func(root);
    node_inorder(root->right, foreach_func);
}

void node_preorder(Node *root, void (*foreach_func)(Node *node)) {
    if (root == NULL) { return; }
    foreach_func(root);
    node_inorder(root->left, foreach_func);
    node_inorder(root->right, foreach_func);
}

void node_postorder(Node *root, void (*foreach_func)(Node *node)) {
    if (root == NULL) { return; }
    node_inorder(root->left, foreach_func);
    node_inorder(root->right, foreach_func);
    foreach_func(root);
}

void node_free(Node *root) {
    if (root == NULL) { return; }
    node_free(root->left);
    node_free(root->right);
    user_free(root->user);
    free(root);
}

AVL *avl_create() {
    AVL *new_avl = malloc(sizeof(AVL));
    new_avl->root = NULL;
    return new_avl;
}

Node *avl_insert(AVL *avl, User *user) {
    avl->root = node_insert(avl->root, user);
    return avl->root;
}

Node *avl_delete(AVL *avl, User *user) {
    avl->root = node_delete(avl->root, user);
    return avl->root;
}

Node *avl_search(AVL *avl, char *login) { return node_search(avl->root, login); }

void avl_inorder(AVL *avl, void (*foreach_func)(Node *node)) { node_inorder(avl->root, foreach_func); }

void avl_preorder(AVL *avl, void (*foreach_func)(Node *node)) { node_preorder(avl->root, foreach_func); }

void avl_postorder(AVL *avl, void (*foreach_func)(Node *node)) { node_postorder(avl->root, foreach_func); }

void node_print(Node *node) { user_print(node->user); }

void avl_print_users(AVL *avl) {
//    avl_inorder(avl, node_print);
//    printf("\n");
    avl_preorder(avl, node_print);
//    printf("\n");
//    avl_postorder(avl, node_print);
}

void avl_free(AVL *avl) {
    node_free(avl->root);
    free(avl);
}

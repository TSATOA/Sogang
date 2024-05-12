#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "varlist.h"

// TODO: Fill in
VarNode* make_varlist(char *var, int val, VarNode *next) {
    VarNode* node = (VarNode*)malloc(sizeof(VarNode));
    node->var = var;
    node->val = val;
    node->next = next;
    return node;
}

// TODO: Fill in
int lookup_var(VarNode *head, char *var) {
    VarNode* cur = head;
    while(cur != NULL){
        if(strcmp(cur->var,var)==0){
            return cur->val;
        }
        cur = cur->next;
    }
    return -1;
} 

// TODO: Fill in
void free_varlist(VarNode *head) {
    while(head!=NULL){
        VarNode* rm = head;
        head = head->next;
        if(rm->var!=NULL){
            free(rm->var);
        }
        free(rm);
    }
}

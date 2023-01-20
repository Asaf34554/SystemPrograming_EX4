#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "edges.h"
#include <string.h>

pnode create_node(int index){
    pnode nhead = (pnode)malloc(sizeof(node));
    memset(nhead,0,sizeof(node));
    nhead->node_num = index;
    nhead->dist  =__INT_MAX__;
    nhead->didvisit = 0;
    nhead->next=NULL;
    return nhead;
}
pnode get_node(pnode *head, int ver){
    pnode nget = (*head);
    while(nget)
    {
        if(nget->node_num == ver){
            return nget;
        }
        if(!(nget->next)){
            break;
        }
        nget=nget->next;
        
    }
    return nget->next;
}
void del_all_ver(pnode* head){
    pnode run = (*head);
    while (run)
    {
        del_edges(run);
        pnode temp = run->next;
        free(run);
        run=temp;
    }
}
void del_ver(pnode ver,pnode* head){
    pnode run = (*head);
    while(run != NULL){     //runs over the linked list and delet all edges to vertex we want do delete
        if(run == ver){
            run = run->next;
        }
        else{
            del_edge(run,ver);
            run=run->next;
            }
    }
    run = (*head);
    if((*head) == ver){
        (*head) = ver->next;
        del_edges(ver);
        free(ver);
        return;
    }
    while(run->next != ver){
        run = run->next;
    }
    run->next = ver->next;
    del_edges(ver);
    free(ver);
    return;
    

}



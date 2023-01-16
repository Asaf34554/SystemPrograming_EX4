#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "edges.h"

pnode create_node(int index){
    pnode nhead = (pnode)calloc(0,sizeof(node));
    nhead->node_num = index;
    return nhead;
}
pnode get_node(pnode head, int ver){
    pnode nget = head;
    while(nget->node_num!=ver)
    {
        nget = nget->next;
        if(!nget){
            return NULL;
        }
    }
    return nget;
}
void del_all_ver(pnode* head){
    pnode run = (*head);
    while (!run)
    {
        del_edges(run);
        pnode temp = run->next;
        free(run);
        run= temp;
    }
}
void del_ver(pnode ver,pnode* head){
    pnode *phead = head;
    pnode run = (*phead);
    while(run != NULL){
        if(run == ver){
            run = run->next;
        }
        else{
            del_edge(run,ver);
            run=run->next;
            }
    }
    run = (*phead);
    if((*head) == ver){
        head = &(ver->next);
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
    

}



#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include "node.h"
#include <string.h>


pedge create_edge(){
    pedge newedge = (pedge)malloc(sizeof(edge));
    memset(newedge,0,sizeof(edge));
    return newedge;
}
char create_edges(pnode *vertex, pnode* head){
    char c[10] = "\0";
    int d=0;
    pedge* temp=&((*vertex)->edges);
    pedge runner;
    while(1){
        scanf(" %s",c);
        if(c[0] == 'n' || c[0] == 'D' || c[0] == 'A' || c[0] == 'S'  ||c[0] == 'B'   || c[0] == 'T' || c[0] == 'Y' || c[0] == 'P' ){
            return c[0];
        }
        int x=0;
        for(int i=0;i<strlen(c);i++){
            x=x*10+(c[i]-48);
        }

        pnode nextnode = get_node(head,x);
        scanf(" %d",&d);
        if((*temp)==NULL){
            (*temp)=create_edge();
            (*temp)->weight=d;
            (*temp)->endpoint=nextnode;
        }
        else{
            pedge* runner2 = temp;
            while((*temp)!=NULL)
            {
                runner = (*temp);
                runner2 = &runner;
                temp=&(runner->next);
            }
            (*runner2)->next = create_edge();
            (*runner2)->next->endpoint=nextnode;
            (*runner2)->next->weight=d;
            temp = runner2;
        }
        
    }
    
}
void del_edges(pnode vertex){
    pedge* main = &(vertex->edges);
    while((*main)){
        pedge temp =(*main)->next;
        free((*main));
        (*main) = temp;
    }

}
void del_edge(pnode ver,pnode endp){
    pedge ehead = ver->edges;
    if(!ehead){
        return;
    }
    if(ehead->endpoint== endp){
        ver->edges = ehead->next;
        free(ehead);
        return;
    }
    pedge prev;
    while (ehead->endpoint != endp){
        if(ehead->next == NULL ){
            return;
        }
        prev = ehead;
        ehead = ehead->next;     
    }
    if(ehead->next == NULL){
        free(ehead);
        prev->next=NULL;
    
    }
    else{
        prev->next = ehead->next;
        free(ehead);
    }
    return;
}

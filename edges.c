#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include "node.h"


pedge create_edge(){
    pedge newedge = (pedge)calloc(0,sizeof(edge));
    return newedge;
}
char create_edges(pnode vertex, pnode head){
    char* c;
    int d=0;
    pnode nextnode;

    while(1){
        pedge temp = vertex->edges;
        scanf(" %s",c);
        if(c[0]>'A'&& c[0]<'z'){
            return c[0];
        }
        int x=0;
        for(int i=0;i<strlen(c);i++){
            x=x*10+(c[i]-48);
        }
        nextnode = get_node(head,x);
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        if(!temp){
            temp=create_edge();
        }
        else{
            temp->next = create_edge();
            temp = temp->next;
        }
        scanf(" %d",&d);
        temp->weight=d;
        temp->endpoint = nextnode;
    }
    
}

void del_edges(pnode vertex){
    pedge main = vertex->edges;
    while(main != NULL){
        pedge temp = main->next;
        free(main);
        main = temp;
    }

}

void del_edge(pnode ver,pnode endp){
    pedge ehead = ver->edges;
    if(ehead->endpoint== endp){
        ver->edges = ehead->next;
        free(ehead);
        return;
    }
    while (ehead->next->endpoint != endp){
        if(ehead->next == NULL ){
            return;
        }
        ehead = ehead->next;     
    }
   
    if(ehead->next->next== NULL){
        free(ehead->next);
    
    }
    else{
        pedge del = ehead->next;
        ehead->next = del->next;
        free(del);
    }
    return;
}


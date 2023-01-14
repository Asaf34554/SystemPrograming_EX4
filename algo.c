#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include "node.c"
#include "edges.h"

char build_graph_cmd(pnode *head){
    pnode *nhead = head;
    //pnode temp = &nhead;
    int x,n,i=0;
    char* c;
    printf("Please enter the number of vertices: ");
    scanf(" %d",&n);
    pnode temp = create_node(i);   
    (*nhead) = temp;
    for(i=1;i<n;i++){
        pnode temp1 = create_node(i);
        temp->next=temp1;
        temp=temp1;
    }
   // nhead=&head;
    pnode v;
    scanf(" %s",c);
    while(c[0] != 'D' && c[0] != 'A' && c[0] != 'S' && c[0] != 'B' && c[0] != 'T'){
        if(strcmp(c,"n")==0){
          scanf(" %s",c);
          x=0;
          if(c[0]<='9' && c[0] >= '0')
            for(int i=0;i<strlen(c);i++){
                x=x*10+(c[i]-48);
                }
            v = get_node((*head),x);
            char ch = create_edges(v,head);
            strcpy(c,ch);
        }
    }
    return c;
}

char insert_node_cmd(pnode *head){
    int d;
    pnode nHead = *head;
    scanf(" %d",&d);
    pnode vertex = get_node(nHead,d);
    if(vertex==-1){
        vertex = create_node(d);
        while(nHead->next != NULL){
            nHead = nHead->next;
        }
        nHead->next=vertex;
        return create_edges(vertex,&head);
    }
    else{
        del_edges(vertex);
        return create_edges(vertex,&head);
    }
}

void delete_node_cmd(pnode *head){
    int d;
    scanf(" %d",&d);
    pnode ver = get_node((*head),d);
    if(!ver){
        return;
    }
    del_ver(ver,head);    
    
}


void shortsPath_cmd(pnode head){
    int src,dest,min=INF;
    scanf(" %d",src);
    scanf(" %d",dest);
    pnode nsrc = get_node(head,src);
    pedge run = nsrc->edges;
    if(!(run)){
        printf("Dijsktra shortest path: %d",-1);
        return;
    }
    pnode ndst = get_node(head,dest);
    while(run){
        int tmin=__INT_MAX__;
        if(run->endpoint == ndst){
            if(min>run->weight){
                min=run->weight;
            }
            run=run->next;
        }
        else{
            while(run->endpoint->edges){
                if(run->endpoint->edges->endpoint == ndst){

                }
            }
            
        }


    }


}








#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "edges.h"

char build_graph_cmd(pnode *head){
    pnode *nhead = head;
    //pnode temp = &nhead;
    int x,n,i=0;
    char c[10] = "\0";
    printf("Please enter the number of vertices: \n");
    scanf(" %d",&n);
    pnode temp = create_node(i);
    (*nhead) = temp;
    for(i=1;i<n;i++){
        printf(" %d\n",temp->node_num);
        pnode temp1 = create_node(i);
        temp->next=temp1;
        temp=temp1;
    }
    pnode v;
    scanf(" %s",c);
    while(1){
        if(c[0] == 'n'){
            scanf(" %s",c);
            x=0;
            if(c[0]<='9' && c[0] >= '0'){
                for(int i=0;i<strlen(c);i++){
                    x=x*10+(c[i]-48);
                }
                v = get_node(head,x);
                printf("%d , %d\n",x,v->node_num);
                c[0] = create_edges(&v,head);
                pedge temp = v->edges;
                while (temp)
                {
                    temp=temp->next;
                }
                
            }    
        }
        else {
            return c[0];
        }
    }
    return c[0];
}
char insert_node_cmd(pnode *head){
    int d;
    pnode nHead = (*head);
    printf("entered B, head first ver=%d\n",nHead->node_num);
    scanf(" %d",&d);
    pnode vertex = get_node(head,d);
    
    if(vertex){
        printf("after get_node %d\n",vertex->node_num);
        del_edges(vertex);
        //printf("vertex: %d\n",vertex->edges->weight);
        return create_edges(&vertex,head);

    }
    else{
        vertex = create_node(d);
        while(nHead->next){
            nHead = nHead->next;
        }
        nHead->next=vertex;
        printf("new ver: %d %d\n",nHead->node_num,vertex->node_num);
        return create_edges(&vertex,head);
    }
}
void delete_node_cmd(pnode *head){
    int d;
    scanf(" %d",&d);
    pnode ver = get_node(head,d);
    if(!ver){
        return;
    }
    del_ver(ver,head);
    return;
    
}
void shortsPath_cmd(pnode head){
    printf("\nEnter To ShortPath func\n");
    int src,dest;
    scanf(" %d",&src);
    scanf(" %d",&dest);
    pnode nsrc = get_node(&head,src);
    nsrc->dist=0;
    pnode ndst = get_node(&head,dest);
    pedge e_run = nsrc->edges;
    if(!(e_run)){
        nsrc->dist=__INT_MAX__;
        printf("Dijsktra shortest path: %d\n",-1);
        return;
    }
    pnode v_runner = nsrc;
    while(v_runner && v_runner!=ndst){
        printf("Enter to the big while\n");
        e_run = v_runner->edges;           //setting runner to edges
        pnode minlast = e_run->endpoint;    //setting default minimum distance last vertex
        while(e_run && minlast->didvisit){
            e_run=e_run->next;
            minlast=e_run->endpoint;
        }
        while(e_run && v_runner!=ndst){
            if(e_run->endpoint == ndst){  //the edge endpoint is the destination vertex
                if(ndst->dist > e_run->weight+v_runner->dist){  //checking destination distance field
                    ndst->dist=e_run->weight+v_runner->dist;     //setting new distance
                    printf("E_Run endpoint = Node_Dest\n");
                    if( minlast->dist > e_run->endpoint->dist ){
                        minlast = e_run->endpoint;
                    }
                }
            }
            else{   
                if(e_run->endpoint->dist > e_run->weight+v_runner->dist){     //checking endpoint vertex distance field
                    e_run->endpoint->dist = e_run->weight+v_runner->dist;
                    printf("E_Run endpoint != Node_Dest\n");
                }
                if(minlast->dist > e_run->endpoint->dist){
                    minlast = e_run->endpoint;
                }
                
                
            }
            printf("EDGE++\n");
            e_run=e_run->next;          //next edge           
        }
        printf("NODE++\n");
        v_runner->didvisit=1;
        v_runner=minlast;                //next vertex
        // while (e_run->endpoint->didvisit==1 && e_run != NULL){
        //     e_run=e_run->next;
        // }
        
    }
    if(ndst->dist == __INT_MAX__){
        printf("Dijsktra shortest path: %d\nResize all vertexes\n",-1);
    }
    else{
        printf("Dijsktra shortest path: %d\nResize all vertexes\n",ndst->dist);
    }

    //reseting all data
    pnode reset = head;
    while(reset!=NULL){
        printf("Reset The Values");
        reset->didvisit=0;
        reset->dist=__INT_MAX__;
//        reset->prev=-1;
        reset=reset->next;
    }
    printf("Go Out From S Func\n");
    return;
    }
void printGraph_cmd(pnode head){
    pnode ncounter = head;
    while (ncounter)
    {
        printf("\nEdge From Vertex : %d, \n",ncounter->node_num);
        pedge* ecounter = &ncounter->edges; 
        pedge ehelp = (*ecounter);
        while((*ecounter)){
            printf("To Vertex: %d,Weight: %d\n",(*ecounter)->endpoint->node_num,(*ecounter)->weight);
            ehelp = (*ecounter);
            ecounter = &(ehelp->next);
            
        }

        ncounter = ncounter->next;
        printf("out\n");
        
    }
    return;
}
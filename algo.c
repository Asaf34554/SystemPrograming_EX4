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
    char c[10] = "\0";
    printf("Please enter the number of vertices: \n");
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
          if(c[0]<='9' && c[0] >= '0'){
            for(int i=0;i<strlen(c);i++){
                x=x*10+(c[i]-48);
                }
            }    
            v = get_node(head,x);
            char ch = create_edges(v,head);
            char stemp[1] = "\0";
            stemp[0] = ch;
            strcpy(c,stemp);
        }
    }

    return c[0];
}
char insert_node_cmd(pnode *head){
    int d;
    pnode nHead = *head;
    scanf(" %d",&d);
    pnode vertex = get_node(head,d);
    if(vertex== NULL){
        vertex = create_node(d);
        while(nHead->next != NULL){
            nHead = nHead->next;
        }
        nHead->next=vertex;
        return create_edges(vertex,head);
    }
    else{
        del_edges(vertex);
        return create_edges(vertex,head);
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
    
}
void shortsPath_cmd(pnode head){
    int src,dest,minlast;
    scanf(" %d",&src);
    scanf(" %d",&dest);
    pnode nsrc = get_node(&head,src);
    nsrc->dist=0;
    pnode ndst = get_node(&head,dest);
    pedge e_run = nsrc->edges;
    if(!(e_run)){
        printf("Dijsktra shortest path: %d",-1);
        return;
    }
    pnode v_runner = nsrc;
    while(v_runner){
        e_run = v_runner->edges;            //setting runner to edges
        minlast = e_run->endpoint->node_num;    //setting sefault minimum distance last vertex
        while(e_run && v_runner!=ndst){
            if(e_run->endpoint == ndst){  //the edge endpoint is the destination vertex
                if(ndst->dist > e_run->weight+v_runner->dist){  //checking destination distance field
                    ndst->dist=e_run->weight+v_runner->dist;     //setting new distance
//                    ndst->prev=v_runner->node_num;                  //setting the last vertex in route                     
                }
            }
            else{   
                if(e_run->endpoint->dist > e_run->weight+v_runner->dist){     //checking endpoint vertex distance field
                    e_run->endpoint->dist = e_run->weight+v_runner->dist;
//                    e_run->endpoint->prev=v_runner->node_num;
                    if(minlast>e_run->endpoint->dist){
                        minlast = e_run->endpoint->node_num;
                    }
                }
            }
                e_run=e_run->next;          //next edge           
        }
        pedge tmpedg=v_runner->edges;
        while(tmpedg->endpoint->node_num != minlast && tmpedg){  //checking for the endpoint with the lowest distance and we one we didnt visited before
            tmpedg = tmpedg->next;
        }
        while(tmpedg->endpoint->didvisit){                      //checking if we visited the min endpoint if yes finding for another
            if(!(tmpedg->next) && tmpedg->next->endpoint->didvisit){
                tmpedg = tmpedg->next;
            }
            else{
                break;
            }
        }
        v_runner->didvisit=1;
        v_runner=tmpedg->endpoint;                //next vertex
    }
    printf("Dijsktra shortest path: %d",ndst->dist);

    //reseting all data
    pnode reset = head;
    while(reset!=NULL){
        reset->didvisit=0;
        reset->dist=__INT_MAX__;
//        reset->prev=-1;
        reset=reset->next;
    }
    return;
    }


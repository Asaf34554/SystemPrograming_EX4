
#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "edges.h"

int tsp_min = __INT_MAX__;

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
int shortsPath_cmd(pnode head,int src,int dst){
    int ret;
    printf("\nEnter To ShortPath func\n");
    pnode nsrc = get_node(&head,src);
    nsrc->dist=0;
    pnode ndst = get_node(&head,dst);
    printf("Node Start: %d, Node End: %d\n",nsrc->node_num,ndst->node_num);
    pedge e_run = nsrc->edges;
    if(!(e_run)){
        nsrc->dist=__INT_MAX__;
     //   printf("why\n");
        return -1;
    }
    pnode v_runner = nsrc;
    pnode minlast2;
    while(v_runner && v_runner!=ndst){
        // printf("Enter to the big while\n");
        e_run = v_runner->edges;           //setting runner to edges
        printf("why\n");
        pnode minlast = e_run->endpoint;    //setting default minimum distance last vertex
        printf("why\n");
        while(minlast->didvisit && e_run){
            e_run=e_run->next;
            printf("!!!!\n");
            minlast=e_run->endpoint;
        }
        while(e_run && v_runner!=ndst){
            if(e_run->endpoint == ndst){  //the edge endpoint is the destination vertex
                if(ndst->dist > e_run->weight+v_runner->dist){  //checking destination distance field
                    ndst->dist=e_run->weight+v_runner->dist;     //setting new distance
                    // printf("E_Run endpoint = Node_Dest\n");
                    if( minlast->dist > e_run->endpoint->dist ){
                        minlast2=minlast;
                        minlast = e_run->endpoint;
                    }
                }
            }
            else{   
                if(e_run->endpoint->dist > e_run->weight+v_runner->dist){     //checking endpoint vertex distance field
                    e_run->endpoint->dist = e_run->weight+v_runner->dist;
                    // printf("E_Run endpoint != Node_Dest\n");
                }
                if(minlast->dist > e_run->endpoint->dist){
                    minlast2 = minlast;
                    minlast = e_run->endpoint;
                }
                
                
            }
            // printf("EDGE++\n");
            e_run=e_run->next;          //next edge           
        }
        // printf("NODE++\n");
        v_runner->didvisit=1;
        if(minlast==NULL){
            minlast=minlast2;
            printf("Go to ver: %d\n",minlast->node_num);
        }
        else{
            v_runner=minlast;                //next vertex
            printf("Go to ver: %d\n",v_runner->node_num);
            if(v_runner->edges == NULL && v_runner != ndst){
                v_runner->didvisit = 1;
                v_runner = minlast2;
                printf("Go to ver: %d\n",v_runner->node_num);
                 
            }   
        }    
    }
    if(ndst->dist == __INT_MAX__){
        ret = -1;
    }
    else{
        ret = ndst->dist;
    }

    //reseting all data
    pnode reset = head;
    while(reset!=NULL){
       // printf("Reset The Values");
        reset->didvisit=0;
        reset->dist=__INT_MAX__;
//        reset->prev=-1;
        reset=reset->next;
    }
    printf("Go Out From S Func\n");
    return ret;
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
void swap(int *a, int*b){
    int temp = *a;
    *a=*b;
    *b=temp;
}

int reset_min(){
    if (tsp_min == __INT_MAX__)
    {
        return -1;
    }
    int temp = tsp_min;
    tsp_min=__INT_MAX__;
    return temp;
}
void TSP_cmd(pnode head,int *arr,int size){
    int tmp_min = 0;        
    int runner = arr[0];
    int next_runner = 0;     

    for (int i = 1; i < size; ++i)
    {
        next_runner = arr[i];
        tmp_min += shortsPath_cmd(head,runner,next_runner); 
        runner = next_runner; 

    }
    if (tsp_min> tmp_min)
    {
        tsp_min = tmp_min;
    }
}
void permut(pnode head,int *arr,int beg ,int fin){
if (beg == fin)
    {
        TSP_cmd(head, arr, fin + 1);
        return;
    }
    int i;
    for (i = beg; i <= fin; i++)
    {
        swap((arr + i), (arr + beg));
        permut(head,arr, beg+ 1, fin);
        swap((arr + i), (arr + beg));
    }
}


#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "edges.h"

int tsp_min = __INT_MAX__;

char build_graph_cmd(pnode *head){
    pnode *nhead = head;
    pnode temp,temp1;
    int x,n;
    char c[10] = "\0";
    scanf(" %d",&n);
    for(int i=0;i<n;i++){
        if(i==0){
            temp = create_node(i);
            (*nhead) = temp;
        }
        else{
            temp1 = create_node(i);
            temp->next=temp1;
            temp=temp1;    
        }

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
    scanf(" %d",&d);
    pnode vertex = get_node(head,d);
    
    if(vertex){
        del_edges(vertex);
        return create_edges(&vertex,head);

    }
    else{
        vertex = create_node(d);
        while(nHead->next){
            nHead = nHead->next;
        }
        nHead->next=vertex;
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
int shortsPath_cmd(pnode head,int src,int dst, int* arr,int size, int* flag){
    int ret,counter=0,out=1;
    int *temp = arr;
    pnode nsrc = get_node(&head,src);
    nsrc->dist=0;
    pnode ndst = get_node(&head,dst);
    pedge e_run = nsrc->edges;
    if(!(e_run)){
        nsrc->dist=__INT_MAX__;
        return -1;
    }
    pnode v_runner = nsrc;
    pnode minlast2;
    while(v_runner && v_runner!=ndst){
        e_run = v_runner->edges;           //setting runner to edges
        pnode minlast = e_run->endpoint;    //setting default minimum distance last vertex
        while(e_run&&minlast->didvisit){
            if(e_run->next!=NULL){
                e_run=e_run->next;
                minlast=e_run->endpoint;
            }
            else{
                e_run=e_run->next;
                out=0;
                break;
            }
        }
        while(e_run && v_runner!=ndst){
            if(e_run->endpoint == ndst){  //the edge endpoint is the destination vertex
                if(ndst->dist > e_run->weight+v_runner->dist){  //checking destination distance field
                    ndst->dist=e_run->weight+v_runner->dist;     //setting new distance
                    if( minlast->dist >= e_run->endpoint->dist ){
                        minlast2=minlast;
                        minlast = e_run->endpoint;
                    }
                }
            }
            else{
                if(e_run->endpoint->dist > e_run->weight+v_runner->dist){     //checking endpoint vertex distance field
                    e_run->endpoint->dist = e_run->weight+v_runner->dist;
                }
                if(minlast->dist >= e_run->endpoint->dist){
                    minlast2 = minlast;
                    minlast = e_run->endpoint;
                }
                
                
            }
            while(e_run->next&&e_run->next->endpoint->didvisit){
                e_run=e_run->next;          //next edge
            }
            e_run=e_run->next;
            
    
   
        }
        v_runner->didvisit=1;
        if(minlast==NULL){
               minlast=minlast2; 
        }
        else if(out==0){
            break;
        }
        else{
            v_runner=minlast;                //next vertex
            for(int i=0;i<size-1;i++){
                if(temp[i]==v_runner->node_num){
                    counter++;
                    break;
                }
            }
            if(v_runner->edges == NULL){
                v_runner->didvisit = 1;
                if(v_runner!=minlast2){
                    v_runner = minlast2;
                    for(int i=0;i<size;i++){
                        if(temp[i]==v_runner->node_num){
                            counter++;
                            break;
                        }
                    } 
                }
                else{
                    break;
                }

            }   
        }    
    }
    if(ndst->dist == __INT_MAX__){
        ret = -1;
    }
    else{
        ret = ndst->dist;
    }
    if(counter>=size-1){
        *flag=1;
    }
    else{
        *flag=0;
    }
    //reseting all data
    pnode reset = head;
    while(reset!=NULL){
        reset->didvisit=0;
        reset->dist=__INT_MAX__;
        reset=reset->next;
    }
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
    int tmp_min=0,flag=0;      
    int runner = arr[0];
    int next_runner = 0;
    for (int i = 1; i < size; ++i)
    {
        flag=0;
        next_runner = arr[i];
        int prevmin = shortsPath_cmd(head,runner,next_runner,arr,size-1,&flag);
        if(prevmin!=-1){
            tmp_min +=  prevmin;
        }
        else{
            tmp_min=__INT_MAX__;
            break;
        }
        runner = next_runner; 

    }
    if (tsp_min > tmp_min)
    {
        
        if(tmp_min!=0){
            tsp_min = tmp_min;
        }
        
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

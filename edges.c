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
    printf("create_Edges: head ver:%d, vertex on:%d \n",(*head)->node_num,(*vertex)->node_num);
    pedge* temp=&((*vertex)->edges);
    pedge runner;
    while(1){
        scanf(" %s",c);
        printf("the first scanf in create_edges %c\n",c[0]);
        if(c[0] == 'n' || c[0] == 'D' || c[0] == 'A' || c[0] == 'S'  ||c[0] == 'B'   || c[0] == 'T' || c[0] == 'Y' ){
            return c[0];
        }
        int x=0;
        for(int i=0;i<strlen(c);i++){
            x=x*10+(c[i]-48);
        }

        pnode nextnode = get_node(head,x);
        printf("creating edge to:%d\n",nextnode->node_num);
        scanf(" %d",&d);
        if(!(*temp)){
            printf("empty edges creating one\n");
            runner=create_edge();
            runner->weight=d;
            runner->endpoint=nextnode;
            temp=&runner;
            printf("temp %d, runner %d \n",(*temp)->endpoint->node_num,runner->endpoint->node_num);
            printf("edge from %d to %d, weight:%d\n\n\n",(*vertex)->node_num,(*temp)->endpoint->node_num,(*temp)->weight);
        }
        else{
            printf("have edges adding another\n");
            pedge* runner2 = temp;
            while((*temp)!=NULL)
            {
                printf("e edge to:%d\n",(*temp)->endpoint->node_num);
                runner = (*temp);
                runner2 = &runner;
                temp=&(runner->next);
            }
            (*runner2)->next = create_edge();
            (*runner2)->next->endpoint=nextnode;
            (*runner2)->next->weight=d;
            temp = runner2;
            printf("edge from %d to %d, weight:%d\n\n\n",(*vertex)->node_num,(*temp)->next->endpoint->node_num,(*temp)->next->weight);
        }
        
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
    if(!ehead){
        printf("empty\n");
        return;
    }
    if(ehead->endpoint== endp){
        printf("first edge del %d\n",ehead->endpoint->node_num);
        ver->edges = ehead->next;
        free(ehead);
        return;
    }
    pedge prev;
    while (ehead->endpoint != endp){
        if(ehead->next == NULL ){
            printf("null\n");
            return;
        }
        printf("not this edge %d",ehead->endpoint->node_num);
        prev = ehead;
        ehead = ehead->next;     
    }
    if(ehead->next == NULL){
        printf("last edge del %d\n",ehead->next->endpoint->node_num);
        free(ehead);
    
    }
    else{
        prev->next = ehead->next;
        printf("deleting %d now %d pointing to %d\n",ehead->endpoint->node_num,prev->endpoint->node_num,prev->next->endpoint->node_num);
        free(ehead);
    }
    return;
}

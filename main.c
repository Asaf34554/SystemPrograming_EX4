#include <stdio.h>
#include "graph.h"


int main(){
    int flag = 1;
    pnode head;
    char let = '\0';
    scanf(" %c",&let);
    
    while(flag == 1){
        
        if(let == 'A'){
            let = build_graph_cmd(&head);
            
        }
        if(let == 'B'){
            let = insert_node_cmd(&head);
        }
        if(let == 'D'){
            delete_node_cmd(&head);
            scanf(" %c",&let);
        }
        if(let == 'S'){
            shortsPath_cmd(head);
            scanf( "%c",&let);
        }
        
    }
    
}
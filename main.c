#include <stdio.h>
#include "graph.h"
#include "node.h"


int main(){
    int flag = 1,dj;
    pnode head;
    char let = '\0';
    scanf(" %c",&let);
    while(flag == 1){
        
        if(let == 'A'){
            if(head != NULL){
                del_all_ver(&head);
            }
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
            int src,dest;
            scanf(" %d",&src);
            scanf(" %d",&dest);
            dj = shortsPath_cmd(head,src,dest);
            printf("Dijsktra shortest path: %d\nResize all vertexes\n",dj);
            scanf( " %c",&let);
        }
        if(let == 'P'){
            printGraph_cmd(head);
            scanf(" %c",&let);
        }
        if(let == 'T'){
            int n,x;
            scanf(" %d",&n);
            int arr[n];
            for(int i = 0; i < n ; i++){
                scanf(" %d",&x);
                arr[i]=x;
            }
            permut(head,arr,0,n-1);
            int ans = reset_min();
            printf("TSP shortest path: %d\n",ans);   
            scanf(" %c",&let);
        }
        if(let == 'Y'){
            del_all_ver(&head);
            return 1;
        }
        
    }
    
}
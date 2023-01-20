#include <stdio.h>
#include "graph.h"
#include "node.h"


int main(){
    int flag = 1,dj;
    pnode head=NULL;
    char let = 'A';
    let = getchar();
    while(let!=EOF&&let!='\n'){
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
            let = getchar();
        }
        if(let == 'S'){
            int src,dest;
            scanf(" %d",&src);
            scanf(" %d",&dest);
            dj = shortsPath_cmd(head,src,dest,NULL,0,&flag);
            printf("Dijsktra shortest path: %d\n",dj);
            let = getchar();
        }
        if(let == 'P'){
            printGraph_cmd(head);
            let = getchar();
        }
        if(let == 'T'){
            int n,x;
            scanf("%d",&n);
            int arr[n];
            for(int i = 0; i < n ; i++){
                scanf("%d",&x);
                arr[i]=x;
            }
            permut(head,arr,0,n-1);
            int ans = reset_min();
            printf("TSP shortest path: %d\n",ans);   
            let = getchar();
        }
        if(let == ' '){
            let = getchar();
        }
        if(let== EOF || let == 'Y' || let == '\n'){
            del_all_ver(&head);
            return 0;
        }
        

    }
    del_all_ver(&head);
    return 0;
}
#include "final.h"
#include <string.h>

int counter = 1,state=0;

int main(int argc, char **argv)
{

    if (argc == 1)
    {
        printf("Enter the Exploaration Strategy you would like to use in CLI\n");
        return 0;
    }

    if (argc > 2)
    {
        printf("Enter only one Exploration Strategy\n");
        return 0;
    }

    char *strategy = argv[1];

    int n;
    scanf("%d", &n);

    Node tree;
    Node *parentptr;
    parentptr = (Node *)malloc(sizeof(Node) * n);

    tree = Create_Tree(n, parentptr);
    printf("\n");
    
    if (strcmp(strategy, "DFS") == 0)
    {
        PQ Q = Init_pq(Q, n);
        parentptr[0]->seen_time = 1;
        Push(Q, parentptr[0], node_comparator_dfs);
        while (!IsEmpty(Q))
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];
            Gfill( Q, state);
            Pop(Q, node_comparator_dfs);
            state++;
            for (int i = 0; i < new_node->children.list.size; i++)
            {   
                counter++;
                new_node->children.list.obj[i]->seen_time = counter;
                Push(Q, new_node->children.Get(&(parentptr[random->self - 1]->children), i), node_comparator_dfs);
            }
        }
        Gprint(state);
        printf("\n");
    }
    else if (strcmp(strategy, "BFS") == 0)
    {
        PQ Q = Init_pq(Q, n);
        parentptr[0]->seen_time = 1;
        Push(Q, parentptr[0], node_comparator_bfs);
        while (!IsEmpty(Q))
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];
            Gfill( Q, state);
            Pop(Q, node_comparator_bfs);
            state++;
            for (int i = 0; i < new_node->children.list.size; i++)
            {
                counter++;
                new_node->children.list.obj[i]->seen_time = counter;
                Push(Q, new_node->children.Get(&(parentptr[random->self - 1]->children), i), node_comparator_bfs);
            }
        }
         Gprint(state);
        printf("\n");
    }
    else if (strcmp(strategy, "GREEDY") == 0)
    {
        PQ Q = Init_pq(Q, n);
        Push(Q, parentptr[0], node_comparator_greedy);
        while (!IsEmpty(Q))
        {
            Node random = Top(Q);
            Node new_node = parentptr[random->self - 1];
            Gfill( Q, state);
            Pop(Q, node_comparator_greedy);
            state++;
            for (int i = 0; i < new_node->children.list.size; i++)
            {
                Push(Q, new_node->children.Get(&(parentptr[random->self - 1]->children), i), node_comparator_greedy);
            }
        }
         Gprint(state);
        printf("\n");
    }
    else if (strcmp(strategy, "A-STAR") == 0)
    {
    }
    else if (strcmp(strategy, "MCTS") == 0)
    {
    }
    else
    {
        printf("\n\nEnter Exploration Strategy from any of the following: \n\n");
        printf("1. DFS\n2. BFS\n3.GREEDY\n4. A-STAR\n5. MCTS\n");
    }
    printf("\n");
    Print_Tree(parentptr, n);
    printf("\n");

    return 0;
}

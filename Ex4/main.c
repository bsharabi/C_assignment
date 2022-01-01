//#include "algo.h"
//
//int main()
//{
//    char *graphList = "";
//    int *addNode_EdgeList = NULL;
//    int nodeDel = 0;
//    int nodeSrc = 0, nodeDest = 0;
//    int dist;
//    int *nodeList = NULL;
//    int *tspList;
//    char ch;
//    while (true)
//    {
//        printf("(A) --> to create a graph\n");
//        printf("(B) --> create new Node\n");
//        printf("(D) --> delete Node\n");
//        printf("(S) --> Shortest Path Dist\n");
//        printf("(T) --> TSP\n");
//        ch=toupper(getchar());
//        system("CLS");
//        switch (ch)
//        {
//        case 'A':
//            createGraph();
//            break;
//        case 'B':
//            createNode(addNode_EdgeList);
//            break;
//        case 'D':
//            deleteNode(nodeDel);
//            break;
//        case 'S':
//            dist = ShortestPathDist(nodeSrc, nodeDest);
//            printf("%d\n", dist);
//            break;
//        case 'T':
//            tspList = tsp(nodeList);
//            break;
//        default:
//            printf("try again \n");
//            getchar();
//            break;
//        }
//        printf("Enter any for the menu");
//        getchar();
//        system("CLS");
//    }
//}
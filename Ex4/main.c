//#include "graph.h"
//int main()
//{
//    while (ch != '\n')
//    {
//        switch (ch)
//        {
//        case 'A':
//            ch = getchar();
//            v_size = 0;
//            e_size = 0;
//            scanf("%d", &v_size);
//            build_graph_cmd(&head);
//            // printGraph_cmd(&head);
//            break;
//        case 'B':
//            insert_node_cmd(&head);
//            // printGraph_cmd(&head);
//            break;
//        case 'D':
//            delete_node_cmd(&head);
//            // printGraph_cmd(&head);
//            break;
//        case 'T':
//            TSP_cmd(&head);
//            break;
//        case 'S':
//            shortsPath_cmd(&head);
//            break;
//        }
//        if (isalpha(ch))
//            continue;
//        if (ch == '\n')
//            break;a
//        ch = getchar();
//    }
//    deleteGraph_cmd(&head);
//    return 0;
//}
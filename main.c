#include"avl.c"


int main(){
    node* AVL;
    initAVL(&AVL);
    
    int choice, MIS;
    char name[50];

    do {
        printf("1. Insert a Node\n");
        printf("2. Remove a Node\n");
        printf("3. Traverse the Tree\n");
        printf("4. Destroy the Tree\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter MIS to insert: ");
                scanf("%d", &MIS);
                printf("Enter first name: ");
                scanf("%s", name);
                insertNode(&AVL, name, MIS);
                break;
            case 2:
                printf("Enter MIS to remove: ");
                scanf("%d", &MIS);
                AVL = removeNode(AVL, MIS);
                break;
            case 3:
                traverse(AVL);
                printf("\n");
                break;
            case 4:
                AVL = destroyTree(AVL);
                AVL = NULL;
                printf("Tree destroyed.\n");
                break;
            case 5:
                printf("Exiting...\n");
                destroyTree(AVL); // Cleanup memory before exit
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 5);

    return 0;
}
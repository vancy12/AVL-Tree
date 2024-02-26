#include"header.h"

void initAVL(node** AVL){
    *AVL = NULL;
}

node* createNode(node* nn, char* n, int rollNumber){
    nn->left = NULL;
    nn->right = NULL;
    nn->parent = NULL;
    nn->name = n;
    nn->balance = 0;
    nn->MIS = rollNumber;
    return nn;
}

int height(node* p){
    if(p == NULL)
        return -1;

    return max(height(p->left), height(p->right)) + 1;
}


void calculateBalance(node** AVL){
    node* p = *AVL;
    p->balance = height(p->left) - height(p->right);
    
}

// all the cases
void LL(node** AVLroot, node* n){
    node* temp = n->left;
    
    // since n is going to take up the right of temp
    // make sure if temp has a right child it is saved
    // so we make n->left point to temp's right child

    n->left = temp->right;
    // deal with parent pointer
    if(temp->right)
        n->left->parent = n;
    
    // now make temp->right point to n
    temp->right = n;
    // now we need to connect via temp not n to the main tree
    temp->parent = n->parent;
    n->parent = temp;

    // if temp is not the root node
    // adjust where the parent node is pointing
    if(temp->parent){
        if(temp->parent->left == n)
            temp->parent->left = temp;
        else    
            temp->parent->right = temp;
    }
    else{
        *AVLroot = temp;
    }
    calculateBalance(&n);
    calculateBalance(&temp);

}

void RR(node** AVLroot, node* n){
    node* temp = n->right;
    
    // since n is going to take up the left of temp
    // make sure if temp has a left child it is saved
    // so we make n->left point to temp's left child

    n->right = temp->left;
    // deal with parent pointer
    if(temp->left)
        n->right->parent = n;
    
    // now make temp->left point to n
    temp->left = n;
    // now we need to connect via temp not n to the main tree
    temp->parent = n->parent;
    n->parent = temp;

    // if temp is not the root node
    // adjust where the parent node is pointing
    if(temp->parent){
        if(temp->parent->left == n)
            temp->parent->left = temp;
        else    
            temp->parent->right = temp;
    }
    else{
        *AVLroot = temp;
    }
    calculateBalance(&n);
    calculateBalance(&temp);

}

void RL(node** AVLroot, node* n){
    RR(AVLroot, n->left);
    LL(AVLroot, n);
}
void LR(node** AVLroot, node* n){
    LL(AVLroot, n->right);
    RR(AVLroot, n);
}

void balanceTree(node** AVL){
    // LL RR RL LR
    node *p = *AVL;
    if(p->balance > 1){
        if(p->left->balance > 0)
            LL(AVL, p);
        else
            RL(AVL, p);
    }
    else if(p->balance < -1){
        if(p->right->balance > 0)
            LR(AVL, p);
        else
            RR(AVL, p);
    }
}

void insertNode(node** AVL, char* n, int rollNumber){
    node* nn = (node*)malloc(sizeof(node));
    nn = createNode(nn, n, rollNumber);

    node *p, *q;
    p = *AVL;
    q = p;
    while(p){
        q = p;
        if(rollNumber < p->MIS)
            p = p->left;
        
        else if(rollNumber > p->MIS)
            p = p->right;
        
        else{
            printf("No two MIS can be same enter correct MIS\n");
            return;
        }
    }
    if(q){
        if(rollNumber < q->MIS)
            q->left = nn;
        else
            q->right = nn;
        nn->parent = q;
    }
    else{
        *AVL = nn;
        nn->parent = NULL;
    }
    
    calculateBalance(AVL);
    balanceTree(AVL);
}

node* removeNode(node* AVLroot, int remove){
    // traverse to the node to be deleted
    if(AVLroot == NULL){
        return AVLroot;
    }

    if(remove < AVLroot->MIS){
        removeNode(AVLroot->left, remove);
        return AVLroot;
    }
    else if(remove > AVLroot->MIS){
        removeNode(AVLroot->right, remove);
        return AVLroot;
    }
    // if node has 1 child
    if(AVLroot->right == NULL){
        node* temp = AVLroot->left;
        free(AVLroot);
        return temp;
    }
    else if(AVLroot->left == NULL){
        node* temp = AVLroot->right;
        free(AVLroot);
        return temp;
    }
    
    // if node has 2 children
    node* succParent = AVLroot;
    node* succ = AVLroot->right;

    while(succ->left != NULL){
        succParent = succ;
        succ = succ->left;
    }

    if(succParent != AVLroot){
        succParent->left = succ->right;
    }
    else{
        succParent->right = succ->right;
    }
    AVLroot->MIS = succ->MIS;
    free(succ);
    return AVLroot;
    calculateBalance(&AVLroot);
    balanceTree(&AVLroot);

}

void traverse(node* root){
    if(root == NULL){
        return;
    }
    traverse(root->left);
    printf("[%d, %s, %d]  ", root->MIS, root->name, root->balance);
    traverse(root->right);
}

node* destroyTree(node* AVL){
    if(AVL != NULL){
        if(AVL->right)
            destroyTree(AVL->right);
        if(AVL->left)
            destroyTree(AVL->left);
        free(AVL);
    }
    return NULL;
}

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include"binary_search_tree.h"

binary_search_tree* create_bst()
{
    /*
       create a binary_search_tree
       associate with each binary_search_tree a root
       and a semaphore to perform thread safe operations
    */

    binary_search_tree* bst = (binary_search_tree*)malloc(sizeof(binary_search_tree));

    bst->root = NULL;
    bst->sem = (sem_t*)malloc(sizeof(sem_t));
    sem_init(bst->sem, 0, 1);

    return bst;
}

void insert_in_bst(binary_search_tree* bst, int data)
{
    /*
        insert data into bst
    */
    sem_t* sem = bst->sem;
    sem_wait(sem);// enter critical section

    // create a node for insertion
    binary_search_tree_node* temp = (binary_search_tree_node*)malloc(sizeof(binary_search_tree_node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    if(bst->root == NULL) // empty binary_search_tree
    {
        bst->root = temp;
    }
    else // non empty
    {
        binary_search_tree_node* root = bst->root;
        binary_search_tree_node* prev = NULL;

        while(root!=NULL)
        {
            prev = root;
            if(data < root->data)
            {
                root = root->left;
            }
            else if(data > root->data)
            {
                root = root->right;
            }
            else // data already in binary_search_tree
            {
                goto end_cs;
            }
        }
        if(data < prev->data)
            prev->left = temp;
        else
            prev->right = temp;
    }
    end_cs: // to indicate the end of critical section
    sem_post(sem); // end critical section
}

int search_bst(binary_search_tree* bst, int data)
{
    /*
        search the binary_search_tree for data
        return 1 if found, 0 otherwise
    */
    sem_t* sem = bst->sem;
    sem_wait(sem); // enter critical section

    binary_search_tree_node* root = bst->root;
    int level=0;
    if(root==NULL) // empty binary_search_tree
    {
        level=-1;
    }
    else
    {
        while(root!=NULL && root->data!=data)
        {
            level++;
            if(data > root->data) // branch right
            {
                root = root->right;
            }
            else // branch left
            {
                root = root->left;
            }
        }
        if(root==NULL)
        {
            level = -1;
        }
    }

    end_cs: // to indicate the end of critical section
    sem_post(sem);
    return level;
}

void delete_from_bst(binary_search_tree* bst, int val)
{
    sem_t* sem = bst->sem;
    sem_wait(sem);

    binary_search_tree_node *ptr, *parent;
    binary_search_tree_node *parent_replacement, *replacement;
    binary_search_tree_node *child_ptr;

    int is_left = 0; // 1 for left. 0 for right.

    /* Find the node to be deleted */
    parent = NULL;
    ptr=bst->root;
    while(ptr != NULL)
    {
        if (val == ptr->data)
            break; // Found it
        else if (val < ptr->data)
        {
            parent = ptr;
            is_left = 1; /* Left */
            ptr = ptr->left;
        }
        else
        {
            parent = ptr;
            is_left = 0; /* Right */
            ptr = ptr->right;
        }
    }

    /* ptr is either NULL or the node to be deleted */
    if (ptr == NULL)
    {
        goto end_cs;
    }

    /* ptr is pointing to the node to be deleted */ 
    /* Three Cases
    * 1) It is leaf node
    * 2) It has one child
    * 3) It has two children
    */

    if ((ptr->left == NULL) && (ptr->right == NULL))
    {
        /* Case 1 : Leaf Node*/
        if (parent == NULL)
        {
                // The node being deleted is root itself!
                free(ptr);
                bst->root = NULL;
        }
        else
        {
                free(ptr);
                if (is_left)
                    parent->left = NULL;
                else
                    parent->right = NULL;
        }
    }
    else
    if ((ptr->left == NULL) || (ptr->right == NULL))
    {
        /* Case 2: The node has exactly one child */
        if (ptr->left != NULL)
            child_ptr = ptr->left;
        else
            child_ptr = ptr->right;

        if (parent == NULL) // root is being deleted 
        {
            bst->root = child_ptr;
            free(ptr);
        }
        else
        {
            // non-root node is being deleted. So, the parent of "to be deleted"
            // node will adopt the "to be deleted" node's child
            if (is_left)
                parent->left = child_ptr;
            else
                parent->right =  child_ptr;
            free(ptr);
        }
    }
    else
    {
        /* Case 3: Node to be deleted has both left and right children */
        
        /* Find replacement. i.e. the highest node less than the to-be-deleted
        *   It can be found as the largest member in the left subtree.
        *   So, we can take one left, and then keep moving right as far as
        *   possible (Note : Alternate approach was to take the minimum in
        *   the right subtree)
        */
        parent_replacement = ptr;
        replacement =  ptr->left;
        is_left = 1; /* Replacement is left child of parent */
        while(replacement->right != NULL)
        {
            parent_replacement = replacement;
            replacement = replacement->right;
            is_left = 0; // Replacement is right child of parent
        }


        /* Copy data */
        ptr->data = replacement->data;
        /* Two broad cases
        * i) Replacement is left child of ptr 
        *   (and could be having 0 or 1 children)
        * ii) Replacement is right (grand)child of ptr->left
        */

        if (is_left)
        {
                // case i : replacement is left child of ptr.
                ptr->left = replacement->left;
                free(replacement);
        }
        else
        {
            // case ii : replacement is right grand(child of ptr->left
            parent_replacement->right = replacement->left;
            free(replacement);
        }
    }
    end_cs:
    sem_post(sem);
}

void delete_bst(binary_search_tree* bst)
{
    sem_t* sem = bst->sem;
    sem_wait(sem);
    free(bst);
    sem_post(sem);
}
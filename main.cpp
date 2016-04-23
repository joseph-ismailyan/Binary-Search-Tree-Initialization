// Joseph Ismailyan
// Binary Search Tree
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

ifstream in ("input.txt");

struct BinaryTree{
   int item;
   BinaryTree * left;
   BinaryTree * right;
};

struct node{
    BinaryTree *leaf;
    node *next;
};

bool inTree(BinaryTree * root, int key);
BinaryTree * AddNode(BinaryTree * root, int key);
void insertname (BinaryTree *leaf, BinaryTree *add);
BinaryTree * insertNoRecursion(BinaryTree *leaf, int key);
void preOrder(BinaryTree *root);
void inOrder(BinaryTree *root);
void postOrder(BinaryTree *root);
void BreathOrder(BinaryTree*, node*&, node*&);
void enqueue(BinaryTree*, node *&, node*&);
void dequeue(node *&, node *&);
BinaryTree* remove(BinaryTree*, int);
int minValue(BinaryTree*);



int main()
{
    char input[20];
    int deletenum;
    BinaryTree *root = NULL;
    BinaryTree *deletenode = NULL;
    node *front, *rear;
    front = rear = NULL;

    while(in.good() && in>>input){
            //if encountered delete character
    if(isalpha(input[0]))
        {
          in>>deletenum;  //grab # following delete
          if(!(inTree(root,deletenum)) ){
            cout<<"Not in tree"<<deletenum<<endl;
            root= AddNode(root,deletenum);
           }
           else{
            cout<<"item is in tree"<<endl;
            cout << "removing " << deletenum;
            //gets the location  of the node to delete
            deletenode = remove(root,deletenum);
           }
           cout<<endl;

    }
      else{
            int a = atoi(input);  //convert characters to int
            cout<<"number is "<<a<<endl;
            root= AddNode(root,a);
      }
    }
    cout << "preOrder:" << endl;
    preOrder(root);
    cout << "inOrder:" << endl;
    inOrder(root);
    cout << "postOrder:" << endl;
    postOrder(root);
    cout << "breathOrder:"<< endl;
    BreathOrder(root, front, rear);


    return 0;
}

void enqueue(BinaryTree* newLeaf, node *&front, node*&rear){
    node *newNode = new node;

    newNode->leaf = newLeaf;
    newNode->next = NULL;
    if (rear){
        rear->next = newNode;
        rear = newNode;
    }else
        front = rear =newNode;
}

void dequeue(node *& front, node *& rear){
    node *temp;
    if(front){
        temp= front;
        front = front->next;
        delete temp;
    }
    if (!front)
        rear =NULL;
}
BinaryTree* findMin(BinaryTree* root){
  while(root->left != NULL) root = root->left;
  return root;
}

BinaryTree* remove(BinaryTree *root, int item){
  if(root == NULL) return root;
  else if(item < root->item) root->left = remove(root->left,item);
  else if(item > root->item) root->right = remove(root->right, item);
  else {
    // Case 1: No Child
    if(root->left == NULL && root->right == NULL){
      delete root;
      root = NULL;
    // Case 2: one child
    } else if(root->left == NULL){
      BinaryTree *temp = root;
      root = root->right;
      delete temp;
    } else if(root->right == NULL){
      BinaryTree *temp = root;
      root = root->left;
      delete temp;
    } else{
      BinaryTree *temp = findMin(root->right);
      root->item = temp->item;
      root->right = remove(root->right, temp->item);
    }
  }
  return root;
}

BinaryTree * AddNode(BinaryTree * root, int key)
{
    if(root == NULL){
        BinaryTree * newnode = new BinaryTree;
        newnode->item = key;
        newnode->left = NULL;
        newnode->right=NULL;
        root = newnode;
    }
    else{
        BinaryTree * add = NULL;
          add = new BinaryTree;
          add->item = key;
          add->left = NULL;
          add->right = NULL;
          //cout<<add->item<<endl;
          insertname(root,add);
    }
    return root;
}
void insertname (BinaryTree *leaf, BinaryTree *add){
    //The new node has already been created which is add.
    //Search_insert will identify the location of where it needs to
    //insert. Here we have to decide to insert to the left or right.
    //We only do insert if we don't come back with a null.
    //We are assuming that there is already a root.
    leaf= insertNoRecursion(leaf,add->item);
        if (add->item > leaf->item){
            leaf->right=add;
            cout<<add->item<<" adding in right of "<<leaf->item<<endl;
           }
        else{
            leaf->left=add;
            cout<<add->item<<" adding in left of: "<<leaf->item<<endl;
            }

}

BinaryTree * insertNoRecursion(BinaryTree *leaf, int key){
    bool foundSpot=false;

    while (leaf!=NULL && !foundSpot){
        if (key == leaf->item){
            leaf = NULL;
            }
        //If it is smaller, then go to the left
        else if (key <leaf->item){
            if (leaf->left !=NULL)
                leaf=leaf->left;
            else foundSpot=true;
           }
        else{
            if (leaf->right!=NULL)
                leaf=leaf->right;
            else
                foundSpot=true;
        }
    }
    return leaf;
}
bool inTree(BinaryTree * root, int key)
{
    bool found = false;
    if(root == NULL)found = false;
    else
    {
      BinaryTree * current = root;

      while (current!=NULL && !found)
       {
        if (key == current->item) found=true;
        else if (key > current->item){
          current=current->right; //if key is bigger go to right
        }
        else {
         current=current->left;  //if key is small than leaf value go to left
        }
       }
    }
 return found;

}

void preOrder(struct BinaryTree *root)
{
    if(root != NULL)
    {
        cout<<'\t' << root->item<<endl;
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(BinaryTree *root)
{
    if(root != NULL)
    {
        inOrder (root->left);
        cout<<'\t' << root->item<<endl;
        inOrder (root->right);
    }
}

void postOrder(BinaryTree *root)
{
    if(root != NULL)
    {
        postOrder (root->left);
        postOrder (root->right);
        cout<< '\t' << root->item<<endl;
    }
}
void BreathOrder(BinaryTree *root, node *&front, node *&rear){
    if(!root)
        return;
    enqueue(root, front, rear);
    while(front){
        root = front->leaf;
        cout << '\t' << front->leaf->item << endl;
        dequeue(front, rear);
        if(root->left)
            enqueue(root->left, front, rear);
        if(root->right)
            enqueue(root->right, front, rear);
    }
}



#include<iostream>
#include<queue>
#include<utility>
using namespace std;

 struct Node
{
     pair<int,int> i;
    int maxValue;
    Node *left, *right;
};
class iTree
{
    Node *root;
public:
    iTree()
    {
        root = NULL;
    }
     Node *createNewNode(pair<int,int>i)
    {
        Node *newNode = new Node;
        newNode->i = i;
        newNode->maxValue = i.second;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
     void inserti(Node *node,pair<int,int>i)
    {
        if(root==NULL)
        {
            root = createNewNode(i);
        }
        else
        {
            Node *point = node;
            if(point->maxValue<i.second)point->maxValue = i.second;
            if(i.first<point->i.first)
            {
                if(point->left==NULL)
                {
                   Node *newNode = createNewNode(i);
                    point->left = newNode;
                }
                else inserti(point->left,i);
            }
            else
            {
                if(point->right==NULL)
                {
                   Node *newNode = createNewNode(i);
                    point->right = newNode;
                }
               else inserti(point->right,i);
            }
        }
    }
    Node *getRoot()
    {
        return root;
    }
     void printTree()
    {
        queue <Node *> printQueue;
        if(root!=NULL)printQueue.push(root);
        else cout<<"Tree is empty"<<endl;
        while(!printQueue.empty())
        {
            Node *node = printQueue.front();
            printQueue.pop();
            cout<<"i: "<<node->i.first<<", "<<node->i.second<<endl;
            cout<<"Max: "<<node->maxValue<<endl;
            if(node->left!=NULL)printQueue.push(node->left);
            if(node->right!=NULL)printQueue.push(node->right);
        }
    }
    bool checkOverlap(pair<int,int>i1, pair<int,int>i2)
    {
        if(i1.first<=i2.second && i2.first<=i1.second)
            return true;
        return false;
    }
    Node *searchOverlap(Node *node,pair<int, int>i)
    {
       Node *match = NULL;
       if(node!=NULL)
        {
           if(checkOverlap((node->i),i))
                match = node;
            else
            {
              if(node->left!=NULL && node->left->maxValue>=i.first)
                    match = searchOverlap(node->left,i);

                else match = searchOverlap(node->right,i);
            }
        }
        return match;
    }

    Node *deletei(Node *node,pair<int,int> i)
    {

        if(node==NULL)
            return node;

        if(i.first<node->i.first)
            node->left = deletei(node->left,i);

        else if(i.first>=node->i.first&&(i!=node->i))
            node->right = deletei(node->right,i);

        else if(i == node->i)
        {

            if(node->left==NULL)
            {

                Node *temp = node->right;
                delete node;
                return temp;
            }

            else if(node->right==NULL)
            {

                Node *temp = node->left;
                delete node;
                return temp;
            }


            Node *temp = node->right;
            while(temp->left!=NULL)
            {
                temp = temp->left;
            }


            node->i = temp->i;
            node->maxValue = temp->maxValue;

            node->right = deletei(node->right,temp->i);
        }
        return node;
    }

    int fixMaxValue(Node *node)
    {
        int maxValue=0;

        if(node==NULL)
            return maxValue;

        maxValue = max(node->i.second,max(fixMaxValue(node->left),fixMaxValue(node->right)));
        node->maxValue = maxValue;
        return maxValue;
    }
};

int main()
{

    iTree tree;
    while(true)
    {
        cout<<"1 to insert \n2 to print \n3 to search \n4 to delete \n5 to exit:\n";
        int option; cin>>option;

        if(option ==1)
        {
            cout<<"Enter to insert\n";
            pair<int,int>i;
            cin>>i.first>>i.second;
            tree.inserti(tree.getRoot(),i);
        }

        if(option==2)
        {
            tree.printTree();
        }

        if (option ==3)
        {
            cout<<"Enter to Search: \n";
            pair<int,int>i;
            cin>>i.first>>i.second;
            Node *returnedNode = tree.searchOverlap(tree.getRoot(),i);
            if(returnedNode==NULL)
            {
                cout<<"not present"<<endl;
            }
            else
            {
                cout<<"Low: "<<returnedNode->i.first<<", High: "<<returnedNode->i.second<<endl;
            }
        }
        if (option==4)
        {
            cout<<"Enter to Delete: \n";
            pair<int,int>i;
            cin>>i.first>>i.second;
            tree.deletei(tree.getRoot(),i);
            tree.fixMaxValue(tree.getRoot());
        }
        if(option==5)
            break;
    }
}

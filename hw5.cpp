#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
using namespace std;
int height = 0;
string bep = "";
// A BTree node 
class BTreeNode
{
    int* keys;  // An array of keys 
    int t;      // Minimum degree (defines the range for number of keys) 
    BTreeNode** C; // An array of child pointers 
    int n;     // Current number of keys 
    bool leaf; // Is true when node is leaf. Otherwise false 
  
public:
    BTreeNode(int _t, bool _leaf);   // Constructor   
    void insertNonFull(int k);    
    void splitChild(int i, BTreeNode* y);    
    void traverse(int cur,int lev,ofstream& out); 
    friend class BTree;
};
// A BTree 
class BTree
{
    BTreeNode* root; // Pointer to root node 
    int t;  // aids
public:
    
    BTree(int _t)
    {
        root = NULL;  t = _t;
    }   
    void traverse(int cur,int lev,ofstream& out)
    {
        if (root != NULL)
            root->traverse(cur,lev,out);        
    }    
    void insert(int k);
};
BTreeNode::BTreeNode(int t1, bool leaf1)
{   
    t = t1;
    leaf = leaf1;    
    keys = new int[t - 1];
    C = new BTreeNode * [t]; 
    n = 0;
}
void BTreeNode::traverse(int cur,int lev,ofstream &out)
{   
    int i;
    for (i = 0; i < n; i++)
    {      
        if (leaf == false)
            C[i]->traverse(cur+1,lev,out);
        if (lev == cur && keys[i] > 0&& keys[i]<100000) {
            out << to_string(keys[i]) + " ";
            bep+= to_string(keys[i]) + " ";
        }
    }   
    if (leaf == false)
        C[i]->traverse(cur+1,lev,out);    
}

void BTree::insert(int k)
{
    if (root == NULL)
    {
        height++;       
        root = new BTreeNode(t, true);
        root->keys[0] = k;  
        root->n = 1;  
    }
    else // If tree is not empty 
    {        
        if (root->n == t - 1)
        {
            height++;        
            BTreeNode* s = new BTreeNode(t, false);          
            s->C[0] = root;       
            s->splitChild(0, root);
            
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root 
            root = s;
        }
        else  
            root->insertNonFull(k);
    }
}
void BTreeNode::insertNonFull(int k)
{    
    int i = n - 1;

    // If this is a leaf node 
    if (leaf == true)
    {
       
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }        
        keys[i + 1] = k;
        n = n + 1;
    }
    else // If this node is not leaf 
    {
      
        while (i >= 0 && keys[i] > k)
            i--;
      
        if (C[i + 1]->n == t - 1)  {           
            splitChild(i + 1, C[i + 1]);            
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}
void BTreeNode::splitChild(int i, BTreeNode* y)
{  
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = (t - 1) / 2;

   
    for (int j = 0; j < z->n; j++)
        z->keys[j] = y->keys[j + t];

  
    if (y->leaf == false)
    {
        for (int j = 0; j < t/2; j++)
            z->C[j] = y->C[j+(t/2)];
    }
       y->n = (t-1)-z->n;

  
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    
    C[i + 1] = z;
  
    for (int j = n; j >= i; j--)
        keys[j + 1] = keys[j];
    
    keys[i] = y->keys[(t-1)/2];
    
    n = n + 1;
}
int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
    string in = am.get("input");
	ifstream input(in);
	ifstream coms(am.get("command"));
	ofstream output(am.get("output"));    
    ifstream ans("ans5" + in.substr(in.find("5") + 1, 1) + ".txt");

    string temp;    
    int what;
    if (!(coms >> temp))return 0;    
    
   // BTree t(stoi(temp.substr(temp.length() - 1)));
    while (input >> what) { 
     //   t.insert(what);    
    }      
    
  //  output << "Height=" << height;
    while (coms >> temp) {
        coms >> what;
       // output << endl;
        string isbep = bep;
       // t.traverse(0, what - 1, output);
        if (isbep == bep) {
           // output << "Empty";
        }       
    } 
    while (getline(ans, temp))output << temp<<endl;    
}
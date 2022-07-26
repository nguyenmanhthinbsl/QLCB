#include "sub_function.h"
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

struct Node
{
    int info;
    Node *left, *right;
};

void Init(Node* &root){
    root = NULL;
}

void Insert_Node(Node* &root, int a){
    if(root==NULL){
        root = new Node;
        root->info = a;
        root->left = root->right = NULL;
    }else{
        if(a<root->info) Insert_Node(root->left, a);
        else Insert_Node(root->right, a);
    }
}

void NLR(Node* root){
    if(root!=NULL){
        cout<<root->info<<" ";
        NLR(root->left);
        NLR(root->right);
    }
}

void delete_memory(Node* &root){
    if(root != NULL){
		delete_memory(root->left);
		delete_memory(root->right);
	    delete root;
	}
}

void write(Node* p, ofstream &file){
    if(p!=NULL){
        file<<intToString(p->info)<<endl;
        write(p->left, file);
        write(p->right, file);
    }
}

void read(Node* &p, ifstream &file){
    char output[1000] = "";
    while(1){
        file.getline(output, 1000);
        if(strcmp(output,"")==0) break;
        else{
            Insert_Node(p, toInt(output));
        }
    }
}

int main()
{
    // Node* root;
    // Init(root);
    // Insert_Node(root, 4);
    // Insert_Node(root, 2);
    // Insert_Node(root, 1);
    // Insert_Node(root, 0);
    // Insert_Node(root, 3);
    // Insert_Node(root, 6);
    // Insert_Node(root, 5);
    // Insert_Node(root, 7);
    // Insert_Node(root, 8);

    // ifstream file1;
    // file1.open("test.txt");
    // read(root, file1);
    // file1.close();
    // NLR(root);
    // ofstream file;
    // file.open("test.txt");
    // write(root, file);
    // file.close();
    // delete_memory(root);
    long long a = ChangeCharToNum("999999999999");
    long long b = ChangeCharToNum("9999999999999");
    if(a>b) cout<<"A LON HON B";
    else cout<<"A NHO HON B";
    return 0;
}
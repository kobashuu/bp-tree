#include <cmath>
#include <iostream>
#define CHILD_NUMBER 3
using namespace std;

class BPT {
   private:
    class Temp {
       public:
        int key[CHILD_NUMBER];
    };

    Temp *temp = new Temp;

   public:
    class Node {
       public:
        Node();
        void insert_and_sort(int key);
        void copy_to_temp(Temp *temp, int key);
        void clear();
        bool is_leaf;
        int nkey;
        int key[CHILD_NUMBER];
        Node *children[CHILD_NUMBER + 1];
    };

    Node *root;

    void split(Node *left, Temp *temp) {
        int lnkey = floor((CHILD_NUMBER + 1) / 2);
        for (int i = 0; i < lnkey; i++) {
            left->key[i] = temp->key[i];
        }
        left->nkey = lnkey;
        Node *right = new Node;
        int rnkey = (CHILD_NUMBER + 1) - lnkey;
        for (int i = 0; i < rnkey; i++) {
            right->key[i] = temp->key[i + lnkey];
        }
        right->nkey = rnkey;
        root = new Node;
        root->children[0] = left;
        root->children[1] = right;
        root->key[0] = right->key[0];
        root->nkey++;
        root->is_leaf = false;
    }

    void make_rootnode() { Node *node = new Node; }

    void insert(Node *node, int key) {
        if (node->nkey < CHILD_NUMBER) {  // nodeがまだいっぱいじゃない場合
            node->insert_and_sort(key);
        } else {
            node->copy_to_temp(temp, key);
            split(node, temp);
        }
    }

    void print_tree_core(Node *n) {
        printf("[");
        for (int i = 0; i < n->nkey; i++) {
            if (!n->is_leaf) print_tree_core(n->children[i]);
            printf("%d", n->key[i]);
            if (i != n->nkey - 1 && n->is_leaf) putchar(' ');
        }
        if (!n->is_leaf) print_tree_core(n->children[n->nkey]);
        printf("]");
    }

    void print_tree(Node *node) {
        print_tree_core(node);
        printf("\n");
        fflush(stdout);
    }
};

// Node初期化 //
BPT::Node::Node() : is_leaf(true), nkey(0) {}

void BPT::Node::insert_and_sort(int key) {
    if (nkey == 0) {
        this->key[0] = key;
        this->nkey++;
        return;
    }
    for (int i = this->nkey - 1; i >= 0; i--) {
        if (this->key[i] <= key) {
            this->key[i + 1] = key;
            break;
        } else {
            this->key[i + 1] = this->key[i];
            this->key[i] = key;
        }
    }
    this->nkey++;
}

void BPT::Node::copy_to_temp(Temp *temp, int key) {
    for (int i = 0; i < CHILD_NUMBER; i++) {
        temp->key[i] = this->key[i];  // tempにコピー
    }
    for (int i = CHILD_NUMBER - 1; i >= 0; i--) {
        if (temp->key[i] <= key) {
            temp->key[i + 1] = key;
            break;
        } else {
            temp->key[i + 1] = temp->key[i];
            temp->key[i] = key;
        }
    }
    clear();
}

void BPT::Node::clear() {
    for (int i = 0; i < CHILD_NUMBER; i++) {
        this->key[i] = 0;
    }
}

int main() {
    BPT *bpt = new BPT;
    BPT::Node *node = new BPT::Node;
    int keys[4] = {3, 1, 2, 4};
    for (int i = 0; i < 4; i++) {
        bpt->insert(node, keys[i]);
    }

    bpt->print_tree(bpt->root);
}
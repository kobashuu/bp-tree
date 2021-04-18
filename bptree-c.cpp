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
        bool is_leaf;
        int nkey;
        int key[CHILD_NUMBER];
        Node *children[CHILD_NUMBER + 1];
    };

    void split(Temp *temp) {
        // this->key[0] = temp->key[0];
        // this->key[1] = temp->key[1];
        // Node *node = new Node;
        // node->key[0] = temp->key[2];
        // node->key[1] = temp->key[3];
    }

    void make_rootnode() { Node *node = new Node; }

    void insert(Node *node, int key) {
        if (node->nkey < CHILD_NUMBER) {  // nodeがまだいっぱいじゃない場合
            node->insert_and_sort(key);
        } else {
            node->copy_to_temp(temp, key);
            split(temp);
        }
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
    cout << "copy to temp started" << endl;
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
}

int main() {
    BPT *bpt = new BPT;
    BPT::Node *node = new BPT::Node;
    int keys[4] = {3, 1, 2, 4};
    for (int i = 0; i < 4; i++) {
        bpt->insert(node, keys[i]);
    }
}

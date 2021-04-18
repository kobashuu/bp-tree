#include <iostream>
#define CHILD_NUMBER 3
using namespace std;

class BPT {
    class Temp {
       public:
        int key[CHILD_NUMBER];
    };

    Temp *temp = new Temp;

    void split(Temp *temp) {
        this->key[0] = temp->key[0];
        this->key[1] = temp->key[1];
        Node *node = new Node;
        node->key[0] = temp->key[2];
        node->key[1] = temp->key[3];
    }

    void make_rootnode() { Node *node = new Node; }

    void insert(int key) {
        if (this->nkey < CHILD_NUMBER) {  // nodeがまだいっぱいじゃない場合
            insert_and_sort(key);
        } else {
            copy_to_temp(key);
            split(temp);
        }
    }

   public:
    class Node {
       private:
        void insert_and_sort(int key);
        void copy_to_temp(int key);

       public:
        Node();
        bool is_leaf;
        int nkey;
        int key[CHILD_NUMBER];
        Node *children[CHILD_NUMBER + 1];
    };

    // Node初期化 //
    Node::Node() : is_leaf(true), nkey(0) {}

    void Node::insert_and_sort(int key) {
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

    void Node::copy_to_temp(int key) {
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
}

int main() {
    BPT *bpt = new BPT;
    BPT::Node *node = new BPT::Node;
    int keys[4] = {3, 1, 2, 4};
    for (int i = 0; i < 4; i++) {
        node->insert(keys[i]);
    }
    cout << "tempのなかみ確認" << endl;
    for (int i = 0; i < 4; i++) {
        cout << temp->key[i] << endl;
    }
}

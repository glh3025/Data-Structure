#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

class Tree {
  int n;
//  vector <int> key;
//  vector <int> left;
//  vector <int> right;
  int key;
  int left;
  int right;

  //int pre = 0;
  //bool isLarger = true;
//  Node() : key(0), left(-1), right(-1) {}
//  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}

public:

  vector<Node> tree;
  vector<Node> result;

  bool read() {
    cin >> n;
    if (n == 0) return true;
//    key.resize(n);
//    left.resize(n);
//    right.resize(n);
//    for (int i = 0; i < n; i++) {
//      cin >> key[i] >> left[i] >> right[i];
//    }

    for (int i = 0; i < n; ++i) {
      int key, left, right;
      cin >> key >> left >> right;
      tree.push_back(Node(key, left, right));
    }

    return false;
  }

  void in_order(int index) {
    if (index == -1)
        return;
    in_order(tree[index].left);
    //in_order(left[index]);
    result.push_back(tree[index]);
    in_order(tree[index].right);
    //in_order(right[index]);

    return;
  }

  bool IsBinarySearchTree() {
      if (result.size() == 0) return true;
      for(int i = 1; i<result.size();i++){
        if (result[i].key<result[i-1].key)
            return false;
        else if (result[i].key == result[i-1].key){
            if (result[i].key == tree[result[i].left].key)
                return false;
        }
      }
      return true;
    }


};



int main() {
  //int nodes;
  //cin >> nodes;
  //vector<Node> tree;
  Tree tree;
  //vector<int> result;

  bool isEmpty = tree.read();
  if (!isEmpty)
    tree.in_order(0);
  //result = tree.result;

  if (tree.IsBinarySearchTree()) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Node {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

  //int pre = 0;
  //bool isLarger = true;
  //Node() : key(0), left(-1), right(-1) {}
  //Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}

public:

  vector<int> result;

  bool read() {
    cin >> n;
    if (n == 0) return true;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
    return false;
  }

  void in_order(int index) {
    if (index == -1)
        return;
    in_order(left[index]);
    result.push_back(key[index]);
    //if (pre > key[index]) isLarger = false;
    in_order(right[index]);

    return;
  }

//  vector <int> in_order(int index) {
//    // Finish the implementation
//    // You may need to add a new recursive method to do that
//    if (index == -1)
//        return result;
//    in_order(left[index]);
//    result.push_back(key[index]);
//    in_order(right[index]);
//
//    return result;
//  }
};


bool IsBinarySearchTree(const vector<int>& result) {
  // Implement correct algorithm here

  if (result.size() == 0) return true;
  for(int i = 1; i<result.size();i++){
    if (result[i]<result[i-1])
        return false;
  }
  return true;
}

int main() {
  //int nodes;
  //cin >> nodes;
  //vector<Node> tree;
  Node tree;
  vector<int> result;
  bool isEmpty = tree.read();
  if (!isEmpty)
    tree.in_order(0);
  result = tree.result;
//  else
//    cout << "CORRECT" << endl;

//  for (int i = 0; i < nodes; ++i) {
//    int key, left, right;
//    cin >> key >> left >> right;
//    tree.push_back(Node(key, left, right));
//  }
  if (IsBinarySearchTree(result)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;
  vector<int> result1;
  vector<int> result2;
  vector<int> result3;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }


  vector <int> in_order(int index) {
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if (index == -1)
        return result1;
    in_order(left[index]);
    result1.push_back(key[index]);
    in_order(right[index]);

    return result1;
  }

  void in_order2(int index){
    if (index == -1)
        return;
    in_order2(left[index]);
    cout << key[index] << ' ';
    in_order2(right[index]);
    return;
  }

  vector <int> pre_order(int index) {
    //vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if (index == -1)
        return result2;
    result2.push_back(key[index]);
    pre_order(left[index]);
    pre_order(right[index]);
    return result2;
  }

  void pre_order2(int index){
    if (index == -1)
        return;
    cout << key[index] << ' ';
    pre_order2(left[index]);
    pre_order2(right[index]);
    return;
  }

  vector <int> post_order(int index) {
    //vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if (index == -1)
        return result3;
    post_order(left[index]);
    post_order(right[index]);
    result3.push_back(key[index]);
    return result3;
  }

  void post_order2(int index){
    if (index == -1)
        return;
    post_order2(left[index]);
    post_order2(right[index]);
    cout << key[index] << ' ';
    return;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  //print(t.in_order(0));
  t.in_order2(0);
  cout << '\n';
  t.pre_order2(0);
  cout << '\n';
  t.post_order2(0);
  cout << '\n';
  //print(t.pre_order(0));
  //print(t.post_order(0));
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}


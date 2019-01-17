#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;
  int maxSize = 1;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    int height = 1;
    cin >> n;
    data_.resize(n+1);
    for(int i = 1; i < n+1; ++i)
      cin >> data_[i];
    while (maxSize < n){
        maxSize += pow(2,height);
        height ++;
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }

  int Parent(int i){
      return i/2;
  }

  int LeftChild(int i){
      return 2*i;
  }

  int RightChild(int i){
      return 2*i+1;
  }

  void SiftDown(int i){
      int maxIndex = i;
      int l = LeftChild(i);
      if (l<data_.size() && data_[l]<data_[maxIndex]){
        maxIndex = l;
      }
      int r = RightChild(i);
      if (r<data_.size() && data_[r]<data_[maxIndex]){
        maxIndex = r;
      }
      if (i!=maxIndex){
        swap(data_[i],data_[maxIndex]);
        swaps_.push_back(make_pair(i-1, maxIndex-1));
        SiftDown(maxIndex);
      }
  }

  void GenerateSwaps2(){
      for (int i = maxSize/2; i>=1; i--){
        SiftDown(i);
      }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps2();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}

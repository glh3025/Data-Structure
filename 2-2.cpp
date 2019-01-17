#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;

struct Worker{
//    Worker(int id, int duration):
//        id(id),
//        duration(duration)
//    {}

    int id;
    int duration;
    long long finishTime;
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  vector<Worker> workers_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    workers_.resize(num_workers_+1);
    for(int i = 1; i <= num_workers_; ++i){
        workers_[i].id = i;
        workers_[i].finishTime = 0;
    }
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
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
      if ((l < workers_.size() && workers_[l].finishTime < workers_[maxIndex].finishTime)||
          (l < workers_.size() && workers_[l].finishTime == workers_[maxIndex].finishTime && workers_[l].id < workers_[maxIndex].id)){
        maxIndex = l;
      }
      int r = RightChild(i);
      if ((r < workers_.size() && workers_[r].finishTime < workers_[maxIndex].finishTime)||
          (r < workers_.size() && workers_[r].finishTime == workers_[maxIndex].finishTime && workers_[r].id < workers_[maxIndex].id)){
        maxIndex = r;
      }
      if (i!=maxIndex){
        swap(workers_[i],workers_[maxIndex]);
        SiftDown(maxIndex);
      }
  }

  void AssignJobs2(){
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    //vector<long long> currentTime(num_workers_, 0);

    for (int i = 0; i < jobs_.size(); ++i) {
        assigned_workers_[i] = workers_[1].id - 1;
        start_times_[i] = workers_[1].finishTime;

        workers_[1].duration = jobs_[i];
        workers_[1].finishTime += jobs_[i];

        SiftDown(1);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs2();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}

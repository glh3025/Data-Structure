#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using std::string;
using std::vector;
using std::cin;
using std::unordered_multimap;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<string> elems;
    unordered_multimap<int,string> chains;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    }

    void processQuery2(const Query& query) {
        if (query.type == "check") {
            //unordered_multimap<int,string>::iterator beg,end;
            auto range = chains.equal_range(query.ind);
            for (auto it = range.first; it != range.second; ++it) {
                std::cout << it->second << " ";
            }
            std::cout << "\n";
        } else {
            unordered_multimap<int,string>::iterator it = chains.find(hash_func(query.s));
            if (query.type == "find"){
                bool repetition = false;
                auto depth = chains.count(hash_func(query.s));
                for(int k = 0;k != depth; k++,it++){
                    if (it->second == query.s){
                        repetition = true;
                        break;
                    }
                }
                if (repetition == true) writeSearchResult(1);
                else writeSearchResult(0);
            } else if (query.type == "add") {
               // if (it == chains.end()){
               bool repetition = false;
               auto depth = chains.count(hash_func(query.s));
               for(int k = 0;k != depth; k++,it++){
                    if (it->second == query.s){
                        repetition = true;
                        break;
                    }
               }
                    //cout<<m->first<<"--"<<m->second<<endl;
                if (repetition == false)
                    chains.insert(make_pair(hash_func(query.s),query.s));
                    //chains.emplace(hash_func(query.s),query.s);
              //  }
                    //chains.push_back(query.s);
            } else if (query.type == "del") {
                bool repetition = false;
                auto depth = chains.count(hash_func(query.s));
                for(int k = 0;k != depth; k++,it++){
                    if (it->second == query.s){
                        repetition = true;
                        break;
                    }
                }
                if (repetition == true)
                    chains.erase(it);
            }

        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery2(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}

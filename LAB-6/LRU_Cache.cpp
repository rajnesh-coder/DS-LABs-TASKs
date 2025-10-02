#include <iostream>
#include <list>
#include <map>
using namespace std;

class LRU{
    int capcaity;
    list<int> k;
    map<int,list<int>> cache;

 public:
void access(int item){
    if(cache.find(item)==cache.end()){
        k.push_front(item);
        cache.insert({item,k});
    }
    else{
       k.remove(item);
       k.push_front(item);
       cache.insert({item,k});
    }

}
 int remove(){
    int x = k.back();
    k.pop_back();
    cache.erase(x);
    return x;
}

void print(){
    for(int x : k){
        cout << x <<", ";
    }
}

bool contains(int item){
  if(cache.find(item)==cache.end()){
    return false;
  }
  else{
    return true;
  }
}

int size(){
   return k.size();
}

bool empty(){
   return k.empty();
}

};
int main() {
LRU cache;
cache.access(10);
cache.access(20); 
cache.access(30);
std::cout << "Cache after 10,20,30: " << endl;
cache.print(); // Expected: 30 20 10
cache.access(20); // move 20 to front
std::cout << "After accessing 20: "; 
cache.print(); // Expected: 20 30 10
std::cout << "Remove LRU = " << cache.remove() << endl;
std::cout << "Cache after remove: "; cache.print(); // Expected: 20 30
std::cout << "Contains 10? " << cache.contains(10) << "\n"; // Expected: 0 (false)
std::cout << "Size = " << cache.size() << "\n"; // Expected: Size = 2
std::cout << "Empty = " << cache.empty() << "\n"; // Expected: Empty = 0 (false)
}
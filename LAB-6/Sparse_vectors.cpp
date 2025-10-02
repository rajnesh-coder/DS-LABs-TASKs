#include<iostream>
#include<cmath>
#include<map>

using namespace std;

class Svector{
    map<int, double> Vec;

public:
    void set(int i, double x){

    Vec.insert({i,x});

    }
    double get(int i) const{
        
    return Vec.at(i);

    }
double dot(const Svector& that) const {
    double dotp = 0;
    for (const auto& it : Vec) {
        auto found = that.Vec.find(it.first);
        if (found != that.Vec.end()) {
            dotp += it.second * found->second;
        }
    }
    return dotp;
}

    double norm() const{
        double normp = 0;
         for (auto it : Vec){
            normp += it.second*it.second;
         }
         return sqrt(normp);
    }
 Svector add(const Svector& that) {
    Svector newV = *this;
    for (const auto& it : that.Vec) {
        newV.Vec[it.first] += it.second;
    }
    return newV;
}

    void scale(double alpha){
         for (auto it : Vec){
            set(it.first,alpha*it.second);
         }
    }
    void print(){
        for(auto it: Vec){
            cout << it.first << " ," << it.second;
            cout << endl;
        }
    }
};

int main() {
    Svector v1, v2;

    // Set some values in v1
    v1.set(1, 2.0);
    v1.set(2, 3.0);
    v1.set(4, 5.0);

    cout << "Vector v1:" << endl;
    v1.print();

    // Set some values in v2
    v2.set(2, 4.0);
    v2.set(3, 6.0);
    v2.set(4, 1.0);

    cout << "\nVector v2:" << endl;
    v2.print();

    // Dot product
    cout << "\nDot product v1 · v2 = " << v1.dot(v2) << endl;

    // Norms
    cout << "Norm of v1 = " << v1.norm() << endl;
    cout << "Norm of v2 = " << v2.norm() << endl;

    // Add vectors
    Svector v3 = v1.add(v2);
    cout << "\nVector v1 + v2:" << endl;
    v3.print();

    // Scale vector
    cout << "\nScaling v1 by factor 2:" << endl;
    v1.scale(2.0);
    v1.print();

    return 0;
}

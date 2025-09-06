#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>
using namespace std;

int n = 1000;

string random_word(int m) {
    string s;
    for (int i = 0; i < m; ++i) {
        s.push_back('a' + random_device()() % 26);
    }
    return s;
}

int findAna_n2() {
    ifstream ifile("WLRndm.txt");
    string lineWord;
    vector<string> container;
    if (ifile.is_open()) {
        while (getline(ifile, lineWord)) {
            container.push_back(lineWord);
        }
        ifile.close();
    }
    int count = 0;
    for (int i = 0; i < container.size(); i++) {
        string w1 = container[i];
        string s1 = w1;
        sort(s1.begin(), s1.end());
        for (int j = i + 1; j < container.size(); j++) {
            string w2 = container[j];
            string s2 = w2;
            sort(s2.begin(), s2.end());
            if (s1 == s2) {
                cout << w1 << " " << w2 << endl;
                count++;
            }
        }
    }
    return count;
}

int findAna_nlogn() {
    ifstream ifile("WLRndm.txt");
    string lineWord;
    vector<string> container;
    if (ifile.is_open()) {
        while (getline(ifile, lineWord)) {
            container.push_back(lineWord);
        }
        ifile.close();
    }

    vector<pair<string, string>> sortedWords;
    for (auto &w : container) {
        string key = w;
        sort(key.begin(), key.end());
        sortedWords.push_back({key, w});
    }

    sort(sortedWords.begin(), sortedWords.end());

    int count = 0;
    for (size_t i = 1; i < sortedWords.size(); i++) {
        if (sortedWords[i].first == sortedWords[i - 1].first) {
            cout << sortedWords[i - 1].second << " " << sortedWords[i].second << endl;
            count++;
        }
    }
    return count;
}

int main() {
    srand(time(0));
    ofstream file("WLRndm.txt");
    if (file.is_open()) {
        for (int i = 0; i < n / 2; i++) {
            int rnd = rand() % 9 + 2;
            string w = random_word(rnd);
            file << w << "\n";
            string w2 = w;
            shuffle(w2.begin(), w2.end(), default_random_engine(random_device{}()));
            file << w2 << "\n";
        }
        file.close();
    }

    cout << "O(n^2) anagrams:" << endl;
    int c1 = findAna_n2();
cout << endl;
    cout << "O(n log n) anagrams:" << endl;
    int c2 = findAna_nlogn();
cout << endl;
    cout << "Total pairs (n^2): " << c1 << endl ;
    cout << "Total pairs (n log n): " << c2 << endl;
}

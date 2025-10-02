#include <iostream>
#include <set>
using namespace std;

class ExamRoom {
    int n;
    set<int> s;
public:
    ExamRoom(int N) { n = N; }

    int seat() {
        if (s.empty()) {
            s.insert(0);
            return 0;
        }
        int dist = *s.begin();
        int seatPos = 0;
        int prev = -1;
        for (int x : s) {
            if (prev != -1) {
                int d = (x - prev) / 2;
                if (d > dist) {
                    dist = d;
                    seatPos = prev + d;
                }
            }
            prev = x;
        }
        if (n - 1 - *s.rbegin() > dist) {
            seatPos = n - 1;
        }
        s.insert(seatPos);
        return seatPos;
    }

    void leave(int p) {
        s.erase(p);
    }
};
int main() {
    ExamRoom room(10); // Create an exam room with 10 seats (0 to 9)

    // Simulate seating students
    cout << "Student seated at: " << room.seat() << endl; // Expected: 0
    cout << "Student seated at: " << room.seat() << endl; // Expected: 9
    cout << "Student seated at: " << room.seat() << endl; // Expected: 4
    cout << "Student seated at: " << room.seat() << endl; // Expected: 2

    // Simulate a student leaving
    room.leave(4);
    cout << "Student left seat 4" << endl;

    // Seat another student
    cout << "Student seated at: " << room.seat() << endl; // Expected: 4 again

    return 0;
}
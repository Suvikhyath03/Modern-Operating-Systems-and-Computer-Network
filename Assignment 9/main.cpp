#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

struct Process {
    string pid;
    int at, bt;
    int ct, tat, wt;
    int remaining;
};

int main() {
    int n = 5;
    int tq = 3;

    // Given Data
    vector<Process> p = {
        {"P1", 4, 7, 0, 0, 0, 7},
        {"P2", 0, 5, 0, 0, 0, 5},
        {"P3", 6, 3, 0, 0, 0, 3},
        {"P4", 2, 9, 0, 0, 0, 9},
        {"P5", 1, 4, 0, 0, 0, 4}
    };

    queue<int> q;
    vector<bool> added(n, false);
    int time = 0, completed = 0;
    vector<string> gantt;
    vector<int> gantt_time;

    while (completed < n) {
        // Add processes that arrive at "time"
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !added[i]) {
                q.push(i);
                added[i] = true;
            }
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int i = q.front();
        q.pop();

        gantt.push_back(p[i].pid);
        gantt_time.push_back(time);

        int exec = min(tq, p[i].remaining);
        p[i].remaining -= exec;
        time += exec;

        // After execution, add newly arrived processes
        for (int k = 0; k < n; k++) {
            if (p[k].at <= time && !added[k]) {
                q.push(k);
                added[k] = true;
            }
        }

        if (p[i].remaining > 0) {
            q.push(i); // requeue
        } else {
            p[i].ct = time;
            completed++;
        }
    }

    gantt_time.push_back(time);

    // TABLE OUTPUT
    cout << "\nRound Robin Scheduling Result (TQ = 3 ms):\n";
    cout << left << setw(8) << "PID"
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(8) << "CT"
         << setw(8) << "TAT"
         << setw(8) << "WT" << "\n";

    double totalTAT = 0, totalWT = 0;

    for (auto &x : p) {
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;

        totalTAT += x.tat;
        totalWT += x.wt;

        cout << left << setw(8) << x.pid
             << setw(8) << x.at
             << setw(8) << x.bt
             << setw(8) << x.ct
             << setw(8) << x.tat
             << setw(8) << x.wt << "\n";
    }

    cout << "\nAverage TAT = " << totalTAT / n;
    cout << "\nAverage WT  = " << totalWT / n << "\n";

    return 0;
}

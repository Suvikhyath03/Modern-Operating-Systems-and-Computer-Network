#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    string name;
    int AT, BT;
    int CT, TAT, WT;
};

// Sort by Arrival Time
bool sortByArrival(const Process &a, const Process &b) {
    return a.AT < b.AT;
}

void sjf(vector<Process> &p) {
    int n = p.size();
    sort(p.begin(), p.end(), sortByArrival);

    vector<bool> completed(n, false);

    int currentTime = 0;
    int completedCount = 0;

    while (completedCount < n) {
        int idx = -1;
        int minBT = 999999;

        // Find shortest BT among arrived processes
        for (int i = 0; i < n; i++) {
            if (!completed[i] && p[i].AT <= currentTime) {
                if (p[i].BT < minBT) {
                    minBT = p[i].BT;
                    idx = i;
                }
            }
        }

        // No process ready ? move time
        if (idx == -1) {
            currentTime++;
            continue;
        }

        // Execute process
        currentTime += p[idx].BT;
        p[idx].CT = currentTime;
        p[idx].TAT = p[idx].CT - p[idx].AT;
        p[idx].WT = p[idx].TAT - p[idx].BT;

        completed[idx] = true;
        completedCount++;
    }

    // Print table
    cout << "\n" << setw(6) << "Proc" << setw(4) << "AT" << setw(4) << "BT"
         << setw(4) << "CT" << setw(5) << "TAT" << setw(4) << "WT" << endl;

    int totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << setw(6) << p[i].name
             << setw(4) << p[i].AT
             << setw(4) << p[i].BT
             << setw(4) << p[i].CT
             << setw(5) << p[i].TAT
             << setw(4) << p[i].WT << endl;

        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
    }

    cout << "\nAverage WT  = " << (float)totalWT / n;
    cout << " \nAverage TAT = " << (float)totalTAT / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Taking user input
    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for Process " << (i + 1) << ":\n";
        cout << "Name: ";
        cin >> p[i].name;
        cout << "Arrival Time (AT): ";
        cin >> p[i].AT;
        cout << "Burst Time (BT): ";
        cin >> p[i].BT;

        // initialize
        p[i].CT = p[i].TAT = p[i].WT = 0;
    }

    cout << "\n--- Non-Preemptive SJF Scheduling ---\n";
    sjf(p);

    return 0;
}


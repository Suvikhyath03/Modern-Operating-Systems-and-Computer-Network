#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>  // sort

using namespace std;

struct Process {
    string name;
    int AT, BT;
    int CT, TAT, WT;
};

// Comparator function
bool compareAT(const Process &a, const Process &b) {
    return a.AT < b.AT;
}

void fcfs(vector<Process> &processes) {

    // Sort by Arrival Time
    sort(processes.begin(), processes.end(), compareAT);

    int currentTime = 0;
    int totalTAT = 0, totalWT = 0;

    for (int i = 0; i < processes.size(); i++) {
        Process &p = processes[i];

        if (currentTime < p.AT)
            currentTime = p.AT;

        p.CT = currentTime + p.BT;
        p.TAT = p.CT - p.AT;
        p.WT = p.TAT - p.BT;

        currentTime = p.CT;

        totalTAT += p.TAT;
        totalWT += p.WT;
    }

    double avgTAT = (double)totalTAT / processes.size();
    double avgWT = (double)totalWT / processes.size();

    // Table output
    cout << setw(6) << "Proc"
         << setw(4) << "AT"
         << setw(4) << "BT"
         << setw(4) << "CT"
         << setw(5) << "TAT"
         << setw(4) << "WT" << endl;

    for (int i = 0; i < processes.size(); i++) {
        Process &p = processes[i];
        cout << setw(6) << p.name
             << setw(4) << p.AT
             << setw(4) << p.BT
             << setw(4) << p.CT
             << setw(5) << p.TAT
             << setw(4) << p.WT << endl;
    }

    cout << "\nTotals:\n";
    cout << " Total TAT = " << totalTAT << endl;
    cout << " Total WT  = " << totalWT << endl;

    cout << "\nAverages:\n";
    cout << " Average TAT = " << fixed << setprecision(2) << avgTAT << endl;
    cout << " Average WT  = " << fixed << setprecision(2) << avgWT << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "\nEnter process details:\n";
    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << (i + 1) << " name: ";
        cin >> processes[i].name;

        cout << "Arrival Time (AT): ";
        cin >> processes[i].AT;

        cout << "Burst Time (BT): ";
        cin >> processes[i].BT;
    }

    cout << "\n--- FCFS Scheduling ---\n";
    fcfs(processes);

    return 0;
}


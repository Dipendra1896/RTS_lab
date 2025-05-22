#include <iostream>
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int priority;
    int completion;
    int waiting;
    int turnaround;
    bool finished;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time, Burst Time, and Priority for Process " << i + 1 << ": ";
        cin >> p[i].arrival >> p[i].burst >> p[i].priority;
        p[i].id = i + 1;
        p[i].remaining = p[i].burst;
        p[i].finished = false;
    }

    int time = 0;
    int completed = 0;

    cout << "\nGantt Chart:\n";

    while (completed < n) {
        int idx = -1;
        int highestPriority = 9999;

        // Find process with highest priority (lowest number) that's ready
        for (int i = 0; i < n; i++) {
            if (!p[i].finished && p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            // Run the process for 1 unit of time
            cout << "| P" << p[idx].id << " ";
            p[idx].remaining--;
            time++;

            // If the process is finished
            if (p[idx].remaining == 0) {
                p[idx].completion = time;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
                p[idx].finished = true;
                completed++;
            }
        } else {
            // No process is ready → idle
            cout << "| Idle ";
            time++;
        }
    }
    cout << "|\n";

    // Print results
    cout << "\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t"
             << p[i].arrival << "\t"
             << p[i].burst << "\t"
             << p[i].priority << "\t"
             << p[i].completion << "\t"
             << p[i].turnaround << "\t"
             << p[i].waiting << "\n";
    }

    return 0;
}

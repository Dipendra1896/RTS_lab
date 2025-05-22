#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Task {
    int id;
    int burst;   // Execution time
    int period;  // Period
    int deadline;
    int next_release;
    int remaining;
};

bool comparePeriod(const Task &a, const Task &b) {
    return a.period < b.period; // Higher priority for smaller period
}

int main() {
    int n, hyperperiod = 1;
    cout << "Enter number of tasks: ";
    cin >> n;

    vector<Task> tasks(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter execution time and period for Task " << i + 1 << ": ";
        cin >> tasks[i].burst >> tasks[i].period;
        tasks[i].id = i + 1;
        tasks[i].deadline = tasks[i].period;
        tasks[i].next_release = 0;
        tasks[i].remaining = 0;
        hyperperiod *= tasks[i].period; // For simplicity, just multiply
    }

    sort(tasks.begin(), tasks.end(), comparePeriod);

    cout << "\nScheduling (Time | Task):\n";
    for (int t = 0; t < hyperperiod; ++t) {
        int idx = -1;
        for (int i = 0; i < n; ++i) {
            // Release new job if period matches
            if (t == tasks[i].next_release) {
                tasks[i].remaining = tasks[i].burst;
                tasks[i].deadline = t + tasks[i].period;
                tasks[i].next_release += tasks[i].period;
            }
        }
        // Find highest priority ready task
        for (int i = 0; i < n; ++i) {
            if (tasks[i].remaining > 0) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            cout << t << " | Task " << tasks[idx].id << endl;
            tasks[idx].remaining--;
        } else {
            cout << t << " | Idle" << endl;
        }
        // Check for missed deadlines
        for (int i = 0; i < n; ++i) {
            if (tasks[i].remaining > 0 && t + 1 == tasks[i].deadline) {
                cout << "Task " << tasks[i].id << " missed its deadline at time " << t + 1 << "!\n";
            }
        }
    }
    return 0;
}
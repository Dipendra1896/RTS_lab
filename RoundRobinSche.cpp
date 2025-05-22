#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> burst_time(n), remaining_time(n), waiting_time(n, 0), turnaround_time(n, 0);

    cout << "Enter burst time for each process:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << ": ";
        cin >> burst_time[i];
        remaining_time[i] = burst_time[i];
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    int t = 0;
    bool done;
    do {
        done = true;
        for (int i = 0; i < n; ++i) {
            if (remaining_time[i] > 0) {
                done = false;
                int time_slice = min(remaining_time[i], quantum);
                t += time_slice;
                remaining_time[i] -= time_slice;
                if (remaining_time[i] == 0)
                    waiting_time[i] = t - burst_time[i];
            }
        }
    } while (!done);

    float avg_wait = 0, avg_turn = 0;
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; ++i) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        avg_wait += waiting_time[i];
        avg_turn += turnaround_time[i];
        cout << i + 1 << "\t" << burst_time[i] << "\t\t" << waiting_time[i]
             << "\t\t" << turnaround_time[i] << '\n';
    }

    avg_wait /= n;
    avg_turn /= n;

    cout << fixed << setprecision(4);
    cout << "\nAverage Waiting Time: " << avg_wait << endl;
    cout << "Average Turnaround Time: " << avg_turn << endl;

    return 0;
}
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int burst_time[n], waiting_time[n], turnaround_time[n];

    cout << "Enter burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> burst_time[i];
    }

    waiting_time[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }

    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << burst_time[i] << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }

    float avg_wait = 0, avg_turn = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += waiting_time[i];
        avg_turn += turnaround_time[i];
    }
    avg_wait /= n;
    avg_turn /= n;

    cout << "\nAverage Waiting Time: " << avg_wait << endl;
    cout << "Average Turnaround Time: " << avg_turn << endl;

    return 0;
}
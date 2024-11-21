#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id, arrival, burst, waiting, turnaround;
};
bool mycom(Process &a ,Process &b)
{
    return a.arrival<b.arrival;
}

// Function to calculate average waiting time and display results
void displayResults(const vector<Process> &processes, const vector<int> &sequence) {
    double totalWaitingTime = 0;
    cout << "Process\tArrival\tBurst\tWaiting\n";
    for (const auto &p : processes) {
        totalWaitingTime += p.waiting;
        cout << "P" << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.waiting << "\n";
    }
    cout << "Average Waiting Time: " << totalWaitingTime / processes.size() << "\n";
    cout << "Execution Sequence: ";
    for (int id : sequence) cout << "P" << id << " ";
    cout << "\n";
}

// FCFS Scheduling
void fcfs(vector<Process> processes) {
    vector<int> sequence;
    int currentTime = 0;

    // Sort by arrival time
    sort(processes.begin(), processes.end(),mycom);

    for (auto &p : processes) {
        if (currentTime < p.arrival) 
            currentTime = p.arrival;
        p.waiting = currentTime - p.arrival;
        currentTime += p.burst;
        sequence.push_back(p.id);
    }

    displayResults(processes, sequence);
}

// SJF (Non-Preemptive) Scheduling
void sjfNonPreemptive(vector<Process> processes)
{
    vector<int> sequence;
    int currentTime = 0, completed = 0;
    vector<bool> isCompleted(processes.size(), false);

    while (completed < processes.size()) 
    {
        int idx = -1;
        for (int i = 0; i < processes.size(); i++) 
        {
            if (!isCompleted[i] && processes[i].arrival <= currentTime) 
            {
                if (idx == -1 || processes[i].burst < processes[idx].burst) 
                    idx = i;
            }
        }
        if (idx != -1) 
        {
            sequence.push_back(processes[idx].id);
            processes[idx].waiting = currentTime - processes[idx].arrival;
            currentTime += processes[idx].burst;
            isCompleted[idx] = true;
            completed++;
        } 
        else 
        {
            currentTime++;
        }
    }

    displayResults(processes, sequence);
}

// SJF (Preemptive) Scheduling
void sjfPreemptive(vector<Process> processes) {
    vector<int> sequence;
    int currentTime = 0, completed = 0;
    vector<int> remainingBurst(processes.size());
    for (int i = 0; i < processes.size(); i++) remainingBurst[i] = processes[i].burst;

    while (completed < processes.size()) {
        int idx = -1;
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival <= currentTime && remainingBurst[i] > 0) {
                if (idx == -1 || remainingBurst[i] < remainingBurst[idx])
                    idx = i;
            }
        }
        if (idx != -1) {
            sequence.push_back(processes[idx].id);
            remainingBurst[idx]--;
            currentTime++;
            if (remainingBurst[idx] == 0) {
                completed++;
                processes[idx].waiting = currentTime - processes[idx].arrival - processes[idx].burst;
            }
        } else {
            currentTime++;
        }
    }

    displayResults(processes, sequence);
}

int main() {
    int n, choice;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
    }

    cout << "Choose Scheduling Algorithm:\n1. FCFS\n2. SJF (Non-Preemptive)\n3. SJF (Preemptive)\n";
    cin >> choice;

    switch (choice) {
        case 1: fcfs(processes); break;
        case 2: sjfNonPreemptive(processes); break;
        case 3: sjfPreemptive(processes); break;
        default: cout << "Invalid choice!\n";
    }

    return 0;
}

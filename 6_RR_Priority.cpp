#include <iostream> 
using namespace std; 
const int MAX_PROCESSES = 10; 
struct Process { 
int id;              // Process ID 
int arrival_time;    // Arrival Time 
int burst_time;      // Burst Time 
int priority;        
// Priority (only for priority scheduling) 
int waiting_time;    // Waiting Time 
int turnaround_time; // Turnaround Time 
int remaining_burst_time; // For preemptive scheduling 
}; 
// Priority Scheduling (Non-Preemptive) 
void prioritySchedulingNonPreemptive(Process processes[], int n) 
{ 
    int current_time = 0; 
    bool completed[MAX_PROCESSES] = {false}; 
    // Process the highest priority first 
    for (int completed_processes = 0; completed_processes < n;) 
    { 
        int idx = -1, highest_priority = -1; 
        for (int i = 0; i < n; ++i) 
        { 
            if (!completed[i] && processes[i].arrival_time <= current_time && processes[i].priority > highest_priority) 
            { 
                highest_priority = processes[i].priority; 
                idx = i; 
            } 
        } 
        if (idx != -1) 
        { 
            processes[idx].waiting_time = current_time - processes[idx].arrival_time; 
            processes[idx].turnaround_time = processes[idx].waiting_time + processes[idx].burst_time; 
            current_time += processes[idx].burst_time; 
            completed[idx] = true; 
            completed_processes++; 
        } 
        else 
        { 
            current_time++; 
        } 
    } 
} 
// Priority Scheduling (Preemptive) 
void prioritySchedulingPreemptive(Process processes[], int n) 
{ 
    int current_time = 0; 
    bool completed[MAX_PROCESSES] = {false}; 
    // Copy the burst times for preemption 
    for (int i = 0; i < n; ++i) 
    { 
        processes[i].remaining_burst_time = processes[i].burst_time; 
    }   
    for (int completed_processes = 0; completed_processes < n;) 
    { 
        int idx = -1, highest_priority = -1; 
        for (int i = 0; i < n; ++i) 
        { 
            if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0 && processes[i].priority > highest_priority) 
            {    
                highest_priority = processes[i].priority; 
                idx = i; 
            }   
        } 
        if (idx != -1) 
        { 
            processes[idx].remaining_burst_time--; 
            if (processes[idx].remaining_burst_time == 0)  
            { 
                processes[idx].waiting_time = current_time-processes[idx].arrival_time - processes[idx].burst_time; 
                processes[idx].turnaround_time = processes[idx].waiting_time + processes[idx].burst_time; 
                completed[idx] = true; 
                completed_processes++; 
            } 
        } 
        current_time++; 
    } 
} 
// Round Robin Scheduling (RR) 
void roundRobinScheduling(Process processes[], int n, int time_quantum) 
{ 
    int current_time = 0, remaining_burst[MAX_PROCESSES]; 
    for (int i = 0; i < n; ++i) 
    { 
    remaining_burst[i] = processes[i].burst_time; 
    } 
    // Round Robin Scheduling 
    while (true) 
    { 
        bool all_done = true; 
        for (int i = 0; i < n; ++i) 
        { 
            if (remaining_burst[i] > 0) 
            { 
                all_done = false; 
                if (remaining_burst[i] > time_quantum) 
                { 
                    remaining_burst[i] -= time_quantum; 
                    current_time += time_quantum; 
                } 
                else 
                { 
                    current_time += remaining_burst[i]; 
                    processes[i].waiting_time = current_time - processes[i].arrival_time - processes[i].burst_time; 
                    processes[i].turnaround_time = current_time - processes[i].arrival_time; 
                    remaining_burst[i] = 0; 
                } 
            } 
        } 
        if (all_done) 
            break; 
    } 
} 

    // Display Results 
void displayResults(Process processes[], int n) 
{ 
    int total_waiting_time = 0, total_turnaround_time = 0; 
    cout << "\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n"; 
    for (int i = 0; i < n; ++i) 
    { 
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << 
        processes[i].burst_time  
        << "\t\t" << processes[i].priority << "\t\t" << processes[i].waiting_time 
        << "\t\t"  
        << processes[i].turnaround_time << endl; 
        total_waiting_time += processes[i].waiting_time; 
        total_turnaround_time += processes[i].turnaround_time; 
    } 
    cout << "\nAverage Waiting Time: " << (float)total_waiting_time / n << endl; 
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n <<endl; 
} 
int main() 
{ 
    int n, choice, time_quantum; 
    cout << "Enter number of processes: "; 
    cin >> n; 
    Process processes[MAX_PROCESSES]; 
    // Input process details 
    for (int i = 0; i < n; ++i) 
    { 
    processes[i].id = i + 1; 
    cout << "Enter arrival time, burst time, and priority for process " << i + 1 << 
    ": "; 
    cin >> processes[i].arrival_time >> processes[i].burst_time >> 
    processes[i].priority; 
    } 
    cout << "\nChoose Scheduling Algorithm:\n"; 
    cout << "2. Priority Scheduling (Non-Preemptive)\n"; 
    cout << "3. Priority Scheduling (Preemptive)\n"; 
    cout << "4. Round Robin (RR)\n"; 
    cout << "Enter your choice: "; 
    cin >> choice; 
    if (choice == 4) 
    { 
    cout << "Enter time quantum for Round Robin: "; 
    cin >> time_quantum; 
    } 
    // Apply chosen scheduling algorithm 
    switch (choice) 
    { 
        case 1: 
        prioritySchedulingNonPreemptive(processes, n); 
        break; 
        case 2: 
        prioritySchedulingPreemptive(processes, n); 
        break; 
        case 3: 
        roundRobinScheduling(processes, n, time_quantum); 
        break; 
        default: 
        cout << "Invalid choice!\n"; 
        return 0; 
    } 
    displayResults(processes, n); 
    return 0; 
}
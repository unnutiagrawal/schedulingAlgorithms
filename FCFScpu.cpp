#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

struct Process {
    int id;       // Process ID
    int arrival;  // Arrival time
    int burst;    // Burst time
    int completion; // Completion time
    int turnaround; // Turnaround time
    int waiting;   // Waiting time
};

// Function to calculate turnaround time and waiting time for each process
void calculateTimes(vector<Process>& processes) {
    int n = processes.size();
    int currenttime=0;
    processes[0].completion = processes[0].arrival + processes[0].burst;
    processes[0].turnaround = processes[0].completion - processes[0].arrival;
    processes[0].waiting =  processes[0].arrival - currenttime ;

 	double totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (int i = 1; i < n; i++) {
        processes[i].completion = max(processes[i - 1].completion, processes[i].arrival) + processes[i].burst;
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
        totalTurnaroundTime += processes[i].turnaround;
    	totalWaitingTime += processes[i].waiting;
    }
    
         cout<< "\nAverage Turnaround Time: " << totalTurnaroundTime / n
         << "\nAverage Waiting Time: " << totalWaitingTime / n ;
         cout<<endl;

    //double throughput = static_cast<double>(n) / currentTime;
    //double utilization = static_cast<double>(totalTurnaroundTime) / currentTime;
    
    
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst;
    }

    // Sort processes by arrival time (FCFS)
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    // Calculate completion, turnaround, and waiting times
    calculateTimes(processes);

    // Display the results
    cout << "Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const Process& p : processes) {
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion << "\t\t" << p.turnaround << "\t\t" << p.waiting << "\n";
    }
    cout<<endl;
    cout << " Gantt Chart:\n";
    cout<<endl;
    cout<<"|";
    for (const Process &p : processes) {
    	int temp= (p.burst)/2;
    	while(temp!=0)
    	{
    		cout<<".";
    		temp--;
		}
        cout << "P" << p.id ;
        temp= (p.burst)/2;
        while(temp!=0)
    	{
    		cout<<".";
    		temp--;
		}
		
		cout<<"|";
    }
    cout<<endl;
    
    cout<<endl;
    
    return 0;
}
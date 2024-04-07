#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int priority;
    int startTime;
    int endTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};

bool comparePriority(const Process &p1, const Process &p2) {
    return p1.priority < p2.priority;
}


int main() {
    int num;
    cout << "Enter the number of processes: ";
    cin >> num;

    vector<Process> processes(num);
    for (int i = 0; i < num; ++i) {
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
        processes[i].id = i + 1;
        processes[i].startTime = -1;
        processes[i].endTime = -1;
    }

    sort(processes.begin(), processes.end(), comparePriority);

    int currentTime = 0;
    
    for (int i = 0; i < num; ++i) {
        processes[i].startTime = currentTime;
        processes[i].endTime = currentTime + processes[i].burstTime;
    	processes[i].waitingTime =processes[i].startTime ;
    	//cout<<"wait time is"<<processes[i].waitingTime<<" ";
		//wait+=  processes[i].burstTime;
        currentTime = processes[i].endTime;
        processes[i].responseTime +=processes[i].startTime;
        //cout<<"response time is\n"<<processes[i].responseTime<<" ";
    }

    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0,totalResponseTime=0;
    for (int i = 0; i < num; ++i) {
    processes[i].turnaroundTime = processes[i].endTime ;
    //processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    totalTurnaroundTime += processes[i].turnaroundTime;
    totalWaitingTime += processes[i].waitingTime;
    totalResponseTime+=processes[i].responseTime;
	}

    double throughput = static_cast<double>(num) / currentTime;
    double utilization = static_cast<double>(totalTurnaroundTime) / currentTime;

	cout<<endl;
    cout << " Gantt Chart:\n";
    cout<<endl;
    cout<<"|";
    for (const Process &p : processes) {
    	int temp= (p.burstTime)/2;
    	while(temp!=0)
    	{
    		cout<<".";
    		temp--;
		}
        cout << "P" << p.id ;
        temp= (p.burstTime)/2;
        while(temp!=0)
    	{
    		cout<<".";
    		temp--;
		}
		
		cout<<"|";
    }
    cout<<endl;
    
    cout<<"\nProcess\t| Turnaround Time\t| Waiting Time\t| Response Time\n";
    for (int i = 0; i < num; ++i) {
        cout<< "P"<<processes[i].id << "\t| "<<processes[i].turnaroundTime << "\t\t\t| " <<processes[i].waitingTime<<"\t\t|"<<processes[i].responseTime<<endl; }
    
    cout<<endl;
    cout << "\nThroughput: " << throughput
         << "\nUtilization: " << utilization
         << "\nAverage Turnaround Time: " << totalTurnaroundTime / num
         << "\nAverage Waiting Time: " << totalWaitingTime / num 
		 <<"\nAverage Response Time:"<<totalResponseTime/num<<endl;


    /*cout<<"Turnaround Time:"<<endl;
    for(const Process &p : processes){
    	cout<< "P"<<p.id<< ":" <<p.turnaroundTime<<endl;
	}
	
	cout<<"Waiting Time:"<<endl;
    for (int i = 0; i < numProcesses; ++i){
    	cout<< "P"<<processes[i].id<< ":" <<processes[i].waitingTime<<endl;
	}
    for (int i = 0; i < num; ++i) {
        cout<< "P"<<processes[i].id<< ":" << processes[i].waitingTime<<" "<<endl;}*/
    	
    return 0;
}

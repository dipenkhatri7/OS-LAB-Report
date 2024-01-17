#include <iostream>

using namespace std;

// Structure to represent a process
struct Process
{
    int id; // Process ID
    int at; // Arrival time
    int bt; // Burst time
    int ct; // Completion time
};

// Function to compare processes based on arrival time
bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.at < b.at;
}

// Function to calculate waiting time for each process
void findwt(Process processes[], int n, int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        wt[i] = tat[i] - processes[i].bt;
    }
}

// Function to calculate turnaround time for each process
void findtat(Process processes[], int n, int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = processes[i].ct - processes[i].at;
    }
}

// Function to find average turnaround time and waiting time for all processes
void findavgtime(Process processes[], int n)
{
    int total_tat = 0, total_wt = 0;
    int wt[n];
    int tat[n];

    // Calculate completion time for each process
    processes[0].ct = processes[0].bt + processes[0].at;
    for (int i = 1; i < n; i++)
    {
        processes[i].ct = max(processes[i - 1].ct + processes[i].bt, processes[i].at + processes[i].bt);
    }

    // Calculate turnaround time and waiting time for each process
    findtat(processes, n, tat);
    findwt(processes, n, wt, tat);

    // Display process details and metrics
    cout << "Process    Arrival Time    Burst Time    Completion Time    Turnaround Time    Waiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        total_tat += tat[i];
        total_wt += wt[i];

        cout << processes[i].id << "           " << processes[i].at << "              "
             << processes[i].bt << "               " << processes[i].ct << "                 "
             << tat[i] << "                " << wt[i] << endl;
    }

    // Display average turnaround time and waiting time
    cout << "Avg wt = " << (float)total_wt / n << endl;
    cout << "Avg tat = " << (float)total_tat / n << endl;
}

int main()
{
    int n;

    // Input the number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    // Declare an array of processes
    Process processes[n];

    // Input arrival times and burst times for each process
    cout << "Enter arrival times and burst times for each process:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].at;

        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].bt;

        processes[i].id = i + 1;
    }

    // Sort processes based on arrival time
    sort(processes, processes + n, compareArrivalTime);

    // Calculate and display average turnaround time and waiting time
    findavgtime(processes, n);

    return 0;
}

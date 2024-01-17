#include <iostream>
using namespace std;

// Structure to represent a process
struct Process
{
  int id;   // Process ID
  int at;   // Arrival time
  int bt;   // Burst time
  int ct;   // Completion time
};

// Comparator function for sorting processes based on arrival time
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

// Function to find and display average turnaround time and waiting time
void findavgtime(Process processes[], int n)
{
  int total_tat = 0, total_wt = 0;
  int wt[n];
  int tat[n];

  processes[0].ct = processes[0].bt + processes[0].at;

  // Calculate completion time for each process
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

    cout << "P" << processes[i].id << "           " << processes[i].at << "              "
         << processes[i].bt << "               " << processes[i].ct << "                 "
         << tat[i] << "                " << wt[i] << endl;
  }

  // Display average turnaround time and waiting time
  cout << "Avg wt = " << (float)total_wt / n << endl;
  cout << "Avg tat = " << (float)total_tat / n << endl;
}

// Function to implement Shortest Job First (SJF) scheduling algorithm
void sjf(Process processes[], int n)
{
  // Sort processes based on arrival time
  sort(processes, processes + n, compareArrivalTime);

  int currentTime = processes[0].at;

  // Iterate through processes and schedule the shortest job first
  for (int i = 0; i < n; i++)
  {
    int shortestJobIndex = i;
    for (int j = i + 1; j < n && processes[j].at <= currentTime; j++)
    {
      if (processes[j].bt < processes[shortestJobIndex].bt)
        shortestJobIndex = j;
    }

    // Swap processes to schedule the shortest job first
    swap(processes[i], processes[shortestJobIndex]);

    // Update completion time and move to the next process
    processes[i].ct = currentTime + processes[i].bt;
    currentTime = processes[i].ct;
  }
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

  // Apply Shortest Job First scheduling algorithm
  sjf(processes, n);

  // Calculate and display average turnaround time and waiting time
  findavgtime(processes, n);

  return 0;
}

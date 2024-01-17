#include <iostream>
using namespace std;

// Function to input elements of a matrix
void matrixInput(int n, int m, vector< vector<int> > &arr)
{
    cout << "Enter the matrix: ";
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the elements of row " << i + 1 << ": ";
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int n, int m, vector< vector<int> > &alloc, vector< vector<int> > &max, int *avail, vector< vector<int> > &need)
{
    vector<bool> finish(n, false);
    int work[m];

    for (int i = 0; i < m; i++)
    {
        work[i] = avail[i];
    }
    int count = 0;
    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canExecute = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute)
                {
                    finish[i] = true;
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += alloc[i][j];
                    }
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return count == n;
}

int main()
{
    // Input the number of processes
    cout << "Enter the number of processes: ";
    int n;
    cin >> n;

    // Input the number of resources
    cout << "Enter the number of resources: ";
    int m;
    cin >> m;

    int inst[m];

    // Input the instances of each resource
    cout << "Enter the instances of each resource: ";
    for (int i = 0; i < m; i++)
    {
        cin >> inst[i];
    }

    // Declare and initialize matrices and arrays
    vector< vector<int> > alloc(n, vector<int>(m));
    vector< vector<int> > max(n, vector<int>(m));
    int avail[m];

    // Input the allocation matrix
    cout << "Enter the allocation matrix: "<<endl;
    matrixInput(n, m, alloc);

    // Input the maximum matrix
    cout << "Enter the max matrix: "<<endl;
    matrixInput(n, m, max);
    cout << "\n\n";

    cout << "The available matrix is:" << endl;

    // Calculate the available matrix
    for (int i = 0; i < m; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += alloc[j][i];
        }
        avail[i] = inst[i] - sum;
        cout << avail[i] << " ";
    }

    // Calculate the need matrix
    vector< vector<int> > need(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    cout << "\n\n";

    // Display the matrices in table format
    cout << "Process |              Allocation          |       Max     |       Need\n";
    for (int i = 0; i < n; i++)
    {
        cout << "   P" << i + 1 << "   |";
        for (int j = 0; j < m; j++)
        {
            cout << "     " << alloc[i][j] << "     ";
        }
        cout << "|";
        for (int j = 0; j < m; j++)
        {
            cout << "  " << max[i][j] << "  ";
        }
        cout << "|";
        for (int j = 0; j < m; j++)
        {
            cout << "    " << need[i][j] << "    ";
        }
        cout << "\n";
    }
    cout << "\n";

    // Check if the system is in a safe state and display the result
    if (isSafe(n, m, alloc, max, avail, need))
    {
        cout << "System is in Safe State" << endl;
    }
    else
    {
        cout << "System is not in Safe State!" << endl;
    }
    return 0;
}

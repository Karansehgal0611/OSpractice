#include<stdio.h>
#include<stdbool.h>

struct  process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    bool iscomp;
};

void sortbyArrival(struct process p[], int n)
{
    struct process temp;
    for(int i = 0;i<n-1 ;i++)
    {
        for(int j = i+1 ; j<n;j++)
        {
            if(p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

        }
    }
}

void CalculateTimes(struct process p[], int n)
{
    int current = 0;
    int completed = 0;

    while(completed!=n)
    {
        int shortest =-1;
        int min_bt = 10000; //Arbitrary large number

        //Find the process with the shortest burst time that has arrived
        for(int i=0;i<n;i++)
        {
            if(p[i].at<=current && !p[i].iscomp &&p[i].bt < min_bt)
            {
                min_bt = p[i].bt;
                shortest = i;
            }
        }
        if(shortest==-1)
        {
            current++;
        }
        else
        {
            current+=p[shortest].bt;
            p[shortest].ct = current;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            p[shortest].iscomp = true;
            completed++;
        }
    }

}

void printTable(struct process p[], int n)
{
    float total_tat = 0, total_wt = 0;
    printf("------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | TAT | Waiting Time |\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("| P%d      |     %2d       |    %2d      |       %2d        |  %2d  |     %2d       |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("------------------------------------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    struct process p[n];
    for(int i=0;i<n;i++)
    {
        printf("Enter the arrival time of process %d: ",i+1);
        scanf("%d",&p[i].at);
        printf("Enter the burst time of process %d: ",i+1);
        scanf("%d",&p[i].bt);
        p[i].pid = i+1;
    }
    sortbyArrival(p,n);
    
    CalculateTimes(p,n);

    printTable(p,n);
    
    return 0;
}
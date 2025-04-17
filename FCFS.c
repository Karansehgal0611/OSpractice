#include<stdio.h>

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void Calculatetimes(struct process p[],int n)
{
    p[0].completion_time=p[0].arrival_time+p[0].burst_time;
    for(int i = 1; i< n;i++)
    {
        if(p[i].arrival_time>p[i-1].completion_time)
        {
            p[i].completion_time = p[i].arrival_time + p[i].burst_time;
        }
        else{
            p[i].completion_time = p[i-1].completion_time + p[i].burst_time;
        }
    }

    for(int i=0;i<n;i++)
    {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }
}

void printTable(struct process p[], int n)
{
    float total_tat = 0, total_wt = 0;
    printf("------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | TAT | Waiting Time |\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
        printf("| P%d      |     %2d       |    %2d      |       %2d        |  %2d  |     %2d       |\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
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
        scanf("%d",&p[i].arrival_time);
        printf("Enter the burst time of process %d: ",i+1);
        scanf("%d",&p[i].burst_time);
        p[i].pid = i+1;
    }
    
    Calculatetimes(p,n);

    printTable(p,n);
    
    return 0;
}

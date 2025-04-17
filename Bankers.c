#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10


int num_processes, num_resources;
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int work[MAX_RESOURCES];
int finish[MAX_PROCESSES];
int safe_sequence[MAX_PROCESSES]; // Array to store the safe sequence


// Function to print matrices
void print_matrices() {
   int i, j;


   // Print Allocation Matrix
   printf("\nAllocation Matrix:\n");
   for (i = 0; i < num_processes; i++) {
       printf("P%d: ", i);
       for (j = 0; j < num_resources; j++) {
           printf("%d ", allocation[i][j]);
       }
       printf("\n");
   }


   // Print Maximum Matrix
   printf("\nMaximum Matrix:\n");
   for (i = 0; i < num_processes; i++) {
       printf("P%d: ", i);
       for (j = 0; j < num_resources; j++) {
           printf("%d ", max[i][j]);
       }
       printf("\n");
   }


   // Print Need Matrix
   printf("\nNeed Matrix:\n");
   for (i = 0; i < num_processes; i++) {
       printf("P%d: ", i);
       for (j = 0; j < num_resources; j++) {
           printf("%d ", need[i][j]);
       }
       printf("\n");
   }


   // Print Available Resources
   printf("\nAvailable Resources:\n");
   for (j = 0; j < num_resources; j++) {
       printf("%d ", available[j]);
   }
   printf("\n");
}


// Function to input data for the system
void input_data() {
   int i, j;
   int total_resources[MAX_RESOURCES];  // To store total instances of each resource
  
   printf("Enter the number of processes: ");
   scanf("%d", &num_processes);
  
   printf("Enter the number of resources: ");
   scanf("%d", &num_resources);
  
   printf("Enter the total instances of each resource:\n");
   for (i = 0; i < num_resources; i++) {
       scanf("%d", &total_resources[i]);
   }
  
   printf("Enter the maximum resources for each process:\n");
   for (i = 0; i < num_processes; i++) {
       for (j = 0; j < num_resources; j++) {
           scanf("%d", &max[i][j]);
       }
   }
  
   printf("Enter the allocated resources for each process:\n");
   for (i = 0; i < num_processes; i++) {
       for (j = 0; j < num_resources; j++) {
           scanf("%d", &allocation[i][j]);
           need[i][j] = max[i][j] - allocation[i][j]; // Calculate the remaining needs
       }
   }
  
   // Calculate available resources
   for (j = 0; j < num_resources; j++) {
       int allocated_sum = 0;
       for (i = 0; i < num_processes; i++) {
           allocated_sum += allocation[i][j];
       }
       available[j] = total_resources[j] - allocated_sum;
   }


   // Print all matrices after input
   print_matrices();
}


// Function to check if the system is in a safe state and print the safe sequence
int safety_check() {
   int i, j, count = 0, process_index = 0;
  
   // Initialize finish array and work array
   for (i = 0; i < num_processes; i++) {
       finish[i] = 0;
   }
   for (i = 0; i < num_resources; i++) {
       work[i] = available[i];
   }


   while (count < num_processes) {
       int found = 0; // Flag to check if a process is found in this iteration


       for (i = 0; i < num_processes; i++) {
           if (finish[i] == 0) { // Process is not finished
               int can_allocate = 1;


               // Check if process can be allocated
               for (j = 0; j < num_resources; j++) {
                   if (need[i][j] > work[j]) {
                       can_allocate = 0;
                       break;
                   }
               }


               // If the process can be allocated, simulate the allocation
               if (can_allocate) {
                   for (j = 0; j < num_resources; j++) {
                       work[j] += allocation[i][j];
                   }
                   finish[i] = 1;
                   safe_sequence[process_index++] = i; // Store the process in safe sequence
                   count++;
                   found = 1; // Process found that can complete
               }
           }
       }


       // If no process was found that can complete, exit with unsafe state
       if (!found) {
           return 0; // Unsafe state
       }
   }


   return 1; // Safe state
}


// Function to request resources for a process
int request_resources(int process, int request[]) {
   int i;


   // Check if request is valid
   for (i = 0; i < num_resources; i++) {
       if (request[i] > need[process][i]) {
           printf("Error: Requested resources exceed the process's maximum claim.\n");
           return 0;
       }
       if (request[i] > available[i]) {
           printf("Error: Resources are not available.\n");
           return 0;
       }
   }


   // Try to allocate resources
   for (i = 0; i < num_resources; i++) {
       available[i] -= request[i];
       allocation[process][i] += request[i];
       need[process][i] -= request[i];
   }


   // Check if the new allocation leaves the system in a safe state
   if (safety_check()) {
       return 1; // Safe state, request granted
   } else {
       // Rollback the allocation if not safe
       for (i = 0; i < num_resources; i++) {
           available[i] += request[i];
           allocation[process][i] -= request[i];
           need[process][i] += request[i];
       }
       return 0; // Unsafe state, request denied
   }
}


int main() {
   // Input data
   input_data();
  
   // Check the initial system state
   if (safety_check()) {
       printf("Initial Safe state - Safe sequence exists: ");
       for (int i = 0; i < num_processes; i++) {
           printf("P%d ", safe_sequence[i]);
       }
       printf("\n");
   } else {
       printf("Initial Unsafe state - No safe sequence.\n");
       return 0;
   }


   // Resource request handling
   int process;
   int request[MAX_RESOURCES];
  
   printf("Enter the process number for resource request: ");
   scanf("%d", &process);
  
   printf("Enter the requested resources for process %d: ", process);
   for (int i = 0; i < num_resources; i++) {
       scanf("%d", &request[i]);
   }


   // Process the resource request
   if (request_resources(process, request)) {
       printf("Resource request granted.\n");
   } else {
       printf("Resource request denied. Unsafe state.\n");
   }


   // Print all matrices after the resource request
   print_matrices();


   return 0;
}
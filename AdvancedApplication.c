/* Here we have implemented an advanced application of Circular Queue 
-->Smart Elevator System */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Hardcoded values for simplicity
#define MAX_ELEVATORS 3// number of elevators
#define MAX_QUEUE_SIZE 10// maximum queue size(requests) for each elevator

//Structure to represent an elevator
typedef struct {
    int destinations[MAX_QUEUE_SIZE];//10 floors can be queued
    int front, rear;
    int count;            // number of queued destinations
    int currentFloor;
    int id;
} Elevator;

// Initialize elevator
void initElevator(Elevator *e, int id) {
    e->front = 0;
    e->rear = 0;
    e->count = 0;
    e->currentFloor = 0;
    e->id = id;//ID of elevator
}

// Check if queue is full
int isFull(Elevator *e) {
    return e->count == MAX_QUEUE_SIZE;
}

// Check if queue is empty
int isEmpty(Elevator *e) {
    return e->count == 0;
}

// Add destination to elevator queue
void enqueue(Elevator *e, int floor) {
    if (isFull(e)) {
        printf("Elevator %d queue is full!\n", e->id);
        return;
    }
    e->destinations[e->rear] = floor;
    e->rear = (e->rear + 1) % MAX_QUEUE_SIZE;
    e->count++;
    printf("Elevator %d assigned to floor %d\n", e->id, floor);
}

// Move elevator to next destination
void moveElevator(Elevator *e) {
    if (isEmpty(e)) return;
    int nextFloor = e->destinations[e->front];
    printf("Elevator %d moving from %d to %d\n", e->id, e->currentFloor, nextFloor);
    e->currentFloor = nextFloor;
    e->front = (e->front + 1) % MAX_QUEUE_SIZE;
    e->count--;
}

// Assign request to best elevator
void assignElevator(Elevator elevators[], int floor) {
    int minDistance = 1e9;
    int bestIndex = -1;

    for (int i = 0; i < MAX_ELEVATORS; i++) {
        int distance = abs(elevators[i].currentFloor - floor);
        if (distance < minDistance) {
            minDistance = distance;
            bestIndex = i;
        }
    }

    if (bestIndex != -1) {
        enqueue(&elevators[bestIndex], floor);
    }
}

/* helper: print elevator status and queues */
static void showStatus(Elevator elevators[]) {
    printf("\n--- Elevators Status ---\n");
    for (int i = 0; i < MAX_ELEVATORS; ++i) {
        Elevator *e = &elevators[i];
        printf("Elevator %d | floor=%d | queued=%d : ", e->id, e->currentFloor, e->count);
        if (isEmpty(e)) {
            printf("[empty]\n");
            continue;
        }
        int idx = e->front;
        for (int k = 0; k < e->count; ++k) {
            printf("%d ", e->destinations[idx]);
            idx = (idx + 1) % MAX_QUEUE_SIZE;
        }
        printf("\n");
    }
}

/* helper: generate random requests (floors 1..20) */
static void simulateRandomRequests(Elevator elevators[], int n) {
    for (int i = 0; i < n; ++i) {
        int floor = (rand() % 20) + 1;
        printf("Request: floor %d\n", floor);
        assignElevator(elevators, floor);
    }
}

/* Interactive main (no hardcoded requests) */
int main(void) {
    Elevator elevators[MAX_ELEVATORS];
    int choice;

    srand((unsigned)time(NULL));
    for (int i = 0; i < MAX_ELEVATORS; ++i) initElevator(&elevators[i], i + 1);

    while (1) {
        printf("\nSmart Elevator System\n");
        printf("1) Request floor\n");
        printf("2) Step one tick (move elevators once)\n");
        printf("3) Run N ticks\n");
        printf("4) Simulate random requests (N)\n");
        printf("5) Show status\n");
        printf("6) Reset system\n");
        printf("7) Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            int c; while ((c = getchar()) != EOF && c != '\n');
            printf("Invalid input\n");
            continue;
        }

        if (choice == 1) {
            int floor;
            printf("Enter floor: ");
            if (scanf("%d", &floor) != 1) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("Invalid floor\n"); continue; }
            assignElevator(elevators, floor);
        } else if (choice == 2) {
            for (int i = 0; i < MAX_ELEVATORS; ++i) moveElevator(&elevators[i]);
        } else if (choice == 3) {
            int n;
            printf("Ticks to run: ");
            if (scanf("%d", &n) != 1 || n <= 0) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("Invalid number\n"); continue; }
            for (int t = 0; t < n; ++t) {
                for (int i = 0; i < MAX_ELEVATORS; ++i) moveElevator(&elevators[i]);
            }
        } else if (choice == 4) {
            int n;
            printf("Number of random requests: ");
            if (scanf("%d", &n) != 1 || n <= 0) { int c; while ((c = getchar()) != EOF && c != '\n'); printf("Invalid number\n"); continue; }
            simulateRandomRequests(elevators, n);
        } else if (choice == 5) {
            showStatus(elevators);
        } else if (choice == 6) {
            for (int i = 0; i < MAX_ELEVATORS; ++i) initElevator(&elevators[i], i + 1);
            printf("System reset.\n");
        } else if (choice == 7) {
            printf("Exiting.\n");
            return 0;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
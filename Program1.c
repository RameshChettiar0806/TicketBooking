#include <stdio.h>
#define SIZE 5   // maximum queue size

// Queue structure
struct Queue {
    int front, rear;
    // number of elements currently in queue
    int count;               
    // storing customer IDs
    int customers[SIZE];     
};

// Initialize queue
void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// Check if queue is full
int isFull(struct Queue *q) {
    return (q->count == SIZE);
}

// Check if queue is empty
int isEmpty(struct Queue *q) {
    return (q->count == 0);
}

// Book ticket (Enqueue)
void bookTicket(struct Queue *q, int id) {
    if (isFull(q)) {
        printf("Queue is full! Customer %d cannot book a ticket.\n", id);
        return;
    }
    q->rear = (q->rear + 1) % SIZE;
    q->customers[q->rear] = id;
    q->count++;
    printf("Customer %d booked a ticket.\n", id);
}

// Issue ticket (Dequeue)
void issueTicket(struct Queue *q) {
    if (isEmpty(q)) {
        printf("No customers in queue.\n");
        return;
    }
    printf("Ticket issued to Customer %d\n", q->customers[q->front]);
    q->front = (q->front + 1) % SIZE;
    q->count--;
    if (q->count == 0) {
        // reset indices for clarity (optional)
        q->front = 0;
        q->rear = -1;
    }
}

// Display queue
void displayQueue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("No customers in queue.\n");
        return;
    }
    printf("Current Queue: ");
    int i = q->front;
    int printed = 0;
    while (printed < q->count) {
        printf("%d ", q->customers[i]);
        i = (i + 1) % SIZE;
        printed++;
    }
    printf("\n");
}

int main() {
    struct Queue q;
    initQueue(&q);

    int choice;
    int id;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Book ticket\n");
        printf("2. Issue ticket\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            // invalid input or EOF
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter customer ID to book: ");
                if (scanf("%d", &id) != 1) {
                    // consume invalid input and continue
                    int c;
                    while ((c = getchar()) != EOF && c != '\n');
                    printf("Invalid ID.\n");
                    continue;
                }
                bookTicket(&q, id);
                break;
            case 2:
                issueTicket(&q);
                break;
            case 3:
                displayQueue(&q);
                break;
            case 4:
                printf("Exiting.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TICKETS 100

// Structure to represent a ticket
typedef struct {
    char ticketId[20];
    char passengerName[50];
    int age;
    char sourceCity[30];
    char destCity[30];
    char paymentMode[20];
} Ticket;

// Array to hold booked tickets
Ticket bookedTickets[MAX_TICKETS];
int ticketCount = 0;

// Function to check if a string contains only alphabets
int isAlphaOnly(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to check if a string contains only digits
int isDigitsOnly(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to check if a city has train transportation
// Mock-up function: you can replace this with more advanced validation logic.
int isValidCity(char *city) {
    // Here, we simulate valid city checks by a basic pattern check.
    // For example, we might check if the city name contains "train" or has a common city name pattern.
    // In a real-world scenario, this function would interact with a database or API.

    // Simulated validation: City names containing "train" or a specific pattern are accepted.
    if (strstr(city, "Train") != NULL || strlen(city) > 3) {
        return 1;
    }
    return 0;
}

// Function to check if a payment mode is valid
int isValidPaymentMode(char *paymentMode) {
    return strcmp(paymentMode, "Credit") == 0 || strcmp(paymentMode, "Debit") == 0 || strcmp(paymentMode, "Cash") == 0;
}

// Function to book a ticket
void bookTicket() {
    if (ticketCount >= MAX_TICKETS) {
        printf("Ticket booking limit reached. Cannot book more tickets.\n");
        return;
    }

    Ticket newTicket;

    printf("Enter Ticket ID (alphanumeric): ");
    scanf("%s", newTicket.ticketId);
    if (strspn(newTicket.ticketId, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != strlen(newTicket.ticketId)) {
        printf("Invalid Ticket ID. It must contain only alphabets and digits.\n");
        return;
    }

    printf("Enter Passenger Name (alphabets only): ");
    scanf(" %[^\n]", newTicket.passengerName);
    if (!isAlphaOnly(newTicket.passengerName)) {
        printf("Invalid Passenger Name. It must contain only alphabets.\n");
        return;
    }

    printf("Enter Age (numbers only): ");
    char ageStr[10];
    scanf("%s", ageStr);
    if (!isDigitsOnly(ageStr)) {
        printf("Invalid Age. It must be a number.\n");
        return;
    }
    newTicket.age = atoi(ageStr);

    printf("Enter Source City: ");
    scanf(" %[^\n]", newTicket.sourceCity);
    if (!isValidCity(newTicket.sourceCity)) {
        printf("Error: Invalid Source City. Please enter a city with train transportation.\n");
        return;
    }

    printf("Enter Destination City: ");
    scanf(" %[^\n]", newTicket.destCity);
    if (!isValidCity(newTicket.destCity)) {
        printf("Error: Invalid Destination City. Please enter a city with train transportation.\n");
        return;
    }

    // Ask for payment mode
    printf("Enter Payment Mode (Credit/Debit/Cash): ");
    scanf(" %[^\n]", newTicket.paymentMode);
    if (!isValidPaymentMode(newTicket.paymentMode)) {
        printf("Invalid Payment Mode. Please choose between Credit, Debit, or Cash.\n");
        return;
    }

    bookedTickets[ticketCount] = newTicket;
    ticketCount++;
    printf("Ticket booked successfully.\n");
}

// Function to cancel a ticket
void cancelTicket() {
    char ticketId[20];
    printf("Enter Ticket ID to cancel: ");
    scanf("%s", ticketId);

    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(bookedTickets[i].ticketId, ticketId) == 0) {
            // Remove the ticket by shifting all subsequent tickets
            for (int j = i; j < ticketCount - 1; j++) {
                bookedTickets[j] = bookedTickets[j + 1];
            }
            ticketCount--;
            printf("Ticket cancelled successfully.\n");
            return;
        }
    }
    printf("Ticket ID not found.\n");
}

// Function to view all booked tickets
void viewBookedTickets() {
    if (ticketCount == 0) {
        printf("No tickets have been booked.\n");
        return;
    }

    printf("\nBooked Tickets:\n");
    for (int i = 0; i < ticketCount; i++) {
        printf("Ticket ID: %s\n", bookedTickets[i].ticketId);
        printf("Passenger Name: %s\n", bookedTickets[i].passengerName);
        printf("Age: %d\n", bookedTickets[i].age);
        printf("Source City: %s\n", bookedTickets[i].sourceCity);
        printf("Destination City: %s\n", bookedTickets[i].destCity);
        printf("Payment Mode: %s\n\n", bookedTickets[i].paymentMode);
    }
}

// Main function to drive the ticket booking system
int main() {
    int choice;

    while (1) {
        printf("\nRailway Ticket Booking System\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. View Booked Tickets\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookTicket();
                break;
            case 2:
                cancelTicket();
                break;
            case 3:
                viewBookedTickets();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define FILE_NAME "records.txt"

// Define the structure
typedef struct {
    int id;
    char name[MAX_NAME];
    double salary;
} Employee;

// Function Prototypes
int storeRecordsASCII(const char *filename, Employee arr[], int n);
long* createSeekPositions(const char *filename, int n);
void displayRecordAtPosition(const char *filename, long seekPos);

int main() {
    // Sample array of structures
    Employee employees[] = {
        {101, "Alice Smith", 65000.50},
        {102, "Bob Jones", 72000.75},
        {103, "Charlie Brown", 55000.00},
        {104, "Diana Prince", 95000.25}
    };
    int n = sizeof(employees) / sizeof(employees[0]);
    int a;
    printf("enter target index:");
    scanf("%d",&a);
    // 1. Store records in ASCII format
    printf("Storing records in ASCII format...\n");
    if (!storeRecordsASCII(FILE_NAME, employees, n)) {
        return 1;
    }

    // 2. Create the array of seek positions
    printf("Building seek positions index...\n");
    long *seekPositions = createSeekPositions(FILE_NAME, n);
    if (seekPositions == NULL) {
        return 1;
    }

    // Print the generated seek positions for visibility
    printf("\nGenerated Seek Positions:\n");
    for (int i = 0; i < n; i++) {
        printf("Record %d starts at byte offset: %ld\n", i + 1, seekPositions[i]);
    }

    // 3. Display a specific record given its position index
    int targetIndex = a; // Let's fetch the 3rd record (Charlie Brown)
    printf("\nFetching record at index %d (Offset %ld):\n", targetIndex, seekPositions[targetIndex]);
    displayRecordAtPosition(FILE_NAME, seekPositions[targetIndex]);

    // Clean up
    free(seekPositions);
    return 0;
}

/**
 * Stores an array of structures in ASCII text format.
 * Each record is written on a new line.
 */
int storeRecordsASCII(const char *filename, Employee arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        // Writing as plain text (ASCII) separated by spaces/tabs, ending with a newline
        fprintf(file, "%d\t%s\t%.2f\n", arr[i].id, arr[i].name, arr[i].salary);
    }

    fclose(file);
    return 1;
}

/**
 * Reads the ASCII file and builds an array containing the starting 
 * byte position (seek position) of each record.
 */
long* createSeekPositions(const char *filename, int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading position index");
        return NULL;
    }

    // Allocate memory for the positions array
    long *positions = (long *)malloc(n * sizeof(long));
    if (positions == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    char buffer[256];
    int i = 0;

    // Get the start position of the very first record
    positions[i] = ftell(file);

    // Read line by line. fgets reads up to the newline character.
    while (fgets(buffer, sizeof(buffer), file) != NULL && i < n - 1) {
        i++;
        // The start of the next record is the current file pointer position
        positions[i] = ftell(file);
    }

    fclose(file);
    return positions;
}

/**
 * Seeks directly to the provided byte offset and displays the record.
 */
void displayRecordAtPosition(const char *filename, long seekPos) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file to display record");
        return;
    }

    // Move the file pointer directly to the specific record beginning
    if (fseek(file, seekPos, SEEK_SET) != 0) {
        perror("Error seeking to position");
        fclose(file);
        return;
    }

    // Temporary variables to parse the ASCII data
    int id;
    char name[MAX_NAME];
    double salary;

    // Read the line data from the current seek position
    // Since names can contain spaces, we parse fields carefully. 
    // This scans ID, reads everything up to the tab/delimiter for name, and then the salary.
    if (fscanf(file, "%d\t %[^\t]\t%lf", &id, name, &salary) == 3) {
        printf("-----------------------------\n");
        printf("ID    : %d\n", id);
        printf("Name  : %s\n", name);
        printf("Salary: $%.2f\n", salary);
        printf("-----------------------------\n");
    } else {
        printf("Error: Could not parse record data at position %ld.\n", seekPos);
    }

    fclose(file);
} 
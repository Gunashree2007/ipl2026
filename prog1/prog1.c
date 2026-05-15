#include <stdio.h>
#include <stdlib.h>

struct Player {
    int id;
    char name[50];
    int runs;
};

// Function to get the m-th record
void getRecord(int m) {
    FILE *fp = fopen("players.bin", "rb");
    if (!fp) return;

    struct Player p;
    // Seek to (m-1) * size of one struct
    fseek(fp, (m - 1) * sizeof(struct Player), SEEK_SET);

    if (fread(&p, sizeof(struct Player), 1, fp)) {
        printf("\nRecord %d: ID: %d, Name: %s, Runs: %d\n", m, p.id, p.name, p.runs);
    } else {
        printf("\nRecord not found.\n");
    }
    fclose(fp);
}

// Function to delete the m-th record
void deleteRecord(int m) {
    FILE *fp = fopen("players.bin", "rb");
    FILE *ft = fopen("temp.bin", "wb");
    if (!fp || !ft) return;

    struct Player p;
    int current = 1;

    while (fread(&p, sizeof(struct Player), 1, fp)) {
        if (current != m) {
            fwrite(&p, sizeof(struct Player), 1, ft);
        }
        current++;
    }

    fclose(fp);
    fclose(ft);
    remove("players.bin");
    rename("temp.bin", "players.bin");
    printf("\nRecord %d deleted successfully.\n", m);
}

int main() {
    int n, m;
    printf("Enter number of records: ");
    scanf("%d", &n);

    struct Player *players = malloc(n * sizeof(struct Player));
    FILE *fp = fopen("players.bin", "wb");

    for (int i = 0; i < n; i++) {
        players[i].id = i + 1;
        printf("Enter name and runs for ID %d: ", i + 1);
        scanf("%s %d", players[i].name, &players[i].runs);
    }

    fwrite(players, sizeof(struct Player), n, fp);
    fclose(fp);

    printf("\nEnter record number to retrieve: ");
    scanf("%d", &m);
    getRecord(m);

    printf("\nEnter record number to delete: ");
    scanf("%d", &m);
    deleteRecord(m);

    free(players);
    return 0;
} 
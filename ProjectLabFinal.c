#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>  

const char *fishKinds[] = {
    "Goldfish", "Salmon", "Trout", "Bass", "Catfish", "Tuna", "Swordfish", "Shark", "Cod", "Carp"
};

#define NUM_FISH_KINDS (sizeof(fishKinds) / sizeof(fishKinds[0]))

int fishCount[NUM_FISH_KINDS] = {0};

void showFishList() {
    printf("+-----------------+------------------+\n");
    printf("| Fish Kind       | Caught Times     |\n");
    printf("+-----------------+------------------+\n");

    for (int i = 0; i < NUM_FISH_KINDS; i++) {
        if (fishCount[i] > 0) {
            printf("| %-15s | %-16d |\n", fishKinds[i], fishCount[i]);
        }
    }

    printf("+-----------------+------------------+\n");
}

int fishWeights[] = {
    20,  // Goldfish (Very common)
    15,  // Salmon (Common)
    10,  // Trout (Common)
    8,   // Bass (Common)
    12,  // Catfish (Common)
    5,   // Tuna (Uncommon)
    3,   // Swordfish (Rare)
    2,   // Shark (Very rare)
    6,   // Cod (Uncommon)
    4    // Carp (Uncommon)
};

const char* getRandomFish() {
    int totalWeight = 0;
    for (int i = 0; i < NUM_FISH_KINDS; i++) {
        totalWeight += fishWeights[i];
    }

    int randomValue = rand() % totalWeight + 1;

    int cumulativeWeight = 0;
    for (int i = 0; i < NUM_FISH_KINDS; i++) {
        cumulativeWeight += fishWeights[i];
        if (randomValue <= cumulativeWeight) {
            return fishKinds[i];
        }
    }

    return fishKinds[0];
}

void showLoadingScreen() {
    printf("Fishing ");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout); 
        usleep(500000); 
    }
    printf("\n");
    system("cls");
}

void fishing() {
    srand(time(NULL));

    char choice;

    do {
        showLoadingScreen();
        
        const char *fish1 = getRandomFish();
        const char *fish2 = getRandomFish();

        for (int i = 0; i < NUM_FISH_KINDS; i++) {
            if (fish1 == fishKinds[i]) {
                fishCount[i]++;
            }
            if (fish2 == fishKinds[i]) {
                fishCount[i]++;
            }
        }

        printf("You caught a %s and a %s!\n", fish1, fish2);
        
        printf("\nYou caught the following fish:\n");
        for (int i = 0; i < NUM_FISH_KINDS; i++) {
            if (fishCount[i] > 0) {
                printf("%s: %d times\n", fishKinds[i], fishCount[i]);
            }
        }

        printf("\nPress Enter to fish again, or press '0' to finish fishing.\n");
        choice = getchar();
        if (choice == '0') {
            break;
        }
        system("cls");

    } while (choice != '0');
}

void bubbleSortAlphabetically(char *fishNames[], int counts[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(fishNames[j], fishNames[j + 1]) > 0) {
                char *tempName = fishNames[j];
                fishNames[j] = fishNames[j + 1];
                fishNames[j + 1] = tempName;

                int tempCount = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = tempCount;
            }
        }
    }
}

void bubbleSortByCount(char *fishNames[], int counts[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (counts[j] < counts[j + 1]) {
                char *tempName = fishNames[j];
                fishNames[j] = fishNames[j + 1];
                fishNames[j + 1] = tempName;

                int tempCount = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = tempCount;
            }
        }
    }
}

void saveFishListToFile() {
    const char *filename = "daftar_ikan.txt";
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }

    for (int i = 0; i < NUM_FISH_KINDS; i++) {
        fprintf(file, "%s: %d\n", fishKinds[i], fishCount[i]);
    }

    fclose(file);
    printf("Daftar ikan berhasil disimpan ke file '%s'.\n", filename);
}

void readFishListFromFile() {
    const char *filename = "daftar_ikan.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk membaca.\n");
        return;
    }

    char buffer[100];
    printf("Daftar ikan:\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main() {
    int choice;

    do {
        puts("  ____        _         _   _            _    _             _    ");
        puts(" |  _ \\      | |       | | | |          | |  | |           | |   ");
        puts(" | |_) |_   _| |_ ___  | |_| |__   ___  | |__| | ___   ___ | | __");
        puts(" |  _ <| | | | __/ _ \\ | __| '_ \\ / _ \\ |  __  |/ _ \\ / _ \\| |/ /");
        puts(" | |_) | |_| | ||  __/ | |_| | | |  __/ | |  | | (_) | (_) |   < ");
        puts(" |____/ \\_,  |\\__\\___|  \\__|_| |_|\\___| |_|  |_|\\___/ \\___/|_|\\_\\");
        puts("         __/ |                                                   ");
        puts("        |___/                                                    ");
        puts(" ");
        printf("===== MENU =====\n");
        puts("1. Play");
        puts("2. List Ikan");
        puts("3. Simpan daftar ikan ke file");
        puts("4. Baca daftar ikan dari file");
        puts("5. Exit");
        printf(">> ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                system("cls");
                fishing();
                break;
            case 2:
                system("cls");
                printf("+-----------------+------------------+\n");
                printf("| Fish Kind       | Caught Times     |\n");
                printf("+-----------------+------------------+\n");

                int sortChoice;
                printf("Sort by:\n");
                printf("1. Alphabetically\n");
                printf("2. Caught Times\n");
                printf(">> ");
                scanf("%d", &sortChoice);
                getchar();

                if (sortChoice == 1) {
                    bubbleSortAlphabetically(fishKinds, fishCount, NUM_FISH_KINDS);
                } else if (sortChoice == 2) {
                    bubbleSortByCount(fishKinds, fishCount, NUM_FISH_KINDS);
                } else {
                    printf("Invalid option.\n");
                }

                for (int i = 0; i < NUM_FISH_KINDS; i++) {
                    if (fishCount[i] > 0) {
                        printf("| %-15s | %-16d |\n", fishKinds[i], fishCount[i]);
                    }
                }

                printf("+-----------------+------------------+\n");
                getchar();
                break;
            case 3:
                saveFishListToFile();
                getchar();
                break;
            case 4:
                system("cls");
                readFishListFromFile();
                getchar();
                break;
            case 5:
                printf("\nTerima kasih telah menggunakan program ini. Sampai jumpa!\n");
                return 0;
            default:
                printf("\nOpsi tidak valid. Silakan coba lagi.\n");
        }
        system("cls");
    } while (1);

    return 0;
}

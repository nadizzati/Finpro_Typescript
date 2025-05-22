#include <stdio.h>
#include <string.h>

// tingkat bahaya polusi
typedef enum {
    LOW,
    MODERATE,
    HIGH
} DangerLevel;

// data lokasi laut
typedef struct {
    char name[50];
    float plasticLevel;
    float oilLevel;
    float pesticideLevel;
    float heavyMetalLevel;
    float totalIndex;
    DangerLevel danger;
    int countPolutionTypes;
} SeaLocation;

// deklarasi function
void inputData(SeaLocation *loc);
void displayStatus(SeaLocation *loc, int index);
void printLine();
void calculateIndex(SeaLocation *loc);
void showDanger();


// fungsi main
int main(){
    int n, i;
    printf("=== Program Pemantauan Polusi Laut ===\n");
    printf("Masukkan jumlah lokasi laut: ");
    scanf("%d", &n);
    getchar();
    printf("\n");
    printLine();

    SeaLocation locations[n];

    for (i = 0; i < n; i++) {
        if (i > 0) {
            printLine();
        }
        printf("Lokasi ke-%d\n\n", i + 1);
        inputData(&locations[i]);       // Orang 1
        calculateIndex(&locations[i]);  // Orang 2
    }

    printf("\n=== Status Polusi Tiap Lokasi ===\n");
    for (i = 0; i < n; i++) {
        displayStatus(&locations[i], i + 1);  // Orang 3
    }
    printLine();

    showDanger();   // Orang 4

    printf("\n=== Daftar Lokasi dengan Polusi Berat (HIGH) ===\n");
    int foundHeavy = 0;
    for (i = 0; i < n; i++) {
        if (locations[i].danger == HIGH) {
            printf("- %s\n", locations[i].name);  // Orang 4
            foundHeavy = 1;
        }
    }
    if (!foundHeavy) {
        printf("Tidak ada lokasi dengan polusi berat.\n");  // Orang 4
    }
    printf("\n");
    return 0;
}


// fungsi untuk input data satu lokasi dengan menu loop untuk jenis polusi
void inputData(SeaLocation *loc) {
    printf("Masukkan lokasi laut: ");
    fgets(loc->name, sizeof(loc->name), stdin);
    loc->name[strcspn(loc->name, "\n")] = 0;

    // inisialisasi semua level polusi ke 0
    loc->plasticLevel = 0.0f;
    loc->oilLevel = 0.0f;
    loc->pesticideLevel = 0.0f;
    loc->heavyMetalLevel = 0.0f;
    loc->countPolutionTypes = 0;

    int pilihan;
    while (1) {
        printf("Pilih jenis polusi:\n");
        printf("  1. Plastik\n");
        printf("  2. Minyak\n");
        printf("  3. Pestisida\n");
        printf("  4. Logam Berat\n");
        printf("  5. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);

        if (pilihan == 5) {
            break;
        }

        float inputLevel;
        int validInput = 0;

        switch (pilihan) {
            case 1:
                if (loc->plasticLevel > 0) {
                    printf("Data plastik sudah diinput sebelumnya.\n");
                    break;
                }
                while (!validInput) {
                    printf("Masukkan tingkat polusi plastik (0-100): ");
                    scanf("%f", &inputLevel);
                    if (inputLevel >= 0 && inputLevel <= 100) {
                        loc->plasticLevel = inputLevel;
                        loc->countPolutionTypes++;
                        validInput = 1;
                    } else {
                        printf("Input tidak valid, masukkan angka antara 0 sampai 100.\n");
                    }
                }
                break;

            case 2:
                if (loc->oilLevel > 0) {
                    printf("Data minyak sudah diinput sebelumnya.\n");
                    break;
                }
                while (!validInput) {
                    printf("Masukkan tingkat polusi minyak (0-100): ");
                    scanf("%f", &inputLevel);
                    if (inputLevel >= 0 && inputLevel <= 100) {
                        loc->oilLevel = inputLevel;
                        loc->countPolutionTypes++;
                        validInput = 1;
                    } else {
                        printf("Input tidak valid, masukkan angka antara 0 sampai 100.\n");
                    }
                }
                break;

            case 3:
                if (loc->pesticideLevel > 0) {
                    printf("Data pestisida sudah diinput sebelumnya.\n");
                    break;
                }
                while (!validInput) {
                    printf("Masukkan tingkat pestisida (0-100): ");
                    scanf("%f", &inputLevel);
                    if (inputLevel >= 0 && inputLevel <= 100) {
                        loc->pesticideLevel = inputLevel;
                        loc->countPolutionTypes++;
                        validInput = 1;
                    } else {
                        printf("Input tidak valid, masukkan angka antara 0 sampai 100.\n");
                    }
                }
                break;

            case 4:
                if (loc->heavyMetalLevel > 0) {
                    printf("Data logam berat sudah diinput sebelumnya.\n");
                    break;
                }
                while (!validInput) {
                    printf("Masukkan tingkat logam berat (0-100): ");
                    scanf("%f", &inputLevel);
                    if (inputLevel >= 0 && inputLevel <= 100) {
                        loc->heavyMetalLevel = inputLevel;
                        loc->countPolutionTypes++;
                        validInput = 1;
                    } else {
                        printf("Input tidak valid, masukkan angka antara 0 sampai 100.\n");
                    }
                }
                break;

            default:
                printf("Pilihan tidak valid, coba lagi.\n");
                break;
        }
        printf("\n");
    }
    getchar();
}

void calculateIndex(SeaLocation *loc) {
    if (loc->countPolutionTypes == 0) {
        loc->totalIndex = 0.0f;
        loc->danger = LOW;
        return;
    }

    float total = 0.0f;
    if (loc->plasticLevel > 0) total += loc->plasticLevel;
    if (loc->oilLevel > 0) total += loc->oilLevel;
    if (loc->pesticideLevel > 0) total += loc->pesticideLevel;
    if (loc->heavyMetalLevel > 0) total += loc->heavyMetalLevel;

    loc->totalIndex = total / (float)(loc->countPolutionTypes);

    if (loc->totalIndex < 30) {
        loc->danger = LOW;
    } else if (loc->totalIndex < 70) {
        loc->danger = MODERATE;
    } else {
        loc->danger = HIGH;
    }
}

//fungsi untuk display status perlokasi
void displayStatus(SeaLocation *loc, int index) {
	printf("Lokasi %d: %s\n", index, loc->name);
	if(loc->plasticLevel > 0) {
		printf(" Plastik     : %.2f\n", loc->plasticLevel);
	}
	if(loc->oilLevel > 0) {
		printf(" Minyak      : %.2f\n", loc->oilLevel);
	}
	if(loc->pesticideLevel > 0) {
		printf(" Pestisida   : %.2f\n", loc->pesticideLevel);
	}
	if(loc->heavyMetalLevel > 0) {
		printf(" Logam Berat : %.2f\n", loc->heavyMetalLevel);
	}
	
	printf(" Indeks Total : %.2f\n", loc->totalIndex);
	printf(" Status Bahaya: ");
	
	switch(loc->danger) {
		case LOW: printf("LOW\n");
		break;
		case MODERATE: printf("MODERATE\n");
		break;
		case HIGH: printf("HIGH\n");
		break;
		default: printf("UNKNOWN\n");
	} printf("\n");
}

void printLine() {
	printf("-------------------------------\n");
}
void showDanger() {
    printf("\n=== Status Bahaya ===\n");
    printf("LOW      : Polusi rendah, kondisi masih aman\n");
    printf("MODERATE : Polusi sedang, perlu perhatian lebih\n");
    printf("HIGH     : Polusi berat, berbahaya bagi lingkungan\n");
}


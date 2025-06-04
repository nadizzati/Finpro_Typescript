#include <stdio.h>
#include <string.h>
#include <math.h> // Untuk fungsi fabs (pH)

// Tingkat bahaya polusi
typedef enum {
    AMAN,
    SEDANG,
    TINGGI,
    SANGAT_TINGGI
} DangerLevel;

// Data lokasi laut
typedef struct {
    char name[50];
    float plasticConcentration;  
    float metalConcentration;    
    float oilConcentration;      
    float b3Concentration;       
    float pH;                    
    float plasticIndex;
    float metalIndex;
    float oilIndex;
    float b3Index;
    float pHIndex;
    float totalIndex;
    DangerLevel danger;
    int countPolutionTypes;
} SeaLocation;

// Deklarasi function
void inputData(SeaLocation *loc);
void displayStatus(SeaLocation *loc, int index);
void printLine();
void calculateIndex(SeaLocation *loc);
void showDanger();
void sortLocations(SeaLocation *locations, int n, int sortType);
void displayAllLocations(SeaLocation *locations, int n);

// Baku mutu lingkungan (standar konsentrasi maksimum)
#define PLASTIC_STANDARD 1.0f     
#define METAL_STANDARD 0.05f      
#define OIL_STANDARD 1.0f         
#define B3_STANDARD 0.1f           
#define PH_STANDARD_MIN 7.5f       
#define PH_STANDARD_MAX 8.5f        

// Fungsi main
int main() {
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
        inputData(&locations[i]);
        calculateIndex(&locations[i]);
    }

    int sortChoice;
    printf("\n=== Pilihan Tampilan Data ===\n");
    printf("1. Tampilkan berdasarkan IPL (Total Indeks Polusi Laut) tertinggi\n");
    printf("2. Tampilkan berdasarkan IPL terendah\n");
    printf("3. Tampilkan berdasarkan konsentrasi plastik tertinggi\n");
    printf("4. Tampilkan berdasarkan konsentrasi logam berat tertinggi\n");
    printf("5. Tampilkan berdasarkan konsentrasi minyak tertinggi\n");
    printf("6. Tampilkan berdasarkan konsentrasi B3 tertinggi\n");
    printf("7. Tampilkan berdasarkan penyimpangan pH terbesar\n");
    printf("8. Tampilkan semua data tanpa pengurutan\n");
    printf("Masukkan pilihan Anda (1-8): ");
    scanf("%d", &sortChoice);

    if (sortChoice >= 1 && sortChoice <= 7) {
        sortLocations(locations, n, sortChoice);
    }

    printf("\n=== Status Polusi Tiap Lokasi ===\n");
    displayAllLocations(locations, n);
    printLine();

    showDanger();

    printf("\n=== Daftar Lokasi dengan Polusi Berat (TINGGI/SANGAT TINGGI) ===\n");
    int foundHeavy = 0;
    for (i = 0; i < n; i++) {
        if (locations[i].danger == TINGGI || locations[i].danger == SANGAT_TINGGI) {
            printf("- %s (IPL: %.2f)\n", locations[i].name, locations[i].totalIndex);
            foundHeavy = 1;
        }
    }
    if (!foundHeavy) {
        printf("Tidak ada lokasi dengan polusi berat.\n");
    }
    printf("\n");
    return 0;
}

// Fungsi untuk mengurutkan lokasi berdasarkan kriteria tertentu
void sortLocations(SeaLocation *locations, int n, int sortType) {
    int i, j;
    SeaLocation temp;

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            int shouldSwap = 0;
            float diff1, diff2;
            
            switch (sortType) {
                case 1: // IPL tertinggi
                    shouldSwap = locations[j].totalIndex < locations[j+1].totalIndex;
                    break;
                case 2: // IPL terendah
                    shouldSwap = locations[j].totalIndex > locations[j+1].totalIndex;
                    break;
                case 3: // Plastik tertinggi
                    shouldSwap = locations[j].plasticConcentration < locations[j+1].plasticConcentration;
                    break;
                case 4: // Logam berat tertinggi
                    shouldSwap = locations[j].metalConcentration < locations[j+1].metalConcentration;
                    break;
                case 5: // Minyak tertinggi
                    shouldSwap = locations[j].oilConcentration < locations[j+1].oilConcentration;
                    break;
                case 6: // B3 tertinggi
                    shouldSwap = locations[j].b3Concentration < locations[j+1].b3Concentration;
                    break;
                case 7: // Penyimpangan pH terbesar
                    diff1 = fabs(locations[j].pH - 8.0f); 
                    diff2 = fabs(locations[j+1].pH - 8.0f);
                    shouldSwap = diff1 < diff2;
                    break;
            }

            if (shouldSwap) {
                temp = locations[j];
                locations[j] = locations[j+1];
                locations[j+1] = temp;
            }
        }
    }
}

// Fungsi untuk menampilkan semua lokasi
void displayAllLocations(SeaLocation *locations, int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printLine();
        }
        displayStatus(&locations[i], i + 1);
    }
}

void inputData(SeaLocation *loc) {
    printf("Masukkan nama lokasi laut: ");
    fgets(loc->name, sizeof(loc->name), stdin);
    loc->name[strcspn(loc->name, "\n")] = 0;

    // Inisialisasi semua konsentrasi ke 0
    loc->plasticConcentration = 0.0f;
    loc->metalConcentration = 0.0f;
    loc->oilConcentration = 0.0f;
    loc->b3Concentration = 0.0f;
    loc->pH = 0.0f;
    loc->countPolutionTypes = 0;

    int pilihan;
    while (1) {
        printf("\nPilih jenis polusi:\n");
        printf("  1. Plastik (mg/m^3)\n");
        printf("  2. Logam Berat (mg/L)\n");
        printf("  3. Minyak (mg/L)\n");
        printf("  4. Bahan Berbahaya dan Beracun - B3 (mg/L)\n");
        printf("  5. pH\n");
        printf("  6. Selesai\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);

        if (pilihan == 6) {
            break;
        }

        float inputValue;
        int validInput = 0;

        switch (pilihan) {
            case 1:
                if (loc->plasticConcentration > 0) {
                    printf("Data plastik sudah diinput sebelumnya.\n");
                    break;
                }
                while (!validInput) {
                    printf("Masukkan konsentrasi plastik (mg/m^3): ");
                    scanf("%f", &inputValue);
                    if (inputValue >= 0) {
                        loc->plasticConcentration = inputValue;
                        loc->countPolutionTypes++;
                        validInput = 1;
                    } else {
                        printf("Input tidak valid, masukkan angka non-negatif.\n");
                    }
                }
                break;

            case 2:
                if (loc->metalConcentration > 0) {
                    printf("Data logam berat sudah diinput sebelumnya.\n");
                    break;
                }
                while (!validInput) {
                    printf("Masukkan konsentrasi logam berat (mg/L): ");
                    scanf("%f", &inputValue);
                    if (inputValue >= 0) {
                        loc->metalConcentration = inputValue;
                        loc->countPolutionTypes++;
                        validInput = 1;
                    } else {
                        printf("Input tidak valid, masukkan angka non-negatif.\n");
                    }
                }
                break;

            case 3:
                if (loc->oilConcentration > 0) {
                    printf("Data minyak sudah diinput sebelumnya.\n");
                    break;
                }
                while (!validInput) {
                    printf("Masukkan konsentrasi minyak (mg/L): ");
                    scanf("%f", &inputValue);
                    if (inputValue >= 0) {
                        loc->oilConcentration = inputValue;
                        loc->countPolutionTypes++;
                        validInput = 1;
                    } else {
                        printf("Input tidak valid, masukkan angka non-negatif.\n");
                    }
                }
                break;

            case 4:
                if (loc->b3Concentration > 0) {
                    printf("Data B3 sudah diinput sebelumnya.\n");
                    break;
                }
                while (!validInput) {
                    printf("Masukkan konsentrasi B3 (mg/L): ");
                    scanf("%f", &inputValue);
                    if (inputValue >= 0) {
                        loc->b3Concentration = inputValue;
                        loc->countPolutionTypes++;
                        validInput = 1;
                    } else {
                        printf("Input tidak valid, masukkan angka non-negatif.\n");
                    }
                }
                break;

            case 5:
                if (loc->pH > 0) {
                    printf("Data pH sudah diinput sebelumnya.\n");
                    break;
                }
                while (!validInput) {
                    printf("Masukkan nilai pH (0-14): ");
                    scanf("%f", &inputValue);
                    if (inputValue >= 0 && inputValue <= 14) {
                        loc->pH = inputValue;
                        loc->countPolutionTypes++;
                        validInput = 1;
                    } else {
                        printf("Input tidak valid, masukkan angka antara 0-14.\n");
                    }
                }
                break;

            default:
                printf("Pilihan tidak valid, coba lagi.\n");
                break;
        }
    }
    getchar();
}

void calculateIndex(SeaLocation *loc) {
    if (loc->countPolutionTypes == 0) {
        loc->totalIndex = 0.0f;
        loc->danger = AMAN;
        return;
    }

    // Hitung indeks untuk masing-masing parameter
    loc->plasticIndex = loc->plasticConcentration / PLASTIC_STANDARD;
    loc->metalIndex = loc->metalConcentration / METAL_STANDARD;
    loc->oilIndex = loc->oilConcentration / OIL_STANDARD;
    loc->b3Index = loc->b3Concentration / B3_STANDARD;
    
    // Hitung indeks pH (berdasarkan penyimpangan dari range normal)
    if (loc->pH > 0) {
        if (loc->pH < PH_STANDARD_MIN) {
            loc->pHIndex = (PH_STANDARD_MIN - loc->pH) / PH_STANDARD_MIN;
        } else if (loc->pH > PH_STANDARD_MAX) {
            loc->pHIndex = (loc->pH - PH_STANDARD_MAX) / (14.0f - PH_STANDARD_MAX);
        } else {
            loc->pHIndex = 0.0f; // Dalam range normal
        }
    }

    // Hitung IPL dengan bobot sama (w=1 untuk semua parameter)
    float total = 0.0f;
    int count = 0;
    
    if (loc->plasticConcentration > 0) {
        total += loc->plasticIndex;
        count++;
    }
    if (loc->metalConcentration > 0) {
        total += loc->metalIndex;
        count++;
    }
    if (loc->oilConcentration > 0) {
        total += loc->oilIndex;
        count++;
    }
    if (loc->b3Concentration > 0) {
        total += loc->b3Index;
        count++;
    }
    if (loc->pH > 0) {
        total += loc->pHIndex;
        count++;
    }

    loc->totalIndex = (count > 0) ? total / count : 0.0f;

    // Tentukan tingkat bahaya
    if (loc->totalIndex < 1) {
        loc->danger = AMAN;
    } else if (loc->totalIndex < 2) {
        loc->danger = SEDANG;
    } else if (loc->totalIndex < 3) {
        loc->danger = TINGGI;
    } else {
        loc->danger = SANGAT_TINGGI;
    }
}

// Fungsi untuk display status per lokasi
void displayStatus(SeaLocation *loc, int index) {
    printf("\nLokasi %d: %s\n", index, loc->name);
    
    if (loc->plasticConcentration > 0) {
        printf(" Plastik      : %.2f mg/m^3 (Indeks: %.2f)\n", 
            loc->plasticConcentration, loc->plasticIndex);
    }
    if (loc->metalConcentration > 0) {
        printf(" Logam Berat  : %.2f mg/L (Indeks: %.2f)\n", 
            loc->metalConcentration, loc->metalIndex);
    }
    if (loc->oilConcentration > 0) {
        printf(" Minyak       : %.2f mg/L (Indeks: %.2f)\n", 
            loc->oilConcentration, loc->oilIndex);
    }
    if (loc->b3Concentration > 0) {
        printf(" B3           : %.2f mg/L (Indeks: %.2f)\n",
            loc->b3Concentration, loc->b3Index);
    }
    if (loc->pH > 0) {
        printf(" pH           : %.2f (Indeks: %.2f)\n",
            loc->pH, loc->pHIndex);
    }
    
    printf("\nIndeks Polusi Laut (IPL): %.2f\n", loc->totalIndex);
    printf("Status Bahaya: ");
    
    switch(loc->danger) {
        case AMAN: printf("AMAN (Rendah)\n"); break;
        case SEDANG: printf("SEDANG\n"); break;
        case TINGGI: printf("TINGGI\n"); break;
        case SANGAT_TINGGI: printf("SANGAT TINGGI (Berbahaya)\n"); break;
        default: printf("UNKNOWN\n");
    }
}

void printLine() {
    printf("------------------------------------\n");
}

void showDanger() {
    printf("\n=== Status Bahaya Berdasarkan IPL ===\n");
    printf("IPL < 1   : AMAN (Polusi rendah)\n");
    printf("IPL 1-2   : SEDANG (Perlu perhatian)\n");
    printf("IPL 2-3   : TINGGI (Berbahaya)\n");
    printf("IPL >= 3  : SANGAT TINGGI (Sangat berbahaya)\n");
}
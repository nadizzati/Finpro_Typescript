#include <stdio.h>
#include <string.h>
#include <math.h> 

// tingkat bahaya polusi
typedef enum {
    LOW,
    MODERATE,
    HIGH
} DangerLevel;

// data lokasi laut
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

// deklarasi function
void inputData(SeaLocation *loc);
void displayStatus(SeaLocation *loc, int index);
void printLine();
void calculateIndex(SeaLocation *loc);
void showDanger();
void sortLocations(SeaLocation *locations, int n, int sortType);
void displayAllLocations(SeaLocation *locations, int n);

// baku mutu lingkungan (standar konsentrasi maksimum)
#define PLASTIC_STANDARD 1.0f      
#define METAL_STANDARD 0.05f      
#define OIL_STANDARD 1.0f       
#define B3_STANDARD 0.1f          
#define PH_STANDARD_MIN 7.5f       
#define PH_STANDARD_MAX 8.5f        

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
        inputData(&locations[i]); 
        calculateIndex(&locations[i]);  
    }

    printf("\n=== Status Polusi Tiap Lokasi ===\n");
    for (i = 0; i < n; i++) {
        displayStatus(&locations[i], i + 1);
    }
    printLine();

    showDanger();

    printf("\n=== Daftar Lokasi dengan Polusi Berat (HIGH) ===\n");
    int foundHeavy = 0;
    for (i = 0; i < n; i++) {
        if (locations[i].danger == HIGH) {
            printf("- %s\n", locations[i].name);
            foundHeavy = 1;
        }
    }
    if (!foundHeavy) {
        printf("Tidak ada lokasi dengan polusi berat.\n");
    }
    printf("\n");
    return 0;
}


// fungsi untuk input data satu lokasi dengan menu loop untuk jenis polusi
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

void calculateIndex(SeaLocation *loc) {
    if (loc->countPolutionTypes == 0) {
        loc->totalIndex = 0.0f;
        loc->danger = AMAN;
        return;
    }

    // Hitung indeks
    loc->plasticIndex = loc->plasticConcentration / PLASTIC_STANDARD;
    loc->metalIndex = loc->metalConcentration / METAL_STANDARD;
    loc->oilIndex = loc->oilConcentration / OIL_STANDARD;
    loc->b3Index = loc->b3Concentration / B3_STANDARD;
    
    // Hitung indeks pH
    if (loc->pH > 0) {
        if (loc->pH < PH_STANDARD_MIN) {
            loc->pHIndex = (PH_STANDARD_MIN - loc->pH) / PH_STANDARD_MIN;
        } else if (loc->pH > PH_STANDARD_MAX) {
            loc->pHIndex = (loc->pH - PH_STANDARD_MAX) / (14.0f - PH_STANDARD_MAX);
        } else {
            loc->pHIndex = 0.0f;
        }
    }

     // Hitung IPL dengan bobot sama
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

//display status per lokasi
void displayStatus(SeaLocation *loc, int index) {
	printf("\nLokasi %d: %s\n", index, loc->name);
	if(loc->plasticConcentration > 0) {
		printf(" Plastik     : %.2f mg/m^3 (Indeks: %.2f)\n", loc->plasticConcentration, loc->plasticIndex);
	}
	if(loc->metalConcentration > 0) {
		printf(" Logam Berat : %.2f mg/L (Indeks: %.2f)\n", loc->metalConcentration, loc->metalIndex);
	}
	if(loc->oilConcentration > 0) {
		printf(" Minyak      : %.2f mg/L (Indeks: %.2f)\n", loc->oilConcentration, loc->oilIndex);
	}
	if(loc->b3Concentration > 0) {
		printf(" B3          : %.2f mg/L (Indeks: %.2f)\n", loc->b3Concentration, loc->b3Index);
	}
	if(loc->pH > 0) {
		printf(" pH          : %.2f (Indeks: %.2f)\n", loc->pH, loc->pHIndex);
	}

	printf("\nIndeks Polusi laut (IPL): %.2f\n", loc->totalIndex);
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
	printf("IPL < 1  : AMAN (Polusi rendah)\n");
	printf("IPL 1-2  : SEDANG (Perlu perhatian)\n");
	printf("IPL 2-3  : TINGGI (Berbahaya)\n");
	printf("IPL >= 3 : SANGAT TINGGI (Sangat Berbahaya)\n");
}


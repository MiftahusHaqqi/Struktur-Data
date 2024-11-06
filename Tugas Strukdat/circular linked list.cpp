#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

// Prototipe fungsi
void tambahAwal(node **list);
void tambahData(node **list);
void tambahAkhir(node **list);
void hapusAwal(node **list);
void hapusTengah(node **list);
void hapusAkhir(node **list);
void cariData(node *list);
void hitungJumlahData(node *list);
void jumlahkanSemuaData(node *list);
void tranverse(node *list);

//========================================================

int main() {
    node *list;
    char pilih;

    list = NULL; // Circular list dimulai dari NULL
    do {
        system("cls");
        printf("Masukkan pilihan\n");
        printf("a. Tambah data di awal\n");
        printf("b. Tambah data di tengah list\n");
        printf("c. Tambah data di akhir\n");
        printf("d. Cetak isi list\n");
        printf("e. Hapus data di awal\n");
        printf("f. Hapus data di tengah list\n");
        printf("g. Hapus data di akhir\n");
        printf("h. Cari data\n");
        printf("i. Tampilkan jumlah data\n");
        printf("j. Tampilkan jumlah semua data\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);

        switch (pilih) {
            case 'a':
                tambahAwal(&list);
                break;
            case 'b':
                tambahData(&list);
                break;
            case 'c':
                tambahAkhir(&list);
                break;
            case 'd':
                tranverse(list);
                getch();
                break;
            case 'e':
                hapusAwal(&list);
                break;
            case 'f':
                hapusTengah(&list);
                break;
            case 'g':
                hapusAkhir(&list);
                break;
            case 'h':
                cariData(list);
                getch();
                break;
            case 'i':
                hitungJumlahData(list);
                getch();
                break;
            case 'j':
                jumlahkanSemuaData(list);
                getch();
                break;
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **list) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;

        if (*list == NULL) {
            // Jika list kosong, node pertama menunjuk ke dirinya sendiri
            *list = pNew;
            pNew->next = *list;
        } else {
            // Jika tidak kosong, tambahkan di depan dan hubungkan node terakhir ke node baru
            pCur = *list;
            while (pCur->next != *list) {
                pCur = pCur->next;
            }
            pNew->next = *list;
            pCur->next = pNew;
            *list = pNew; // `list` menunjuk ke node baru di awal
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **list) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*list);
    printf("\nposisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    if (*list == NULL) {
        printf("List masih kosong, silakan tambahkan di awal terlebih dahulu");
        getch();
        return;
    }

    pCur = *list;
    do {
        if (pCur->data == pos) break;
        pCur = pCur->next;
    } while (pCur != *list);

    pNew = (node *)malloc(sizeof(node));
    if (pCur == *list && pCur->data != pos) {
        printf("Node tidak ditemukan\n");
        getch();
    } else if (pNew == NULL) {
        printf("Alokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
    }
}

//========================================================

void tambahAkhir(node **list) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        if (*list == NULL) {
            // Jika list kosong, node pertama menunjuk ke dirinya sendiri
            *list = pNew;
            pNew->next = *list;
        } else {
            pCur = *list;
            while (pCur->next != *list) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->next = *list;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void hapusAwal(node **list) {
    node *pTemp, *pCur;

    system("cls");
    if (*list != NULL) {
        if ((*list)->next == *list) { // Hanya satu node
            pTemp = *list;
            *list = NULL;
            free(pTemp);
        } else {
            pCur = *list;
            while (pCur->next != *list) {
                pCur = pCur->next;
            }
            pTemp = *list;
            pCur->next = (*list)->next;
            *list = (*list)->next;
            free(pTemp);
        }
        printf("Data awal berhasil dihapus");
    } else {
        printf("List kosong, tidak ada data yang dapat dihapus");
    }
    getch();
}

//========================================================

void hapusTengah(node **list) {
    int pos;
    node *pCur, *pTemp;

    system("cls");
    tranverse(*list);
    printf("\nMasukkan nilai data yang ingin dihapus: ");
    fflush(stdin);
    scanf("%d", &pos);

    if (*list == NULL) {
        printf("List kosong, tidak ada data yang dapat dihapus");
    } else if ((*list)->data == pos) {
        hapusAwal(list);
    } else {
        pCur = *list;
        while (pCur->next != *list && pCur->next->data != pos) {
            pCur = pCur->next;
        }
        if (pCur->next == *list) {
            printf("Node tidak ditemukan");
        } else {
            pTemp = pCur->next;
            pCur->next = pTemp->next;
            free(pTemp);
            printf("Data berhasil dihapus");
        }
    }
    getch();
}

//========================================================

void hapusAkhir(node **list) {
    node *pCur, *pTemp;

    system("cls");
    if (*list == NULL) {
        printf("List kosong, tidak ada data yang dapat dihapus");
    } else if ((*list)->next == *list) {
        pTemp = *list;
        *list = NULL;
        free(pTemp);
        printf("Data akhir berhasil dihapus");
    } else {
        pCur = *list;
        while (pCur->next->next != *list) {
            pCur = pCur->next;
        }
        pTemp = pCur->next;
        pCur->next = *list;
        free(pTemp);
        printf("Data akhir berhasil dihapus");
    }
    getch();
}

//========================================================

void cariData(node *list) {
    int bil, found = 0;
    node *pCur = list;

    system("cls");
    printf("Masukkan bilangan yang dicari: ");
    fflush(stdin);
    scanf("%d", &bil);

    if (list == NULL) {
        printf("List kosong\n");
        return;
    }

    do {
        if (pCur->data == bil) {
            printf("Data %d ditemukan!\n", bil);
            found = 1;
            break;
        }
        pCur = pCur->next;
    } while (pCur != list);

    if (!found) {
        printf("Data %d tidak ditemukan.\n", bil);
    }
}

//========================================================

void hitungJumlahData(node *list) {
    int count = 0;
    node *pCur = list;

    system("cls");
    if (list == NULL) {
        printf("Jumlah data dalam linked list: 0\n");
        return;
    }

    do {
        count++;
        pCur = pCur->next;
    } while (pCur != list);

    printf("Jumlah data dalam linked list: %d\n", count);
}

//========================================================

void jumlahkanSemuaData(node *list) {
    int sum = 0;
    node *pCur = list;

    system("cls");
    if (list == NULL) {
        printf("Jumlah semua data dalam linked list: 0\n");
        return;
    }

    do {
        sum += pCur->data;
        pCur = pCur->next;
    } while (pCur != list);

    printf("Jumlah semua data dalam linked list: %d\n", sum);
}

//========================================================

void tranverse(node *list) {
    node *pWalker;

    system("cls");
    if (list == NULL) {
        printf("List kosong\n");
        return;
    }

    pWalker = list;
    do {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    } while (pWalker != list);
    printf("... (Circular)\n");
}


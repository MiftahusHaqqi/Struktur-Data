#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Definisi struktur node untuk double linked list
struct node {
    int data;
    struct node *left;
    struct node *right;
};
typedef struct node node;

// Prototipe fungsi
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void hitungJumlahData(node *head);
void jumlahkanSemuaData(node *head);
void traverse(node *head);

int main() {
    node *head = NULL;
    char pilih;

    do {
        system("cls");
        printf("Masukkan pilihan:\n");
        printf("a. Tambah data di awal\n");
        printf("b. Tambah data di tengah\n");
        printf("c. Tambah data di akhir\n");
        printf("d. Cetak isi list\n");
        printf("e. Hapus data di awal\n");
        printf("f. Hapus data di tengah\n");
        printf("g. Hapus data di akhir\n");
        printf("h. Cari data\n");
        printf("i. Tampilkan jumlah data\n");
        printf("j. Jumlahkan semua data\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar): ");
        fflush(stdin);
        scanf("%c", &pilih);

        if (pilih == 'a') {
            tambahAwal(&head);
        } else if (pilih == 'b') {
            tambahData(&head);
        } else if (pilih == 'c') {
            tambahAkhir(&head);
        } else if (pilih == 'd') {
            traverse(head);
            getch();
        } else if (pilih == 'e') {
            hapusAwal(&head);
        } else if (pilih == 'f') {
            hapusTengah(&head);
        } else if (pilih == 'g') {
            hapusAkhir(&head);
        } else if (pilih == 'h') {
            cariData(head);
            getch();
        } else if (pilih == 'i') {
            hitungJumlahData(head);
            getch();
        } else if (pilih == 'j') {
            jumlahkanSemuaData(head);
            getch();
        }
    } while (pilih != 'q');

    return 0;
}

// Fungsi untuk menambah node di awal
void tambahAwal(node **head) {
    int bil;
    node *pNew = (node *)malloc(sizeof(node));

    system("cls");
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);
    pNew->data = bil;
    pNew->left = NULL;
    pNew->right = *head;

    if (*head != NULL) {
        (*head)->left = pNew;
    }

    *head = pNew;
}

// Fungsi untuk menambah node di tengah
void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    traverse(*head);
    printf("\nPosisi penyisipan setelah data bernilai: ");
    scanf("%d", &pos);
    printf("\nMasukkan bilangan: ");
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->right;
    }

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
        return;
    }

    pNew = (node *)malloc(sizeof(node));
    pNew->data = bil;
    pNew->left = pCur;
    pNew->right = pCur->right;

    if (pCur->right != NULL) {
        pCur->right->left = pNew;
    }

    pCur->right = pNew;
}

// Fungsi untuk menambah node di akhir
void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    pNew->data = bil;
    pNew->right = NULL;

    if (*head == NULL) {
        pNew->left = NULL;
        *head = pNew;
    } else {
        pCur = *head;
        while (pCur->right != NULL) {
            pCur = pCur->right;
        }
        pCur->right = pNew;
        pNew->left = pCur;
    }
}

// Fungsi untuk menghapus node di awal
void hapusAwal(node **head) {
    node *pTemp;

    system("cls");
    if (*head != NULL) {
        pTemp = *head;
        *head = (*head)->right;
        if (*head != NULL) {
            (*head)->left = NULL;
        }
        free(pTemp);
        printf("Data awal berhasil dihapus");
    } else {
        printf("List kosong, tidak ada data yang dapat dihapus");
    }
    getch();
}

// Fungsi untuk menghapus node di tengah
void hapusTengah(node **head) {
    int pos;
    node *pCur;

    system("cls");
    traverse(*head);
    printf("\nMasukkan nilai data yang ingin dihapus: ");
    scanf("%d", &pos);

    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dapat dihapus");
        getch();
        return;
    }

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->right;
    }

    if (pCur == NULL) {
        printf("Node tidak ditemukan");
        getch();
        return;
    }

    if (pCur->left != NULL) {
        pCur->left->right = pCur->right;
    } else {
        *head = pCur->right;
    }

    if (pCur->right != NULL) {
        pCur->right->left = pCur->left;
    }

    free(pCur);
    printf("Data berhasil dihapus");
    getch();
}

// Fungsi untuk menghapus node di akhir
void hapusAkhir(node **head) {
    node *pCur;

    system("cls");
    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dapat dihapus");
        getch();
        return;
    }

    pCur = *head;
    while (pCur->right != NULL) {
        pCur = pCur->right;
    }

    if (pCur->left != NULL) {
        pCur->left->right = NULL;
    } else {
        *head = NULL;
    }

    free(pCur);
    printf("Data akhir berhasil dihapus");
    getch();
}

// Fungsi untuk mencari data
void cariData(node *head) {
    int bil, found = 0;
    node *pCur = head;

    system("cls");
    printf("Masukkan bilangan yang dicari: ");
    scanf("%d", &bil);

    while (pCur != NULL) {
        if (pCur->data == bil) {
            printf("Data %d ditemukan!\n", bil);
            found = 1;
            break;
        }
        pCur = pCur->right;
    }
    if (!found) {
        printf("Data %d tidak ditemukan.\n", bil);
    }
}

// Fungsi untuk menghitung jumlah data
void hitungJumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    system("cls");
    while (pCur != NULL) {
        count++;
        pCur = pCur->right;
    }
    printf("Jumlah data dalam linked list: %d\n", count);
}

// Fungsi untuk menjumlahkan semua data
void jumlahkanSemuaData(node *head) {
    int sum = 0;
    node *pCur = head;

    system("cls");
    while (pCur != NULL) {
        sum += pCur->data;
        pCur = pCur->right;
    }
    printf("Jumlah semua data dalam linked list: %d\n", sum);
}

// Fungsi untuk menampilkan list
void traverse(node *head) {
    node *pCur = head;

    system("cls");
    if (head == NULL) {
        printf("List kosong\n");
    } else {
        while (pCur != NULL) {
            printf("%d -> ", pCur->data);
            pCur = pCur->right;
        }
        printf("NULL\n");
    }
}


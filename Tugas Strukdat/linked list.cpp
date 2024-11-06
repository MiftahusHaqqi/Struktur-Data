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
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void hitungJumlahData(node *head);
void jumlahkanSemuaData(node *head);
void tranverse(node *head);

//========================================================

int main() {
    node *head;
    char pilih;

    head = NULL;
    do {
        system("cls");
        printf("masukkan pilihan\n");
        printf("a. tambah data di awal\n");
        printf("b. tambah data di tengah list\n");
        printf("c. tambah data di akhir\n");
        printf("d. cetak isi list\n");
        printf("e. hapus data di awal\n");
        printf("f. hapus data di tengah list\n");
        printf("g. hapus data di akhir\n");
        printf("h. cari data\n");
        printf("i. tampilkan jumlah data\n");
        printf("j. tampilkan jumlah semua data\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);
        if (pilih == 'a')
            tambahAwal(&head);
        else if (pilih == 'b')
            tambahData(&head);
        else if (pilih == 'c')
            tambahAkhir(&head);
        else if (pilih == 'd') {
            tranverse(head);
            getch();
        } else if (pilih == 'e')
            hapusAwal(&head);
        else if (pilih == 'f')
            hapusTengah(&head);
        else if (pilih == 'g')
            hapusAkhir(&head);
        else if (pilih == 'h') {
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

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur -> data != pos) {
        pCur = pCur -> next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nnode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nalokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) { // List kosong
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) { // Cari node terakhir
                pCur = pCur->next;
            }
            pCur->next = pNew;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void hapusAwal(node **head) {
    node *pTemp;

    system("cls");
    if (*head != NULL) {
        pTemp = *head;
        *head = (*head)->next;
        free(pTemp);
        printf("Data awal berhasil dihapus");
    } else {
        printf("List kosong, tidak ada data yang dapat dihapus");
    }
    getch();
}

//========================================================

void hapusTengah(node **head) {
    int pos;
    node *pCur, *pTemp;

    system("cls");
    tranverse(*head);
    printf("\nMasukkan nilai data yang ingin dihapus: ");
    fflush(stdin);
    scanf("%d", &pos);

    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dapat dihapus");
    } else if ((*head)->data == pos) {
        hapusAwal(head);
    } else {
        pCur = *head;
        while (pCur->next != NULL && pCur->next->data != pos) {
            pCur = pCur->next;
        }
        if (pCur->next == NULL) {
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

void hapusAkhir(node **head) {
    node *pCur, *pTemp;

    system("cls");
    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dapat dihapus");
    } else if ((*head)->next == NULL) {
        pTemp = *head;
        *head = NULL;
        free(pTemp);
        printf("Data akhir berhasil dihapus");
    } else {
        pCur = *head;
        while (pCur->next->next != NULL) { // Mencari node sebelum node terakhir
            pCur = pCur->next;
        }
        pTemp = pCur->next;
        pCur->next = NULL;
        free(pTemp);
        printf("Data akhir berhasil dihapus");
    }
    getch();
}

//========================================================

void cariData(node *head) {
    int bil, found = 0;
    node *pCur = head;

    system("cls");
    printf("Masukkan bilangan yang dicari: ");
    fflush(stdin);
    scanf("%d", &bil);

    while (pCur != NULL) {
        if (pCur->data == bil) {
            printf("Data %d ditemukan!\n", bil);
            found = 1;
            break;
        }
        pCur = pCur->next;
    }
    if (!found) {
        printf("Data %d tidak ditemukan.\n", bil);
    }
}

//========================================================

void hitungJumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    system("cls");
    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }
    printf("Jumlah data dalam linked list: %d\n", count);
}

//========================================================

void jumlahkanSemuaData(node *head) {
    int sum = 0;
    node *pCur = head;

    system("cls");
    while (pCur != NULL) {
        sum += pCur->data;
        pCur = pCur->next;
    }
    printf("Jumlah semua data dalam linked list: %d\n", sum);
}

//========================================================

void tranverse(node *head) {
    node *pWalker;

    system("cls");
    pWalker = head;
    while (pWalker != NULL) {
        printf("%d\t", pWalker->data);
        pWalker = pWalker->next;
        printf(" -> ");
    }
    printf("NULL\n");
}


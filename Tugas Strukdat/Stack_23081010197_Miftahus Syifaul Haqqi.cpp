#include <stdio.h>
#include <stdlib.h>
 
 // Nama : Miftahus Syifaul Haqqi
 // NPM : 23081010197
 
typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct stack {
    node *top;
    int count;
    int maxSize;
} stack;

void initStack(stack *s, int maxSize) {
    s->top = NULL;
    s->count = 0;
    s->maxSize = maxSize;
}

int isFull(stack *s) {
    return s->count >= s->maxSize;
}

int isEmpty(stack *s) {
    return s->count == 0;
}

int push(stack *s, int data) {
    if (isFull(s)) {
        printf("Stack sudah penuh.\n");
        return 0;
    }
    node *newPtr = (node *)malloc(sizeof(node));
    if (newPtr == NULL) {
        printf("Alokasi Memory Gagal.\n");
        return 0;
    }
    newPtr->data = data;
    newPtr->next = s->top;
    s->top = newPtr;
    s->count += 1;
    return 1;
}

int pop(stack *s, int *dataOut) {
    if (isEmpty(s)) {
        printf("Stack Kosong.\n");
        return 0;
    }
    node *dltPtr = s->top;
    *dataOut = s->top->data;
    s->top = s->top->next;
    free(dltPtr);
    s->count -= 1;
    return 1;
}

int peek(stack *s, int *dataOut) {
    if (isEmpty(s)) {
        printf("Stack Kosong.\n");
        return 0;
    }
    *dataOut = s->top->data;
    return 1;
}

int getCount(stack *s) {
    return s->count;
}

void clearStack(stack *s) {
    while (s->top != NULL) {
        node *temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
    s->count = 0;
    printf("Stack Dibersihkan.\n");
}

void displayMenu() {
    printf("=== Stack Menu ===\n");
    printf("1. Push(Tambahkan Data ke Stack)\n");
    printf("2. Pop(Hapus Data dari Stack)\n");
    printf("3. Top(Tampilkan Data Teratas)\n");
    printf("4. Check Apakah Stack Kosong\n");
    printf("5. Check Apakah Stack Penuh\n");
    printf("6. Hitung Jumlah Data dalam Stack\n");
    printf("7. Hapus Stack\n");
    printf("8. Keluar\n");
    printf("Masukkan Pilihan: ");
}

int main() {
    stack s;
    int maxSize, choice, data, success;

    printf("Masukkan Berapa Jumlah Data Yang Diinginkan: ");
    scanf("%d", &maxSize);
    initStack(&s, maxSize);

    do {
        system("cls"); // Clear the screen
        displayMenu();
        scanf("%d", &choice);
        system("cls"); // Clear the screen again for action feedback

        switch (choice) {
            case 1:
                printf("Masukkan Nilai Pada Data: ");
                scanf("%d", &data);
                success = push(&s, data);
                if (success) printf("Data dimasukkan ke stack.\n");
                break;
            case 2:
                success = pop(&s, &data);
                if (success) printf("Menghapus data: %d\n", data);
                break;
            case 3:
                success = peek(&s, &data);
                if (success) printf("Data Teratas: %d\n", data);
                break;
            case 4:
                if (isEmpty(&s)) printf("Stack Kosong.\n");
                else printf("Stack Tidak Kosong.\n");
                break;
            case 5:
                if (isFull(&s)) printf("Stack Penuh.\n");
                else printf("Stack Tidak Penuh.\n");
                break;
            case 6:
                printf("Jumlah Stack: %d\n", getCount(&s));
                break;
            case 7:
                clearStack(&s);
                break;
            case 8:
                printf("Keluar...\n");
                clearStack(&s);
                break;
            default:
                printf("Pilihan Tidak Valid.\n");
        }

        printf("\nTekan Enter untuk Melanjutkan...");
        getchar(); // Wait for Enter key
        getchar(); // Double getchar to handle new line from scanf
    } while (choice != 8);

    return 0;
}


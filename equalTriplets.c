#include <stdio.h>
#include <stdlib.h>

void fileInput(FILE **myFile, int *count, int **numbers); //reads input from a file and loads it into an array
void swap(int *x, int *y); //swaps two numbers in an array
int permute(int *a, int l, int r); //returns 1 if a permutation with equal triplet sums exists
int equalSums(int *numbers, int arraySize); //returns 1 if all triplets have equal sums

int main () {
    int *numbers, count = 0;
    FILE *myFile;

    fileInput(&myFile, &count, &numbers);

    //checking whether a permutation with equal triplet sums exists
    if (count % 3 != 0) {
        printf("The set cannot be divided into triplets!");
        return 0;
    }
    if (permute(numbers, 0, count - 1) != 1) {
        printf("No permutation with equal triplet sums could be found!");
    }

    free(numbers);
    fclose(myFile);
    return 0;
}

void fileInput(FILE **myFile, int *count, int **numbers) {
    int num;

    //file input
    (*myFile) = fopen("duomenys.txt", "r");
    if ((*myFile) == NULL) {
        printf("Could not find input file!");
        return;
    }

    //counting numbers in the file for creating a dynamic array
    while(!feof(*myFile)) {
        fscanf((*myFile), "%d", &num);
        (*count)++;
    }

    //loading input from the file into a dynamic array
    rewind(*myFile);
    (*numbers) = (int *) malloc (sizeof(int) * (*count));
    for (int i = 0; i < (*count); i++) {
        fscanf((*myFile), "%d", (*numbers) + i);
    }
}

void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int permute(int *a, int l, int r) {
    int i;
    if (l == r) {
        if (equalSums(a, r + 1)) {
            //prints a permutation
            printf("A permutation with equal triplet sums has been found!\n");
            printf("The permutation is:\n");
            for (int j = 0; j <= r; j++) {
                printf("%d;", a[j]);
                if (j % 3 == 2) {
                    printf(" ");
                }
            }
            printf("\n");
            return 1;
        }
    } else {
        for (i = l; i <= r; i++) {
            swap((a + l), (a + i));
            if (permute(a, l + 1, r) == 1) {
                return 1;
            };
            swap((a + l), (a + i)); //backtrack
        }
    }
}

int equalSums(int *numbers, int arraySize) {
    int firstSum = 0;
    int comparativeSum = 0;
    int triplets = arraySize / 3;
    if (triplets == 1) {
        return 1; //sum is equal to itself
    } else {
        //calculating the sum of the first triplet
        for (int i = 0; i < 3; i++) {
            firstSum += numbers[i];
        }
        //comparing other sums to the first one
        for (int i = 1; i < triplets; i++) {
            for (int j = 0; j < 3; j++) {
                comparativeSum += numbers[i * 3 + j];
            }
            if (comparativeSum != firstSum) {
                return 0; //sum of the triplets is not equal
            }
            comparativeSum = 0;
        }
    }
    return 1; //all triplet sums were equal
}

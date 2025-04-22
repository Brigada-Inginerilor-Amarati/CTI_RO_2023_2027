/*
3. Algoritmul se sortare quick-sort (QS)

Implementati o functie cu antetul void qs(int v[], unsigned stg, unsigned dr); care sorteaza crescator un tablou v cu elemente intregi folosind algoritmul de sortare numit quick-sort, descris conform pseudocodului de mai jos.

a) analizati (pe hartie) functionarea algoritmului pentru un set de date de test (ex. {10, 80, 30, 90, 40, 50, 70});

b) masurati timpul de executie al algortmului in implementarea de mai jos si comparati cu timpul de executie al implementarii oferite de functia qsort(...) din stdlib.h

//Algoritmul QS

quickSort(arr[], stg, dr)
{
    if (stg < dr)
    {
        //pi este indexul (pozitia) pivotului/partitiei
        pi = partition(arr, stg, dr);
        quickSort(arr, stg, pi - 1);  // pana la pozitia indexului
        quickSort(arr, pi + 1, dr); // dupa pozitia indexului
    }
}

//functia de determinare a pozitiei pivotului (preluat din CLRS)

This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot 
partition (arr[], stg, dr)
{
    // pivot (Element to be placed at right position)
    pivot = arr[dr];  
 
    i = (stg - 1)  // Index of smaller element and indicates the 
                   // right position of pivot found so far

    for (j = stg; j <= dr - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++;    // increment index of smaller element
            swap arr[i] and arr[j]
        }
    }
    swap arr[i + 1] and arr[dr])
    return (i + 1)
}*/

#include <stdio.h>

void swap(int *p1, int *p2){
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(int arr[], int stg, int dr){
    int pivot = arr[dr];

    int i = (stg - 1);

    for(int j = stg; j <= dr - 1; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[dr]);

    return (i + 1);
}

void quicksort(int arr[], int stg, int dr){

    if(stg < dr){
        int pi = partition(arr, stg, dr);

        quicksort(arr, stg, pi - 1);
        quicksort(arr, pi + 1, dr);
    }
}

int main(void){
    int v[] = {3, 1, 10, 7, 16, 5};

    quicksort(v, 0, 5);

    for(int i = 0; i < 6; i++){
        printf("%d ", v[i]);
    }

    return 0;
}
#include <stdio.h>

void merge_sort(int v[], int left, int right) {
  if (left == right)
    return;

  int mid = (left + right) / 2;
  int i = left;
  int j = mid + 1;

  merge_sort(v, left, mid);
  merge_sort(v, mid + 1, right);

  int aux[right - left + 1];
  int k = 0;

  while (i <= mid && j <= right) {
    if (v[i] < v[j])
      aux[k++] = v[i++];
    else
      aux[k++] = v[j++];
  }

  while (i <= mid)
    aux[k++] = v[i++];

  while (j <= right)
    aux[k++] = v[j++];

  for (i = 0; i < k; i++)
    v[left + i] = aux[i];
}

int main(void) {
  int v[] = {38, 27, 43, 3, 9, 82, 10};
  int n = sizeof(v) / sizeof(v[0]);

  merge_sort(v, 0, n - 1);
}

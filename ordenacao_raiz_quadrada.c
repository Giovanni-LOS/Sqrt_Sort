#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define LIM1 10000

void insertion_sort(int *v, size_t size);
void initArray(int array[], int len);

int main()
{
  srand(time(NULL));

  int *auxArray = (int *)malloc(sizeof(int) * LIM1);
  int *array = (int *)malloc(sizeof(int) * LIM1);
  int tam = (int)sqrt(LIM1);
  int qnt = (LIM1 / tam) + 1;
  int rest = LIM1 % tam;
  clock_t start, end;
  double cpu_time_used;

  initArray(array, LIM1);
  int **a = (int **)malloc(sizeof(int *) * qnt);
  for (int i = 0; i < qnt - 1; i++)
  {

    a[i] = (int *)malloc(sizeof(int) * tam);
  }
  a[qnt - 1] = (int *)malloc(sizeof(int) * rest);

  int u = 0;
  for (int j = 0; j < qnt - 1; j++)
  {
    for (int k = 0; k < tam; k++)
    {
      a[j][k] = array[u++];
    }
  }
  for (int k = 0; k < rest; k++)
  {
    a[qnt - 1][k] = array[u++];
  }

  start = clock();

  for (int i = 0; i < qnt - 1; i++)
  {
    insertion_sort(a[i], tam);
  }
  insertion_sort(a[qnt - 1], rest);

  int indexs[qnt];
  for (int i = 0; i < qnt - 1; i++)
  {
    indexs[i] = tam - 1;
  }
  indexs[qnt - 1] = rest - 1;

  int auxArrayIndex = LIM1 - 1;
  while (auxArrayIndex >= 0)
  {
    int max = 0, bestIndex = 0;
    for (int i = 0; i < qnt; i++)
    {
      if (indexs[i] < 0)
        continue;
      if (max <= a[i][indexs[i]])
      {

        max = a[i][indexs[i]];
        bestIndex = i;
      }
    }
    auxArray[auxArrayIndex--] = max;
    indexs[bestIndex]--;
  }

  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("%f\n", cpu_time_used);

  /*for (int i = 0; i < LIM1; i++)
  {
    printf("%d ", auxArray[i]);
  }
  puts("");*/

  for (int i = 0; i < qnt; i++)
  {
    free(a[i]);
  }
  free(a);
  free(array);
  free(auxArray);
  return 0;
}

void insertion_sort(int *v, size_t size)
{
  int i, j, chosen;
  for (i = 1; i < size; i++)
  {
    chosen = v[i];
    for (j = i - 1; (j >= 0) && chosen < v[j]; j--)
    {
      v[j + 1] = v[j];
    }
    v[j + 1] = chosen;
  }
}

void initArray(int array[], int len)
{

  for (int i = 0; i < len; i++)
  {
    array[i] = rand() % LIM1;
  }
}

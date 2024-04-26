#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define LIM1 1000000

void initArray(int array[], int len);
static void heapify(int *v, size_t i, size_t size);
static void make_heap(int *v, size_t size);
void heap_insert(int *v, int *size, int element);
void heap_pop(int *v, int *size);

int main()
{

  srand(time(NULL));

  int *auxArray = (int *)malloc(sizeof(int) * LIM1);
  int *array = (int *)malloc(sizeof(int) * LIM1);
  int tam = (int)sqrt(LIM1);
  int qnt = (LIM1 / tam) + 1;
  int rest = LIM1 % tam;
  int arrayIndex[qnt];
  int maxArray[qnt];
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
    make_heap(a[i], tam);
  }
  make_heap(a[qnt - 1], rest);

  for (int i = 0; i < qnt - 1; i++)
  {
    maxArray[i] = a[i][0];
    arrayIndex[i] = tam;
  }
  maxArray[qnt - 1] = a[qnt - 1][0];
  arrayIndex[qnt - 1] = rest;
  make_heap(maxArray, qnt);
  int flag = LIM1 - 1;
  int maxIndex = qnt;
  auxArray[flag--] = maxArray[0];

  while (flag >= 0)
  {
    for (int i = 0; i < qnt; i++)
    {
      if (maxArray[0] == a[i][0])
      {
        if (arrayIndex[i] > 0)
        {
          heap_pop(maxArray, &maxIndex);
          heap_pop(a[i], &arrayIndex[i]);
          int elem = a[i][0];
          heap_insert(maxArray, &maxIndex, elem);
          auxArray[flag--] = maxArray[0];
          break;
        }
        else
        {
          heap_pop(maxArray, &maxIndex);
          auxArray[flag--] = maxArray[0];
          break;
        }
      }
    }
  }
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("%f\n", cpu_time_used);

  for (int i = 0; i < qnt; i++)
  {
    free(a[i]);
  }
  free(a);
  free(array);
  free(auxArray);
  return 0;
}

void initArray(int array[], int len)
{

  for (int i = 0; i < len; i++)
  {

    array[i] = rand() % LIM1;
  }
}

static void heapify(int *v, size_t i, size_t size)
{
  int left;
  int right;
  int largest;
  while (i < size)
  {
    left = (i * 2) + 1;
    right = (i * 2) + 2;
    largest = i;
    if (left < size && v[left] > v[largest])
    {
      largest = left;
    }
    if (right < size && v[right] > v[largest])
    {
      largest = right;
    }
    if (i == largest)
    {
      break;
    }
    int swp = v[i];
    v[i] = v[largest];
    v[largest] = swp;
    i = largest;
  }
}

static void make_heap(int *v, size_t size)
{
  int i;
  for (i = size / 2; i >= 0; i--)
  {
    heapify(v, i, size);
  }
}

void heap_pop(int *v, int *size)
{

  v[0] = v[*size - 1];

  (*size)--;

  heapify(v, 0, *size);
}

void heap_insert(int *v, int *size, int element)
{
  v[*size] = element;

  (*size)++;

  size_t i = *size - 1;
  while (i > 0 && v[i] > v[(i - 1) / 2])
  {
    int temp = v[i];
    v[i] = v[(i - 1) / 2];
    v[(i - 1) / 2] = temp;

    i = (i - 1) / 2;
  }
}

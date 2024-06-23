#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define LIM1 100000000

typedef struct heap {
    int number;
    int line;
} heap;

void initArray(int array[], int len);
static void heapify(heap *v, size_t i, size_t size);
static void make_heap(heap *v, size_t size);
void heap_insert(heap *v, int *size, heap element);
void heap_pop(heap *v, int *size);

int main()
{
    srand(time(NULL));

    int *auxArray = (int *)malloc(sizeof(int) * LIM1);
    int *array = (int *)malloc(sizeof(int) * LIM1);
    int tam = (int)sqrt(LIM1);
    int qnt = (LIM1 / tam) + 1;
    int rest = LIM1 % tam;
    int arrayIndex[qnt];
    heap maxArray[qnt];
    clock_t start, end;
    double cpu_time_used;

    initArray(array, LIM1);
    heap **a = (heap **)malloc(sizeof(heap *) * qnt);
    for (int i = 0; i < qnt - 1; i++)
    {
        a[i] = (heap *)malloc(sizeof(heap) * tam);
    }
    a[qnt - 1] = (heap *)malloc(sizeof(heap) * rest);

    int u = 0;
    for (int j = 0; j < qnt - 1; j++)
    {
        for (int k = 0; k < tam; k++)
        {
            a[j][k].number = array[u++];
            a[j][k].line = j;
        }
    }
    for (int k = 0; k < rest; k++)
    {
        a[qnt - 1][k].number = array[u++];
        a[qnt - 1][k].line = qnt - 1;
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
    auxArray[flag--] = maxArray[0].number;

    while (flag >= 0)
    {
        int i = maxArray[0].line;
        heap_pop(maxArray, &qnt);
        if (arrayIndex[i] > 0)
        {
            heap_pop(a[i], &arrayIndex[i]);
            if (arrayIndex[i] > 0) {
                heap_insert(maxArray, &qnt, a[i][0]);
            }
        }
        if (qnt > 0) {
            auxArray[flag--] = maxArray[0].number;
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

static void heapify(heap *v, size_t i, size_t size)
{
    int left;
    int right;
    int largest;
    while (i < size)
    {
        left = (i * 2) + 1;
        right = (i * 2) + 2;
        largest = i;
        if (left < size && v[left].number > v[largest].number)
        {
            largest = left;
        }
        if (right < size && v[right].number > v[largest].number)
        {
            largest = right;
        }
        if (i == largest)
        {
            break;
        }
        heap swp = v[i];
        v[i] = v[largest];
        v[largest] = swp;
        i = largest;
    }
}

static void make_heap(heap *v, size_t size)
{
    int i;
    for (i = size / 2; i >= 0; i--)
    {
        heapify(v, i, size);
    }
}

void heap_pop(heap *v, int *size)
{
    v[0] = v[*size - 1];
    (*size)--;
    heapify(v, 0, *size);
}

void heap_insert(heap *v, int *size, heap element)
{
    v[*size] = element;
    (*size)++;
    int i = *size - 1;
    while (i > 0 && v[i].number > v[(i - 1) / 2].number)
    {
        heap temp = v[i];
        v[i] = v[(i - 1) / 2];
        v[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}
/*

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define LIM1 10

typedef struct heap {
    int number;
    int line;
} heap;

void initArray(int array[], int len);
static void heapify(heap *v, size_t i, size_t size);
static void make_heap(heap *v, size_t size);
void heap_insert(heap *v, int *size, heap element);
void heap_pop(heap *v, int *size);

int main()
{

  srand(time(NULL));

  int *auxArray = (int *)malloc(sizeof(int) * LIM1);
  int *array = (int *)malloc(sizeof(int) * LIM1);
  int tam = (int)sqrt(LIM1);
  int qnt = (LIM1 / tam) + 1;
  int rest = LIM1 % tam;
  int arrayIndex[qnt];
  heap maxArray[qnt];
  clock_t start, end;
  double cpu_time_used;

  initArray(array, LIM1);
  heap **a = (heap **)malloc(sizeof(heap *) * qnt);
  for (int i = 0; i < qnt - 1; i++)
  {

    a[i] = (heap *)malloc(sizeof(heap) * tam);
  }
  a[qnt - 1] = (heap *)malloc(sizeof(heap) * rest);

  int u = 0;
  for (int j = 0; j < qnt - 1; j++)
  {
    for (int k = 0; k < tam; k++)
    {
      a[j][k].number = array[u++];
      a[j][k].line = j;
    }
  }
  for (int k = 0; k < rest; k++)
  {
    a[qnt - 1][k].number = array[u++];
    a[qnt - 1][k].line = qnt - 1;
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
  auxArray[flag--] = maxArray[0].number;

  while (flag >= 0)
  {
    if (arrayIndex[maxArray[0].line] > 0)
    {
        int i = maxArray[0].line;
        heap_pop(maxArray, &maxIndex);
        heap_pop(a[i], &arrayIndex[i]);
        heap elem = a[i][0];
        heap_insert(maxArray, &maxIndex, elem);
        auxArray[flag--] = maxArray[0].number;
        break;
    }
    else
    {
      heap_pop(maxArray, &maxIndex);
      auxArray[flag--] = maxArray[0].number;
      break;
    }
  }
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("%f\n", cpu_time_used);

  for(int i = 0; i < LIM1; i++)
  {
    printf("%d ", auxArray[i]);
  }

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

*/
/*static void heapify(int *v, size_t i, size_t size)
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
}*//*


static void heapify(heap *v, size_t i, size_t size)
{
    int left;
    int right;
    int largest;
    while (i < size)
    {
        left = (i * 2) + 1;
        right = (i * 2) + 2;
        largest = i;
        if (left < size && v[left].number > v[largest].number)
        {
            largest = left;
        }
        if (right < size && v[right].number > v[largest].number)
        {
            largest = right;
        }
        if (i == largest)
        {
            break;
        }
        heap swp = v[i];
        v[i] = v[largest];
        v[largest] = swp;
        i = largest;
    }
}

static void make_heap(heap *v, size_t size)
{
    int i;
    for (i = size / 2; i >= 0; i--)
    {
        heapify(v, i, size);
    }
}

*/
/*void heap_pop(int *v, int *size)
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
}*//*


void heap_pop(heap *v, int *size)
{
    v[0] = v[*size - 1];
    (*size)--;
    heapify(v, 0, *size);
}

void heap_insert(heap *v, int *size, heap element)
{
    v[*size] = element;
    (*size)++;
    size_t i = *size - 1;
    while (i > 0 && v[i].number > v[(i - 1) / 2].number)
    {
        heap temp = v[i];
        v[i] = v[(i - 1) / 2];
        v[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}
*/

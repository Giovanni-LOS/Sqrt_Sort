#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define LIM1 100000000

void initArray(int array[], int len);
static void heapify(int *v, size_t i, size_t size);
static void make_heap(int *v, size_t size);

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

  // Criando arrays menores.
  initArray(array, LIM1);
  int **a = (int **)malloc(sizeof(int *) * qnt);
  for (int i = 0; i < qnt - 1; i++)
  {

    a[i] = (int *)malloc(sizeof(int) * tam);
  }
  a[qnt - 1] = (int *)malloc(sizeof(int) * rest);

  // Copiando o array em arrays menores.
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
    arrayIndex[i] = tam;
    maxArray[i] = heap_pop(a[i], &arrayIndex[i]);
  }
  arrayIndex[qnt - 1] = rest;
  maxArray[qnt - 1] = heap_pop(a[qnt - 1], &arrayIndex[qnt - 1]);
  make_heap(maxArray, qnt);
  int flag = qnt-1;
  auxArray[flag--] = heap_pop(maxArray, &qnt);

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

int heap_pop(int *v, size_t *size)
{
  if (*size == 0)
    return -1; // If the heap is empty, return -1 or some invalid value

  // Save the root of the heap
  int root = v[0];

  // Swap the root with the last element
  v[0] = v[*size - 1];

  // Decrease the size of the heap
  (*size)--;

  // Sift down the new root to its proper position
  heapify(v, 0, *size);

  // Return the removed element
  return root;
}

void heap_insert(int *v, size_t *size, int element)
{
  // Add the new element to the end of the heap
  v[*size] = element;

  // Increase the size of the heap
  (*size)++;

  // Sift up the new element to its proper position
  size_t i = *size - 1;
  while (i > 0 && v[i] > v[(i - 1) / 2])
  {
    // Swap the element with its parent
    int temp = v[i];
    v[i] = v[(i - 1) / 2];
    v[(i - 1) / 2] = temp;

    // Move to the parent
    i = (i - 1) / 2;
  }
}
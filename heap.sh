#!/bin/bash

gcc -O3 -o raiz_heap ordenacao_raiz_quadrada_heap.c

./raiz_heap >resultado_busca.txt

./raiz_heap >>resultado_busca.txt

./raiz_heap >>resultado_busca.txt

./raiz_heap >>resultado_busca.txt

./raiz_heap >>resultado_busca.txt

gcc -O3 -o media media.c

./media resultado_busca.txt

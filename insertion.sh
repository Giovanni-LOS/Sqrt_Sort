#!/bin/bash

gcc -O3 -o raiz ordenacao_raiz_quadrada.c

./raiz >resultado_busca.txt

./raiz >>resultado_busca.txt

./raiz >>resultado_busca.txt

./raiz >>resultado_busca.txt

./raiz >>resultado_busca.txt

gcc -O3 -o media media.c

./media resultado_busca.txt

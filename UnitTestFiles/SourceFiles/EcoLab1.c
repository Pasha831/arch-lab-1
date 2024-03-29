﻿/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include <stdio.h>
#include <stdlib.h>

// функции сравнения для разных типов

int __cdecl compInts(const void *a_ptr, const void *b_ptr) {
	const int a = *(int *)a_ptr;
	const int b = *(int *)b_ptr;
	return (a > b) - (a < b);
}

int __cdecl compDoubles(const void *a_ptr, const void *b_ptr) {
	double a = *(double *)a_ptr;
	double b = *(double *)b_ptr;
	return (a > b) - (a < b);
}

int __cdecl compFloats(const void *a_ptr, const void *b_ptr) {
	float a = *(float *)a_ptr;
	float b = *(float *)b_ptr;
	return (a > b) - (a < b);
}

int __cdecl compStrings(const void *a_ptr, const void *b_ptr) {
	char *a = *(char **)a_ptr;
	char *b = *(char **)b_ptr;
	return strcmp(a, b);
}

void testIntsSorting(IEcoLab1 *pIEcoLab1, IEcoMemoryAllocator1 *pIMem, FILE *file, int seriousArraySize) {
	const int simpleArraySize = 10;
	size_t i;
	clock_t before, after;
	double heapsortDuration;
	double qsortDuration;
	FILE * results;

	// Simple heapsort test
    int *arr = (int *) pIMem->pVTbl->Alloc(pIMem, simpleArraySize * sizeof(int));
    for (i = 0; i < simpleArraySize; i++) {
        arr[i] = rand() % 20003 - 10000;
    }
    
	printf("\033[33mTesting sort for ints\033[0m:\n\n");
    printf("Array before sorting:\n");
    for (i = 0; i < simpleArraySize; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

	pIEcoLab1->pVTbl->heapsort(pIEcoLab1, arr, simpleArraySize, sizeof(int), compInts);

	printf("Array after sorting:\n");
	for (i = 0; i < simpleArraySize; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

	for (i = 0; i < simpleArraySize - 1; ++i) {
		if (arr[i] > arr[i + 1]) {
			printf("\033[31mTest failed\033[0m: array was not sorted properly\n");
			return;
		}
	}
	printf("\033[32mTest successed\033[0m: array was sorted properly\n");

	pIMem->pVTbl->Free(pIMem, arr);
	//

	// Serious heapsort test
	arr = (int *) pIMem->pVTbl->Alloc(pIMem, seriousArraySize * sizeof(int));
    for (i = 0; i < seriousArraySize; i++) {
        arr[i] = rand() % 20003 - 10000;
    }

	before = clock();
	pIEcoLab1->pVTbl->heapsort(pIEcoLab1, arr, seriousArraySize, sizeof(int), compInts);
	after = clock();
	heapsortDuration = (double)(after - before) / CLOCKS_PER_SEC;
	pIMem->pVTbl->Free(pIMem, arr);
	//

	// Serious qsort test
	arr = (int *) pIMem->pVTbl->Alloc(pIMem, seriousArraySize * sizeof(int));
    for (i = 0; i < seriousArraySize; i++) {
        arr[i] = rand() % 20003 - 10000;
    }

	before = clock();
	qsort(arr, seriousArraySize, sizeof(int), compInts);
	after = clock();
	qsortDuration = (double)(after - before) / CLOCKS_PER_SEC;
	pIMem->pVTbl->Free(pIMem, arr);
	//

	// Save results
	printf("\033[32mTime test for ints done\033[0m\n\n");
	fprintf(file, "%s,%s,%d,%lf\n", "heapsort", "int", seriousArraySize, heapsortDuration);
    fprintf(file, "%s,%s,%d,%lf\n", "qsort", "int", seriousArraySize, qsortDuration);
}

void testFloatsSorting(IEcoLab1 *pIEcoLab1, IEcoMemoryAllocator1 *pIMem, FILE *file, int seriousArraySize) {
	const int simpleArraySize = 10;
	size_t i;
	clock_t before, after;
	double heapsortDuration;
	double qsortDuration;
	FILE * results;

	// Simple heapsort test
    float *arr = (float *) pIMem->pVTbl->Alloc(pIMem, simpleArraySize * sizeof(float));
    for (i = 0; i < simpleArraySize; i++) {
         arr[i] = ((float) (rand() %20003 - 10000)) / ((float)(rand() % 1000 + 1)) ;
    }
    
	printf("\033[33mTesting sort for ints\033[0m:\n\n");
    printf("Array before sorting:\n");
    for (i = 0; i < simpleArraySize; ++i) {
        printf("%f ", arr[i]);
    }
    printf("\n\n");

	pIEcoLab1->pVTbl->heapsort(pIEcoLab1, arr, simpleArraySize, sizeof(float), compFloats);

	printf("Array after sorting:\n");
	for (i = 0; i < simpleArraySize; ++i) {
        printf("%f ", arr[i]);
    }
    printf("\n\n");

	for (i = 0; i < simpleArraySize - 1; ++i) {
		if (arr[i] > arr[i + 1]) {
			printf("\033[31mTest failed\033[0m: array was not sorted properly\n");
			return;
		}
	}
	printf("\033[32mTest successed\033[0m: array was sorted properly\n");

	pIMem->pVTbl->Free(pIMem, arr);
	//

	// Serious heapsort test
	arr = (float *) pIMem->pVTbl->Alloc(pIMem, seriousArraySize * sizeof(float));
    for (i = 0; i < seriousArraySize; i++) {
        arr[i] = ((float) (rand() %20003 - 10000)) / ((float)(rand() % 1000 + 1)) ;
    }

	before = clock();
	pIEcoLab1->pVTbl->heapsort(pIEcoLab1, arr, seriousArraySize, sizeof(float), compFloats);
	after = clock();
	heapsortDuration = (double)(after - before) / CLOCKS_PER_SEC;
	pIMem->pVTbl->Free(pIMem, arr);
	//

	// Serious qsort test
	arr = (float *) pIMem->pVTbl->Alloc(pIMem, seriousArraySize * sizeof(float));
    for (i = 0; i < seriousArraySize; i++) {
        arr[i] = ((float) (rand() %20003 - 10000)) / ((float)(rand() % 1000 + 1)) ;
    }

	before = clock();
	qsort(arr, seriousArraySize, sizeof(float), compFloats);
	after = clock();
	qsortDuration = (double)(after - before) / CLOCKS_PER_SEC;
	pIMem->pVTbl->Free(pIMem, arr);
	//

	// Save results
	printf("\033[32mTime test for floats done\033[0m\n\n");
	fprintf(file, "%s,%s,%d,%lf\n", "heapsort", "float", seriousArraySize, heapsortDuration);
    fprintf(file, "%s,%s,%d,%lf\n", "qsort", "float", seriousArraySize, qsortDuration);
}

void testDoublesSorting(IEcoLab1 *pIEcoLab1, IEcoMemoryAllocator1 *pIMem, FILE *file, int seriousArraySize) {
	const int simpleArraySize = 10;
	size_t i;
	clock_t before, after;
	double heapsortDuration;
	double qsortDuration;
	FILE * results;

	// Simple heapsort test
    double *arr = (double *) pIMem->pVTbl->Alloc(pIMem, simpleArraySize * sizeof(double));
    for (i = 0; i < simpleArraySize; i++) {
         arr[i] = ((double) (rand() %20003 - 10000)) / ((float)(rand() % 1000 + 1));
    }
    
	printf("\033[33mTesting sort for ints\033[0m:\n\n");
    printf("Array before sorting:\n");
    for (i = 0; i < simpleArraySize; ++i) {
        printf("%lf ", arr[i]);
    }
    printf("\n\n");

	pIEcoLab1->pVTbl->heapsort(pIEcoLab1, arr, simpleArraySize, sizeof(double), compDoubles);

	printf("Array after sorting:\n");
	for (i = 0; i < simpleArraySize; ++i) {
        printf("%lf ", arr[i]);
    }
    printf("\n\n");

	for (i = 0; i < simpleArraySize - 1; ++i) {
		if (arr[i] > arr[i + 1]) {
			printf("\033[31mTest failed\033[0m: array was not sorted properly\n");
			return;
		}
	}
	printf("\033[32mTest successed\033[0m: array was sorted properly\n");

	pIMem->pVTbl->Free(pIMem, arr);
	//

	// Serious heapsort test
	arr = (double *) pIMem->pVTbl->Alloc(pIMem, seriousArraySize * sizeof(double));
    for (i = 0; i < seriousArraySize; i++) {
        arr[i] = ((double) (rand() %20003 - 10000)) / ((float)(rand() % 1000 + 1));
    }

	before = clock();
	pIEcoLab1->pVTbl->heapsort(pIEcoLab1, arr, seriousArraySize, sizeof(double), compDoubles);
	after = clock();
	heapsortDuration = (double)(after - before) / CLOCKS_PER_SEC;
	pIMem->pVTbl->Free(pIMem, arr);
	//

	// Serious qsort test
	arr = (double *) pIMem->pVTbl->Alloc(pIMem, seriousArraySize * sizeof(double));
    for (i = 0; i < seriousArraySize; i++) {
        arr[i] = ((double) (rand() %20003 - 10000)) / ((float)(rand() % 1000 + 1));
    }

	before = clock();
	qsort(arr, seriousArraySize, sizeof(double), compDoubles);
	after = clock();
	qsortDuration = (double)(after - before) / CLOCKS_PER_SEC;
	pIMem->pVTbl->Free(pIMem, arr);
	//

	// Save results
	printf("\033[32mTime test for floats done\033[0m\n\n");
	fprintf(file, "%s,%s,%d,%lf\n", "heapsort", "double", seriousArraySize, heapsortDuration);
    fprintf(file, "%s,%s,%d,%lf\n", "qsort", "double", seriousArraySize, qsortDuration);
}

void testStringSorting(IEcoLab1 *pIEcoLab1, IEcoMemoryAllocator1 *pIMem, FILE *file, int seriousArraySize) {
	const int simpleArraySize = 10;
	size_t i, j, str_size;
	clock_t before, after;
	double heapsortDuration;
	double qsortDuration;
	char *first;
	char *second;
	char **helping_arr;
	FILE * results;

	// Simple heapsort test
	char **arr = (char **) pIMem->pVTbl->Alloc(pIMem, simpleArraySize * sizeof(char *));
    for (i = 0; i < simpleArraySize; i++) {
        arr[i] = (char *) pIMem->pVTbl->Alloc(pIMem, 20 * sizeof(char));
        str_size = rand() % 14 + 4;
        for (j = 0; j < str_size; ++j) {
            arr[i][j] = (char) (rand() % ('z' - 'a' + 1) + 'a');
        }
        arr[i][str_size] = 0;
    }
    
	printf("\033[33mTesting sort for ints\033[0m:\n\n");
    printf("Array before sorting:\n");
	for (i = 0; i < simpleArraySize; ++i) {
        printf("'%s' ", arr[i]);
    }
    printf("\n\n");

	pIEcoLab1->pVTbl->heapsort(pIEcoLab1, arr, simpleArraySize, sizeof(char *), compStrings);

	printf("Array after sorting:\n");
	for (i = 0; i < simpleArraySize; ++i) {
        printf("'%s' ", arr[i]);
    }
    printf("\n\n");

	for (i = 0; i < simpleArraySize - 1; ++i) {
		first = *(char **)arr;
		second = *(char **)(arr + sizeof(char));
		if (strcmp(first, second) > 0) {
			printf("\033[31mTest failed\033[0m: array was not sorted properly\n");
			return;
		}
	}
	printf("\033[32mTest successed\033[0m: array was sorted properly\n");

	helping_arr = arr;
    for (i = 0; i < simpleArraySize; ++i) {
        pIMem->pVTbl->Free(pIMem, arr[i]);
    }
    pIMem->pVTbl->Free(pIMem, helping_arr);
	//

	// Serious heapsort test
	arr = (char **) pIMem->pVTbl->Alloc(pIMem, seriousArraySize * sizeof(char *));
    for (i = 0; i < seriousArraySize; i++) {
        arr[i] = (char *) pIMem->pVTbl->Alloc(pIMem, 20 * sizeof(char));
        str_size = rand() % 14 + 4;
        for (j = 0; j < str_size; ++j) {
            arr[i][j] = (char) (rand() % ('z' - 'a' + 1) + 'a');
        }
        arr[i][str_size] = 0;
    }

	before = clock();
	pIEcoLab1->pVTbl->heapsort(pIEcoLab1, arr, seriousArraySize, sizeof(char *), compStrings);
	after = clock();
	heapsortDuration = (double)(after - before) / CLOCKS_PER_SEC;
	
	helping_arr = arr;
    for (i = 0; i < seriousArraySize; ++i) {
        pIMem->pVTbl->Free(pIMem, arr[i]);
    }
    pIMem->pVTbl->Free(pIMem, helping_arr);
	//

	// Serious qsort test
	arr = (char **) pIMem->pVTbl->Alloc(pIMem, seriousArraySize * sizeof(char *));
    for (i = 0; i < seriousArraySize; i++) {
        arr[i] = (char *) pIMem->pVTbl->Alloc(pIMem, 20 * sizeof(char));
        str_size = rand() % 14 + 4;
        for (j = 0; j < str_size; ++j) {
            arr[i][j] = (char) (rand() % ('z' - 'a' + 1) + 'a');
        }
        arr[i][str_size] = 0;
    }

	before = clock();
	qsort(arr, seriousArraySize, sizeof(char *), compStrings);
	after = clock();
	qsortDuration = (double)(after - before) / CLOCKS_PER_SEC;
	
	helping_arr = arr;
    for (i = 0; i < seriousArraySize; ++i) {
        pIMem->pVTbl->Free(pIMem, arr[i]);
    }
    pIMem->pVTbl->Free(pIMem, helping_arr);
	//

	// Save results
	printf("\033[32mTime test for floats done\033[0m\n\n");
	fprintf(file, "%s,%s,%d,%lf\n", "heapsort", "string", seriousArraySize, heapsortDuration);
    fprintf(file, "%s,%s,%d,%lf\n", "qsort", "string", seriousArraySize, qsortDuration);
}

int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* name = 0;
    char_t* copyName = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;
	int arraySizes[] = {80000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000, 1200000};

	int* arrayToSort;
	size_t i;
	FILE * resultFile;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Выделение блока памяти */
    name = (char_t *)pIMem->pVTbl->Alloc(pIMem, 10);

    /* Заполнение блока памяти */
    pIMem->pVTbl->Fill(pIMem, name, 'a', 9);


    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	srand(time(0));
	fopen_s(&resultFile, "output.csv", "w");
	fprintf(resultFile, "sort,type,size,time\n");

	for (i = 0; i < 12; i++) {
		testIntsSorting(pIEcoLab1, pIMem, resultFile, arraySizes[i]);
		testFloatsSorting(pIEcoLab1, pIMem, resultFile, arraySizes[i]);
		testDoublesSorting(pIEcoLab1, pIMem, resultFile, arraySizes[i]);
		testStringSorting(pIEcoLab1, pIMem, resultFile, arraySizes[i]);
	}

	fclose(resultFile);

    /* Освобождение блока памяти */
    pIMem->pVTbl->Free(pIMem, name);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}


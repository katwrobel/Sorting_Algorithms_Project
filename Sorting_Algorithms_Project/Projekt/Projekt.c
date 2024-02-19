#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NMAX 1000
#define NBUCKET 100

//Funkcje zwracajaca najwieksza wartosc w tablicy
long int get_max(long int arr[], long int n)
{
	long int mx = arr[0];
	for (long int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

//Funkcja, która sprawdza czy tablica jest prawie posortowana
int count_inversions(int* array, int n) {
	int inversions = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (array[i] > array[j]) {
				inversions++;
			}
		}
	}

	return inversions;
}


// Funkcja wykonuj¹ca sortowanie przez zliczanie dla tablicy arr wed³ug
// cyfry reprezentowanej przez exp.
int* count_sort(long int arr[], long int n, long int exp)
{
	long int i, count[10] = { 0 };
	long int* output = NULL;
	output = (long int*)malloc(((size_t)n) * sizeof(long int));
	if (output == NULL) {
		printf("B³¹d alokacji pamiêci!\n");
		return 0;
	}

	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--) {
		long int digit = (arr[i] / exp) % 10;
		if (digit >= 0 && digit < 10 && count[digit] - 1 >= 0 && count[digit] - 1 < n) {
			output[count[digit] - 1] = arr[i];
			count[digit]--;
		}
	}

	return output;
}

//Sortowanie pozycyjne
void radix_sort(long int arr[], long int n)
{
	long int m = get_max(arr, n);

	int* output;
	for (int exp = 1; m / exp > 0; exp *= 10) {
		output = count_sort(arr, n, exp);
		if (output == NULL) {
			printf("Blad\n");
			return;
		}
		for (int i = 0; i < n; i++) {
			arr[i] = output[i];
		}
		free(output);
	}
}

//Sortowanie kube³kowe
void bucket_sort(long int arr[], long int n)
{
	// Tworzenie tablicy kube³ków
	long int* bucket[NBUCKET] = { 0 };
	for (int i = 0; i < NBUCKET; i++)
	{
		bucket[i] = (long int*)malloc(n * sizeof(long int));
		if (bucket[i] == NULL)
		{
			printf("B³¹d alokacji pamiêci.\n");
			return;
		}
	}

	static long int i, j[NBUCKET], k, l, d = 1;
	long int c;
	c = get_max(arr, n);

	for (long int m = 0; m < c; m++)
	{
		for (i = 0; i < NBUCKET; i++)
			j[i] = 0;
		for (i = 0; i < n; i++)
		{
			k = (arr[i] / d) % NBUCKET;
			bucket[k][j[k]] = arr[i];
			j[k]++;
		}

		l = 0;
		for (i = 0; i < NBUCKET; i++)
		{
			for (k = 0; k < j[i]; k++)
			{
				arr[l] = bucket[i][k];
				l++;
			}
		}
		d *= NBUCKET;
	}

	for (int i = 0; i < NBUCKET; i++)
	{
		free(bucket[i]);
	}
}

//Funkcja zamieniaj¹ca miejscami dwa elementy
void swap(long int* a, long int* b)
{
	if (*a == *b) return;
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

//Funkcja wykonuje podzia³ tablicy arr[] na podtablice z wykorzystaniem elementu pivotu
long int partition(long int arr[], long int p, long int r)
{
	long int pivotIndex = p + rand() % (r - p + 1);
	long int pivot;
	long int i = p - 1;
	long int j;
	pivot = arr[pivotIndex];
	swap(&arr[pivotIndex], &arr[r]);
	for (j = p; j < r; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[r]);
	return i + 1;
}

//Sortowanie szybkie
void quick_sort(long int arr[], long int low, long int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}

// Funckcja do wypisywania tablicy na ekran
void print_array(long int arr[], long int size)
{
	for (long int i = 0; i < size; ++i) {
		printf("%ld  ", arr[i]);
	}
	printf("\n");
}

//Funkcja wype³niaj¹ca tablicê losowymi liczbami
void generate_array(long int a[], long int n, long int min, long int max)
{
	srand(0);
	for (int i = 0; i < n; ++i)
	{
		a[i] = (rand() * rand()) % (max - min + 1) + min;
	}
}

//Funkcja, która zapisuje tablice do pliku
void save_to_file(long int* array, int size, char* name_of_file)
{
	FILE* fp;
	if (fopen_s(&fp, name_of_file, "w"))
	{
		printf("Blad otwarcia pliku.\n");
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		fprintf_s(fp, "%d ", array[i]);
	}

	fclose(fp);
}

//Funkcja, która czyta tablice z pliku
void get_from_file(long int* array, int size, char* name_of_file)
{
	FILE* fp;
	if (fopen_s(&fp, name_of_file, "r"))
	{
		printf("Blad otwarcia pliku.\n");
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		fscanf_s(fp, "%ld ", &array[i]);
	}

	fclose(fp);
}

//Funkcja, ktora pyta uzytkownika czy chce zapisac tablice do pliku
void save_question(long int a[], long int n)
{
	int answer;
	printf("Czy chcesz zapisac tablice do pliku? (odpowiedz 1, jesli tak lub 2, jesli nie)\n");
	if (scanf_s("%d", &answer) < 1 || (answer != 1 && answer != 2)) { printf("Niepoprawne dane\n"); return; }
	if (answer == 1)
	{
		char filename[30];
		printf("Podaj nazwe pliku:\n");
		scanf_s("%s", filename, (unsigned int)sizeof(filename));
		save_to_file(a, n, filename); printf("Zapisano do pliku\n"); return;

	}
	printf("Program zakonczyl dzialanie. Dziekuje\n");
}

//Sortowanie przez zliczanie
void counting_sort(int array[], long int n) {
	int x = array[0];
	for (int i = 1; i < n; i++) {
		if (array[i] > x)
			x = array[i];
	}

	//Rozmiar tablicy count_arr jest równy x + 1
	size_t count_size = (size_t)(x + 1);
	int* arr1 = (int*)malloc(n * sizeof(int));
	size_t* count_arr = (size_t*)calloc(count_size, sizeof(size_t));


	if (count_arr == NULL || arr1 == NULL) {
		printf("Blad alokacji pamieci\n");
		free(count_arr);
		free(arr1);
		return;
	}

	for (int i = 0; i < n; i++) {
		count_arr[array[i]]++;
	}

	for (int i = 1; i <= x; i++) {
		count_arr[i] += count_arr[i - 1];
	}

	for (int i = n - 1; i >= 0; i--) {
		arr1[count_arr[array[i]] - 1] = array[i];
		count_arr[array[i]]--;
	}

	for (int i = 0; i < n; i++) {
		array[i] = arr1[i];
	}

	free(count_arr);
	free(arr1);
}

//Funkcja, która pozwala u¿ytkownikowi na wybór wczytania danych i dobiera odpowiedni algorytm sortowania 
void choice()
{
	int user_choice, min, max;
	long int n;
	long int* a = NULL;
	printf("Wybierz sposob wczytania danych (Wpisz 1 lub 2):\n1.Chce wczytac dane z pliku\n2.Generuj liczby losowe\n");
	if (scanf_s("%d", &user_choice) < 1 || (user_choice != 1 && user_choice != 2)) { printf("Niepoprawne dane\n");  return; }
	char file_name[30];
	switch (user_choice)
	{
	case 1:
		printf("Podaj nazwe pliku:\n");
		scanf_s("%s", file_name, (unsigned int)sizeof(file_name));
		printf("Podaj rozmiar tablicy:\n");
		if (scanf_s("%d", &n) < 1) { printf("Niepoprawne dane"); }
		a = (long int*)malloc(n * sizeof(long int));
		if (a == NULL)
		{
			printf("B³¹d alokacji pamiêci.\n");
			return;
		}
		get_from_file(a, n, file_name);
		print_array(a, n);
		break;
	case 2:
		printf("Podaj rozmiar tablicy:\n");
		scanf_s("%d", &n);
		a = (int*)malloc(n * sizeof(int));
		if (a == NULL)
		{
			printf("B³¹d alokacji pamiêci.\n");
			return;
		}
		printf("Podaj dolna granice losowania:\n");
		if (scanf_s("%d", &min) < 1) { printf("Niepoprawne dane"); return; }
		printf("Podaj gorna granice losowania:\n");
		if (scanf_s("%d", &max) < 1) { printf("Niepoprawne dane"); return; }
		if (min >= max)
		{
			printf("Niepoprawne dane. Dolna granica powinna byæ mniejsza od górnej granicy.\n");
			free(a);
			return;
		}
		generate_array(a, n, min, max);
		print_array(a, n);
		break;
	}
	if (a == NULL) { printf("Blad programu\n"); return; }

	int inversions = count_inversions(a, n);
	if (inversions < 0.2)
	{
		counting_sort(a, n);
		printf("Tablica posortowana algorytmem przez zliczanie:\n");
		print_array(a, n);
		save_question(a, n);
		return;
	}

	int answer;
	if (user_choice == 1)
	{
		printf("Czy sortujesz liczby w systemie dziesietnym?(odpowiedz 1, jesli tak lub 2, jesli nie)\n");
		if (scanf_s("%d", &answer) < 1 || (answer != 1 && answer != 2)) { printf("Niepoprawne dane\n"); return; }
		if (answer == 2)
		{
			radix_sort(a, n);
			printf("Tablica posortowana algorytmem radixsort:\n");
			print_array(a, n);
			save_question(a, n);
			return;
		}
		printf("Czy sortujesz liczby zmiennoprzecinkowe?(odpowiedz 1, jesli tak lub 2, jesli nie)\n");
		if (scanf_s("%d", &answer) < 1 || (answer != 1 && answer != 2)) { printf("Niepoprawne dane\n"); return; }
		if (answer == 1)
		{
			bucket_sort(a, n);
			printf("Tablica posortowana algorytmem kubelkowym\n");
			print_array(a, n);
		}

		else if (get_max(a, n) > 10000)
		{
			radix_sort(a, n);
			printf("Tablica posortowana algorytmem radixsort:\n");
			print_array(a, n);
		}

		else if (n > 250000)
		{
			counting_sort(a, n);
			printf("Tablica posortowana algorytmem przez zliczanie:\n");
			print_array(a, n);
		}
		else
		{
			quick_sort(a, 0, n - 1);
			printf("Tablica posortowana algorytmem quicksort:\n");
			print_array(a, n);
		}

	}
	if (user_choice == 2)
	{
		printf("Czy zalezy ci na stabilnym sortowaniu? (odpowiedz 1, jesli tak lub 2, jesli nie)\n");
		if (scanf_s("%d", &answer) < 1 || (answer != 1 && answer != 2)) { printf("Niepoprawne dane\n"); return; }
		if (answer == 2)
		{
			quick_sort(a, 0, n - 1);
			printf("Tablica posortowana algorytmem quicksort:\n");
			print_array(a, n);
		}
		else if (answer == 1 && n < 10000)
		{
			counting_sort(a, n);
			printf("Tablica posortowana algorytmem przez zliczanie:\n");
			print_array(a, n);
		}
		else if (answer == 1 && n >= 10000)
		{
			radix_sort(a, n);
			printf("Tablica posortowana algorytmem przez przesuniecie:\n");
			print_array(a, n);
		}

	}
	save_question(a, n);
	free(a);
}


# include <iostream>
# include <cmath> // serve per poter usare funzione sqrt

static const int N = 10; //evitare "variable lenght array"
// aggiungiamo comunque opzione "-Werror=vla" quando chiamiamo compilatore per evitare questo errore

int main ()
{
	double arr[N] = {7.2, 2.7, 3.2, 2.3, 4.5, 5.4, 8.1, 1.8, 4.9, 9.4};
	double min_arr = arr[0];
	double max_arr = arr[0];
	double sum_arr = arr[0];
	for (int i=1; i<N; i++){
		min_arr = std::min(arr[i],min_arr);
		max_arr = std::max(arr[i],max_arr);
		sum_arr += arr[i];
	}
	double mean_arr = sum_arr/N;
	double somma_scarti_quadratici_arr = 0;
	for (int i=0; i<N; i++) {
		double diff = arr[i] - mean_arr;
		somma_scarti_quadratici_arr += diff * diff;
	}
	
	double dev_standard_arr = std::sqrt(somma_scarti_quadratici_arr/(N-1));
	
	std::cout << "L'elemento minimo è " << min_arr << "\n";
	std::cout << "L'elemento massimo è " << max_arr << "\n";
	std::cout << "La media è " << mean_arr << "\n";
	std::cout << "La deviazione standard è " << dev_standard_arr << "\n";
}

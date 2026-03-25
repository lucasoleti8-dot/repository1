# include <iostream>

int main()
{
	double ad[4] = {0.0, 1.1, 2.2, 3.3};
	float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
	int ai[3] = {0, 1, 2};
	
	// std::cout << "indirizzi array double: \n";
	// for (int i = 0; i < 4; i += 1) {
		// std::cout << &ad[i] << "\n";
	// }
	
	// std::cout << "indirizzi array float: \n";
	// for (int i = 0; i < 8; i += 1) {
		// std::cout << &af[i] << "\n";
	// }
	
	// std::cout << "indirizzi array int: \n";
	// for (int i = 0; i < 3; i += 1) {
		// std::cout << &ai[i] << "\n";
	// }

	int x = 1;
	float y = 1.1;

	(&y)[1] = 0;
	// ottengo posizione in memoria della variabile y
	// nella posizione successiva in memoria (dove presente x) assegno 0

	std::cout << x << "\n";
	// --> ottengo infatta stampa zero (con entrambi compilatori)
	
	std::cout << "indirizzo variabile x " << &x << "\n";
	std::cout << "indirizzo variabile y " << &y << "\n";
	
	return 0;
}
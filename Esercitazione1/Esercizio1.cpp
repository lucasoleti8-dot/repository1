#include <iostream>  // devo fare imput/output con terminale
#include <fstream> // devo leggere file di testo

using namespace std; //evito scrivre sempre std all'inizio

int main(void) {
	cout << "Enter file name: \n"; 
	// oss: cout necessariamente richiede di scrivere qualcosa --> impossibile che parametro non sia stato specificato
	string filename;
	cin >> filename; //mette nella stringa "filename" input dato da terminale
	ifstream ifs(filename);
	if (ifs.is_open()) {
		for (int i = 1; i<4; i=i+1) {
			//per ogni riga mi interessa nome della città e 4 temperature registrate per fare media
			string location;
			double temp1;
			double temp2;
			double temp3;
			double temp4;
			ifs >> location >> temp1 >> temp2 >> temp3 >> temp4;
			double mean_temp = (temp1 + temp2 + temp3 + temp4)/4;
			cout << location << " " << mean_temp << "\n";
		}
	}
	else {
		cout << "File non aperto correttamente \n";
		// attenzione -> file input deve essere nella stessa directory di questo programma
	}
}	
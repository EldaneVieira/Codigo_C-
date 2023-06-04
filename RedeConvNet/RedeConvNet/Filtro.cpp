#include "stdafx.h"
#include "Filtro.h"


Filtro::Filtro()
{
}


Filtro::~Filtro()
{
}

void Filtro::DefineFiltros(vector<float> filtro1, vector<float> filtro2) {
	for (int i = 0; i < filtro1.size(); i++) {
		this->filtro1.push_back(filtro1[i]);
		this->filtro2.push_back(filtro2[i]);
	}

}

void Filtro::ImprimeValoresFiltros() {
	cout.precision(3);
	cout << "Filtro BE:";
	for (int i = 0; i < this->filtro1.size(); i++) {
		cout << ' ' << this->filtro1[i];
	}
	cout << endl;

	cout << "Filtro BD:";
	for (int i = 0; i < this->filtro2.size(); i++) {
		cout << ' ' << this->filtro2[i];
	}
	cout << endl;
}

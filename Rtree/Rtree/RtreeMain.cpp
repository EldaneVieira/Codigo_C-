// Rtree.cpp : Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"


int main()
{
	Rtree rtree("rtree.txt",512);
	vector <char> info;

	info.push_back('A');

	//Cada chamada do ManageCreationPage ocupa uma página integralmente, forçando a criação de uma nova.
	//Não foi feita a lógica para alocar as entradas na página mais adequada.
	
	rtree.ManageCreationPage(info);
	info.push_back('B');
	rtree.ManageCreationPage(info);

    return 0;
}


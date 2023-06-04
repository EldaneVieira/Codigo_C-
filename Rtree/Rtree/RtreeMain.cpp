// Rtree.cpp : Define o ponto de entrada para a aplica��o de console.
//

#include "stdafx.h"


int main()
{
	Rtree rtree("rtree.txt",512);
	vector <char> info;

	info.push_back('A');

	//Cada chamada do ManageCreationPage ocupa uma p�gina integralmente, for�ando a cria��o de uma nova.
	//N�o foi feita a l�gica para alocar as entradas na p�gina mais adequada.
	
	rtree.ManageCreationPage(info);
	info.push_back('B');
	rtree.ManageCreationPage(info);

    return 0;
}


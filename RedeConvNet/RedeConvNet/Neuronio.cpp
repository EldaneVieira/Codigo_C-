#include "stdafx.h"
#include "Neuronio.h"


Neuronio::Neuronio(int idJanelaConv, int idFiltro)
{
	this->idJanelaConv = idJanelaConv;
	this->idFiltro = idFiltro;
}


Neuronio::~Neuronio()
{
}

void Neuronio::SetResultadoFiltroConv(float resultFiltroConv) {

	this->ResultadoFiltroConv=resultFiltroConv;
	
}



void Neuronio::SetIdJanelaConv(int id) {
	this->idJanelaConv = id;
}


int Neuronio::GetIdJanelaConv() {
	return this->idJanelaConv;
}

bool Neuronio::ComparaNeuronios(Neuronio neo) {
	if (this->idJanelaConv == neo.idJanelaConv && this->ResultadoFiltroConv == neo.ResultadoFiltroConv) {
		return true;
	}
	return false;	
}
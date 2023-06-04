#include "stdafx.h"
#include "Treinamento.h"


Treinamento::Treinamento()
{
}


Treinamento::~Treinamento()
{
}

void Treinamento::SetPadraoReconhecido(int indice) {
	this->padroesReconhecidos[indice] = true;
}

void Treinamento::ResetPadroesReconhecidos() {
	for (int i = 0; i < 4; i++) {
		this->padroesReconhecidos[i] = false;
	}
}

bool Treinamento::IdentificaFimTreinamento() {
	for (int i = 0; i < 4; i++) {
		if (this->padroesReconhecidos[i] == false) {
			return false;
		}
	}
	return true;
}

void Treinamento::TestaTreinamento(vector<int> imagemTeste, Filtro filtro, ConvolutionalLayer cl, PoolingLayer pl, FullyConnectedLayer fcl) {
	cl.AplicaFiltro(imagemTeste, filtro.filtro1, 0);//aplica-se o filtro da barra '\'
	cl.AplicaFiltro(imagemTeste, filtro.filtro2, 1);//aplica-se o filtro da barra '/'
	pl.MesclandoResultados(cl);
	pl.OrdenacaoNeuronios();
	fcl.CriarSequencias(pl);

	fcl.CalcularNota(filtro);
	cout << endl << "Resultado do teste pos-treinemento" << endl;
	fcl.DeclaraVencedor();
}
#include "stdafx.h"
#include "ConvolutionalLayer.h"


ConvolutionalLayer::ConvolutionalLayer()
{
}


ConvolutionalLayer::~ConvolutionalLayer()
{
}

void ConvolutionalLayer::SetNeuronioConjunto(Neuronio neuronio, int indice) {

	if (this->conjuntoNeuronios.size() < 8) {
		this->conjuntoNeuronios.push_back(neuronio);
	}
	else {

		this->conjuntoNeuronios[indice] = neuronio;
	}

}

void ConvolutionalLayer::SetDimensaoConv(int largura, int altura) {
	this->dimensaoConv[0] = largura;
	this->dimensaoConv[1] = altura;
}

// Etapa correspondente a Convolutional layer
void ConvolutionalLayer::AplicaFiltro(vector<int> imagem, vector<float> filtro, int idFiltro) {

	int inicioLaço = 0, fimLaço = inicioLaço + this->dimensaoConv[0];
	vector <int> aux;

	int janelaProcessada = 0, j = 0, i = 0;
	int auxcalculo = 0;
	this->conjuntoNeuronios.begin();
	while (janelaProcessada < (this->dimensaoConv[0]* this->dimensaoConv[1])) {
		
		if (janelaProcessada == this->dimensaoConv[0]) {
			i++;
		}
			
		auxcalculo = auxcalculo + imagem[i]*filtro[j] + imagem[i+1] * filtro[j+1]+ imagem[i + 3] * filtro[j + 2]+imagem[i + 4] * filtro[j + 3];
			
		
		Neuronio neu = Neuronio(janelaProcessada, idFiltro);
		neu.SetResultadoFiltroConv(auxcalculo);
		neu.dadosEntrada.push_back(imagem[i]);
		neu.dadosEntrada.push_back(imagem[i + 1]);
		neu.dadosEntrada.push_back(imagem[i + 3]);
		neu.dadosEntrada.push_back(imagem[i + 4]);

		aux.clear();
		
		this->SetNeuronioConjunto(neu, i);

		
		j = 0;
		i++;
		janelaProcessada++;
		auxcalculo = 0;

	}

}

void ConvolutionalLayer::ResetSetNeuronio() {
	this->conjuntoNeuronios.erase(this->conjuntoNeuronios.begin(), this->conjuntoNeuronios.end());
}


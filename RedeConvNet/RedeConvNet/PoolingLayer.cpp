#include "stdafx.h"
#include "PoolingLayer.h"


PoolingLayer::PoolingLayer()
{
}


PoolingLayer::~PoolingLayer()
{
}




void PoolingLayer::MesclandoResultados(ConvolutionalLayer conv) {

	int quantCombinacoesQuad = 0, janelaProcessada = 0;
	int quadrantesConv = conv.dimensaoConv[0] * conv.dimensaoConv[1];
	int qntConv = conv.conjuntoNeuronios.size();//resultados das aplicações de filtros
	int quadranteUsado[4] = { 0 };
	vector<Neuronio> mesclagem;

	for (int i = 0; i < conv.conjuntoNeuronios.size(); i++) {
		
		if (quadranteUsado[conv.conjuntoNeuronios[i].GetIdJanelaConv()] == 0) {
			mesclagem.push_back(conv.conjuntoNeuronios[i]);
			quadranteUsado[conv.conjuntoNeuronios[i].GetIdJanelaConv()] = 1;
			janelaProcessada++;

			for (int j = 0; j < conv.conjuntoNeuronios.size() / 2; j++) {
				if (quadranteUsado[conv.conjuntoNeuronios[j].GetIdJanelaConv()] == 0) {
					mesclagem.push_back(conv.conjuntoNeuronios[j]);
					quadranteUsado[conv.conjuntoNeuronios[j].GetIdJanelaConv()] = 1;
					janelaProcessada++;
					for (int k = conv.conjuntoNeuronios.size() / 2; k < conv.conjuntoNeuronios.size(); k++) {
						if (quadranteUsado[conv.conjuntoNeuronios[k].GetIdJanelaConv()] == 0) {
							mesclagem.push_back(conv.conjuntoNeuronios[k]);
							quadranteUsado[conv.conjuntoNeuronios[k].GetIdJanelaConv()] = 1;
							janelaProcessada++;

							if (janelaProcessada == quadrantesConv) {
								this->ConvMescladas.push_back(mesclagem);
								mesclagem.clear();
								janelaProcessada = 0;
								for (int l = 0; l < 4; l++) {
									quadranteUsado[l] = 0;
								}
								break;
							}
						}
					}
				}

			}
			
		}

	}
	this->OrdenacaoNeuronios();
	this->EliminaMesclagensInuteis();//otimiza eliminando mesclagens que significam nada
	this->CalculaErro();
}

void PoolingLayer::OrdenacaoNeuronios() {
	int i=0, j, min;


	for (int k = 0; k < this->ConvMescladas.size(); k++) {
		for (i = 0; i < this->ConvMescladas[k].size() - 1; i++) {
			min = i;
			for (j = (i + 1); j < this->ConvMescladas[k].size(); j++) {
				if (this->ConvMescladas[k][j].GetIdJanelaConv() < this->ConvMescladas[k][min].GetIdJanelaConv()) {
					min = j;
				}

			}
			if (this->ConvMescladas[k][i].GetIdJanelaConv() != this->ConvMescladas[k][min].GetIdJanelaConv()) {

				Neuronio aux = this->ConvMescladas[k][i];
				this->ConvMescladas[k][i] = this->ConvMescladas[k][min];
				this->ConvMescladas[k][min] = aux;

			}
		}

	}
	
}

bool PoolingLayer::VerificaCombinacaodescartada(int posicao) {
	for (int i = 0; i < this->posCombinacaoDescartada.size(); i++) {
		if (posicao == this->posCombinacaoDescartada[i]) {
			return true;
		}
	}
	return false;
}

void PoolingLayer::EliminaMesclagensInuteis() {

	int qntValValido;
	vector<vector<Neuronio>> convMantidas;

	for (int i = 0; i < this->ConvMescladas.size(); i++) {
		qntValValido = 0;
		for (int j = 0; j < this->ConvMescladas[i].size(); j++) {
			if (this->ConvMescladas[i][j].ResultadoFiltroConv == 4) {
				qntValValido++;
			}
		}
		//contabiliza a quantidade minima de quadrantes para formar um padrão
		if (qntValValido >= 2) {
			convMantidas.push_back(this->ConvMescladas[i]);//guarda-se as mesclagens que não serão descartadas
		}
	}
	if (convMantidas.size() != 0) {
		this->ConvMescladas.swap(convMantidas);
	}
}

void PoolingLayer::ResetConvMescladas() {
	this->ConvMescladas.erase(this->ConvMescladas.begin(), this->ConvMescladas.end());
}

void PoolingLayer::CalculaErro() {
	this->erros.erase(this->erros.begin(), this->erros.end());
	vector<float> aux;
	for (int i = 0; i < this->ConvMescladas.size(); i++) {
	
		for (int j = 0; j < this->ConvMescladas[i].size(); j++) {

			aux.push_back(4 - this->ConvMescladas[i][j].ResultadoFiltroConv);
			
		}
		this->erros.push_back(aux);
		aux.clear();
	}

}






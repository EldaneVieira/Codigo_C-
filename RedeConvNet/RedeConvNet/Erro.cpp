#include "stdafx.h"
#include "Erro.h"


Erro::Erro()
{
}


Erro::~Erro()
{
}

float Erro::CalculoErro(float saidaObtida, float saidaDesejada) {
	return (saidaDesejada - saidaObtida);
}


//gera a sequencia obtida para o método GerenciaCalculoErro
vector<vector<int>> Erro::UniSequenciasPadroes(vector<vector<int>> sequencia1, vector<vector<int>> sequencia2) {
	
	for (int i = 0; i < sequencia2.size(); i++) {
		for (int j = 0; j < sequencia2[i].size(); j++) {
			sequencia1[i].push_back(sequencia2[i][j]);
		}
	}

	return sequencia1;
}

void Erro::GerenciaCalculoErro(vector<vector<int>> sequenciaPadraoObtida, vector<int> sequenciaPadraoEsperada) {

	//this->erro.erase(this->erro.begin(), this->erro.end());
	vector<float>erroAux;
	vector<vector<float>>erroAux2;
	erro.swap(erroAux2);
	for (int i = 0; i < sequenciaPadraoObtida.size(); i++) {
		for (int j = 0; j < sequenciaPadraoObtida[i].size(); j++) {
			if (erroAux2.size() != 0) {
				erroAux.push_back(this->CalculoErro(sequenciaPadraoObtida[i][j], sequenciaPadraoEsperada[j]) + erroAux2[i][j]);
			}
			else {

				erroAux.push_back(this->CalculoErro(sequenciaPadraoObtida[i][j], sequenciaPadraoEsperada[j]));
			}
		}
		this->erro.push_back(erroAux);
		erroAux.clear();
	}
}




void Erro::GerenciaAtualizacoes(Filtro &filtro, PoolingLayer pl) {

	ofstream arquivo;
	arquivo.open("relatorio.txt", std::ios::app);

	for (int j = 0; j < pl.ConvMescladas.size(); j++) {


		arquivo << "Combinacao de convolucoes " << j << endl<< endl;
		int i, k = 0;
		for (int n = 0; n < pl.ConvMescladas[j].size(); n++) {
			arquivo << "São usados os pixels que geraram quadrante " << n << " apos a convolucao" << endl;
			for (i = 0; i < filtro.filtro1.size(); i++) {
				
				arquivo << "Filtro BE[" << i << "]: ";
				arquivo << filtro.filtro1[i] << " +" << this->taxaAprendizagem << "*" << "(" << this->erro[j][k] << " *" << this->erro[j][k] << ")" << "*" << pl.ConvMescladas[j][n].dadosEntrada[i];
				filtro.filtro1[i] = filtro.filtro1[i] + this->taxaAprendizagem*(this->erro[j][k]* this->erro[j][k]) * pl.ConvMescladas[j][n].dadosEntrada[i];
				k++;
				arquivo << " =>" << filtro.filtro1[i] << endl << endl;
				
				
			}//for i

			k = 0;
		}//for n

		k = 4;//pegando a segunda metade que são os erros para o filtro 2
		for (int n = 0; n < pl.ConvMescladas[j].size(); n++) {
			for (i = 0; i < filtro.filtro2.size(); i++) {
				filtro.filtro2[i] = filtro.filtro2[i] + this->taxaAprendizagem*(this->erro[j][k] * this->erro[j][k]) * pl.ConvMescladas[j][n].dadosEntrada[i];
						k++;
					
			}//for i

			k = 4;
		}//for n
	}//for j
	arquivo.close();
}



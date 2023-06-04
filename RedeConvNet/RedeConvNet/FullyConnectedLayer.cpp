#include "stdafx.h"
#include "FullyConnectedLayer.h"


FullyConnectedLayer::FullyConnectedLayer()
{
	for (int i = 0; i < 4; i++) {
		this->nota[i] = 0;
	}
	
}


FullyConnectedLayer::~FullyConnectedLayer()
{
}

//Este método gera um nota que avalia a sequência gerada em 'GerarSequencias' em relação ao filtro apresentado por parametro
int FullyConnectedLayer::CalcularNotaFiltro(vector<int> seqBE, vector<int> seqBD, vector<vector<int>> filtro) {
	int nota1 = 0;

	for (int i = 0; i < seqBE.size(); i++) {
		//if (i == 0 | i == 3) {
			if (filtro[0][i] == 1) {
				nota1 = nota1 + seqBE[i];
			}
			else {
				nota1 = nota1 - seqBE[i];
			}
		
	}

	for (int i = 0; i < seqBD.size(); i++) {
		//if (i == 1 | i == 2) {
			if (filtro[1][i] == 1) {
				nota1 = nota1 + seqBD[i];
			}
			else {
				nota1 = nota1 - seqBD[i];
			}
	
	}
	return(nota1);
}


void FullyConnectedLayer::CalcularNota(Filtro filtro) {
	
	for (int i = 0; i < this->SequenciaPadraoBD.size(); i++) {
		this->nota[0] = this->CalcularNotaFiltro(this->SequenciaPadraoBE[i], this->SequenciaPadraoBD[i], filtro.filtroX);
		this->nota[1] = this->CalcularNotaFiltro(this->SequenciaPadraoBE[i], this->SequenciaPadraoBD[i], filtro.filtroO);
		this->nota[2] = this->CalcularNotaFiltro(this->SequenciaPadraoBE[i], this->SequenciaPadraoBD[i], filtro.filtroBarraE);
		this->nota[3] = this->CalcularNotaFiltro(this->SequenciaPadraoBE[i], this->SequenciaPadraoBD[i], filtro.filtroBarraD);
		this->IdentificaVitoria();
	}
	
	
}

//É chamada em CalcularNota, gerando uma avaliação para cada padrão do problema
void FullyConnectedLayer::IdentificaVitoria() {
	int vencedor = 0;

	for (int i = 1; i < 4; i++) {
		if (this->nota[i] > this->nota[vencedor]) {
			vencedor = i;
		}

	}
	this->controleVencedor[vencedor]++;
}


void FullyConnectedLayer::CriarSequencias(PoolingLayer &pl) {

	vector<int> aux1, aux2;

	this->SequenciaPadraoBD.erase(this->SequenciaPadraoBD.begin(), this->SequenciaPadraoBD.end());
	this->SequenciaPadraoBE.erase(this->SequenciaPadraoBE.begin(), this->SequenciaPadraoBE.end());

	for (int i = 0; i < pl.ConvMescladas.size(); i++) {


		for (int j = 0; j < pl.ConvMescladas[i].size(); j++) {
			
			//o valor 4 indica a existência do padrão, se o valor foi gerado pelo filtro 0 então o padrão é '\'
			if (pl.ConvMescladas[i][j].ResultadoFiltroConv == 4 && pl.ConvMescladas[i][j].idFiltro == 0) {
					aux1.push_back(1);//insere 1 na sequência indicando a existência do padrão "\"
				
			}
			else {
				aux1.push_back(-1);//insere -1 na sequência indicando a ausência do padrão "\"
			}

		}

		for (int j = 0; j < pl.ConvMescladas[i].size(); j++) {
			
			//o valor 4 indica a existência do padrão, se o valor foi gerado pelo filtro 1 então o padrão é '/'
			if (pl.ConvMescladas[i][j].ResultadoFiltroConv == 4 && pl.ConvMescladas[i][j].idFiltro == 1) {
				aux2.push_back(1);//insere 1 na sequência indicando a existência do padrão "/"
				
			}
			else {
				aux2.push_back(-1);//insere -1 na sequência indicando a ausência do padrão "/"
			}


		}
		
		this->SequenciaPadraoBE.push_back(aux1);
		this->SequenciaPadraoBD.push_back(aux2);
		aux1.clear();
		aux2.clear();
	

	}

}

//se a quantidade de quadrantes negativos for maior que 3, essa sequência é eliminada
bool FullyConnectedLayer::EliminarSequenciasInuteis(vector<int> sequencia) {
	int qntQuadNeg = 0;

	for (int i = 0; i < sequencia.size(); i++) {

		if (sequencia[i] < 0) {
			qntQuadNeg++;
		}
		if (qntQuadNeg >= 3) {
			return true; //deve ser eliminado
		}
	}
	return false;
}



int FullyConnectedLayer::DeclaraVencedor() {
	ofstream arquivo;
	int maiorVencedor = 0;

	for (int i = 1; i < 4; i++) {
		if (this->controleVencedor[i] > this->controleVencedor[maiorVencedor]) {
			maiorVencedor = i;
		}
	}

	if (maiorVencedor == 0) {
		arquivo.open("relatorio.txt", std::ios::app);
		arquivo << "Padrão reconhecido 'X'" << endl;
		arquivo.close();
		cout << "Padrao reconhecido 'X'" << endl;
	}

	if (maiorVencedor == 1) {
		arquivo.open("relatorio.txt", std::ios::app);
		arquivo << "Padrão reconhecido 'O'" << endl;
		arquivo.close();
		cout << "Padrao reconhecido 'O'" << endl;
	}

	if (maiorVencedor == 2) {
		arquivo.open("relatorio.txt", std::ios::app);
		arquivo << "Padrao reconhecido BarraE" << endl;
		arquivo.close();
		cout << "Padrao reconhecido BarraE" << endl;
	}

	if (maiorVencedor == 3) {
		arquivo.open("relatorio.txt", std::ios::app);
		arquivo << "Padrao reconhecido BarraD" << endl;
		arquivo.close();
		cout << "Padrao reconhecido BarraD" << endl;
	}
	this->ResetaControleVencedor();
	return maiorVencedor;
}

void FullyConnectedLayer::ResetaControleVencedor() {
	for (int i = 0; i < 4; i++) {
		this->controleVencedor[i] = 0;
	}
}

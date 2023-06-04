#pragma once
class Treinamento
{
private:

	bool padroesReconhecidos[4] = { false };// inicialmente nenhum padrão foi reconhecido

public:
	Treinamento();
	~Treinamento();


	void SetPadraoReconhecido(int indice);
	void ResetPadroesReconhecidos();
	bool IdentificaFimTreinamento();
	void TestaTreinamento(vector<int> imagemTeste, Filtro filtro, ConvolutionalLayer cl, PoolingLayer pl, FullyConnectedLayer fcl);
};


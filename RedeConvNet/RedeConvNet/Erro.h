#pragma once
class Erro
{
public:
	Erro();
	~Erro();
	float taxaAprendizagem=0.5;
	vector<vector<float>>erro;
	

	float CalculoErro(float saidaObtida, float saidaDesejada);
	void GerenciaCalculoErro(vector<vector<int>> sequenciaPadraoObtida, vector<int> sequenciaPadraoEsperada);
	void AtualizacaoParametro(Filtro filtro, vector<Neuronio> neu, vector<float> erro);
	int DeclaraVencedor(FullyConnectedLayer fc);
	vector<vector<int>>UniSequenciasPadroes(vector<vector<int>> sequencia1, vector<vector<int>> sequencia2);
	void GerenciaAtualizacoes(Filtro &filtro, PoolingLayer pl);
	void GerenciaAtualizacoes2(Filtro &filtro, PoolingLayer pl);
};


#pragma once
class FullyConnectedLayer
{
public:
	FullyConnectedLayer();
	~FullyConnectedLayer();
	vector<vector<int>>SequenciaPadraoBE;//padrao barra esquerda
	vector<vector<int>>SequenciaPadraoBD;//padrao barra direita
	

	int nota[4] = {0};
	int controleVencedor[4] = { 0 };

	void CalcularNota(Filtro filtro);
	void CriarSequencias(PoolingLayer &pl);
	bool EliminarSequenciasInuteis(vector<int>);
	int CalcularNotaFiltro(vector<int>, vector<int>, vector<vector<int>> filtro);
	void IdentificaVitoria();
	int DeclaraVencedor();

	void ResetaControleVencedor();
};


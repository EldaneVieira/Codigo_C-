#pragma once
class PoolingLayer
{
public:
	PoolingLayer();
	~PoolingLayer();

	vector<vector<Neuronio>>ConvMescladas;//as atualizações de treinamento ocorre sobre este set de neurônios.
	vector<int> posCombinacaoDescartada;
	vector<vector<float>> erros;

	void MesclandoResultados(ConvolutionalLayer conv);
	void OrdenacaoNeuronios();
	bool VerificaCombinacaodescartada(int posicao);
	void EliminaMesclagensInuteis();
	void ResetConvMescladas();
	void CalculaErro();
};


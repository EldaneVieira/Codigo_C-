#pragma once
class ConvolutionalLayer
{
public:
	ConvolutionalLayer();
	~ConvolutionalLayer();

	
	int convLayerID;
	int dimensaoConv[2];
	vector<Neuronio> conjuntoNeuronios;


	void SetNeuronioConjunto(Neuronio, int);
	void SetDimensaoConv(int largura, int altura);
	void AplicaFiltro(vector<int> imagem, vector<float> filtro, int idFiltro);
	void ResetSetNeuronio();


	
};


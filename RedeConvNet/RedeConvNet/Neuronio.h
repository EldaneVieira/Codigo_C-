#pragma once
class Neuronio
{

	private:
		int idJanelaConv;
	

	public:
		Neuronio(int, int);
		~Neuronio();


		int idFiltro;//0 barra inclina��o esquerda; 1 barra inclina��o direita
	
		float ResultadoFiltroConv;//valor resultante da aplica��o do filtro na convolutional layer

		void SetResultadoFiltroConv(float resultFiltroConv);

		void SetIdJanelaConv(int);

		int GetIdJanelaConv();

		bool ComparaNeuronios(Neuronio neo);

		vector<int> dadosEntrada;

};


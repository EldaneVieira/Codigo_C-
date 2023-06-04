#pragma once
class Neuronio
{

	private:
		int idJanelaConv;
	

	public:
		Neuronio(int, int);
		~Neuronio();


		int idFiltro;//0 barra inclinação esquerda; 1 barra inclinação direita
	
		float ResultadoFiltroConv;//valor resultante da aplicação do filtro na convolutional layer

		void SetResultadoFiltroConv(float resultFiltroConv);

		void SetIdJanelaConv(int);

		int GetIdJanelaConv();

		bool ComparaNeuronios(Neuronio neo);

		vector<int> dadosEntrada;

};


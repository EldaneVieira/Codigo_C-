#pragma once
using namespace std;
class Filtro
{
public:
	Filtro();
	~Filtro();
	//vector<int> filtro1;
	//vector<int> filtro2;

	vector<float> filtro1;
	vector<float> filtro2;


	//filtro para a fully connected layer
	//0-> subtração
	//1-> adição
	vector<vector<int>> filtroX= {{1,0,0,1}, {0,1,1,0} };
	vector<vector<int>> filtroO= { {0,1,1,0}, {1,0,0,1} };
	vector<vector<int>> filtroBarraD= { {0,0,0,0}, {0,1,1,0} };
	vector<vector<int>> filtroBarraE= { {1,0,0,1}, {0,0,0,0} };

	void DefineFiltros(vector<float> filtro1, vector<float> filtro2);

	void ImprimeValoresFiltros();
};



#pragma once
#include "Filtro.h"

using namespace std;

class Imagem
{
public:
	Imagem(vector<int>, int, int);
	~Imagem();

	int numPixelImagem, larguraImagem, alturaImagem;
	vector<float> imagem;
};


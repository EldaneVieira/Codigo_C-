#include "stdafx.h"
#include "Imagem.h"



Imagem::Imagem(vector<int> imagem, int larguraImagem, int alturaImagem)
{
	this->larguraImagem = larguraImagem;
	this->alturaImagem = alturaImagem;
	this->numPixelImagem = alturaImagem*larguraImagem;
	
	for (int i = 0; i < numPixelImagem; i++) {
		this->imagem.push_back(imagem[i]);
	}
}


Imagem::~Imagem()
{
}



#include "stdafx.h"
#include "Rtree.h"


Rtree::Rtree(char *filename, int pageSize)
{
	this->handle = fopen(filename, "r+");
	if (this->handle == NULL) {
		this->handle = fopen(filename, "w+");

		this->header.height = 0;
		this->header.pageCount = 0;
		this->header.pageSize = pageSize;
		this->header.rootPage = sizeof(this->header);
		fseek(this->handle, 0, SEEK_SET);
		fwrite(&this->header, sizeof(this->header), 1, this->handle);

		if (this->handle == NULL) {
			cout << "Arquivo não criado!" << endl;
		}

	}
	
}


Rtree::~Rtree()
{
	fclose(this->handle);
}

int Rtree::GetHeight() {
	return this->header.height;
}

int Rtree::GetPageCount() {
	return this->header.pageCount;
}

void Rtree::WritePage(int position, vector<char> buffer) {

	struct Entry e;
	struct Page p;

	//set dados da Entry
	e.previous = -1;
	e.successor = -1;
	e.info.swap(buffer);

	//grava a entry em uma página determinada por position
	int offset = sizeof(this->header) + (this->header.pageSize / this->maxElementPerPage)*position;
	fseek(this->handle, offset, SEEK_SET);
	fread(&p, this->header.pageSize, 1, this->handle);
	p.elements.push_back(e);
	fwrite(&p, offset, 1, this->handle);

}

void Rtree::CreateRootPage() {

	struct Page p;
	int positionPage = sizeof(this->header) + (this->header.pageSize / this->maxElementPerPage) *this->header.pageCount;

	//cria página
	fseek(this->handle, positionPage, SEEK_SET);
	fwrite(&p, this->header.pageSize, 1, this->handle);
	
	
	this->header.pageCount++;
	//atualiza cabeçalho
	fseek(this->handle, 0, SEEK_SET);
	fwrite(&this->header, sizeof(this->header), 1, this->handle);

}


void Rtree::CreatePage() {
	struct Page p;
	int positionNewPage = sizeof(this->header) + (this->header.pageSize / this->maxElementPerPage)*this->header.pageCount;

	//cria página
	fseek(this->handle, positionNewPage, SEEK_SET);
	fwrite(&p, this->header.pageSize, 1, this->handle);

	
	this->header.pageCount++;
		
	//atualiza cabeçalho
	fseek(this->handle, 0, SEEK_SET);
	fwrite(&this->header, sizeof(this->header), 1, this->handle);

	//vincula a página com alguma já existente

	//NÃO TESTADO
	/*
	for (int i = 0; i < this->GetPageCount() - 1; i++) {
		int offset = sizeof(this->header) + this->header.pageSize*i;
		fseek(this->handle, offset, SEEK_SET);
		fread(&p, this->header.pageSize, 1, this->handle);

		for (int j = 0; j < p.elements.size(); j++) {
			if (p.elements[j].previous != -1) {
				p.elements[j].previous = positionNewPage;
				fseek(this->handle, offset, SEEK_SET);
				fwrite(&p, this->header.pageSize, 1, this->handle);
				return;
			}
			if (p.elements[j].successor != -1) {
				p.elements[j].successor = positionNewPage;
				fseek(this->handle, offset, SEEK_SET);
				fwrite(&p, this->header.pageSize, 1, this->handle);
				return;
			}
		}
	}*/
}

void Rtree::ReadPage(int position) {
	int offset = sizeof(this->header) + (this->header.pageSize / this->maxElementPerPage)*position;
	struct Page p;

	fseek(this->handle, offset, SEEK_SET);

	fread(&p, this->header.pageSize, 1, this->handle);

	for (int i = 0; i < p.elements.size(); i++) {
		printf("\n %s", p.elements[i].info);//cout << p.elements[i] << endl;
	}

}

void Rtree::ManageCreationPage(vector<char> info) {

	/*Não está implementada o algoritmo de escolha da página,
	então é inserida na última página criada até esta fica completa e crie uma nova.*/

	int offset = sizeof(this->header) + (this->header.pageSize / this->maxElementPerPage)*this->GetPageCount();
	struct Page p;
	fseek(this->handle, offset, SEEK_SET);
	fread(&p, this->header.pageSize, 1, this->handle);

	//variavel de teste
	int teste = 1;
	if (this->GetPageCount() == 0) {
		this->CreateRootPage();
	}

	//p.elements.size() == this->maxElementPerPage
	//testa se o limite de armazenamento da página foi atingido
	if (teste == this->maxElementPerPage) {
		this->CreatePage();
		cout << "Nova pagina criada!" << endl;
	}

	//this->WritePage(this->GetPageCount(), info);

}

void Rtree::SearchInsertionPosition() {

}


void Rtree::UpdateRootPage(int newValue) {
	this->header.rootPage = newValue;
}

void Rtree::UpdateHeight(int newValue) {
	this->header.height = newValue;
}



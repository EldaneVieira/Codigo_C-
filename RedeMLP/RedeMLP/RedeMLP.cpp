// RedeMLP.cpp : Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"


int main()
{
	// seed random number function
	srand(time(NULL));

	ofstream arquivo;
	arquivo.open("relatorio.txt", std::ios::app);
	arquivo << "Rede MLP: 4 entradas, 2 neuronios na camada intermediária e 1 nerônio na camada de saída. \n";
	arquivo << "\n Inicializa os pesos \n";
	arquivo.close();

	Rede r = Rede();

	// initiate the weights
	r.initWeights();

	// load in the data
	r.initData();

	// train the network
	int j = 0;
	double erro= -1;
	bool aux = true;
	//for (int j = 0; j <= numEpochs; j++)
	while (aux)
	{
		for (int i = 0; i<numPatterns; i++)
		{
			arquivo.open("relatorio.txt", std::ios::app);
			//select a pattern at random
			//r.patNum = rand() % numPatterns;
			arquivo << "\n\n##################### Treinando padrao " << i << "#####################\n\n";
			arquivo.close();
			r.patNum = i;
			//calculate the current network output
			//and error for this pattern
			r.calcNet();

			//change network weights
			r.WeightChangesHO();
			r.WeightChangesIH();
		}

		//display the overall network error
		//after each epoch
		r.calcOverallError();
		erro = r.RMSerror;
		arquivo.open("relatorio.txt", std::ios::app);
		arquivo << "+-+-+-+-+- Finalizada epoca " << j << ". +-+-+-+-+-\n\n";
		printf("epoch = %d RMS Error = %f\n", j, erro);
		if (erro > -0.0000001 && erro < 0.0000001) {
			aux = false;
		} 
		j++;
		arquivo.close();
	}

	//training has finished
	//display the results
	r.displayResults();

	
	system("PAUSE");
	return 0;
}


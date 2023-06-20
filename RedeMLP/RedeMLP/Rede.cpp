#include "stdafx.h"



Rede::Rede()
{
}


Rede::~Rede()
{
}


void Rede::calcNet(void)
{
	//calculate the outputs of the hidden neurons
	//the hidden neurons are tanh

	ofstream arquivo;
	arquivo.open("relatorio.txt", std::ios::app);

	int i = 0;
	for (i = 0; i<numHidden; i++)
	{
		hiddenVal[i] = 0.0;

		for (int j = 0; j<numInputs; j++)
		{
			hiddenVal[i] = hiddenVal[i] + (trainInputs[patNum][j] * weightsIH[j][i]);
		}
		arquivo << "\nPotencial Ativação neuronio [" << i << "] camada intermediaria: " << hiddenVal[i] << "\n";
		hiddenVal[i] = tanh(hiddenVal[i]);
		arquivo << "\nResultado da funcao de tranferencia (tangh) sobre o potencial ativação do neuronio [" << i << "] camada intermediaria: " << hiddenVal[i] << "\n\n";
	}

	//calculate the output of the network
	//the output neuron is linear
	outPred = 0.0;

	
	for (i = 0; i<numHidden; i++)
	{

		outPred = outPred + hiddenVal[i] * weightsHO[i];
	}

	arquivo << "\nPotencial Ativacao neuronio saída:" << outPred<<"\n";
	
	//double saida = tanh(outPred);
	//calculate the error
	errThisPat = outPred - trainOutput[patNum];
	arquivo << "\nCalculo erro: " << outPred << " - " << trainOutput[patNum] << " => " << errThisPat << "\n\n";
}


//************************************
//adjust the weights hidden-output
void Rede::WeightChangesHO(void)
{
	ofstream arquivo;
	arquivo.open("relatorio.txt", std::ios::app);
	arquivo << "Ajustes de pesos das conexoes entre a camada intermediaria e a saida (peso = pesoAnterior + (erro * taxaAprendizagem * dado): \n\n";
	for (int k = 0; k<numHidden; k++)
	{
		double weightChange = LR_HO * errThisPat * hiddenVal[k];

		arquivo << "Peso [" << k << "] =" << weightsIH[k] << " - " << weightChange ;

		weightsHO[k] = weightsHO[k] - weightChange;

		arquivo << " => " << weightsHO[k] << "\n";
		//regularisation on the output weights
		if (weightsHO[k] < -5)
		{
			weightsHO[k] = -5;
		}
		else if (weightsHO[k] > 5)
		{
			weightsHO[k] = 5;
		}
	}
	arquivo.close();

}


//************************************
// adjust the weights input-hidden
void Rede::WeightChangesIH(void)
{
	ofstream arquivo;
	arquivo.open("relatorio.txt", std::ios::app);
	arquivo << "\nAjustes de pesos das conexoes entre a entrada e a camada intermediária (peso = pesoAnterior + (erro * taxaAprendizagem * dado): \n\n";
	for (int i = 0; i<numHidden; i++)
	{
		for (int k = 0; k<numInputs; k++)
		{
			double x = 1 - (hiddenVal[i] * hiddenVal[i]);
			x = x * weightsHO[i] * errThisPat * LR_IH;
			x = x * trainInputs[patNum][k];
			double weightChange = x;
			arquivo << "Peso [" << k << "] [" << i << "]=" << weightsIH[k][i] << " - " << weightChange;
			weightsIH[k][i] = weightsIH[k][i] - weightChange;
			arquivo << " => " << weightsIH[k][i] << "\n";
			
		}
	}
	arquivo.close();

}


//************************************
// generates a random number
double Rede::getRand(void)
{
	return ((double)rand()) / (double)RAND_MAX;
}



//************************************
// set weights to random numbers 
void Rede::initWeights(void)
{
	ofstream arquivo;
	arquivo.open("relatorio.txt", std::ios::app);


	for (int j = 0; j<numHidden; j++)
	{
		weightsHO[j] = (getRand() - 0.5) / 2;
		for (int i = 0; i<numInputs; i++)
		{
			weightsIH[i][j] = (getRand() - 0.5) / 5;
			printf("Weight = %f\n", weightsIH[i][j]);
			arquivo << "Peso = " << weightsIH[i][j] << "\n";
		}
	}
	arquivo.close();

}


//************************************
// read in the data
void Rede::initData(void)
{
	printf("initialising data\n");

	// the data here is the XOR data
	// it has been rescaled to the range
	// [-1][1]
	// an extra input valued 1 is also added
	// to act as the bias
	// the output must lie in the range -1 to 1

	trainInputs[0][0] = 1;
	trainInputs[0][1] = 0;
	trainInputs[0][2] = 1;    //bias
	trainOutput[0] = 1;

	trainInputs[1][0] = 0;
	trainInputs[1][1] = 1;
	trainInputs[1][2] = 1;       //bias
	trainOutput[1] = 1;

	trainInputs[2][0] = 1;
	trainInputs[2][1] = 1;
	trainInputs[2][2] = 1;        //bias
	trainOutput[2] = 0;

	trainInputs[3][0] = 0;
	trainInputs[3][1] = 0;
	trainInputs[3][2] = 1;     //bias
	trainOutput[3] = 0;

	
}


//************************************
// display results
void Rede::displayResults(void)
{
	ofstream arquivo;
	arquivo.open("relatorio.txt", std::ios::app);

	for (int i = 0; i<numPatterns; i++)
	{
		patNum = i;
		calcNet();
		printf("Padrao = %d Esperado = %d Obtido = %f\n", patNum + 1, trainOutput[patNum], outPred);
		if (i == 0) {
			arquivo << "Padrao \\: " << " Esperado = " << trainOutput[patNum] << " Obtido = " << outPred << "\n\n";
		}
		else {
			arquivo << "Padrao /: " << " Esperado = " << trainOutput[patNum] << " Obtido = " << outPred << "\n\n";
		}
		
	}
	arquivo.close();
}


//************************************
// calculate the overall error
void Rede::calcOverallError(void)
{
	RMSerror = 0.0;
	for (int i = 0; i<numPatterns; i++)
	{
		patNum = i;
		calcNet();
		RMSerror = RMSerror + (errThisPat * errThisPat);
	}
	RMSerror = RMSerror / numPatterns;
	RMSerror = sqrt(RMSerror);
}

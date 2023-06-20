#pragma once

//// Data dependent settings ////
#define numInputs  3 //qnt neuronios de entrada + bias
#define numPatterns  4//padrões a serem reconhecidos pela rede 

//// User defineable settings ////
#define numHidden 2
const int numEpochs = 500;
const double LR_IH = 0.3;
const double LR_HO = 0.07;



class Rede
{
public:
	Rede();
	~Rede();

	//// variables ////
	int patNum = 0;
	double errThisPat = 0.0;
	double outPred = 0.0;
	double RMSerror = 0.0;

	// the outputs of the hidden neurons
	double hiddenVal[numHidden];

	// the weights
	double weightsIH[numInputs][numHidden];
	double weightsHO[numHidden];

	// the data
	int trainInputs[numPatterns][numInputs];
	int trainOutput[numPatterns];

	//// functions ////
	void initWeights();
	void initData();
	void calcNet();
	void WeightChangesHO();
	void WeightChangesIH();
	void calcOverallError();
	void displayResults();
	double getRand();

};


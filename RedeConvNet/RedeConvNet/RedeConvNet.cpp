// RedeConvNet.cpp : Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"


int main()
{
	srand((unsigned)time(0));


	ofstream arquivo;
	arquivo.open("relatorio.txt",std::ios::app);
	arquivo << "Treinamento da ConvNet\n";
	arquivo << "Para reduzir a quantidade de informação sera treinado o filtro que busca \n o padrao de barra com inclinação para esquerada (Filtro BE).";
	arquivo.close();


	const int qntImagens = 4;
	int indiceVencedor = -1, ciclosTreinamento=0;

	//ordem das imagens X, O, \ e /
	int imagens[qntImagens][9] = { {1,-1,1,-1,1,-1,1,-1,1},{-1,1,-1,1,-1,1 - 1,1,-1},{1,-1,-1,-1,1,-1,-1,-1,1},{-1,-1,1,-1,1,-1,1,-1,-1} };
	int aux = 0;

	//O vetor padrão esperado possui  a sequencia de 1 e -1, sendo os 3 primeiro números para o filtro '\' e os últimos 4 números para o filtro do padrão '/'
	vector<vector<int>> padraoEsperado = { { 1,-1,-1,1,-1,1,1,-1 },{-1,1,1,-1,1,-1,-1,1},{1,-1,-1,1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,1,1,-1} };

	vector<int> imgEntrada;
	for (int i = 0; i < 9; i++) {
		imgEntrada.push_back(imagens[aux][i]);
	}
	Imagem img(imgEntrada, 3, 3);
	Filtro filtro = Filtro();
	//filtro.DefineFiltros({ 1,-1,1,1 }, { -1,1,1,-1 });// Filtros que precisam de ajustes
	filtro.DefineFiltros({ 1,-1,-1,1 }, { -1,1,1,-1 });// Filtros que funcionam para os 4 padrões

	Treinamento treinamento = Treinamento();

	ConvolutionalLayer cvLayer1 = ConvolutionalLayer();
	cvLayer1.SetDimensaoConv(2, 2);

	
	
	Erro erro = Erro();

	PoolingLayer pl = PoolingLayer();
	FullyConnectedLayer fc = FullyConnectedLayer();
	
	while (treinamento.IdentificaFimTreinamento() == false) {

		//identifica o final de um ciclo de treinamento
		if (aux > 3) {
			arquivo.open("relatorio.txt", std::ios::app);
			arquivo << endl << "\nCICLOS DE TREINAMENTO:" << ciclosTreinamento++ << endl;
			arquivo.close();


			aux = 0;
		}
		

		cvLayer1.AplicaFiltro(imgEntrada, filtro.filtro1, 0);//aplica-se o filtro da barra '\'
		cvLayer1.AplicaFiltro(imgEntrada, filtro.filtro2, 1);//aplica-se o filtro da barra '/'
		pl.MesclandoResultados(cvLayer1);
		pl.OrdenacaoNeuronios();
		fc.CriarSequencias(pl);

		fc.CalcularNota(filtro);
		indiceVencedor = fc.DeclaraVencedor();
		//filtro.ImprimeValoresFiltros();

		if (aux == indiceVencedor) {
			treinamento.SetPadraoReconhecido(aux);//registra o padrão reconhecido com o peso corrente

			aux++;

			imgEntrada.erase(imgEntrada.begin(), imgEntrada.end());
			//Apresentada outra imagem da base de treinamento
			for (int i = 0; i < 9; i++) {
				imgEntrada.push_back(imagens[aux][i]);
			}
			Imagem img(imgEntrada, 3, 3);
			
		}
		else {
			//se não foi identificado o padrao esperado, então ocorre ajustes
			erro.GerenciaCalculoErro(erro.UniSequenciasPadroes(fc.SequenciaPadraoBE, fc.SequenciaPadraoBD), padraoEsperado[aux]);
			erro.GerenciaAtualizacoes(filtro, pl);
			
			//caso ocorra ajuste, o que foi reconhecido é descartado
			treinamento.ResetPadroesReconhecidos();
		}

		

		//serão feitas novas convoluções com os novos valores dos filtros, as convoluções anteriores são descartadas
		cvLayer1.ResetSetNeuronio();
		pl.ResetConvMescladas();
		
			

		
		
	}

	int controleTeste = 0;
	while (controleTeste != -1)
	{


		vector<int> imagemTeste;

		cout << endl << " Digite -1 para encerrar os testes ou qualquer outro numero para continuar.";
		cin >> controleTeste;


		if (controleTeste != -1) {
			int aux;

			imagemTeste.erase(imagemTeste.begin(), imagemTeste.end());

			cout << endl << "Entre com os pixels de uma imagem 3x3 (1 = pixel ativo e -1 = pixel inativo)";
			for (int i = 0; i < 9; i++) {
				cout << endl << "Digite o pixel " << i + 1<<": ";
				cin >> aux;
				imagemTeste.push_back(aux);
			}
			treinamento.TestaTreinamento(imagemTeste, filtro, cvLayer1, pl, fc);
		}
		else {
			cout << endl << "Testes encerrados!";
		}

		
	}
	
	getchar();
    return 0;
}


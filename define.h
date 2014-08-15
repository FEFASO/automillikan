/*
 * define.h
 *
 *  Created on: 18/05/2012
 *      Author: F. Viviani Martins
 */

#ifndef DEFINE_H_
#define DEFINE_H_

//
// Bibliotecas comuns
#include <iostream>
//#include <sstream>
//#include <math.h>
//#include <time.h>
//#include <SDL/SDL.h>                // Bliblioteca SDL para maniputacao de imagens
//#include <SDL/SDL_image.h>

// 
// Define namespace padrão
using namespace std;

//
// Definição de constantes

// Constantes lógicas

#define CABECA                -10               // Identifica a cabeca de cabeca de estruturas
#define N_COR                 256               // Numero de cores de uma imagem em escala cinza
#define N_CANAL               3                 // Numero de canais levados em consideracao





// VETOR > POSICAO E TAMANHO > 'infoProc[]' do VIDEO
#define ANALISAR              0                 // Se o VIDEO devera' ser analisado
#define QUEBRADO              1                 // Se o VIDEO ja' foi quebrado em imagens
#define ESCALA_CINZA          2                 // Se as imagens do VIDEO ja' foram transformada para escala cinza
#define FILTRO_MEDIA          3                 // Se o filtro menos media ja' foi aplicado
#define FILTRO_LIMITE         4                 // Se o filtro limite ja' foi aplicado
#define VIDEO_INICIADO        5                 // Se as IMAGEMs finais e as informacoes do VIDEO ja' foram iniciadas
#define GOTAS_IDENTIFICADAS   6
#define N_INFOPROC            7                 // Numero de informacoes de processo de um VIDEO
// VALORES POSSIVEIS DOS ELEMENTOS DE 'infoProc[]'
#define SIM                   's'
#define NAO                   'n'
// CORES EM ESCALA CINZA
#define PRETO                 0
#define BRANCO                N_COR - 1
// LIMETES PARA RASTREAMENTO DE GOTAS
#define LIM_X                 0.02
#define LIM_Y                 0.05
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VALORES DE DEVOLUCAO
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EM CASO DE ERRO DO PROGRAMA
#define ERRO_LEITURA          -1                // Erro envolvendo leitura de arquivos, diretorios, videos ou imagens
#define ERRO_LOGICA           -2                // Erro de logica interna do programa
#define ERRO_MEMORIA          -3                // Nao foi possivel alocar mais memoria
#define ERRO_INI_SDL          -4                // Erro na inicializacao da SDL
#define ERRO_IMG              -5                // Nao foi possivel carregar ou salvar uma imagem
// FUNCOES DO PROGRAMA
#define SUCESSO               0
#define NAO_SUCESSO           1
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARQUIVOS E DIRETORIOS PRE-DEFINIDOS
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DIR_VIDEOS            "videos/"         // Diretorio padrao onde os videos se encontram
#define DIR_FRAMES            "frames/"         // Diretorio onde os frames dos videos serao armazenados
#define DIR_FRAMES_CINZA      "escala_cinza/"   // Diretorio onde os frames em escala cinza serao armazenados
#define DIR_FRAMES_FINAL      "final/"          // Diretorio onde os frames finais serao armazenados
#define DIR_RESULTADOS        "resultados/"     // Diretorio onde os frames dos videos serao armazenados
#define ARQ_INFOPROC          "infoProc.at"     // Arquivo onde estao as informacoes de processamento dos VIDEOs
#define ARQ_DADOSAD           "dados.txt"       // Arquivo onde estao os dados adicionais
//
// REGISTROS
//
/*struct PAR {
      int x, y; // Par ordenado de plano cartesiano
};
struct VALOR {
      float valor;
      float incerteza;
};
//
// DEFINICOES DE FUNCOES
//
// Dado 'n', aloca 'n' bytes de memoria e devolve o ponteiro para ela. Caso haja falta de memoria, finaliza o programa
void *malloc_void(int n);
// Dado 'dir', verifica se o diretorio 'dir' existe, retornando 0 em caso positivo e 1 caso negativo
short verifica_dir(string dir);
// Dados dois pares, calcula e devolve a distancia entre eles
float distancia(PAR c1, PAR c2);
// Dados dois pares, devolve true caso eles sejam iguais e false caso contrario
bool igual(PAR c1, PAR c2);
*/
#endif /* DEFINE_H_ */

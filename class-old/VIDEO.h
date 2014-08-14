/*
 * VIDEO.h
 *
 *  Created on: 18/05/2012
 *      Author: F. Viviani Martins
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#include "define.h"
#include "FRAME.h"
//
//
// CLASSE VIDEO
//
class VIDEO
{
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ATRIBUTOS ESTATICOS
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   private:
      static int nVideo;               // Numero de videos carregados
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ATRIBUTOS DO OBJETO
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   private:
      // Nome e localizacao do VIDEO no computador
      string nome;                     // Nome do video sem a extensao
      string extensao;                 // Extensao do VIDEO (ex.: '.avi')
      string dir;                      // Diretorio onde o VIDEO se encontra
      // Informacoes dos FRAMEs e IMAGEMs do VIDEO
      string dirFrame;                 // Diretorio onde os frames do VIDEO se encontram
      int nFrame;                      // Numeros de frames existentes no VIDEO do objeto envolvido
      FRAME **vFrame;                  // Vetor de frames do VIDEO
      unsigned int lrgIMAGEM;          // Largura das IMAGEMs dos FRAMEs do VIDEO
      unsigned int altIMAGEM;          // Altura das IMAGEMs dos FRAMEs do VIDEO
      // Gotas do VIDEO
      int nGotas;                      // Numero total de gotas do VIDEO
      GOTA_VIDEO *gotas;               // GOTAs encontratadas e tastreadas no VIDEO
      // Estrutura de dados do video
      VIDEO *prx;                      // Proximo video da lista
      // Informacoes para o processamento
      char infoProc[N_INFOPROC];      // Armazena se o video ja' foi quebrado em FRAMEs
      // Dados adicionais
      VALOR ddp;
      VALOR densidade_oleo;
      VALOR humidade_relativa;
      VALOR temperatuda;
      int taxaframes;
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONSTRUTORES E DESTRUTORES
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Procura videos dentro do diretorio padrao DIR_VIDEOS.
      //    1) Em caso positivo, carrega os VIDEOs e suas informacoes em uma lista
      //       circular com cabeca e o objeto envolvido apontara' para esta cabeca
      //    2) Em caso negativo, escreve mensagem de erro e finaliza o programa
      VIDEO();
      // Destroi todos os VIDEOs da lista e todos os objetos com dependencia deles
      virtual ~VIDEO();
   private:
      // Dado o diretorio e o nome de um video dentro computador, cria um objeto VIDEO referente
      VIDEO(string dir, string nome);
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ESCADA DE PROCESSAMENTO E DADOS ADICIONAIS
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // A partir do arquivo ARQ_INFOPROC, adquiri as informacoes de processamento dos VIDEOs
      void leitura_infoProc();
      // Escreve no arquivo ARQ_INFO as informacoes de processamento de cada VIDEO carregado no programa
      void escreve_infoProc();
      // Le do arquivo 'dados.txt' os dados adicionais dados pelo usuario
      void leitura_dadosAdicionais();
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // IMPRESSAO NA TELA E SALVAMENTO
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Imprime na tela as informacoes dos videos carregados
      void printf();
      // Salva as imagens do video no diretorio 'this->dirFrames + DIR_FRAMES_FINAL'
      void salva();
      // Salva as imagens do video no diretorio 'this->dirFrames + diretorio'
      void salva(string diretorio);
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // METODOS QUE DEVOLVEM E MANIPULAM ATRIBUTOS DO VIDEO <> GETs e SETs
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Devolve o valor do atributo nVideo
      int get_nVideo();
      // Devolve o nome do VIDEO do objeto envolvido
      string get_nome();
      // Devolve o diretorio onde os VIDEOs inseridos na lista se encontram
      string get_dir();
      // Devolve o atributo 'nFrame' do VIDEO envolvido
      int get_nFrame();
      // Devolve a largura dos FRAMES do VIDEO envolvido
      unsigned int get_lrgIMAGEM();
      // Devolve a altura dos FRAMES do VIDEO envolvido
      unsigned int get_altIMAGEM();
      // Devolve o atributo 'prx' do VIDEO envolvido
      VIDEO *get_prx();
      // Dado o 'nivel' desejado, devolve o atributo infoProc[nivel] do objeto envolvido
      int get_infoProc(int nivel);
      // Devolve o atributo 'taxaframes' do VIDEO envolvido
      int get_taxaframes();
      // Incrementa em +1 o valor do atributo nGotas
      void inc_nGotas();
      // Subtrai em -1 o valor do atributo nGotas
      void sub_nGotas();
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // MANIPULACAO DE IMAGEM E VIDEO
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Sendo o objeto envolvido um elemento da lista de VIDEOs diferente da CABECA, esta funcao o quebra em frames
      void quebra_frames();
      // Sendo o objeto envolvido um elemento da lista de VIDEOs diferente da CABECA e que
      // ele ja' tenha sido quebrados em frames, converte todos eles para a escala cinza
      void converte_cinza();
      // Sendo o objeto envolvido um elemento da lista de VIDEOs diferente da CABECA, carrega as imagens para o video
      // OBS: A leitura desta funcao e' indicada para quem quer entender o procedimento do programa
      void inicia_video();
      // Sendo o objeto envolvido um video da lista que nao seja a CABECA, esta funcao calcula as medias de
      // cada ponto fixo (lrg, alt) de (todos os frames) * porcao e as subtraem de seus repectivos pontos
      // 'distancia': valores de cores que estao a uma 'distancia' do desvio padrao sao eliminados
      void filtro_menosmedia(float porcao, float distancia);
      // Sendo o objeto envolvido um video da lista que nao seja a CABECA, esta funcao aplica o filtro limite
      void filtro_limite();
      // Identifica as GOTAs em todos os FRAMEs do VIDEO
      void identifica_gotas();
      // Rastrea gotas no video
      void rastrea_gotas();
      // Faz com que todas as gotas voltem para cor BRANCA
      void gotas_brancas();
      // Dada uma gota, a insere na lista 'gotas' do VIDEO
      void insere(GOTA_VIDEO *gota);
      // Libera espaco alocado para as imagens
      void libera_memoria();
      // Determina velocidades das gotas
      void determina_velocidades();
};

#endif /* VIDEO_H_ */

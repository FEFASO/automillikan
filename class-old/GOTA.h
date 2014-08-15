/*
 * GOTA.h
 *
 *  Created on: 19/05/2012
 *      Author: F. Viviani Martins
 */

#ifndef GOTA_H_
#define GOTA_H_

#include "define.h"
#include "PONTO.h"
#include "FRAME.h"
class VIDEO;
class FRAME;
//
//
// GOTA :: uma gota de um FRAME
//
class GOTA
{
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ATRIBUTOS DO OBJETO
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   private:
      PAR centro;          // Centro da GOTA
      PONTO **vPontos;     // Vetor dos PONTOs que formam a GOTA envolvida
      int nPontos;         // Numero de PONTOs pertencentes 'a GOTA envolvida
      FRAME *frame;        // FRAME a qual a GOTA envolvida pertence
      GOTA *prx, *ant;     // Proxima e anterior GOTA da lista
      GOTA *prxFrame;      // Gota do proximo frame
      GOTA **antFrame;     // Gotas do frame anterior
      short nGotasAnt;     // Numero de gotas anteriores
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONSTRUTORES E DESTRUTORES
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Dado o PAR inicial 'cini e o FRAME 'frame', rastrea e determina todos os pontos da GOTA e a cria
      GOTA(PAR cini, FRAME *frame);
      // Cria uma instansia GOTA que sera' a cabeca de uma lista
      GOTA();
      virtual ~GOTA();
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // GETs e SETs
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Devolve o valor de 'nPontos' do objeto envolvido
      int get_nPontos();
      // Devolve o ponto com 'id' de 'vPontos'
      PONTO *get_ponto(int id);
      // Devolve o valor do atributo 'prx' do objeto envolvido
      GOTA *get_prx();
      // Devolve o valor do atributo 'prxFrame' do objeto envolvido
      GOTA *get_prxFrame();
      // Devolve o valor do atributo 'ant' do objeto envolvido
      GOTA *get_ant();
      // Devolve o valor do atributo 'antFrame' do objeto envolvido
      GOTA *get_antFrame();
      // Devolve o centro da gota
      PAR get_centro();
      // Devolve o atributo 'nGotasAnt' do objeto envolvido
      int get_nGotasAnt();
      // Devolve o atributo 'frame' do objeto envolvido
      FRAME *get_frame();
      // Incrementa em +1 o valor do atributo 'nPontos' do objeto envolvido
      void incrementa_nPontos();
      // Dado 'valor', incrementa o atributo 'centro' do objeto envolvido em valor
      void incrementa_centro(PAR valor);
      // Dado 'prx', atribui tal valor ao atributo 'prx' do objeto envolvido
      void set_prx(GOTA *prx);
      // Dado 'prx', atribui tal valor ao atributo 'ant' do objeto envolvido
      void set_ant(GOTA *ant);
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // PROCESSAMENTO IMAGEM
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Apaga todos os pontos referente a esta GOTA do frame do objeto envolvido
      void apaga();
      // Dada uma lista de gotas do frame anterior, procura a gota que deve ser a sua antecessora
      void encontra_possiveis_anteriores(GOTA *lgotas_anterior);
      // Dada uma 'lista' de gotas e o numero 'nGotas' total de gotas possiveis
      // encontradas, encontra gotas possiveis das gotas desta 'lista'
      void encontra_possiveis_anteriores(GOTA *lista, int nGotas);
      // Sendo que as possiveis gotas anteriores ja' foram encontradas, determina qual delas e' a anterior verdadeira
      void determina_anterior(VIDEO *video);
      // Faz com que todas as gotas voltem para cor BRANCA
      void pinta_branca();
      // Pinta com a 'cor' a gota
      void pinta(int cor);
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // IMPRESSAO
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Imprime o par ordenado que representa o centro
      void print_centro();
      // Imprime informacoes relevantes sobre a gota
      void print_infoGota();
};
//
//
// GOTA_VIDEO :: uma lista de GOTAs de varios FRAMEs de um VIDEO
//
class GOTA_VIDEO {
   private:
      GOTA_VIDEO *prx;  // Proxima GOTA_VIDEO do VIDEO
      GOTA *gota;       // Lista de uma GOTA nos FRAMEs
      VALOR vs, vd;     // Tempo na subida e na descida
      VALOR q, a;       // Valor de carga e raio da gota
      unsigned int ldmax, lsmax; // Deslocamento de descida e subida maximos
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONSTRUTORES E DESTRUTORES
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Cria a cabeca de uma lista de gotas do VIDEO
      GOTA_VIDEO();
      // Inicia um no de uma lista lista de gotas do VIDEO
      GOTA_VIDEO(GOTA *gota);
      // Destroi a gota
      ~GOTA_VIDEO();
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // GETs e SETs
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Devolve o atributo 'prx'
      GOTA_VIDEO *get_prx();
      // Devolve o atributo 'gota'
      GOTA *get_gota();
      // Inserer 'valor' no atributo 'prx'
      void set_prx(GOTA_VIDEO *valor);
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // MANIPULACAO DE IMAGENS
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Pinta com a 'cor' dada todas as gotas da lista de gaotas envolvida
      void pinta(int cor);
      // Determina velocidades da gota envolvida
      void determina_velocidades(VIDEO *video);
      // Dada a gota inicial e a final do movimento, calcula a velocidade
      void calcula_velocidade(GOTA *ini, GOTA *fim, VIDEO *video, VALOR *v);
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // MANIPULACAO DE ESTRUTURA
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Sendo o elemento envolvido a cabeca, insere o elemento 'novo' dado na lista
      void insere(GOTA_VIDEO *novo);
};

#endif /* GOTA_H_ */

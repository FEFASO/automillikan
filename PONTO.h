/*
 * PONTO.h
 *
 *  Created on: 20/05/2012
 *      Author: F. Viviani Martins
 */

#ifndef PONTO_H_
#define PONTO_H_

#include "define.h"
#include "GOTA.h"
#include "FRAME.h"
class FRAME;
class GOTA;
//
//
// PONTO :: um ponto de uma GOTA de uma imagem de um FRAME
//
class PONTO
{
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ATRIBUTOS DO OBJETO
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   private:
      PAR c;               // Par ordenado onde a gota se encontra
      int id;              // Posicao deste ponto em 'this->vPontos[]'
      GOTA *gota;          // Gota a qual o ponto envolvido pertence
      PONTO *esq, *dir;    // Filhos esquerdos e direitos da arvore binaria que armazena os pontos
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONSTRUTORES E DESTRUTORES
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Dado o PAC 'c', a 'gota' e o 'frame', verifica se 'c' e' valido e cria o objeto PONTO
      PONTO(PAR c, GOTA *gota, FRAME *frame);
      //
      virtual ~PONTO();
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // GETs e SETs
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Devolve o valor do atributo 'c' do objeto envolvido
      PAR get_c();
      // Devolve o valor do atributo 'id' do objeto envolvido
      int get_id();
      // Devolve o valor do atributo 'dir' do objeto envolvido
      PONTO *get_dir();
      // Atribui 'valor' ao atributo 'dir'
      void set_dir(PONTO *valor);
      // Atribui 'valor' ao atributo 'esq'
      void set_esq(PONTO *valor);
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // PROCESSAMENTE DE IMAGENS
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Dado o 'frame', procura por pontos conexos aos do PONTO envolvido
      void procura_conexos(GOTA *gota, FRAME *frame);
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ESTRUTURA
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Insere um ponto novo 'a arvore onde o elemento envolvido e' a raiz
      void insere(PONTO *novo);
      // Imprime na tela todos os pontos da arvore onde o objeto envolvido e' a raiz
      void imprime_arvore();
      // Imprime na tela o ponto envolvido
      void imprime();
};

#endif /* PONTO_H_ */

/*
 * FRAME.h
 *
 *  Created on: 18/05/2012
 *      Author: F. Viviani Martins
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "define.h"
#include "GOTA.h"
#include "FRAME.h"
class GOTA;
class PONTO;
//
//
// CLASSE FRAME
//
class FRAME
{
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // ATRIBUTOS DO OBJETO
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   private:
      short id;						   // Id do Frame em questao
      SDL_Surface *img;                // Ponteiro para a IMAGEM
      GOTA *gotas;                     // Lista de gotas presentes no FRAME
      short nGotas;                    // Numero de GOTAs presentes no FRAME
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CONSTRUTORES E DESTRUTORES
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Dado a imagem que tem endereco 'endereco_img', cria um objeto com ela
      FRAME(string endereco_img, int id);
      // Destroi o objeto FRAME envolvido e todos os objetos inferiores
      virtual ~FRAME();
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // MANIPULACOA DE PIXEL
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Devolve o valor do pixel posicionado na largura 'lrg' e altura 'alt' da IMAGEM envolvida
      Uint32 get_pixel(int lrg, int alt);
      // Dada uma 'cor', a armazena no pixel ['lrg']['alt'] da IMAGEM envolvida
      void set_pixel(int lrg, int alt, Uint32 cor);
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // GETs
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Devolve largura da IMAGEM envolvida
      unsigned int get_largura();
      // Devolve altura da IMAGEM envolvida
      unsigned int get_altura();
      // Devolve a lista de gotas
      GOTA *get_gotas();
      // Devolve o atributo 'nGotas'
      short get_nGotas();
      // Devolve o atributo 'id'
      short get_id();
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SALVA E IMPREME
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Salva a imagem do FRAME envolvido com o endereco dado 'endereco_salvar'
      void salva(string endereco_salvar);
      // imprime as gotas
      void imprime_gotas();
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // MANIPULACAO DE IMAGEM
      // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   public:
      // Identifica as gotas da imagem referente ao FRAME envolvido
      void identifica_gotas();
      // Dada uma GOTA, a insere na lista 'gotas' e os PONTOs dela na arvore 'pontos' do FRAME envolvido
      void insere(GOTA *nova);
      // Faz com que todas as gotas voltem para cor BRANCA
      void gotas_brancas();
      // Libera memoria alocada para a imagem
      void libera_memoria();
};

#endif /* FRAME_H_ */

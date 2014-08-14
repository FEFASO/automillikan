/*
 * PONTO.cpp
 *
 *  Created on: 20/05/2012
 *      Author: F. Viviani Martins
 */

#include "PONTO.h"
//
//
// PONTO :: um ponto de uma GOTA de uma imagem de um FRAME
//
// Dado o PAC 'c', a 'gota' e o 'frame', verifica se 'c' e' valido e cria o objeto PONTO
PONTO::PONTO(PAR c, GOTA *gota, FRAME *frame)
{
   //
   // Verifica a validade do ponto dado
   if (c.x < 0 || c.x >= (int) frame->get_largura()) {
      cout << "ERRO_LOGICA <> PONTO::PONTO(PAR,GOTA*,FRAME*) > parametro invalido > c: " << c.x << "," << c.y << endl;
      exit(ERRO_LOGICA);
   }
   if (c.y < 0 || c.y >= (int) frame->get_altura()) {
      cout << "ERRO_LOGICA <> PONTO::PONTO(PAR,GOTA*,FRAME*) > parametro invalido > c: " << c.x << "," << c.y << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Atribui valores aos atributos
   this->c = c;
   this->id = gota->get_nPontos();
   this->gota = gota;
   this->esq = this->dir = NULL;
   //
   // Atualizando atributos do objeto 'gota'
   gota->incrementa_nPontos(); // gota->nPontos++
   gota->incrementa_centro(c); // gota->centro += c
   //
   // Marca na imagem PONTO ja' identificado
   frame->set_pixel(c.x, c.y, BRANCO - 1);
}

PONTO::~PONTO()
{
   // TODO Auto-generated destructor stub
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GETs
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Devolve o valor do atributo 'c' do objeto envolvido
PAR PONTO::get_c()
{
   return this->c;
}
// Devolve o valor do atributo 'id' do objeto envolvido
int PONTO::get_id()
{
   return this->id;
}
// Devolve o valor do atributo 'dir' do objeto envolvido
PONTO *PONTO::get_dir()
{
   return this->dir;
}
// Atribui 'valor' ao atributo 'dir'
void PONTO::set_dir(PONTO *valor)
{
   this->dir = valor;
}
// Atribui 'valor' ao atributo 'esq'
void PONTO::set_esq(PONTO *valor)
{
   this->esq = valor;
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROCESSAMENTE DE IMAGENS
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dado o 'frame', procura por pontos conexos aos do PONTO envolvido
void PONTO::procura_conexos(GOTA *gota, FRAME *frame)
{
   PONTO *novo;
   PAR cnovo;
   cnovo.x = this->c.x - 1;
   cnovo.y = this->c.y;
   if (cnovo.x >= 0 && (int) frame->get_pixel(cnovo.x, cnovo.y) == BRANCO) {
      novo = new PONTO(cnovo, gota, frame);
      novo->dir = this->dir;
      this->dir = novo;
      novo->procura_conexos(gota, frame);
   }
   cnovo.x = this->c.x + 1;
   cnovo.y = this->c.y;
   if (cnovo.x < (int) frame->get_largura() && frame->get_pixel(cnovo.x, cnovo.y) == BRANCO) {
      novo = new PONTO(cnovo, gota, frame);
      novo->dir = this->dir;
      this->dir = novo;
      novo->procura_conexos(gota, frame);
   }
   cnovo.x = this->c.x;
   cnovo.y = this->c.y - 1;
   if (cnovo.y >= 0 && (int) frame->get_pixel(cnovo.x, cnovo.y) == BRANCO) {
      novo = new PONTO(cnovo, gota, frame);
      novo->dir = this->dir;
      this->dir = novo;
      novo->procura_conexos(gota, frame);
   }
   cnovo.x = this->c.x;
   cnovo.y = this->c.y + 1;
   if (cnovo.y < (int) frame->get_altura() && frame->get_pixel(cnovo.x, cnovo.y) == BRANCO) {
      novo = new PONTO(cnovo, gota, frame);
      novo->dir = this->dir;
      this->dir = novo;
      novo->procura_conexos(gota, frame);
   }
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ESTRUTURA
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Insere um ponto novo 'a arvore onde o elemento envolvido e' a raiz
void PONTO::insere(PONTO *novo)
{
   if (this == NULL) {
      cout << "ERRO_LOGICA <> PONTO::insere(GOTA*) > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   if (novo->c.x == this->c.x && novo->c.y == this->c.y) {
      cout << "ERRO_LOGICA <> PONTO::insere(GOTA*) > dois pontos iguais" << endl;
      exit(ERRO_LOGICA);
   }
   if (novo->c.x < this->c.x || (novo->c.x == this->c.x && novo->c.y < this->c.y)) {
      if (this->esq == NULL)
         this->esq = novo;
      else
         this->esq->insere(novo);
      return;
   }
   if (this->dir == NULL) {
      this->dir = novo;
      return;
   }
   this->dir->insere(novo);
}
// Imprime na tela todos os pontos da arvore onde o objeto envolvido e' a raiz
void PONTO::imprime_arvore()
{
   if (this == NULL)
      return;
   this->esq->imprime_arvore();
   this->imprime();
   this->dir->imprime_arvore();
}
// Imprime na tela o ponto envolvido
void PONTO::imprime()
{
   if (this == NULL)
      return;
   cout << this->c.x << " , " << this->c.y << flush;
   if (this->esq == NULL)
      cout << " | esq == NULL <> " << flush;
   else
      cout << " | esq: " << this->esq->c.x << " , " << this->esq->c.y << " <> " << flush;
   if (this->dir == NULL)
      cout << "dir == NULL" << flush;
   else
      cout << "dir: " << this->dir->c.x << " , " << this->dir->c.y << flush;
   cout << endl;
}

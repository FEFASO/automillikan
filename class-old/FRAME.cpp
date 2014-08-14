/*
 * FRAME.cpp
 *
 *  Created on: 18/05/2012
 *      Author: F. Viviani Martins
 */

#include "FRAME.h"
#include "PROGRESSO.h"
//
//
// CLASSE FRAME
//
// Dado a imagem que tem endereco 'endereco_img', cria um objeto com ela
FRAME::FRAME(string endereco_img, int id)
{
   //
   // Carrega imagem
   this->img = IMG_Load(endereco_img.c_str());
   if (this->img == NULL) {
      cout << endl << "ERRO_IMG <> FRAME::FRAME(string) nao foi possivel abrir \"" << endereco_img << "\"" << endl;
      cout << SDL_GetError() << endl;
      exit(ERRO_IMG);
   }
   //
   // Id do FRAME
   this->id = id;
   //
   // Verificando consistencia do numero de cores da FRAME
   if (int cor = pow(2, this->img->format->BitsPerPixel) != N_COR) {
      cout << endl << "ERRO_IMG <> FRAME::FRAME(string) o numero de cores da imagem: " << cor;
      cout << " != " << N_COR << endl;
      cout << SDL_GetError() << endl;
      exit(ERRO_IMG);
   }
   //
   // Iniciando a lista de gotas
   this->gotas = new GOTA();
   this->nGotas = 0;
}
//
FRAME::~FRAME()
{
   if (this == NULL)
      return;
   if (this->img != NULL)
      SDL_FreeSurface(this->img);
   //
   // DESTRUIR LISTA DE GOTAS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MANIPULACOA DE PIXEL
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Devolve o valor do pixel posicionado na largura 'lrg' e altura 'alt' da FRAME envolvida
Uint32 FRAME::get_pixel(int lrg, int alt)
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> FRAME::get_pixel(int, int) > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   if (this->img == NULL) {
      cout << endl << "ERRO_LOGICA <> FRAME::get_pixel(int, int) > this->img == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   int bpp = this->img->format->BytesPerPixel;
   /* Here p is the address to the pixel we want to retrieve */
   Uint8 *p = (Uint8 *)this->img->pixels + alt * this->img->pitch + lrg * bpp;
   switch(bpp) {
   case 1:
      return *p;
   case 2:
      return *(Uint16 *)p;
   case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
         return p[0] << 16 | p[1] << 8 | p[2];
      else
         return p[0] | p[1] << 8 | p[2] << 16;
   case 4:
      return *(Uint32 *)p;
   default:
      return 0; // shouldn't happen, but avoids warnings
   }
}
// Dada uma 'cor', a armazena no pixel ['lrg']['alt'] da FRAME envolvida
void FRAME::set_pixel(int lrg, int alt, Uint32 cor)
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> FRAME::set_pixel(int, int, int) > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   if (this->img == NULL) {
      cout << endl << "ERRO_LOGICA :: FRAME::set_pixel(int, int, int) > this->img == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   //
   // Verifica cor minima e maxima possivel
   if (cor < 0)
      cor = 0;
   else if (cor >= N_COR)
      cor = N_COR - 1;
   //
   // Armazenando cor no pixel (lrg, alt)
   int bpp = this->img->format->BytesPerPixel;
   /* Here p is the address to the pixel we want to set */
   Uint8 *p = (Uint8 *)this->img->pixels + alt * this->img->pitch + lrg * bpp;
   switch(bpp) {
   case 1:
      *p = cor;
      break;
   case 2:
      *(Uint16 *)p = cor;
      break;
   case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
         p[0] = (cor >> 16) & 0xff;
         p[1] = (cor >> 8) & 0xff;
         p[2] = cor & 0xff;
      }
      else {
         p[0] = cor & 0xff;
         p[1] = (cor >> 8) & 0xff;
         p[2] = (cor >> 16) & 0xff;
      }
      break;
   case 4:
      *(Uint32 *)p = cor;
      break;
   }
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GETs
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Devolve largura da FRAME envolvida
unsigned int FRAME::get_largura()
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> FRAME::get_largura() > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   if (this->img == NULL) {
      cout << endl << "ERRO_LOGICA <> FRAME::get_largura() > this->img == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   return this->img->w;
}
// Devolve altura da FRAME envolvida
unsigned int FRAME::get_altura()
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> FRAME::get_altura() > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   if (this->img == NULL) {
      cout << endl << "ERRO_LOGICA <> FRAME::get_altura() > this->img == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   return this->img->h;
}
// Devolve a lista de gotas
GOTA *FRAME::get_gotas()
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> FRAME::get_gotas() > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   return this->gotas;
}
// Devolve o atributo 'nGotas'
short FRAME::get_nGotas()
{
   return this->nGotas;
}
// Devolve o atributo 'id'
short FRAME::get_id()
{
	return this->id;
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SALVAR
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Salva a imagem do FRAME envolvido com o endereco dado 'endereco_salvar'
void FRAME::salva(string endereco_salvar)
{
   if (this == NULL) {
      cout << endl << "ERRO_LOGICA <> FRAME::salva(string) > this == NULL" << endl;
      exit(ERRO_LOGICA);
   }
   if (SDL_SaveBMP(this->img, endereco_salvar.c_str())) {
      cout << endl << "ERRO_IMG <> FRAME::salva(string) nao foi possivel salvar \"" << endereco_salvar << "\"" << endl;
      cout << SDL_GetError() << endl;
      exit(ERRO_IMG);
   }
}
// imprime as gotas
void FRAME::imprime_gotas()
{
   int i = 0;
   for (GOTA *lgotas = this->gotas; lgotas != NULL; lgotas = lgotas->get_prx()) {
      cout << "i: " << ++i << " | ";
      lgotas->print_centro();
      cout << endl;
   }
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MANIPULACAO DE IMAGEM
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Identifica as gotas da imagem referente ao FRAME envolvido
void FRAME::identifica_gotas()
{
   GOTA *nova;
   PAR ponto;
   for (ponto.x = 0; ponto.x < (int) this->get_largura(); ++ponto.x)
      for (ponto.y = 0; ponto.y < (int) this->get_altura(); ++ponto.y)
         if (this->get_pixel(ponto.x, ponto.y) == BRANCO) {
            nova = new GOTA(ponto, this);
            if (nova->get_nPontos() <= 10) {
               nova->apaga();
               nova->~GOTA();
            }
            else
               this->insere(nova);
         }
}
// Dada uma GOTA, a insere na lista 'gotas' e os PONTOs dela na arvore 'pontos' do FRAME envolvido
void FRAME::insere(GOTA *nova)
{
   //
   // Insere GOTA na lista
   GOTA *busca;
   for (busca = this->gotas; busca->get_prx() != NULL; busca = busca->get_prx())
      if (nova->get_centro().x < busca->get_prx()->get_centro().x ||
            (nova->get_centro().x == busca->get_prx()->get_centro().x &&
                  nova->get_centro().y < busca->get_prx()->get_centro().y))
         break;
   nova->set_prx(busca->get_prx());
   busca->set_prx(nova);
   if (nova->get_prx() != NULL)
      nova->get_prx()->set_ant(nova);
   nova->set_ant(busca);
   ++this->nGotas;
}
// Faz com que todas as gotas voltem para cor BRANCA
void FRAME::gotas_brancas()
{
   for (GOTA *atual = this->gotas; atual != NULL; atual = atual->get_prx())
      atual->pinta_branca();
}
// Libera memoria alocada para a imagem
void FRAME::libera_memoria()
{
	if (this->img != NULL) {
		SDL_FreeSurface(this->img);
		this->img = NULL;
	}
	for (GOTA *gota = this->gotas->get_prx(); gota != NULL; ) {
		GOTA *prx = gota->get_prx();
		gota->~GOTA();
		gota = prx;
	}
	this->gotas->~GOTA();
}

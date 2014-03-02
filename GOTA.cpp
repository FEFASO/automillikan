/*
 * GOTA.cpp
 *
 *  Created on: 19/05/2012
 *      Author: F. Viviani Martins
 */

#include "GOTA.h"
#include "VIDEO.h"
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUTORES E DESTRUTORES
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dado o PAR inicial 'cini e o FRAME 'frame', rastrea e determina todos os pontos da GOTA e a cria
GOTA::GOTA(PAR cini, FRAME *frame)
{
   //
   // Inicia atributos
   this->centro.x = this->centro.y = 0;
   this->nPontos = 0;
   this->frame = frame;
   this->prx = this->ant = this->prxFrame = NULL;
   this->antFrame = NULL;
   this->nGotasAnt = 0;
   PONTO *lPontos = new PONTO(cini, this, frame); // Lista dos pontos rastreados
   //
   // Procura por pontos conexos ao 'cini'
   lPontos->procura_conexos(this, frame); // Forma a lista de PONTOs encontrados
   //
   // Organiza no vetor 'vPontos[]' os PONTOs que estao na lista 'lPontos'
   this->vPontos = (PONTO**) malloc_void(this->nPontos * sizeof(PONTO*));
   for (int iPonto = 0; lPontos != NULL; iPonto++) {
      this->vPontos[iPonto] = lPontos;
      lPontos = lPontos->get_dir();
      this->vPontos[iPonto]->set_dir(NULL);
   }
   this->centro.x /= this->nPontos;
   this->centro.y /= this->nPontos;
}
// Cria uma instansia GOTA que sera' a cabeca de uma lista
GOTA::GOTA()
{
   this->centro.x = this->centro.y = this->nPontos = this->nGotasAnt = CABECA;
   this->vPontos = NULL;
   this->frame = NULL;
   this->prx = this->ant = this->prxFrame = NULL;
   this->antFrame = NULL;
}
GOTA::~GOTA()
{
   if (this->prx != NULL)
      this->prx->ant = this->ant;
   if (this->ant != NULL)
      this->ant->prx = this->prx;
   for (int iPonto = 0; iPonto < this->nPontos; ++iPonto)
      this->vPontos[iPonto]->~PONTO();
   free(this->vPontos);
   free(this->antFrame);
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GETs e SETs
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Devolve o valor de 'nPontos' do objeto envolvido
int GOTA::get_nPontos()
{
   return this->nPontos;
}
// Devolve o ponto com 'id' de 'vPontos'
PONTO *GOTA::get_ponto(int id)
{
   return this->vPontos[id];
}
// Devolve o valor do atributo 'prx' do objeto envolvido
GOTA *GOTA::get_prx()
{
   return this->prx;
}
// Devolve o valor do atributo 'prxFrame' do objeto envolvido
GOTA *GOTA::get_prxFrame()
{
   return this->prxFrame;
}
// Devolve o valor do atributo 'ant' do objeto envolvido
GOTA *GOTA::get_ant()
{
   return this->ant;
}
// Devolve o valor do atributo 'antFrame' do objeto envolvido
GOTA *GOTA::get_antFrame()
{
	return this->antFrame[0];
}
// Devolve o centro da gota
PAR GOTA::get_centro()
{
   return this->centro;
}
// Devolve o atributo 'nGotasAnt' do objeto envolvido
int GOTA::get_nGotasAnt()
{
   return this->nGotasAnt;
}
// Devolve o atributo 'frame' do objeto envolvido
FRAME *GOTA::get_frame()
{
	return this->frame;
}
// Incrementa em +1 o valor do atributo 'nPontos' do objeto envolvido
void GOTA::incrementa_nPontos()
{
   ++this->nPontos;
}
// Dado 'valor', incrementa o atributo 'centro' do objeto envolvido em valor
void GOTA::incrementa_centro(PAR valor)
{
   this->centro.x += valor.x;
   this->centro.y += valor.y;
}
// Dado 'prx', atribui tal valor ao atributo 'prx' do objeto envolvido
void GOTA::set_prx(GOTA *valor)
{
   this->prx = valor;
}
// Dado 'prx', atribui tal valor ao atributo 'ant' do objeto envolvido
void GOTA::set_ant(GOTA *ant)
{
   this->ant = ant;
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROCESSAMENTO IMAGEM
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Apaga todos os pontos referente a esta GOTA do frame do objeto envolvido
void GOTA::apaga()
{
   for (int iPonto = 0; iPonto < this->nPontos; ++iPonto)
      this->frame->set_pixel(this->vPontos[iPonto]->get_c().x, this->vPontos[iPonto]->get_c().y, PRETO);
}
// Dada uma lista de gotas do frame anterior, procura a gota que deve ser a sua antecessora
void GOTA::encontra_possiveis_anteriores(GOTA *lgotas_anterior)
{
	this->encontra_possiveis_anteriores(lgotas_anterior, 0);
}
// Dada uma 'lista' de gotas e o numero 'nGotas' total de gotas possiveis encontradas, encontra gotas possiveis das gotas desta 'lista'
void GOTA::encontra_possiveis_anteriores(GOTA *lista, int nGotas)
{
	if (lista == NULL) {
		if (nGotas == 0)
			return;
		this->nGotasAnt = nGotas;
		this->antFrame = (GOTA**) malloc_void(nGotas * sizeof(GOTA*));
		for (int iGota = 0; iGota < nGotas; ++iGota)
			this->antFrame[iGota] = NULL;
		return;
	}
	if (lista->get_centro().x == CABECA || this->centro.x - lista->centro.x > LIM_X * this->frame->get_largura()) {
		this->encontra_possiveis_anteriores(lista->prx, nGotas);
		return;
	}
	if (lista->centro.x - this->centro.x > LIM_X * this->frame->get_largura()) {
		if (nGotas == 0)
			return;
		this->nGotasAnt = nGotas;
		this->antFrame = (GOTA**) malloc_void(nGotas * sizeof(GOTA*));
		for (int iGota = 0; iGota < nGotas; ++iGota)
			this->antFrame[iGota] = NULL;
		return;
	}
	if (abs(this->centro.y - lista->centro.y) > LIM_Y * this->frame->get_altura()) {
		this->encontra_possiveis_anteriores(lista->prx, nGotas);
		return;
	}
	this->encontra_possiveis_anteriores(lista->prx, nGotas + 1);
	this->antFrame[nGotas] = lista;
}
// Sendo que as possiveis gotas anteriores ja' foram encontradas, determina qual delas e' a anterior verdadeira
void GOTA::determina_anterior(VIDEO *video)
{
	if (this->centro.x != CABECA) {
		cout << "ERRO_LOGICA <> GOTA::determina_anterior(VIDEO *) o elemento envolvido deve ser a CABECA" << endl;
		exit(ERRO_LOGICA);
	}
	//
	// Resolve todos os casos simples
	for (GOTA *atual = this->prx; atual != NULL; atual = atual->prx) {
		//atual->print_infoGota();
		if (atual->nGotasAnt == 0) { // Insere uma gota nova na lista de gotas do video referente
			video->inc_nGotas();
			video->insere(new GOTA_VIDEO(atual));
			//cout << " < inserido na lista";
		}
		else if (atual->nGotasAnt == 1) {
			if (atual->antFrame[0]->prxFrame == NULL) { // Quando nao existe conflito
				atual->antFrame[0]->prxFrame = atual;
				//cout << " < OK!";
			}
			else {
				//cout << " < conflito";
				if (atual->antFrame[0]->nGotasAnt == 1) {
					//cout << " < gotas separadas";
					if (distancia(atual->centro, atual->antFrame[0]->centro) < distancia(atual->centro, atual->antFrame[0]->prxFrame->centro)) {
						atual->antFrame[0]->prxFrame->nGotasAnt = 0;
						video->inc_nGotas();
						video->insere(new GOTA_VIDEO(atual->antFrame[0]->prxFrame));
						atual->antFrame[0]->prxFrame = atual;
					}
					else {
						atual->nGotasAnt = 0;
						video->inc_nGotas();
						video->insere(new GOTA_VIDEO(atual));
					}
				}
			}
		}
	}
	//
	// Eliminlando da lista antFrame onde nGotasAnt > 1 os que ja' foram organizados no laco anterior
	//cout << endl << "# Casos espcial:";
	for (GOTA *atual = this->prx; atual != NULL; atual = atual->prx) {
		if (atual->nGotasAnt > 1) {
			short nPossiveisAnteriores = 0;
			GOTA *GotaFrameAnt;
			//atual->print_infoGota();
			//cout << " >>> ";
			for (short i = 0; i < atual->nGotasAnt; ++i)
				if (atual->antFrame[i]->prxFrame == NULL) {
					++nPossiveisAnteriores;
					GotaFrameAnt = atual->antFrame[i];
				}
			if (nPossiveisAnteriores == 0) {
				free(atual->antFrame);
				atual->antFrame = NULL;
				atual->nGotasAnt = 0;
				//atual->print_infoGota();
			}
			else if (nPossiveisAnteriores == 1) {
				free(atual->antFrame);
				atual->antFrame = (GOTA**) malloc_void(sizeof(GOTA*));
				atual->antFrame[0] = GotaFrameAnt;
				GotaFrameAnt->prxFrame = atual;
				atual->nGotasAnt = 1;
				//atual->print_infoGota();
			}
			else if (nPossiveisAnteriores < atual->nGotasAnt) {
				GOTA** novo_antFrame = (GOTA**) malloc_void(nPossiveisAnteriores * sizeof(GOTA*));
				for (short i = 0, j = 0; i < atual->nGotasAnt; ++i)
					if (atual->antFrame[i]->prxFrame == NULL)
						novo_antFrame[j++] = atual->antFrame[i];
				free(atual->antFrame);
				atual->antFrame = novo_antFrame;
				atual->nGotasAnt = nPossiveisAnteriores;
				//atual->print_infoGota();
			}
		}
	}
	//
	// Quando ha' mais do que uma anterior, procura a mais proxima
	//cout << endl << "# Especial 2 :";
	for (GOTA *atual = this->prx; atual != NULL; atual = atual->prx)
		if (atual->nGotasAnt > 1) {
			//atual->print_infoGota();
			GOTA *anterior = atual->antFrame[0];
			float distancia_minima = distancia(atual->centro, anterior->centro);
			for (int i = 1; i < atual->nGotasAnt; ++i)
				if (distancia(atual->centro, atual->antFrame[i]->centro) < distancia_minima) {
					distancia_minima = distancia(atual->centro, atual->antFrame[i]->centro);
					anterior = atual->antFrame[i];
				}
			if (anterior->prxFrame == NULL) {
				anterior->prxFrame = atual;
				//cout << " < encontrou : ";
				//anterior->print_centro();
			}
			else
				if (distancia(atual->centro, anterior->centro) < distancia(anterior->prxFrame->centro, anterior->centro)) {
					GOTA *outra = anterior->prxFrame;
					GOTA *outraAnt = NULL;
					float dist_min_outra = 2 * video->get_lrgIMAGEM();
					for (int i = 0; i < outra->nGotasAnt; ++i) {
						if (outra->antFrame[i]->prxFrame == NULL && dist_min_outra > distancia(outra->centro, outra->antFrame[i]->centro)) {
							outraAnt = outra->antFrame[i];
							dist_min_outra = distancia(outra->centro, outra->antFrame[i]->centro);
						}
					}
					if (outraAnt != NULL)
						outraAnt->prxFrame = outra;
					else
						;//cout << "Ferrou com a outra";
					anterior->prxFrame = atual;
					//cout << " < encontrou com conflito : ";
					//anterior->print_centro();
				}
				else {
					GOTA *outra = anterior->prxFrame;
					GOTA *outraAnt = NULL;
					float dist_min_outra = video->get_lrgIMAGEM();
					for (int i = 0; i < outra->nGotasAnt; ++i) {
						if (outra->antFrame[i]->prxFrame == NULL && dist_min_outra > distancia(outra->centro, outra->antFrame[i]->centro)) {
							outraAnt = outra->antFrame[i];
							dist_min_outra = distancia(outra->centro, outra->antFrame[i]->centro);
						}
					}
					if (outraAnt != NULL) {
						outraAnt->prxFrame = outra;
						//anterior->print_centro();
					}
					else
						;//cout << "merda";
					//cout << " < encontrou com conflito 2!!";
				}
		}
	//
	//
	//cout << endl << "Mais uma vez:";
	for (GOTA *atual = this->prx; atual != NULL; atual = atual->prx)
		if (atual->nGotasAnt > 1) {
			GOTA *anterior = NULL;
			bool flag = true;
			for (int i = 0; i < atual->nGotasAnt; ++i) {
				if (atual->antFrame[i]->prxFrame == NULL)
					flag = false;
				if (atual->antFrame[i]->prxFrame == atual)
					anterior = atual->antFrame[i];
			}
			if (flag == true && anterior != NULL) {
				free(atual->antFrame);
				atual->antFrame = (GOTA**) malloc_void(sizeof(GOTA*));
				atual->antFrame[0] = anterior;
				atual->nGotasAnt = 1;
				//atual->print_infoGota();
			}
			else if (flag == true && anterior == NULL) {
				free(atual->antFrame);
				atual->nGotasAnt = 0;
				video->insere(new GOTA_VIDEO(atual));
			}
			else if (flag == false && anterior != NULL) {
				free(atual->antFrame);
				atual->antFrame = (GOTA**) malloc_void(sizeof(GOTA*));
				atual->antFrame[0] = anterior;
				atual->nGotasAnt = 1;
				//atual->print_infoGota();
			}
			else {
				float dist = video->get_lrgIMAGEM() * 2;
				for (int i = 0; i < atual->nGotasAnt; ++i)
					if (atual->antFrame[i]->prxFrame == NULL && dist > distancia(atual->centro, atual->antFrame[i]->centro)) {
						anterior = atual->antFrame[i];
						dist = distancia(atual->centro, atual->antFrame[i]->centro);
					}
				free(atual->antFrame);
				atual->antFrame = (GOTA**) malloc_void(sizeof(GOTA*));
				atual->antFrame[0] = anterior;
				atual->nGotasAnt = 1;
			}
		}
	//cout << endl << "Final";
	for (GOTA *atual = this->prx; atual != NULL; atual = atual->prx)
		if (atual->nGotasAnt > 1)
			atual->print_infoGota();
}
// Faz com que todas as gotas voltem para cor BRANCA
void GOTA::pinta_branca()
{
   this->pinta(BRANCO);
}
// Pinta com a 'cor' a gota
void GOTA::pinta(int cor)
{
   for (int iPonto = 0; iPonto < this->nPontos; ++iPonto)
      this->frame->set_pixel(this->vPontos[iPonto]->get_c().x, this->vPontos[iPonto]->get_c().y, cor);
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPRESSAO
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Imprime o par ordenado que representa o centro
void GOTA::print_centro()
{
   cout << this->centro.x << " , " << this->centro.y <<  flush;
}
// Imprime informacoes relevantes sobre a gota
void GOTA::print_infoGota()
{
	cout << endl;
	this->print_centro();
	cout << " (" << this->nGotasAnt << ")\t" <<  flush;
	for (int i = 0; i < this->nGotasAnt; ++i) {
		cout << " > " <<  flush;
		this->antFrame[i]->print_centro();
		cout << " (" << this->antFrame[i]->nGotasAnt << ")" <<  flush;
	}
}
//
//
// GOTA_VIDEO :: uma lista de GOTAs de varios FRAMEs de um VIDEO
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUTORES E DESTRUTORES
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cria a cabeca de uma lista de gotas do VIDEO
GOTA_VIDEO::GOTA_VIDEO()
{
   this->gota = NULL;
   this->prx = NULL;
   this->vs.valor = this->vd.valor = 0;
   this->vs.incerteza = this->vd.incerteza = 0;
}
// Inicia uma lista de gotas do VIDEO
GOTA_VIDEO::GOTA_VIDEO(GOTA *gota)
{
   this->gota = gota;
   this->prx = NULL;
   this->vs.valor = this->vd.valor = 0;
   this->vs.incerteza = this->vd.incerteza = 0;
   this->ldmax = this->lsmax = 0;
}
// Destroi a gota
GOTA_VIDEO::~GOTA_VIDEO()
{
   ;
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GETs e SETs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Devolve o atributo 'prx'
GOTA_VIDEO *GOTA_VIDEO::get_prx()
{
   return this->prx;
}
// Devolve o atributo 'gota'
GOTA *GOTA_VIDEO::get_gota()
{
   return this->gota;
}
// Inserer 'valor' no atributo 'prx'
void GOTA_VIDEO::set_prx(GOTA_VIDEO *valor)
{
   this->prx = valor;
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MANIPULACAO DE IMAGENS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pinta com a 'cor' dada todas as gotas da lista de gaotas envolvida
void GOTA_VIDEO::pinta(int cor)
{
   for (GOTA *gota = this->gota; gota != NULL; gota = gota->get_prxFrame())
      gota->pinta(cor);
}
// Determina velocidades da gota envolvida
void GOTA_VIDEO::determina_velocidades(VIDEO *video)
{
	if (this->gota == NULL)
		return;
	//cout << endl;
	for (GOTA *no = this->gota; no->get_prxFrame() != NULL; no = no->get_prxFrame()) {
		//cout << no->get_centro().y << " (" << no->get_frame()->get_id() << ") | dif: ";
		//cout << no->get_prxFrame()->get_centro().y - no->get_centro().y;
		if (no->get_prxFrame()->get_centro().y - no->get_centro().y <= 0) {
			GOTA *ini_subida = no;		// Onde a gota comeca a subir
			bool inverte_mov = false;
			no = no->get_prxFrame();
			//cout << " > Subida" << endl;
			while (no->get_prxFrame() != NULL && inverte_mov == false) {
				//cout << no->get_centro().y << " (" << no->get_frame()->get_id() << ") | dif: ";
				//cout << no->get_prxFrame()->get_centro().y - no->get_centro().y;
				if (no->get_prxFrame()->get_centro().y - no->get_centro().y > 0)
					for (GOTA *p = no->get_prxFrame(); p->get_prxFrame() != NULL; p = p->get_prxFrame()) {
						if (p->get_prxFrame()->get_centro().y - no->get_centro().y > 0) {
							inverte_mov = true;
							break;
						}
						if (p->get_prxFrame()->get_centro().y - no->get_centro().y > 0)
							break;
					}
				no = no->get_prxFrame();
				//cout << endl;
			}
			//cout << "AQUI" << endl;
			//no->get_antFrame()->print_centro();
			//cout << endl;
			//ini_subida->print_centro();
			//cout << endl;
			if (no->get_antFrame() != ini_subida) {
				if (this->lsmax < abs(no->get_antFrame()->get_centro().y - ini_subida->get_centro().y)) {
					this->calcula_velocidade(ini_subida, no, video, &(this->vs));
					this->lsmax = no->get_antFrame()->get_centro().y - ini_subida->get_centro().y;
				}
			}
		}
		if (no->get_prxFrame() == NULL)
			break;
		if (no->get_prxFrame()->get_centro().y - no->get_centro().y >= 0) {
			GOTA *ini_descida = no;		// Onde a gota comeca a subir
			no = no->get_prxFrame();
			//cout << " > Descida" << endl;
			while (no->get_prxFrame() != NULL) {
				//cout << no->get_centro().y << " (" << no->get_frame()->get_id() << ") | dif: ";
				//cout << no->get_prxFrame()->get_centro().y - no->get_centro().y;
				if (no->get_prxFrame()->get_centro().y - no->get_centro().y < 0)
					break;
				no = no->get_prxFrame();
				//cout << endl;
			}
			if (no->get_antFrame() != ini_descida) {
				if (this->ldmax < abs(no->get_antFrame()->get_centro().y - ini_descida->get_centro().y)) {
					this->calcula_velocidade(ini_descida, no, video, &(this->vd));
					this->lsmax = no->get_antFrame()->get_centro().y - ini_descida->get_centro().y;
				}
			}
		}
		if (no->get_prxFrame() == NULL)
			break;
	}
	FILE *arq;
	arq = fopen("velocidades.txt", "a+");
	if (this->vs.valor != 0 && this->vd.valor != 0) {
		//monitcout << "vs: " << this->vs.valor << " | vd: " << this->vd.valor << endl;
		fprintf(arq, "%lf\t%lf\n", fabs(this->vs.valor), fabs(this->vd.valor));
		//exit(1);
	}
	else
		video->sub_nGotas();
	fclose(arq);
}
// Dada a gota inicial e a final do movimento, calcula a velocidade
void GOTA_VIDEO::calcula_velocidade(GOTA *ini, GOTA *fim, VIDEO *video, VALOR *v)
{
	if (ini == fim)
		return;
	if (ini == fim->get_antFrame())
		return;
	//
	// Regressao linear
	//VALOR coef_linear;
	float somax = 0;
	float somay = 0;
	float somaxquad = 0;
	float somaxy = 0;
	int nFrames = 0;
	for (GOTA *p = ini; p != fim; p = p->get_prxFrame(), ++nFrames) {
		float x = (float) nFrames / (float) video->get_taxaframes();
		somax += x;
		somay += p->get_centro().y - ini->get_centro().y;
		somaxquad += x * x;
		somaxy += x * (p->get_centro().y - ini->get_centro().y);
		//cout << (float) nFrames / (float) video->get_taxaframes() << "\t| " << p->get_centro().y - ini->get_centro().y << endl;
	}
	//
	// Calculo da velocidade, ou seja, coeficiente angular
	v->valor = (nFrames * somaxy - somax * somay) / (nFrames * somaxquad - somax * somax);
	v->incerteza = 0;
	//
	// Calculo do coeficiente linear que deve ser compativel com zero
	//coef_linear.valor = (somay * somaxquad - somax * somaxy) / (nFrames * somaxquad - somax * somax);
	//coef_linear.incerteza = 0;
	//
	// Calculo do erro
	//float erro;
	/*nFrames = 0;
	FILE *arq = fopen("dados.txt", "w");
	for (GOTA *p = ini; p != fim; p = p->get_prxFrame(), ++nFrames) {
		float x = (float) nFrames / (float) video->get_taxaframes() + 9.13334;
		int y = p->get_centro().y - ini->get_centro().y;
		fprintf(arq, "%f\t%d\n", x, y);
	}
	fclose(arq);
	cout << endl << "Velocidade: " << v->valor << endl;*/
	//cout << "Coef_lin: " << coef_linear.valor << endl;
	//cout << "Erro: " << erro << endl;
	//cout << "v: " << velocidade.valor << endl;
	//cout << "esperado: " << (fim->get_centro().y - ini->get_centro().y) * video->get_taxaframes() / (float) nFrames;
	//velocidade.valor = (fim->get_centro().y - ini->get_centro().y) * video->get_taxaframes() / (float) nFrames;
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MANIPULACAO DE ESTRUTURA
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sendo o elemento envolvido a cabeca, insere o elemento 'novo' dado na lista
void GOTA_VIDEO::insere(GOTA_VIDEO *novo)
{
	if (this->gota != NULL) {
		cout << "ERRO_LOGICA <> GOTA_VIDEO::insere(GOTA_VIDEO*) o elemento envolvido deve ser a cabeca" << endl;
		exit(1);
	}
	novo->prx = this->prx;
	this->prx = novo;
}

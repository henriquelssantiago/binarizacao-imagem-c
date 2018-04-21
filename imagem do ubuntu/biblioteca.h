/*******************************************************************************/
/* Aluno : Henrique Luis de Sousa Santiago                                     */
/* Matricula : 20142045050180                                                  */
/* Avaliacao 04: Trabalho Final                                                */
/* UDM−255 − 2015.1 − Prof. Daniel Ferreira                                    */
/* Compilador:...(DevC++ ou gcc) versao...                                     */
/*******************************************************************************/
#include <stdio.h>
typedef struct imagem{
    char cod[3];
    int lin,col,maxVal;
    float *data;
}imagem;

void criarImagem(FILE *arq, imagem *img);
void gravarImagem(imagem *img);

void binarizacao(imagem *img, float limiar,int inii, int fini, int inij,int finj,int jan);
float mediaArt(imagem *img,int inii, int fini, int inij,int finj,int jan);
float desvioP(imagem *img, float mediaArt,int inii, int fini, int inij,int finj,int jan);

float limiartres(float mediaArt,float desvioP,float k,float r);
float limiarquatro(float mediaArt,float desvioP,float k,float r,float q,float p);

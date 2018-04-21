/*******************************************************************************/
/* Aluno : Henrique Luis de Sousa Santiago                                     */
/* Matricula : 20142045050180                                                  */
/* Avaliacao 04: Trabalho Final                                                */
/* UDM−255 − 2015.1 − Prof. Daniel Ferreira                                    */
/* Compilador:...(DevC++ ou gcc) versao...                                     */
/*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "biblioteca.h"

void criarImagem(FILE *arq, imagem *img){
    int i;
    float aux;
    fscanf(arq,"%s\n",img->cod);
    printf("Codigo: %s\n",img->cod);
    fscanf(arq,"%d %d\n",&img->col, &img->lin);
    printf("Linha: %d\n",img->lin);
    printf("Coluna: %d\n",img->col);
    fscanf(arq,"%d\n",&img->maxVal);
    printf("MaxVal: %d\n",img->maxVal);
    if( (img->data = (float*) malloc(img->lin * img->col * sizeof(float))) == NULL ) puts("Erro na alocacao");
    else
        for(i=0; i<img->col*img->lin; i++) {
            fscanf (arq, "%f", &aux);
            img->data[i] = aux / img->maxVal;
        }
}
void gravarImagem(imagem *img){
    FILE *arqC;
    arqC = fopen("saida.pgm", "w");
	if(arqC == NULL) printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
        fprintf(arqC,"%s\n",img->cod);
        fprintf(arqC,"%d %d \n",img->col,img->lin);
        fprintf(arqC,"%d\n",img->maxVal);
        int i,j;
        for(i=0; i<img->lin; i++){
            for(j=0; j<img->col; j++){
                fprintf(arqC, "%.f ",img->data[(img->col*i) +j]);
            }
            fprintf(arqC,"\n");
        }
        puts("gravando...");
	}
	fclose(arqC);
}

float limiartres(float mediaArt,float desvioP,float k,float r){

    return (mediaArt * (1 + k*((desvioP/r) -1)));
}
float limiarquatro(float mediaArt,float desvioP,float k,float r,float q,float p){
    return (mediaArt * (1 + p*pow(2.718281,-q*mediaArt) + k*((desvioP/r) -1)));
}

void binarizacao(imagem *img, float limiar,int inii, int fini, int inij,int finj,int jan){
    int i,j;
    for(i=inii; i<fini; i++){
        for(j=inij; j<finj; j++){
            if (img->data[(img->col*i) + j] > limiar){
                img->data[(img->col*i) + j] = 255;
            }
            else{
                img->data[(img->col*i) + j] = 0;
            }
        }
    }
}
float mediaArt(imagem *img,int inii, int fini, int inij,int finj,int jan){
    int i,j;
    float acum=0;
    for(i=inii; i<fini; i++)
        for(j=inij; j<finj; j++)
            acum += img->data[ (img->col*i) + j];

    return acum / (float) ((fini-inii)*(finj-inij));
}
float desvioP(imagem *img, float mediaArt,int inii, int fini, int inij,int finj,int jan){
    int i,j;
    float acum=0;

    for(i=inii; i<fini; i++)
        for(j=inij; j<finj; j++)
            acum += pow((img->data[(img->col*i) + j] - mediaArt),2);

    return sqrt(acum /  (float)  ((fini - inii) * (finj - inij) ));
}



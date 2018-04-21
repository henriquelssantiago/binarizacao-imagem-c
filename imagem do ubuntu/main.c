/*******************************************************************************/
/* Aluno : Henrique Luis de Sousa Santiago                                     */
/* Matricula : 20142045050180                                                  */
/* Avaliacao 04: Trabalho Final                                                */
/* UDM−255 − 2015.1 − Prof. Daniel Ferreira                                    */
/* Compilador:...(DevC++ ou gcc) versao...                                     */
/*******************************************************************************/


#include <stdio.h>
#include "header.h"

int main(int argc, char** argv){
    FILE *arq = fopen(argv[1],"r");

    if (arq == NULL) puts("Bugou");
    else{

        imagem img;

        criarImagem(arq,&img);
        float k=0.25,r=0.5,q=10,p=3;
        float media,desvio,limiar;
        int i,j,jan=250;

        //printf("Digite o k: ");scanf("%f",&k);
        //printf("Digite o r: ");scanf("%f",&r);
        //printf("Digite a janela: ");scanf("%d",&jan);
        //display(&img);


        //parte normal
        for(i=0; i<(img.lin - img.lin%jan)/jan; i++){
            for(j=0; j<(img.col-img.col%jan)/jan; j++){
                media = mediaArt(&img,jan*i,jan*(i+1),j*jan,jan*(j+1),jan);
                desvio = desvioP(&img,media,jan*i,jan*(i+1),j*jan,jan*(j+1),jan);
                //limiar = limiartres(media,desvio,k,r);
                limiar = limiarquatro(media,desvio,k,r,q,p);
                printf("media: %f ",media);
                printf("desvio: %f ",desvio);
                printf("limiar: %f\n",limiar);
                binarizacao(&img,limiar,jan*i,jan*(i+1),j*jan,jan*(j+1),jan);
            }
        }

        //borda direita
        if(img.col%jan > 0){
            for(i=0; i<(img.lin-img.lin%jan)/jan; i++){
                media = mediaArt(&img,jan*i,jan*(i+1),img.col-img.col%jan,img.col,jan);
                desvio = desvioP(&img,media,jan*i,jan*(i+1),img.col-img.col%jan,img.col,jan);
                limiar = limiartres(media,desvio,k,r);
                binarizacao(&img,limiar,jan*i,jan*(i+1),img.col-img.col%jan,img.col,jan);
            }
        }

        //parte inferior
        if(img.lin%jan > 0){
            for(i=0; i<(img.col-img.col%jan)/jan; i++){
                media = mediaArt(&img,img.lin-img.lin%jan,img.lin,jan*i,jan*(i+1),jan);
                desvio = desvioP(&img,media,img.lin-img.lin%jan,img.lin,jan*i,jan*(i+1),jan);
                limiar = limiartres(media,desvio,k,r);
                binarizacao(&img,limiar,img.lin-img.lin%jan,img.lin,jan*i,jan*(i+1),jan);
            }
        }

        if(img.lin%jan > 0 && img.col%jan >0){
            media = mediaArt(&img,img.lin-img.lin%jan,img.lin,img.col-img.col%jan,img.col,jan);
            desvio = desvioP(&img,media,img.lin-img.lin%jan,img.lin,img.col-img.col%jan,img.col,jan);
            limiar = limiartres(media,desvio,k,r);
            binarizacao(&img,limiar,img.lin-img.lin%jan,img.lin,img.col-img.col%jan,img.col,jan);
        }
        gravarImagem(&img);
        fclose(arq);
    }
    return 0;
}

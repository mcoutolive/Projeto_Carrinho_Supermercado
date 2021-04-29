#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define S 1200 //Utilizado para o Sleep
#define L 110 //Pode ser alterado; acima deste numero, considera-se que o carrinho esta lotado;
#define T 55 //Pode testar ate T = 55 devido à base de dados disponível. este e' o numero de produtos catalogados salvos no arquivo txt e no codigo

int opcao=0,parar_compra=0,carrinho_lotado=1;
void menu()
{
    while((opcao!=1)&&(opcao!=2)){//Menu para dar ao usuario a opcao de interromper o programa
    printf("1 - Continuar fazendo compras\n");
    printf("2 - Terminar as compras\n");
    printf("Digite a sua opcao: ");
    scanf("%d", &opcao);
    fflush(stdin);
    if((opcao!=1)&&(opcao!=2)){
        printf(" Opcao invalida !! \n");
    }
    Sleep(S);
    system("cls");
    }
    if ((opcao)==1){
        opcao=0;
    }
}

int main(void)
{
    FILE *file; //1ª etapa: leitura dos arquivos. Caso o arquivo nao seja encontrado no mesmo diretorio do codigo, o programa ira mostrar a mensagem
    file = fopen("produtos.txt", "r");
    if (file == NULL){
        printf("Nao foi possivel abrir o arquivo. \n");
        getchar();
        exit(1);
    }
    int i=0, codigo, vetor_codigo[T],numitens_total=0;
    char produto[T],resposta='a';
    //Utilizou-se uma forma manual para armazenar os produtos em um vetor
    char array[][T] = {"Acucar","Absorventes","Agua_oxigenada","Agua_Sanitaria","Alcool_em_gel","Algodao","Amaciante","Arroz","Barbeador_descartavel","Biscoitos_de_polvilho","Cafe","Carne_Bovina_Alcatra","Condicionador","Creme_dental","Curativos","Desinfetante","Desodorante","Detergente","Escova_de_dente","Esparadrapo","Esponja_de_aco","Esponja_de_pia","Farinha_de_trigo","Feijao","Fermento","Fio_dental","Flanelas","Fosforo","Gaze","Guardanapo_de_papel","Hastes_flexiveis","Tomate","Inseticida","Iogurte","Lampadas","Leite","Lustra_moveis","Luvas_plasticas","Macarrao","Margarina","Molho_de_tomate","Oleo","Ovos","Paes","Papel_Aluminio","Papel_Filme","Papel_higienico","Papel_toalha","Queijo_ralado","Sabao_em_barra","Sabao_em_po","Sabonete","Sacos_de_lixo","Sal","Shampoo","Temperos"};
    float preco,valor_total=0, vetor_preco[T],vetor_valor_pago_produto[T],numitens, vetor_numitens[T];
    printf(" ---------------------- * ---------------------- * ---------------------- \n");
    printf(" (-: Bem vindo ao Supermercado Fatec Mogi! >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(" ---------------------- * ---------------------- * ---------------------- \n");
    printf(" (-: Aqui voce pode comprar de forma pratica e rapida !! (-: \n");
    printf(" ---------------------- * ---------------------- * ---------------------- \n");
    printf(" (-: So nao pode se arrepender, pois comprou tem que levar !! (-: \n");
    printf(" ---------------------- * ---------------------- * ---------------------- \n");
    fflush(stdin);
    //lendo os dados do arquivo txt
    while (fscanf(file, "%d %s %f", &codigo, &produto, &preco)!= EOF){
        parar_compra++;
        printf(" (-: Codigo: %d|Produto: %s|Preco Unitario: R$%3.2f\n", codigo, produto, preco);
        printf(" ---------------------- * ---------------------- * ---------------------- \n");
        while ((resposta!='s')&&(resposta!='n')){
           printf(" (-: Gostaria de comprar %s? Escreva 's' para sim e 'n' para nao!\n",&produto);
           scanf("%c",&resposta);
           printf(" ---------------------- * ---------------------- * ----------------------  \n");
           fflush(stdin);
           if ((resposta!='s')&&(resposta!='n')){
                printf(" ---------------------- * ---------------------- * ---------------------- \n");
                printf(" )-: Este comando e' invalido!! Tente de novo )-:!!\n");
                printf(" ---------------------- * ---------------------- * ---------------------- \n");
                Sleep(S);
                system("cls");
           }
        }
           if (resposta=='s'){
                printf("Gostaria de comprar quantas unidades? \n");
                scanf("%f",&numitens);
                fflush(stdin);
                printf(" ---------------------- * ---------------------- * ---------------------- \n");
                printf(" (-: Voce comprou %2.0f unidades de %s (-: \n",numitens,produto);
                printf(" ---------------------- * ---------------------- * ---------------------- \n");
                printf(" (-: Produto adicionado ao carrinho (-: \n");
                vetor_codigo[i] = codigo;
                vetor_preco[i] = preco;
                vetor_numitens[i] = numitens;
                numitens_total = numitens_total + numitens;
                vetor_valor_pago_produto[i] = preco*numitens;
                valor_total = valor_total + vetor_valor_pago_produto[i];
                resposta='a';
                Sleep(S);
                system("cls");
                if (numitens_total>L){
                    printf(" ---------------------- * ---------------------- * ---------------------- \n");
                    printf("Carrinho lotado!! \n");
                    for (i=carrinho_lotado;i<=T;i++){
                        vetor_codigo[i] = 0;
                    }
                    goto end;
                }
           }
           else{
                printf(" )-: Fica para a proxima! Vc nao comprou %s )-: \n",produto);
                printf(" ---------------------- * ---------------------- * ---------------------- \n");
                vetor_codigo[i] = 0;
                resposta='a';
                Sleep(S);
                system("cls");
           }
           i++;
           carrinho_lotado++;
           menu();
           switch(opcao)
           {
           case 1:
           printf(" ---------------------- * ---------------------- * ---------------------- \n");
           break;
           case 2:
           remove("carrinho.txt");
           for (i=parar_compra;i<=T;i++){
                vetor_codigo[i] = 0;
           }
           printf(" ---------------------- * ---------------------- * ---------------------- \n");
           printf(" (-: Volte sempre!! (-: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
           printf(" ---------------------- * ---------------------- * ---------------------- \n");
           goto end;
          }
    }
    end:
    // Escrevendo os dados no arquivo txt
    for (i=0;i<=T;i++){
         if (vetor_codigo[i]!=0){
            FILE *fp;
            remove("carrinho.txt");
            fp=fopen("carrinho.txt", "a+");
            fprintf(fp,"Codigo:%d|",(vetor_codigo[i]));
            fprintf(fp,"Produto:%s|",(array[i]));
            fprintf(fp,"Preco Unit.:R$%3.2f|",(vetor_preco[i]));
            fprintf(fp,"Num.Itens:%2.0f|",(vetor_numitens[i]));
            fprintf(fp,"ValorPago:R$%3.2f|\n",(vetor_valor_pago_produto[i]));
         }

         if (i==T){
            FILE *fp;
            fp=fopen("carrinho.txt", "a+");
            fprintf(fp,"Total de Itens:%d itens|",(numitens_total));
            fprintf(fp,"Valor da Compra:R$%3.2f\n",(valor_total));
         }
    }
    fclose(file);

    return 0;
}

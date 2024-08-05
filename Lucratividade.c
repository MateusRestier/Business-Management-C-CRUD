#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//STRUCTS
struct Produto{
    int codigo;
    char descricao[50];
    float preco;
    int quantidadeVendida;
    float percentualLucro;
    float lucroObtido;
};


//FUNÇÕES GENERICAS
int buscaProduto(int tam,int cod,struct Produto * produto){
    int pos = -1;

    for (int i = 0; i < tam; ++i) {
        if(cod == produto[i].codigo){
            pos = i;
            break;
        }
    }
    return pos;
}

void receberDados(int pos,struct Produto *produto){
    printf("Digite o codigo:\n");
    scanf_s("%d",&produto[pos].codigo);
    fflush(stdin);
    printf("Digite uma descricao de ate 50 caracteres:\n");
    gets(produto[pos].descricao);
    printf("Digite o preco do produto:\n");
    scanf_s("%f",&produto[pos].preco);
    fflush(stdin);
    printf("Digite a quantidade vendida do produto:\n");
    scanf_s("%d",&produto[pos].quantidadeVendida);
    printf("Digite o percentual de lucro do produto: \n");
    scanf_s("%f",&produto[pos].percentualLucro);
    printf("Digite o lucro obtido:\n");
    scanf_s("%f",&produto[pos].lucroObtido);
    fflush(stdin);
};

void exibirDados(int pos,struct Produto * produto){
    printf("Descricao: %s\n",produto[pos].descricao);
    printf("Lucro obtido: R$ %.2f\n\n",produto[pos].lucroObtido);
}

void trocaPosicao(int pos1, int pos2, struct Produto *produto) {
    struct Produto *aux1;
    aux1 = (struct Produto*) malloc(sizeof(struct Produto));
    aux1[0].codigo = produto[pos1].codigo;
    strcpy(aux1[0].descricao, produto[pos1].descricao);
    aux1[0].preco = produto[pos1].preco;
    aux1[0].quantidadeVendida = produto[pos1].quantidadeVendida;
    aux1[0].percentualLucro = produto[pos1].percentualLucro;
    aux1[0].lucroObtido = produto[pos1].lucroObtido;

    produto[pos1].codigo = produto[pos2].codigo;
    strcpy(produto[pos1].descricao, produto[pos2].descricao);
    produto[pos1].preco = produto[pos2].preco;
    produto[pos1].quantidadeVendida = produto[pos2].quantidadeVendida;
    produto[pos1].percentualLucro = produto[pos2].percentualLucro;
    produto[pos1].lucroObtido = produto[pos2].lucroObtido;

    produto[pos2].codigo = aux1[0].codigo;
    strcpy(produto[pos2].descricao,aux1[0].descricao);
    produto[pos2].preco = aux1[0].preco;
    produto[pos2].quantidadeVendida = aux1[0].quantidadeVendida;
    produto[pos2].percentualLucro = aux1[0].percentualLucro;
    produto[pos2].lucroObtido = aux1[0].lucroObtido;
    free(aux1);
}


//FUNÇÕES DO MENU

//OPÇÃO 1
int incluirProduto(int tam,struct Produto *produto){

    int pos;
    if (tam > 0){
        produto = (struct Produto*) realloc(produto,(tam+1)* sizeof(struct Produto));
    }
    tam ++;
    pos = tam-1;
    receberDados(pos,produto);
    return tam;
}

//OPÇÃO 2

void ordenaLucro(int tam,int pos,struct Produto *produto){

    if(tam > 1){
        if (pos == 0)
        {
            if(produto[pos].lucroObtido < produto[pos+1].lucroObtido){
                trocaPosicao(pos,pos + 1,produto);
            }
            ordenaLucro(tam,pos + 1,produto);
        }else if(pos < tam-1){
            if(produto[pos].lucroObtido < produto[pos+1].lucroObtido){
                trocaPosicao(pos,pos + 1,produto);
                if(produto[pos].lucroObtido < produto[pos-1].lucroObtido) {
                    ordenaLucro(tam,pos+1,produto);
                } else {
                    ordenaLucro(tam, pos - 1, produto);
                }
            } else{
                ordenaLucro(tam,pos+1,produto);
            }
        }
    }
}

void Ordenar (int tam, struct Produto *produto)
{
    int i;
    if (tam > 1)
    {
        for (i=0; i<tam-1; i++)
        {
            if (produto[i].lucroObtido < produto[i + 1].lucroObtido )
            {
                trocaPosicao(i,i+1,produto);
            }
        }
        Ordenar(tam-1, produto);
    }
}


void registrarVenda(int tam,struct Produto *produto){
    int cod;
    printf("Digite o codigo do produto que deseja registrar a venda:\n");
    scanf_s("%d",&cod);

    int pos = buscaProduto(tam,cod,produto);

    if(pos < 0){
        printf("Nenhum produto com esse codigo foi encontrado!!\n");
    } else{
        printf("Digite a quantidade vendida do produto:\n");
        int qnt;
        scanf_s("%d",&qnt);
        produto[pos].quantidadeVendida += qnt;
    }
}

//OPÇÃO 3
void emitirLucratividade(int tam, struct Produto *produto){
    for (int i = 0; i < tam; i++)
    {
        produto[i].lucroObtido += produto[i].preco * produto[i].quantidadeVendida * (produto[i].percentualLucro / 100);
    }

    ordenaLucro(tam,0,produto);

    printf("\n===========Relatorio de Lucratividade===========\n\n");
    for (int i = 0; i < tam; ++i) {
        printf("Produto %d:\n",i +1);
        exibirDados(i,produto);
    }

}


int main() {
    int opcao = 0;
    struct Produto *produto;
    produto = (struct Produto*) malloc(sizeof(struct Produto));
    int tam = 0;
    int pos;
    printf("Bem vindo ao sitema!!!\n\n");
    while (opcao != 9){
        printf("Menu:\n\n");
        printf("1-Incluir Produto\n");
        printf("2-Registrar Venda\n");
        printf("3-Emitir Lucratividade\n");
        printf("9-Sair\n\n");
        printf("Escolha umas das opcoes acima:\n");
        scanf_s("%d",&opcao);

        switch (opcao) {
            case 9:
                printf("Finalizando o programa!");
                free(produto);
                exit(2);
                break;
            case 1:
                tam = incluirProduto(tam,produto);
                break;
            case 2:
                registrarVenda(tam,produto);
                break;
            case 3:
                emitirLucratividade(tam,produto);
                break;
            default:
                printf("Digite uma opcao valida!!");
        }

    }

    return 0;
}



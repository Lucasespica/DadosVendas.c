#include "Arvore.h"

int gerarIDUnico(Arv *a1)
{
    int id;
    bool idExiste = true;

    do
    {
        id = rand() % 9000 + 1000;

        if (Arv_vazia(a1))
            return id;
    }
    while (Busca(a1->raiz, id));

    return id;
}

void gerarMatricula(Arv *a1, char matricula[])
{
    do
    {
        char letra = 'A' + (rand() % 26);
        int numero = rand() % 900 + 100;

        sprintf(matricula, "%c%03d", letra, numero);

    }
    while (BuscaPorMatricula(a1->raiz, matricula) != NULL);
}

int validarTexto(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        char c = str[i];
        if (!((c >= 'A' && c <= 'Z') ||
                (c >= 'a' && c <= 'z') ||
                c == ' '))
        {
            return 0;
        }
    }
    return 1;
}

int validarMatricula(const char *str)
{
    char c = toupper(str[0]);
    if (!(c >= 'A' && c <= 'Z'))
    {
        return 0;
    }
    for(int i = 1; str[i] != '\0'; i++)
    {
        char c = str[i];
        if (!(c >= '0' && c <= '9'))
        {
            return 0;
        }
    }
    return 1;
}

void novaVenda(Arv *a1)
{
    char confirm[2];
    char nomeCliente[50];
    char nomeVendedor[50];
    char matricula[5];
    float valorTransacao;

    NoArv *vendedorExistente = NULL;
    Data dataInsercao;
    int dataValida;
    char input[11];

    if(!Arv_vazia(a1))
    {
        do
        {
            printf("\nVenda de um vendedor ja cadastrado? (S/N):");
            scanf("%s", &confirm);
            while (getchar() != '\n');

            if (toupper(confirm[0]) != 'S' && toupper(confirm[0]) != 'N' || strlen(confirm) != 1)
            {
                printf("\nErro...\nDigite somente s ou n!\n");

            }

        }
        while(toupper(confirm[0]) != 'S' && toupper(confirm[0]) != 'N' || strlen(confirm) != 1);
    }
    else
    {
        confirm[0] = 'N';
    }

    printf("\nInsira os dados da venda (Enter para avancar)\n");

    if (toupper(confirm[0]) == 'S')
    {
        do
        {
            do
            {
                printf("\nDigite a matricula do vendedor: ");
                scanf("%5s", matricula);
                while (getchar() != '\n');

                matricula[0] = toupper(matricula[0]);

                if (!validarMatricula(matricula) || strlen(matricula) != 4)
                {
                    printf("\nMatricula invalida! Tente novamente.\n");
                }
            } while(!validarMatricula(matricula) || strlen(matricula) != 4);

            vendedorExistente = BuscaPorMatricula(a1->raiz, matricula);

            if (vendedorExistente == NULL)
            {
                printf("\nMatricula nao encontrada.\nTente novamente\n");
            }
        } while(vendedorExistente == NULL);


        strcpy(nomeVendedor, vendedorExistente->vendedor);
    }

    if(toupper(confirm[0]) == 'N')
    {
        do
        {
            printf("\nVendedor: ");
            scanf("%49s", nomeVendedor);

            if(!validarTexto(nomeVendedor))
            {
                printf("\nNome invalido! Use apenas letras e espacos.\n");
            }

        }
        while(!validarTexto(nomeVendedor));

        gerarMatricula(a1, matricula);

    }

    int ID = gerarIDUnico(a1);

    do
    {
        printf("\nCliente: ");
        scanf("%49s", nomeCliente);
        while (getchar() != '\n');

        if(!validarTexto(nomeCliente))
        {
            printf("\nNome invalido! Use apenas letras e espacos.\n");
        }
    }
    while(!validarTexto(nomeCliente));

    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    do
    {
       dataValida = 1;
       printf("\nDigite a data da venda (dd/mm/aaaa): ");
       scanf("%11s", input);
       while (getchar() != '\n');

       if (sscanf(input, "%2d/%2d/%4d", &dataInsercao.dia, &dataInsercao.mes, &dataInsercao.ano) != 3 || strlen(input) != 10)
       {
           printf("\nFormato invalido! Tente novamente.\n");
           dataValida = 0;
           continue;
       }
       if (dataInsercao.dia < 1 || dataInsercao.dia > 31)
       {
           printf("\nDia invalido! Tente novamente.\n");
           dataValida = 0;
       }
       if (dataInsercao.mes < 1 || dataInsercao.mes > 12)
       {
           printf("\nMes invalido! Tente novamente.\n");
           dataValida = 0;
       }
       if (dataInsercao.ano < 1995 || dataInsercao.ano > tm.tm_year + 1900)
       {
           printf("\nAno invalido! Tente novamente.\n");
           dataValida = 0;
       }
    }
    while (!dataValida);

    int confirmDoFloat;
    do
    {
        confirmDoFloat = 0;
        printf("\nValor da transacao: ");

        if (!scanf("%f", &valorTransacao))
        {
            fflush(stdin);
            printf("\nValor de transacao invalida!\n");
            confirmDoFloat = 1;
        }
    }
    while (confirmDoFloat);

    insereArv(a1, ID, nomeCliente, nomeVendedor, dataInsercao, valorTransacao, matricula);
    printf("\nVenda cadastrada com sucesso! Dados da venda:\n");

    printf("\nID: %d| Vendedor: %s| Matricula: %s| Cliente: %s| Data de Transacao: %d/%d/%d| Valor(R$): %.2f\n", ID, nomeVendedor, matricula,
           nomeCliente, dataInsercao.dia, dataInsercao.mes, dataInsercao.ano, valorTransacao);

    system("pause");
    system("cls");

}

void inOrderCrescente(NoArv *a1)
{
    if (a1 == NULL)
        return;
        
    if (a1->esq != NULL)
    {
        inOrderCrescente(a1->esq);
    }
    
    printf("\nID: %d | Vendedor: %s | Matricula: %s | Cliente: %s | Data de Transacao: %d/%d/%d | Valor(R$): %.2f\n", 
           a1->ID, a1->vendedor, a1->matricula, a1->cliente,
           a1->dataTransacao.dia, a1->dataTransacao.mes, a1->dataTransacao.ano, a1->valorVenda);
    
    if (a1->dir != NULL)
    {
        inOrderCrescente(a1->dir);
    }
}

void listarVendas(Arv *a1)
{
    if (Arv_vazia(a1))
    {
        printf("\nNao ha nenhuma venda registrada!\n");
        return;
    }

    int opcaoOrdem;
    
    printf("\n=== Listagem de Vendas ===\n");
    printf("\nEscolha a ordem de listagem:\n");
    printf("1. Ordem decrescente de ID\n");
    printf("2. Ordem crescente de ID\n");
    printf("\nOpcao: ");
    
    if (!scanf("%d", &opcaoOrdem))
    {
        fflush(stdin);
        printf("\nOpcao invalida! Digite um numero.\n");
        return;
    }
    
    while (getchar() != '\n');
    
    printf("\n=== Vendas Registradas ===\n");
    
    if (opcaoOrdem == 1)
    {
        inOrder(a1->raiz);
    }
    else if (opcaoOrdem == 2)
    {
        inOrderCrescente(a1->raiz);
    }
    else
    {
        printf("\nOpcao invalida!\n");
        return;
    }
}

//--------------------------------------------------------------------------------------
//funcoes estatisticas

int contarNos(NoArv *no) {
    if (no == NULL)
    {
        return 0;
    }
    return 1 + contarNos(no->esq) + contarNos(no->dir);
}

float somarVendas(NoArv *no) {
    if (no == NULL)
    {
        return 0;
    }
    return no->valorVenda + somarVendas(no->esq) + somarVendas(no->dir);
}

float media(float valor, int num)
{
    float med = valor/num;
    return med;
}

float maiorVenda(NoArv *no) {
    if (no == NULL) return 0;

    float maior = no->valorVenda;

    float e = maiorVenda(no->esq);
    float d = maiorVenda(no->dir);

    if (e > maior)
    {
        maior = e;
    }
    if (d > maior)
    {
        maior = d;
    }

    return maior;
}

float menorVenda(NoArv *no) {
    if (no == NULL) return 999999999; // valor grande

    float menor = no->valorVenda;

    float e = menorVenda(no->esq);
    float d = menorVenda(no->dir);

    if (e < menor)
    {
        menor = e;
    }

    if (d < menor)
    {
        menor = d;
    }

    return menor;
}


void estatistica(Arv *a1)
{
    int numTotal = contarNos(a1->raiz);
    float somaVenda = somarVendas(a1->raiz);

    printf("\nEstatistica das vendas: \n");
    printf("\nNumero de vendas: %d\n", numTotal);
    printf("Soma total das vendas: %.2f\n", somaVenda);
    printf("Media das vendas: %.2f\n", media(somaVenda, numTotal));
    printf("Maior venda: %.2f\n", maiorVenda(a1->raiz));
    printf("Menor venda: %.2f\n", menorVenda(a1->raiz));

    system("pause");
    system("cls");
}

void removerVenda(Arv *a1)
{
    if (Arv_vazia(a1))
    {
        printf("\nNao ha vendas registradas!\n");
        return;
    }

    int idRemover;
    
    printf("\n=== Remocao de Venda ====\n");
    printf("\nInsira o ID para a exclusao (Enter para avancar): ");
    
    if (!scanf("%d", &idRemover))
    {
        fflush(stdin);
        printf("\nID invalido! Digite um numero.\n");
        return;
    }
    
    while (getchar() != '\n');
    
    if (!Busca(a1->raiz, idRemover))
    {
        printf("\nNao ha vendas registradas com este ID.\n");
        return;
    }
    
    Arv *resultado = remover(a1, idRemover);
    
    if (resultado == NULL)
    {
        printf("\nVenda removida com sucesso!\n");
        printf("A arvore de vendas agora esta vazia.\n");
        a1 = criaArv();
        return;
    }
    
    printf("\nVenda removida com sucesso!\n");
}

//--------------------------------------------------------------------------------------
void exibirMenu()
{
    printf("\n====================================================================\n");
    printf(" Bem vindo ao Gerenciamento de Vendas\n");
    printf("====================================================================\n");
    printf("\n| Funcionalidades |\n");
    printf("\n1. Inserir uma nova venda\n");
    printf("2. Listar todas as vendas\n");
    printf("3. Buscar as vendas de um determinado vendedor\n");
    printf("4. Listar vendas acima ou abaixo de um valor definido\n");
    printf("5. Exibir estatisticas\n");
    printf("6. Remocao de uma venda\n");
    printf("7. Sair\n");
    printf("\nEscolha a funcionalidade desejada: ");
}

int main()
{
    srand((unsigned)time(NULL));
    Arv *arvorePrincipal = criaArv();

    int opcao;

    do
    {
        exibirMenu();

        if (!scanf("%d", &opcao))
        {
            fflush(stdin);
            system("cls");
            printf("\nOpcao invalida! Digite um numero.\n");
            continue;
        }

        switch (opcao)
        {
        case 1:
            system("cls");
            novaVenda(arvorePrincipal);
            break;

        case 2:
            system("cls");
            listarVendas(arvorePrincipal);
            break;

        case 3:
            system("cls");
            //implementar
            break;

        case 4:
            system("cls");
            //implementar
            break;

        case 5:
            system("cls");
            estatistica(arvorePrincipal);
            break;

        case 6:
            system("cls");
            removerVenda(arvorePrincipal);
            break;

        case 7:
            system("cls");
            printf("\nSaindo do sistema...\n");
            break;

        default:
            system("cls");
            printf("\nOpcao invalida! Escolha uma opcao valida.\n");
        }

    } while (opcao != 7);

    liberaArv(arvorePrincipal->raiz);
    printf("Sistema encerrado com sucesso!\n");

    return 0;
}

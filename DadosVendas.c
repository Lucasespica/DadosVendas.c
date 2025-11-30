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
    system("pause");
    system("cls");
}

void auxPercorre(NoArv *no, char *nomeBuscado, int *achou) {
    if (no == NULL) return;

    auxPercorre(no->esq, nomeBuscado, achou);

    if (strcmp(no->vendedor, nomeBuscado) == 0 || strcmp(no->matricula, nomeBuscado) == 0) {

        if (*achou == 0) {
            printf("\n=== Vendas Encontradas ===\n");
            printf("%-6s | %-12s | %-15s | %-10s | %s\n", "ID", "Matricula", "Cliente", "Data", "Valor (R$)");
            printf("--------------------------------------------------------------------------------------\n");
            *achou = 1;
        }

        printf("%-6d | %-12s | %-15s | %02d/%02d/%04d | R$ %.2f\n",
               no->ID, no->matricula, no->cliente,
               no->dataTransacao.dia, no->dataTransacao.mes, no->dataTransacao.ano,
               no->valorVenda);
    }

    auxPercorre(no->dir, nomeBuscado, achou);
}


void BuscaVendedor(NoArv *a1) {

    if (a1 == NULL) {
        printf("\nArvore vazia / Nao ha vendas.\n");
        return;
    }

    char nome[50];
    int flag = 0;

    printf("\nDigite o Nome do Vendedor ou Matricula: ");
    scanf(" %49[^\n]", nome);
    while(getchar() != '\n');

    auxPercorre(a1, nome, &flag);

    if (flag == 0) {
        printf("\nNenhum registro encontrado para '%s'.\n", nome);
    } else {
        printf("--------------------------------------------------------------------------------------\n");
    }

    system("pause");
    system("cls");
}

typedef struct Lista {
    int ID;
    char cliente[50];
    char vendedor[50];
    char matricula[4];
    Data dataTransacao;
    float valorVenda;

    struct Lista* prox;
} Lista;


Lista* lista_insere(Lista* L, NoArv* no) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));

    novo->ID = no->ID;
    strcpy(novo->cliente, no->cliente);
    strcpy(novo->vendedor, no->vendedor);
    strcpy(novo->matricula, no->matricula);
    novo->dataTransacao = no->dataTransacao;
    novo->valorVenda = no->valorVenda;

    novo->prox = L;
    return novo;
}

void libera_lista(Lista* L)
{
    Lista* aux;
    while (L != NULL)
    {
        aux = L->prox;
        free(L);
        L = aux;
    }
}

void lista_coleta_acima(NoArv* raiz, float valor, Lista** L) {
    if (raiz == NULL)
    {
        return;
    }
    lista_coleta_acima(raiz->esq, valor, L);

    if (raiz->valorVenda > valor)
    {
        *L = lista_insere(*L, raiz);
    }

    lista_coleta_acima(raiz->dir, valor, L);
}

void lista_coleta_abaixo(NoArv* raiz, float valor, Lista** L) {
    if (raiz == NULL)
    {
        return;
    }
    lista_coleta_abaixo(raiz->esq, valor, L);

    if (raiz->valorVenda < valor)
    {
        *L = lista_insere(*L, raiz);
    }
    lista_coleta_abaixo(raiz->dir, valor, L);
}

void encontrar_larguras_lista(Lista *L, int *maxVend, int *maxMat, int *maxCli)
{
    *maxVend = 0;
    *maxMat = 0;
    *maxCli = 0;

    while (L != NULL)
    {
        int tv = strlen(L->vendedor);
        int tm = strlen(L->matricula);
        int tc = strlen(L->cliente);

        if (tv > *maxVend) *maxVend = tv;
        if (tm > *maxMat) *maxMat = tm;
        if (tc > *maxCli) *maxCli = tc;

        L = L->prox;
    }
}

void imprimir_lista_formatada(Lista *L, int maxVend, int maxMat, int maxCli)
{
    char formato[200];

    sprintf(formato,"%%-6d | %%-%ds | %%-%ds | %%-%ds | %%02d/%%02d/%%04d | R$%%.2f\n",maxVend, maxMat, maxCli);

    for (Lista* p = L; p != NULL; p = p->prox)
    {
        printf(formato, p->ID, p->vendedor, p->matricula, p->cliente, p->dataTransacao.dia, p->dataTransacao.mes, p->dataTransacao.ano, p->valorVenda);
    }
}


void imprime_vendas(Arv* Arvore)
{
    int filtrando_acima_abaixo;
    float valor;

    while (1)
    {
    printf("\nFiltragem de Vendas\n");
    printf("Informe o tipo de filtro desejado:\n");
    printf("  1 - Exibir vendas acima do valor a informar\n");
    printf("  0 - Exibir vendas abaixo do valor a informar\n");
    printf("Opcao: ");

    if (scanf("%d", &filtrando_acima_abaixo) != 1)
    {
        system("cls");
        printf("\nEntrada inválida! Digite apenas números.\n");
        while (getchar() != '\n');

        continue;
    }

    if (filtrando_acima_abaixo == 0 || filtrando_acima_abaixo == 1)
    {
        break;
    }
    system("cls");
    printf("\nOpcao invalida! Digite 0 ou 1.\n");
    }

    system("cls");

    if(Arvore->raiz == NULL)
    {
        printf("Não ha valores registrados\n");
        printf("Pressione ENTER para retornar ao MENU\n");
        getchar();
        getchar();
        system("cls");
        return;
    }

    while (1)
    {
        if(filtrando_acima_abaixo == 1)
        {
            printf("FILTRANDO ACIMA\n");
        }
        else
        {
            printf("FILTRANDO ABAIXO\n");
        }

        printf("Insira o valor desejado: ");

        if (scanf("%f", &valor) != 1)
        {
            system("cls");
            printf("\nEntrada inválida! Digite apenas números.\n\n");

            while (getchar() != '\n');
            continue;
        }

        break;
    }

    system("cls");


    Lista* L = NULL;

    if (filtrando_acima_abaixo == 1)
    {
        lista_coleta_acima(Arvore->raiz, valor, &L);

        if (L == NULL)
        {
            printf("Nao ha valores maiores que o inserido.\n");

            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();

            system("cls");
            return;
        }
        else
        {
            int mv, mm, mc;
            encontrar_larguras_lista(L, &mv, &mm, &mc);
            imprimir_lista_formatada(L, mv, mm, mc);

            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();

            system("cls");
        }
    }
    else
    {
        lista_coleta_abaixo(Arvore->raiz, valor, &L);

        if (L == NULL)
        {
            printf("Nao ha valores menores que o inserido.\n");

            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();

            system("cls");
            return;
        }
        else
        {
            int mv, mm, mc;
            encontrar_larguras_lista(L, &mv, &mm, &mc);
            imprimir_lista_formatada(L, mv, mm, mc);

            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();

            system("cls");
        }
    }

    libera_lista(L);
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
    if (valor == 0 || num ==0)
        {
            return 0;
        }
    float med = valor/num;
    return med;
}

float maiorVenda(NoArv *no) {
    if (no == NULL)
    {
        return 0;
    }

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
    if (no == NULL)
    {
        return 999999999;
    }

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
            BuscaVendedor(arvorePrincipal->raiz);
            break;

        case 4:
            system("cls");
            imprime_vendas(arvorePrincipal);
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

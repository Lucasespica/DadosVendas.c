# DadosVendas.c

# Projeto: Organização e análise de dados de vendas

<p>O sistema deverá analisar rapidamente o histórico de vendas.<p>
<p>Cada venda registrada deve conter informações completas sobre o cliente, vendedor, data e valor.<p>
<p>Essas vendas serão organizadas em uma Árvore Binária de Busca (ABB) para permitir consultas eficientes.<p> 
<p>O sistema deverá possibilitar a inserção, listagem, busca, remoção e análise estatística das vendas. <p>
<p>Dessa forma, será possível identificar facilmente as transações de maior ou menor valor.<p>

Portanto, este sistema deverá, obrigatoriamente, trabalhar com **ARVORES**.  
O time deverá adaptar a biblioteca de Arvore 'Arvore.h'.

---
## As informações necessárias para a implementação do sistema são:

- **ID** – código da venda inteiro gerado aleatoriamente entre 1000 e 9999 (**NÃO É PERMITIDO ID REPETIDO**). Chave da Inserção e Remoção na árvore
- **Cliente** – alfanumérico com no máximo 50 caracteres
- **Vendedor** – alfanumérico com no máximo 50 caracteres
- **Matrícula do Vendedor** – código alfanumérico gerado aleatoriamente, inicializado com a letra V e 3 dígitos. Exemplo: V345
- **Data da Transação** – estrutura Data contendo dia, mês e ano inteiros.
- **Valor da Transação** – valor monetário com 2 casas decimais

---

## Funcionalidades do sistema

### 1. Inserir uma nova venda
- Consiste na inserção dos dados de uma nova venda, armazenado numa árvore binária. Obedecendo a regra trabalhada em sala de aula

### 2. Listar todas as vendas.
- O usuário terá a opção de obter a listagem em ordem crescente ou decrescente de ID.
- Imprimir os dados em forma de uma tabela, onde o cabeçalho da tabela deve ser:
  <ID | Vendedor | Matrícula |Cliente | Data de Transação| Valor(R$)>

### 3. Buscar as vendas de um determinado Vendedor
- A busca poderá ser realizada pela Matrícula ou Nome do Vendedor. A impressão dos dados deverá seguir o modelo abaixo:
1. Vendedor: Nome do Vendedor
2. Matrícula: Matrícula do Vendedor
- Construir uma tabela de informações com o seguinte cabeçalho: ID | Cliente | Data de Transação| Valor(R$)

### 4. Listar vendas acima ou abaixo de um valor definido
O usuário fornece o valor e o sistema imprime as informações das vendas acima ou abaixo.
As informações são impressas em tabela seguindo o cabeçalho:
ID | Vendedor | Matrícula |Cliente | Data de Transação| Valor(R$)

### 5. Exibir estatísticas:
- Número total de vendas,
- Soma total do faturamento
- Caso o time deseje colocar uma análise estatística que considere relevante, deve colocar e explicar no relatório, o que é e o porquê de ter feito.

### 6. Remoção de uma venda
- O sistema deve estar preparado para a remoção de uma venda pelo ID, caso ela tenha algum problema.
- A regra de remoção dever ser aquela estudada em aula.

### 7. Finalizar o sistema

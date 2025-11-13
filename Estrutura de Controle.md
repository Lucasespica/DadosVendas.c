**1. Inserir uma nova venda**
* Insira os dados da venda (Enter para avançar):
* Cliente:
* Vendedor:
* Data de Transação (dd/mm/aaaa):
* Valor da Transação:
  
  * Mensagem de Erro: `"Os campos não foram preenchidos corretamente, por favor complete-os novamente!"`
  * Mensagem de Sucesso: `O Pet <nome> de ID: <id_num> foi cadastrado com sucesso!`

---

**2. Listar todas as vendas**
* Verifica se há uma **Arvore** com dados.
  * Caso haja, imprime todas as vendas em ordem crescente de ID:
    `"ID | Vendedor | Matrícula |Cliente | Data de Transação| Valor(R$)"`
* Se não houver vendas, exibe:
  `"Não há nenhuma venda registrada!"`

---

**3. Buscar as vendas de um determinado vendedor**
* Insira os dados do vendedor (Enter para avançar):
* Vendedor:
* Matrícula do vendedor:

   * Mensagem de Erro `"Os campos não foram preenchidos corretamente, por favor complete-os novamente!"`
   * Mensagem quando não encontrar `"Não foram encontradas vendas de tal vendedor."`
   * Mensagem de Sucesso `"Encontrado! ` E logo em seguida a sequência de vendas: `ID | Cliente | Data de Transação| Valor(R$)"`

---

**4. Listar vendas acima ou abaixo de um valor definido**
* Valores acima ou abaixo? (1 para cima e 0 para baixo):
* Insira o valor desejado:
  * Mensagem de Erro `"Os campos não foram preenchidos corretamente, por favor complete-os novamente!"`
  * Mensagem quando não houver valores acima `"Não há valores maiores que o inserido."`
  * Mensagem quando não houver valores abaixo `"Não há valores menores que o inserido."`
  * Mensagem quando não houver valores `"Não há valores registrados."`
  * Mensagem de Sucesso `"ID | Vendedor | Matrícula |Cliente | Data de Transação| Valor(R$)"` E se houver mais valores, serão exibidos em sequência.

---

**5. Exibir estatísticas**
* Número total de vendas:
* Soma total do faturamento:
* Média de vendas:
* Maior venda:
* Menor venda:
* Mediana (com dados ordenados):

---

**6. Remoção de uma venda**
* Insira o ID para a exclusão (Enter para avançar):
  * Mensagem quando não houver a venda `"Não há vendas registradas com este ID."`
  * Mensagem de Sucesso `"Venda removida com sucesso!"`

---

**7. Finalizar o sistema**
* Libera a arvore e exibe: `"Saindo...`

# ep1-aed2-test

Função main para testar o EP1 de AED2 (do professor Ivandré).

## Instruções

Siga o passo a passo:

1. Baixe o arquivo `main-testes-EP.c` para o diretório do seu código.
2. Altere a segunda linha `#include "arquivo.cpp"` para o nome do arquivo do
   seu EP.
3. Compile e rode o arquivo `main-testes-EP.c`

Se você estiver em um ambiente Linux (incluindo o Replit), você pode usar o
seguinte comando no bash:

```bash
# Substitua o comando abaixo pelo nome do arquivo do seu EP
ARQUIVO_TESTE=nome_do_arquivo.cpp
```

Em seguida, copie e cole os seguintes comandos:

```bash
# O comando seguinte baixa o arquivo main.c diretamente do GitHub
curl -O "https://raw.githubusercontent.com/MarcusPeixe/ep1-aed2-test/main/main-testes-EP.c"
# O comando seguinte adapta a diretriz include para o seu EP
sed -i "s/arquivo.cpp/$ARQUIVO_TESTE/" main-testes-EP.c

# O comando seguinte compila e roda o programa
gcc -Wall main-testes-EP.c -o main-testes && ./main-testes
```

Alternativamente, caso você esteja em uma IDE onde é difícil trabalhar com
mais de um arquivo, você pode copiar todo o conteúdo de `main-testes-EP.c` para o seu 
arquivo, substituindo a sua main.

Este código testa uma variedade de casos especiais no grafo-exemplo do
enunciado do EP.

## Grafos

O teste 1 utiliza o seguinte grafo (caminho mais curto: 1, 4, 5):

![Grafo para o teste 1](test1.drawio.png)

---

O teste 2 utiliza um grafo muito denso para representar em imagem, mas o
caminho de menor custo é uma única aresta (que liga o início 5 direto ao
fim 12).

---

O teste 3 utiliza o seguinte grafo (caminho mais curto com chave: 9, 5, 7, 10, 4, 2):

![Grafo para o teste 3](test3.drawio.png)

---

O teste 4 utiliza o seguinte grafo (caminho mais curto: 5, 1, 2, 8, 4):

![Grafo para o teste 4](test4.drawio.png)

---

A partir do teste 5, o grafo utilizado é o grafo de exemplo, e a principal alteração
é as posições dos vértices *início*, *chave*, e *fim*.

![Grafo para o teste 3](test-example-graph.png)



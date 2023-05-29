#define main main_
#include "dijkstra.cpp"
#undef main

// COPIE E COLE TODO O CÓDIGO ABAIXO DESTA LINHA NO ARQUIVO DO SEU EP //////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _countof(x) (sizeof(x) / sizeof(*(x)))

struct _tests
{
  int N, A;
  int *aberto, *ijpeso;
  int inicio, chave, fim;

  int custo_esperado;
  char const *descricao;
};

void print_path(NO const *path)
{
  if (!path) {
    printf("(sem caminho)\n");
    return;
  }
  for (NO const *no = path; no; no = no->prox) {
    printf("%3d ", no->adj);
  }
  printf("\n");
}

int get_cost(int const ijpeso[], int A, int v1, int v2)
{
  int menor_peso = -1;
  for (int i = 0; i < A; ++i) {
    // look for edge v1 -> v2 or v2 -> v1, and return its cost
    int ii   = ijpeso[3 * i + 0];
    int jj   = ijpeso[3 * i + 1];
    int peso = ijpeso[3 * i + 2];
    if ((ii == v1 && jj == v2) || (jj == v1 && ii == v2)) {
      if (menor_peso == -1 || peso < menor_peso) {
        menor_peso = peso;
      }
    }
  }
  return menor_peso;
}

void print_error(NO const *path, int bad_node, char const *msg)
{
  printf("Caminho:\n");
  print_path(path);
  for (int i = 0; i < bad_node; ++i) printf("    ");
  printf("^^^ neste vertice\n");
  printf("ERRO: %s\n", msg);
}

bool check_path(
  NO *path, int aberto[], int ijpeso[], int N, int A,
  int inicio, int fim, int chave, int *cost)
{
  int total_cost = 0;
  bool unlocked = false;
  NO *no = path;

  if (!no) {
    *cost = -1;
    return true; // no path (valid solution in some instances)
  }
  if (no->adj != inicio) {
    print_error(path, 0, "Caminho nao comeca em 'inicio'");
    return false;
  }

  int idx;
  for (idx = 0; no->prox; no = no->prox, ++idx) {
    int current = no->adj, next = no->prox->adj;
    if (next < 1 || next > N) {
      print_error(path, idx + 1, "Caminho passa por vertice inexistente");
      return false;
    }
    // if passed through key room, set unlocked to true
    if (current == chave) unlocked = true;
    // check if path goes through locked room illegally
    if (!unlocked && !aberto[next - 1]) {
      print_error(
        path, idx + 1,
        "Caminho passa por sala fechada sem ter antes obtido a chave"
      );
      return false;
    }
    int cost = get_cost(ijpeso, A, current, next);
    // check if path teleports from one room to another
    if (cost == -1) {
      print_error(
        path, idx + 1,
        "Esta sala nao se conecta com a sala anterior"
      );
      return false;
    }
    total_cost += cost;
  }

  if (no->adj != fim) {
    print_error(path, idx, "Caminho nao termina em 'fim'");
    return false;
  }

  *cost = total_cost;
  return true;
}

void free_nodes(NO *nodes)
{
  // free the path's nodes
  for (NO *no = nodes; no;) {
    NO *temp = no;
    no = no->prox;
    free(temp);
  }
}

////////////////////////////////////////////////////////////////////////////////


struct _tests test1()
{
  static int aberto[] = {
    1, 1, 1, 1, 1, 0
  };
  static int ijpeso[] = {
    1, 2, 14,
    1, 6, 3,
    1, 4, 5,
    2, 3, 6,
    2, 6, 5,
    3, 4, 8,
    4, 5, 10,
    5, 6, 8
  };
  int inicio = 1, chave = 2, fim = 5;
  int custo_esperado = 15;
  
  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao = NULL,
  };
}

struct _tests test2()
{
  static int aberto[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1
  };
  static int ijpeso[] = {
    1, 2, 15,
    2, 5, 16,
    1, 7, 20,
    1, 2, 13,
    2, 8, 12,
    2, 9, 14,
    3, 4, 8,
    3, 7, 10,
    3, 10, 8,
    3, 13, 6,
    3, 14, 5,
    4, 5, 14,
    4, 9, 5,
    4, 10, 14,
    4, 15, 20,
    5, 6, 9,
    5, 9, 11,
    5, 12, 19,
    6, 11, 9,
    6, 15, 16,
    7, 12, 25,
    8, 10, 7,
    8, 15, 5,
    10, 11, 2,
    10, 13, 13,
    11, 12, 13,
    12, 13, 9,
    13, 14, 18,
    14, 15, 18
  };
  int inicio = 5, chave = 2, fim = 12;
  int custo_esperado = 19;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao = NULL,
  };
}

struct _tests test3()
{
  static int aberto[] = {
    0, 1, 1, 0, 1, 1, 1, 1, 1, 1
  };
  static int ijpeso[] = {
    1, 2, 10,
    1, 3, 7,
    1, 5, 8,
    1, 8, 14,
    2, 4, 3,
    2, 6, 6,
    2, 10, 18,
    3, 7, 7,
    4, 8, 3,
    4, 8, 15,
    4, 10, 2,
    5, 7, 7,
    5, 9, 5,
    6, 7, 10,
    6, 8, 4,
    7, 10, 7
  };
  int inicio = 9, chave = 7, fim = 2;
  int custo_esperado = 24;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao = NULL,
  };
}

struct _tests test4()
{
  static int aberto[] = {
    1, 1, 0, 1, 1, 1, 0, 1
  };
  static int ijpeso[] = {
    1, 2, 8,
    1, 3, 6,
    1, 5, 9,
    2, 3, 8,
    2, 6, 11,
    2, 7, 7,
    2, 8, 14,
    3, 6, 13,
    3, 8, 2,
    6, 7, 10,
    7, 8, 9,
    8, 4, 8
  };
  int inicio = 5, chave = 6, fim = 4;
  int custo_esperado = 39;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao = NULL,
  };
}

struct _tests test5()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 7, chave = 6, fim = 4;
  int custo_esperado = 100;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado (inicio = 7, chave = 6, fim = 4)\n"
      "teste padrao.",
  };
}

struct _tests test6()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 3, chave = 4, fim = 2;
  int custo_esperado = 90;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado (inicio = 3, chave = 4, fim = 2)\n"
      "testando um caso onde melhor caminho precisa de chave, e precisa "
      "repetir um vertice.",
  };
}

struct _tests test7()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 3, chave = 4, fim = 5;
  int custo_esperado = -1;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado (inicio = 3, chave = 4, fim = 5)\n"
      "testando um caso onde nao ha caminho para o fim, mesmo com chave.",
  };
}

struct _tests test8()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 5, chave = 4, fim = 3;
  int custo_esperado = -1;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado (inicio = 5, chave = 4, fim = 3)\n"
      "testando um caso onde nao ha caminho para o fim nem para a chave.",
  };
}

struct _tests test9()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 5, chave = 4, fim = 8;
  int custo_esperado = 10;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado (inicio = 5, chave = 4, fim = 8)\n"
      "testando um caso onde ha caminho para o fim, mas nao para a chave.",
  };
}

struct _tests test10()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 2, chave = 0, fim = 3;
  int custo_esperado = 110;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado (inicio = 2, chave = 0, fim = 3)\n"
      "testando um caso onde ha caminho para o fim, sem chave",
  };
}

struct _tests test11()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 2, chave = 2, fim = 3;
  int custo_esperado = 50;
  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado (inicio = 2, chave = 2, fim = 3)\n"
      "testando um caso onde ha caminho para o fim, com chave, e chave "
      "esta numa sala aberta (sala inicial).",
  };
}

struct _tests test12()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 2, chave = 3, fim = 3;
  int custo_esperado = 110;
  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado (inicio = 2, chave = 3, fim = 3)\n"
      "testando um caso onde ha caminho para o fim, com chave, e chave "
      "esta numa sala aberta (sala final).",
  };
}

struct _tests test13()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 2, chave = 8, fim = 4;
  int custo_esperado = 130;
  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado (inicio = 2, chave = 8, fim = 4)\n"
      "testando um caso onde ha caminho para o fim, com chave, mas chave "
      "esta numa sala inacessivel.",
  };
}

struct _tests test14()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 0, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 8, 20,
    7, 9, 80,
  };
  int inicio = 7, chave = 4, fim = 5;
  int custo_esperado = 230;
  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado modificado (inicio = 2, chave = 8, fim = 4)\n"
      "testando um caso onde nao ha caminho direto para o fim, apenas com "
      "chave.",
  };
}

struct _tests test15()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 0, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 20,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 8, 20,
    7, 9, 80,
  };
  int inicio = 5, chave = 4, fim = 7;
  int custo_esperado = -1;
  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado modificado (inicio = 2, chave = 8, fim = 4)\n"
      "testando um caso onde nao ha caminho para lugar nenhum.",
  };
}

struct _tests test16()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 10,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 7, chave = 6, fim = 4;
  int custo_esperado = 90;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado modificado (inicio = 7, chave = 6, fim = 4)\n"
      "caminho com chave eh mais rapido",
  };
}

struct _tests test17()
{
  static int aberto[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  static int ijpeso[] = {
    1, 2, 30,
    1, 3, 30,
    2, 6, 20,
    2, 7, 30,
    3, 4, 20,
    3, 7, 80,
    4, 9, 80,
    5, 8, 10,
    6, 7, 10,
    7, 9, 80,
  };
  int inicio = 7, chave = 6, fim = 4;
  int custo_esperado = 100;

  return (struct _tests) {
    .N = _countof(aberto), .A = _countof(ijpeso) / 3,
    .aberto = aberto, .ijpeso = ijpeso,
    .inicio = inicio, .chave = chave, .fim = fim,
    .custo_esperado = custo_esperado,
    .descricao =
      "Grafo do enunciado modificado (inicio = 7, chave = 6, fim = 4)\n"
      "caminho sem chave eh mais rapido",
  };
}


////////////////////////////////////////////////////////////////////////////////


int main()
{
  // all tests
  struct _tests tests[] = {
    test1(),  test2(),  test3(),  test4(),  test5(),
    test6(),  test7(),  test8(),  test9(),  test10(),
    test11(), test12(), test13(), test14(), test15(),
    test16(), test17(),
  };

  int const test_count = _countof(tests);

  for (int i = 0; i < test_count; ++i) {
    struct _tests const *test = &tests[i];
    
    int N = test->N;
    int A = test->A;

    int *aberto = test->aberto;
    int *ijpeso = test->ijpeso;
    
    int inicio = test->inicio;
    int chave = test->chave;
    int fim = test->fim;

    int custo_esperado = test->custo_esperado;
    char const *descricao = test->descricao;

    printf("=== TESTE %d ===\n", i + 1);
    if (descricao) {
      printf("descricao: %s\n", descricao);
    }

    printf("inicio = %d, chave = %d, fim = %d\n", inicio, chave, fim);

    // o EP sera testado com uma serie de chamadas como esta
    NO *teste = caminho(N, A, ijpeso, aberto, inicio, fim, chave);
    
    // imprime o caminho
    printf("\nResposta encontrada: ");
    print_path(teste);
    printf("\n");

    // verifica se o caminho esta correto
    int custo;
    if (check_path(teste, aberto, ijpeso, N, A, inicio, fim, chave, &custo)) {
      if (custo != custo_esperado) {
        printf("Custo %d diferente (esperado: %d)\n",
          custo, custo_esperado);
        if (custo < custo_esperado) {
          printf(
            "(Talvez seja preciso atualizar o custo esperado deste "
            "caso de teste?)\n");
        }
        free_nodes(teste);
        return 1; // fail
      }
      else if (custo == -1 && custo_esperado > -1) {
        printf(
          "Esperado caminho de custo %d, mas programa "
          "retornou caminho vazio\n", custo_esperado
        );
        free_nodes(teste);
        return 1; // fail
      }
      else if (teste) {
        printf("Custo: %d\n", custo);
      }
    }
    else {
      printf("Caminho invalido\n");
      free_nodes(teste);
      return 1; // fail
    }

    // libera a memoria do caminho
    free_nodes(teste);
    printf("===\n\n");
  }

  return 0; // all tests succeeded
}

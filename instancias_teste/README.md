# Instancias para testar os algoritmos

Os arquivos `.txt` podem ser carregados pelo programa `main`. Os arquivos `.dot`
correspondentes mostram as arestas com seus identificadores (`a1`, `a2`, etc.).
Como as buscas percorrem arestas de saída, as conexões não direcionadas estão
representadas nos arquivos de entrada por duas arestas orientadas, uma em cada
sentido. Os vetores de pesos seguem a ordem dos identificadores das arestas.

## `algoritmos_conexo`

- 6 vértices e 18 arestas orientadas (9 conexões bidirecionais).
- Para BEL ou BEP, use o vértice inicial `1`; todos os vértices serão alcançados.
- Para CC, o grafo deve formar um único componente.
- Para AGM, carregue `algoritmos_conexo_pesos.txt`; o custo da árvore mínima é
  `13.00`.
- Para CMC, carregue o mesmo vetor e consulte o caminho de `1` até `6`; a
  distância mínima é `13.00`.

## `algoritmos_desconexo`

- 8 vértices: um componente com `1` a `4`, outro com `5` e `6`, e os vértices
  isolados `7` e `8`.
- Para CC, são esperados 4 componentes.
- Para BEL ou BEP a partir de `1`, somente os vértices `1` a `4` serão alcançados.
- Para CMC de `1` até `6`, não existe caminho.
- O vetor `algoritmos_desconexo_pesos.txt` também permite carregar pesos para
  testar CMC neste caso.

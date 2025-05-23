[Read this page in English](README.md)

# FindTreasure: Aventura em labirinto 2D em OpenGL

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![OpenGL](https://img.shields.io/badge/OpenGL-4.6-lightgrey)
![GLUT](https://img.shields.io/badge/GLUT-3.0-orange)
![stb\_image](https://img.shields.io/badge/stb__image-compatible-blue)
![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)


<p align="center">
  <img src="img/docs/gameplay.gif" alt="" />
</p>

## Introdução

**FindTreasure** é uma aplicação interativa desenvolvida em C++ com OpenGL/GLUT, que desafia o jogador a explorar um labirinto em 2D, coletar tesouros e evitar obstáculos. O projeto enfatiza conceitos fundamentais de computação gráfica, design modular e manipulação de arquivos externos, consolidando habilidades essenciais para desenvolvimento de jogos.

Este projeto serve como exercício prático de:

* **Computação Gráfica 2D**: renderização de formas e texturas usando o pipeline OpenGL.
* **Design Modular**: separação clara de responsabilidades em diferentes módulos (lógica de jogo, renderização, carregamento de recursos).
* **Processamento de Arquivos**: leitura dinâmica de mapas a partir de arquivos TXT externos.

### Formato de Entrada

O mapa do labirinto é definido em um arquivo de texto com o seguinte formato:

```
<N> <M>                   # Número de linhas (N) e colunas (M)
<start_row> <start_col>   # Posição inicial do jogador (linha e coluna)
<linha1>                  # Sequência de N linhas, cada uma com M               elementos separados por espaço
<linha2>
...
<linhaN>
```

Cada elemento da matriz pode ser:

* `0`: espaço livre onde o jogador pode se mover.
* `1`: parede que bloqueia o caminho.
* `*`: tesouro que deve ser coletado.

#### Exemplo de arquivo de [entrada](!src/entries/map.txt):
```txt
5 6
1 1
1 1 1 1 1 1
1 0 0 1 * 1
1 * 0 0 0 1
1 1 1 * 0 1
1 1 1 1 1 1
```

Com esse formato, é possível criar e testar múltiplos cenários dinamicamente, basta alterar ou adicionar novos arquivos de mapa.

### Assets
Todos os recursos visuais projeto foram obtidos a partir de bibliotecas públicas ou criados e editados manualmente para garantir uma identidade própria ao FindTreasure. Texturas e ícones utilizados são licenciados para uso livre ou derivados de arquivos open‑source, tendo passado por ajustes de cores, dimensões e formatos para manter a consistência estética e funcionalidade no ambiente OpenGL.

### Objetivos e Funcionalidades

* **Renderização de Labirinto:** Leitura de mapas em formato TXT e conversão em matriz para desenhar paredes, caminhos e tesouros.
* **Movimentação e Colisão:** Controle do jogador via teclado (`W`, `A`, `S`, `D`), com detecção de colisões para impedir atravessar paredes.
* **Coleta de Tesouros:** Lógica para remoção de itens do mapa ao coletar, atualizando pontuação em tempo real.
* **Interface de Usuário (HUD):** Exibição de tempo decorrido e quantidade de tesouros coletados na tela.
* **Telas de Fim de Jogo:** Mensagens de vitória e derrota, apresentando tempo final e condições de reinício.

### Estrutura do Projeto

```
FindTreasure/
img/
├── assets/
│   ├── floor.png
│   ├── ...
├── docs/
│   ├── gameplay.gif
│   ├── ...             
src/
│   ├── main.cpp           
│   ├── game/
│   │   ├── game.cpp           
│   │   ├── game.hpp           
│   │   ├── textures.cpp           
│   │   ├── textures.hpp           
│   ├── util/
│   │   ├── adjust_directory.cpp           
│   │   ├── colors.hpp           
│   │   ├── maze.hpp           
└── 
```

### Como Executar

1. **Pré-requisitos:**

   * Compilador C++ compatível com C++11 ou superior (por exemplo, gcc-13/g++-13).
   * CMake e ferramentas de compilação:

     ```bash
     sudo apt update
     sudo apt install gcc-13 g++-13 cmake build-essential
     ```
   * Bibliotecas OpenGL e utilitários:

     ```bash
     sudo apt install libglew-dev freeglut3-dev mesa-utils
     ```
   * Biblioteca stb\_image:

     ```bash
     sudo apt install libstb-dev
     ```
2. **Compilação:**

   ```bash
   make
   ```
3. **Execução:**

   ```bash
   make run
   ```
   ou
   ```bash
   make && ./build/jogo
   ```

### Sugestões de Melhorias futuras

* **Sistema de Níveis:** Implementar múltiplos mapas com dificuldades crescentes.
* **Inimigos:** Adicionar inimigos que perseguem o jogador.
* **Animações e Efeitos:** Transições suaves, partículas ao coletar tesouro.


### Habilidades Demonstradas

* **Programação C++ Avançada:** Modularização, classes e métodos, tratamento de arquivos e strings.
* **OpenGL/GLUT:** Pipeline de renderização 2D, texturas, manipulação de buffers e coordenadas.
* **Debugging e Otimização:** Gerenciamento de timers, callbacks eficientes e lógica de colisão.

## Desenvolvedores

|   | Name             | Github                         | 
| -------------------------------------------------------------------------------------------- | ---------------- | ------------------------------ |
| <img src="https://avatars.githubusercontent.com/u/60756521"  width="100px" heigth="100px" /> | Filipe Abner     | https://github.com/FilipeAbner |
| <img src="https://avatars.githubusercontent.com/u/70250416?v=4"  width="100px" heigth="100px" /> | Lucas Freitas     | https://github.com/LucasFreitaslpf1 |
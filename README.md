# FindTreasure: 2D Maze Adventure in OpenGL

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

### Habilidades Demonstradas

* **Programação C++ Avançada:** Modularização, classes e métodos, tratamento de arquivos e strings.
* **OpenGL/GLUT:** Pipeline de renderização 2D, texturas, manipulação de buffers e coordenadas.
* **Debugging e Otimização:** Gerenciamento de timers, callbacks eficientes e lógica de colisão.

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

## Developers

|   | Name             | Github                         | 
| -------------------------------------------------------------------------------------------- | ---------------- | ------------------------------ |
| <img src="https://avatars.githubusercontent.com/u/60756521"  width="100px" heigth="100px" /> | Filipe Abner     | https://github.com/FilipeAbner |
| <img src="https://avatars.githubusercontent.com/u/70250416?v=4"  width="100px" heigth="100px" /> | Lucas Freitas     | https://github.com/LucasFreitaslpf1 |
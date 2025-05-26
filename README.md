# Lógica Fatal
> Você está pronto para encarnar um detetive com um misterioso caso de assassinato em mãos?

## Programação Imperativa e Funcional - 2025.1

### - Professor Diego de Freitas
### - CESAR School

## Membros

<ul>
    <li>Victor Ferreira Marques: @vic-fmr</li>
    <li>Lucas Rodrigues da Silva Junior: @lucxsz-web</li>
    <li>Camila Maria Teixeira Alcântara: @camilamta275</li>
    <li>Ana Sofia Da Silva Moura: @sun-cs-sol</li>
    <li>René Melo de Lucena: @renysoo</li>
</ul>

## 🎯 Objetivo do Jogo

Sua principal missão é identificar corretamente três elementos-chave para solucionar o caso:

* O **Suspeito** 👤
* A **Arma** do crime 🔪
* O **Local** exato do ocorrido 📍

A cada nova partida, a combinação correta é gerada aleatoriamente, oferecendo um novo desafio e alta rejogabilidade.

## 룰 Como Jogar

Para desvendar o mistério, você precisará explorar, coletar pistas e usar sua capacidade de dedução.

### 🗺️ Exploração: Mapa Interativo

* A faculdade é composta por um conjunto fixo de cômodos (ex: Auditório, Sala 401, Biblioteca, Praça, Copa, Sala de TI, Sala dos Professores e Garagem).
* Movimente-se entre os cômodos utilizando as teclas **W, A, S e D**.
* A movimentação é gerenciada por menus na interface com a `CLI-lib`, simulando um mapa simples.

### 🔍 Sistema de Pistas

* Em cada sala que você visitar, haverá uma pista lógica relacionada ao caso.
* As pistas são apresentadas como proposições condicionais ou negativas. Exemplos:
    * _"Se o crime ocorreu no Local 1, então a arma não foi a Arma 1.”_
    * _"A Suspeito 1 nunca entraria na Local 2.”_
    * _"Se o assassino foi o Suspeito 3, a arma não foi a Arma 2.”_
* Você deve usar sua dedução lógica a partir dessas proposições para chegar à solução.

### ☝️ Dedução e Acusação

* Quando se sentir confiante sobre a solução, pressione a tecla **"C"** para fazer uma acusação.
* Será solicitado que você escolha:
    1.  Um suspeito
    2.  Uma arma
    3.  Um lugar
* Sua resposta será comparada com a solução correta, e o resultado (acerto total ou erro parcial/total) será mostrado.

## 🏆 Ranking

* Seu desempenho será avaliado com base no tempo!
* **Quanto menos tempo** você levar para resolver o caso de Diego, **maior será sua posição no ranking** de detetives.
* Será solicitado que você digite seu nome para que, ao final do jogo, seu tempo seja contabilizado.
* Os jogadores que resolverem o problema mais rápido ficam nas maiores posições e são eleitos os melhores detetives!

Prepare sua mente analítica, colete as evidências e mostre suas habilidades para solucionar o assassinato de Diego e se consagrar como o melhor detetive!

## Como Compilar e Executar

Estas instruções irão guiá-lo sobre como compilar e executar o jogo em um ambiente Linux ou macOS.

### 1. Pré-requisitos

* **Compilador C (GCC):** É necessário ter o GCC (GNU Compiler Collection) instalado.
    * **Linux (Debian/Ubuntu):**
        ```bash
        sudo apt update && sudo apt install build-essential
        ```
    * **Linux (Fedora):**
        ```bash
        sudo dnf groupinstall "Development Tools"
        ```
    * **macOS:** Instale as Ferramentas de Linha de Comando do Xcode. Abra o Terminal e digite `gcc`. Se não estiver instalado, o sistema solicitará a instalação.

### 2. Compilando o Jogo

**Usando o `Makefile`**

O projeto inclui um `Makefile` que automatiza o processo de compilação.

1.  Abra o seu terminal e navegue até o diretório raiz do projeto:
    ```bash
    cd caminho/para/logica-fatal/
    ```
2.  Execute o comando `make`:
    ```bash
    make
    ```
    Isso compilará todos os arquivos fonte e gerará o arquivo executável chamado `logica-fatal` dentro de uma pasta `build/` (ou seja, `build/logica-fatal`).

### 3. Executando o Jogo

Após a compilação bem-sucedida:

* **Opção 1: Usando o alvo `run` do Makefile (Mais conveniente)**
  O `Makefile` possui um alvo `run` que compila (se necessário) e executa o jogo para você:
    ```bash
    make run
    ```

* **Opção 2: Executando o arquivo diretamente**
  Se você compilou com `make` ou manualmente (e o executável está em `build/logica-fatal`):
    ```bash
    ./build/logica-fatal
    ```

### 4. Limpando os Arquivos de Compilação

O  `Makefile` também inclui um alvo para limpar os arquivos gerados pela compilação (arquivos objeto e o executável):

```bash
make clean

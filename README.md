# Lógica Fatal

include/: Esta pasta normalmente contém os arquivos de cabeçalho (com extensão .h). Estes arquivos definem a interface dos módulos do programa, como declarações de funções, estruturas de dados, macros, etc. Outros arquivos de código fonte (.c) incluirão estes cabeçalhos para utilizar as funcionalidades neles declaradas.

chute.h
dados.h
dialogo.h
jogo.h
keyboard.h
mapa.h
pistas.h
player.h
ranking.h
salas.h
screen.h
temporizador.h
timer.h
ui.h

src/: Esta pasta contém os arquivos de código fonte (com extensão .c). Estes arquivos contêm a implementação real das funções e lógicas declaradas nos arquivos de cabeçalho.

chute.c
dialogo.c
jogo.c
keyboard.c
main.c: Este é o ponto de entrada principal do programa.
mapa.c
pistas.c
player.c
ranking.c
salas.c
screen.c
temporizador.c
timer.c
ui.c

.clang-format: Este arquivo é usado para definir um estilo de formatação de código consistente para o projeto quando se utiliza a ferramenta clang-format. Isso ajuda a manter o código legível e uniforme, especialmente quando vários desenvolvedores trabalham no mesmo projeto.


LICENSE: Este arquivo contém as informações sobre a licença sob a qual o software é distribuído (por exemplo, MIT, GPL, Apache). Ele define como outras pessoas podem usar, modificar e distribuir o código.


Makefile: Este arquivo é usado pela ferramenta make para compilar e construir o projeto. Ele contém regras que especificam como compilar os arquivos de código fonte, linká-los e gerar o executável final.

##Organização dos Arquivos

logica-fatal/
├── include/       <-- Arquivos de cabeçalho (.h)
│   ├── chute.h
│   ├── dados.h
│   ├── dialogo.h
│   ├── jogo.h
│   ├── keyboard.h
│   ├── mapa.h
│   ├── pistas.h
│   ├── player.h
│   ├── ranking.h
│   ├── salas.h
│   ├── screen.h
│   ├── temporizador.h
│   ├── timer.h
│   └── ui.h
├── src/           <-- Arquivos de código fonte (.c)
│   ├── chute.c
│   ├── dialogo.c
│   ├── jogo.c
│   ├── keyboard.c
│   ├── main.c
│   ├── mapa.c
│   ├── pistas.c
│   ├── player.c
│   ├── ranking.c
│   ├── salas.c
│   ├── screen.c
│   ├── temporizador.c
│   ├── timer.c
│   └── ui.c
├── .clang-format
├── LICENSE
└── Makefile       <-- Arquivo para automatizar a compilação
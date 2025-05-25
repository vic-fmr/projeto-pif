#include "salas.h"
#include "dialogo.h"
#include "player.h"
#include "mapa.h"

tamanhoSala tamanhoAuditorio = {1, 19, 1, 4};
tamanhoSala tamanhoBiblioteca = {21, 59, 1, 4};
tamanhoSala tamanhoSala401 = {61, MAP_WIDTH - 1, 1, 4};
tamanhoSala tamanhoCopa = {61, MAP_WIDTH - 1, 6, MAP_HEIGHT - 6};
tamanhoSala tamanhoGaragino = {61, MAP_WIDTH - 1, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
tamanhoSala tamanhoSalaProf = {21, 59, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
tamanhoSala tamanhoSalaTI = {1, 19, MAP_HEIGHT - 4, MAP_HEIGHT - 1};
tamanhoSala tamanhoPraca = {1, 19, 6, MAP_HEIGHT - 6};

void initNomesNasSalas() {
  desenharNomeNoMapa(tamanhoAuditorio.Xinicial + 4, 2, "AUDITORIO");
  desenharNomeNoMapa(tamanhoBiblioteca.Xinicial + 10, 2, "BIBLIOTECA");
  desenharNomeNoMapa(tamanhoSala401.Xinicial + 5, 2, "SALA 401");
  desenharNomeNoMapa(tamanhoCopa.Xinicial + 10, 10, "COPA");
  desenharNomeNoMapa(tamanhoGaragino.Xinicial + 8, MAP_HEIGHT - 3, "GARAGINO");
  desenharNomeNoMapa(tamanhoSalaProf.Xinicial + 10, MAP_HEIGHT - 3, "SALA DOS PROFESSORES");
  desenharNomeNoMapa(tamanhoSalaTI.Xinicial + 4, MAP_HEIGHT - 3, "SALA DE TI");
  desenharNomeNoMapa(tamanhoPraca.Xinicial + 4, 10, "PRACA");
}

bool verificarSala(tamanhoSala sala, const char *clue1, const char *clue2) {
  if (playerX >= sala.Xinicial && playerX <= sala.Xfinal && playerY >= sala.Yinicial && playerY <= sala.Yfinal) {
    showDialog(clue1, clue2);
    return true;
  }
  return false;
}

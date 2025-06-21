#include <stdio.h>
#include "evento.h"
#include "atividade.h"
#include "participante.h"


int main() {
    Evento *eventos = NULL;

    inserirEvento(&eventos, criarEvento("SINFO", "15/08/2025"));
    inserirEvento(&eventos, criarEvento("SEMANA DE SI", "22/09/2025"));
    listarEventos(eventos);

    removerEvento(&eventos, "SINFO");
    listarEventos(eventos);

    return 0;
}

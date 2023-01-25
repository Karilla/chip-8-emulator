#ifndef REVISON_PRG2_DEBUG_H
#define REVISON_PRG2_DEBUG_H
#include "state.h"

/**
 *
 * @param state Structure de la memoire a dumper
 * @param filename nom du fichier ou on dumpera la memoire
 */
void dump_memory(State* state, const char* filename);

#endif //REVISON_PRG2_DEBUG_H

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    // Verifica se o número de argumentos é válido
    if (argc != 2) {
        fprintf(2, "Usage: sleep <ticks>\n");
        exit(1);
    }

    // transforma em inteiro
    int ticks = atoi(argv[1]);

    //syscall sleep
    sleep(ticks);

    // Finaliza o programa
    exit(0);
}

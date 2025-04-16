#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pipe_parent_to_child[2], pipe_child_to_parent[2];
    char buffer;
   if (pipe(pipe_parent_to_child) < 0 || pipe(pipe_child_to_parent) < 0) {
        fprintf(2, "Erro, não foi ´possível criar pipeline\n");
        exit(1);
    }
    int pid = fork();
    if (pid < 0) {
        fprintf(2, "Erro ao criar processo filho\n");
        exit(1);
    }

    if (pid == 0) { // Processo filho
        close(pipe_parent_to_child[1]); // Fecha escrita do pipe pai → filho
        close(pipe_child_to_parent[0]); // Fecha leitura do pipe filho → pai

        
        if (read(pipe_parent_to_child[0], &buffer, 1) != 1) {
            fprintf(2, "Erro de leitura no filho\n");
            exit(1);
        }
        printf(1, "%d: received ping\n", getpid());

       
        if (write(pipe_child_to_parent[1], &buffer, 1) != 1) {
            fprintf(2, "Erro de escrita no filho\n");
            exit(1);
        }

        close(pipe_parent_to_child[0]);
        close(pipe_child_to_parent[1]);
        exit(0);

    } else { 
        close(pipe_parent_to_child[0]); // Fecha leitura do pipe pai → filho
        close(pipe_child_to_parent[1]); // Fecha escrita do pipe filho → pai

        
        if (write(pipe_parent_to_child[1], "a", 1) != 1) {
            fprintf(2, "Erro de escrita no pai\n");
            exit(1);
        }
        close(pipe_parent_to_child[1]); // Fecha após escrever

      
        if (read(pipe_child_to_parent[0], &buffer, 1) != 1) {
            fprintf(2, "Erro de leitura no pai\n");
            exit(1);
        }
        printf(1, "%d: received pong\n", getpid());

        close(pipe_child_to_parent[0]);
        wait(0); // Espera o filho encerrar
        exit(0);
    }
}

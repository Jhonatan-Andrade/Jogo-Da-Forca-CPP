#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

typedef struct {
    char *name;
    int point;
} User;

typedef struct {
    User users[100];
    int numberUser;
} Users;

User parseLine(char *line) {
    User user;
    char *part = strtok(line, ":");
    if (part) {
        user.name = strdup(part); 
        part = strtok(NULL, ":\n");
        user.point = part ? atoi(part) : 0;
    } else {
        user.name = strdup("");
        user.point = 0;
    }
    return user;
}

Users searchAllUser() {
    Users users;
    users.numberUser = 0;

    char line[100];

    FILE *file = fopen("meu_arquivo.txt", "r");

    if (!file) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    while (fgets(line, sizeof(line), file) && users.numberUser < 100) {
        User user = parseLine(line);
        users.users[users.numberUser++] = user;
    }
    fclose(file);
    return users;
}

User searchUniqueUser(const char *name) {
    
    Users users = searchAllUser();
    for (int i = 0; i < users.numberUser; i++) {
        if (strcmp(users.users[i].name, name) == 0) {
            return users.users[i];
        }
    }
    User userVoid;
    userVoid.name = strdup("");
    userVoid.point = 0;
    return userVoid;
}

void addPoints(const char *name, int pointsToAdd) {

    Users users = searchAllUser();
    int itFound = 0;
    for (int i = 0; i < users.numberUser; i++) {
        if (strcmp(users.users[i].name, name) == 0) {
            users.users[i].point += pointsToAdd;
            itFound = 1;
        }
    }
    if (!itFound) {printf("Usuario nao encontrado\n");return;}


    FILE *file = fopen("meu_arquivo.txt", "w");
    if (!file) {return;}

    for (int i = 0; i < users.numberUser; i++) {
        fprintf(file, "%s:%d\n", users.users[i].name, users.users[i].point);
    }
    fclose(file);

}

void createUser(const char *name) {
    Users users = searchAllUser();
    for (int i = 0; i < users.numberUser; i++) {
        if (strcmp(users.users[i].name, name) == 0) {
            printf("Usuario já existe\n");
            return;
        }
    }
    
    FILE *file = fopen("meu_arquivo.txt", "a");
    if (!file) {return;}

    fprintf(file, "%s:%d\n", name, 0);
    fclose(file);

}

int mainUser() {
    printf("\n\t1 : criar usuario");
    printf("\n\t2 : buscar apenas um usuario");
    printf("\n\t3 : buscar todos os usuarios");
    printf("\n\t4 : adicionar pontos ");
    printf("\n\t");
    int id;
    scanf("%d",&id);
    printf("\n\t");
    if (id == 1){
        char name[20];

        scanf("%19s",name);
        createUser(name);
    }else if(id == 2){
        char name[20];
        scanf("%19s",name);
        User user = searchUniqueUser(name);
        if (strcmp(user.name, "") == 0) {
            printf("Usuario nao encontrado\n");
        } else {
            printf("\n%s tem %d pontos\n", user.name, user.point);
        }
        
    }else if(id == 3){
        Users users = searchAllUser();
        for (int i = 0; i < users.numberUser; i++) {
            printf("\nnome: %s", users.users[i].name);
            printf("\npontos: %d\n", users.users[i].point);
        }
    }else if(id == 4){
        printf("\nnome:  ");
        char name[20];
        scanf("%19s",name);

        printf("pontos:  ");
        int points;
        scanf("%d",&points);
        addPoints(name,points);
    }

    return 0;
}
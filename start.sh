#!/bin/bash

# Função para perguntar ao usuário
perguntar() {
    while true; do
        read -p "$1 [s/n]: " resposta
        case $resposta in
            [Ss]* ) return 0;;
            [Nn]* ) return 1;;
            * ) echo "Por favor, responda sim (s) ou não (n).";;
        esac
    done
}

# Perguntar se o usuário quer buildar o projeto
if perguntar "Você quer buildar o projeto?"; then
    mkdir -p build
    cd build
    cmake ..
    make
else
    echo "Build cancelado."
    exit 0
fi

# Perguntar se o usuário quer rodar os testes ou a aplicação
if perguntar "Você quer rodar os testes?"; then
    ctest
else
    read -p "Digite o caminho personalizado para rodar a aplicação: " caminho
    ./runTests "$caminho"
fi
#!/bin/bash
# deleta arquivos inúteis

read -p "deletar arquivos inúteis (apos ter instalado os patches com sucesso) [y/N]? " -n 1 -r
echo    
if [[ ! $REPLY =~ ^[Nn]$ ]]
then
    echo deletados arquivos inuteis
    rm -rf *.o
    rm -rf *.orig
    rm -rf config.h
    rm -rf dwm
fi




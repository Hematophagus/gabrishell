# **GABRISHELL**

por *Gabriel Xavier Bras*

Este é um interpretador de comandos bastante simples que faz chamadas ao sistema operacional realizar as seguintes comandos:

### PWD
Imprime o diretório de trabalho atual

### CD [caminho]
Muda o diretório de trabalho para o especificado em [caminho]

### LS
Imprime o conteúdo do diretório atual

### MORE [arquivo]
Imprime o conteúdo do arquivo especificado

### GREP [item]
Imprime todas as linhas em que a string [item] aparece

## PIPE
A rigor, um pipe entre comandos é uma funcionalidade que permite que a saída de um comando sirva de pamâmetro para outro comando. Para realizar um pipe, use o operador "|" entre um comando e outro.
Por  exemplo:

```more README.md | grep PWD``` 
fará a busca por "PWD" apenas em README.md

```ls | more main.cpp``` 
imprimirá somente o nome do arquivo main.cpp

## INSTALAÇÃO
Este Shell usa a biblioteca *curses*. Se seu sistema não possui essa biblioteca, é recomendado q a instale:


```sudo apt-get install libncurses5-dev libncursesw5-dev```

Basta clonar este repositório:

**```git clone https://github.com/Hematophagus/gabrishell.git```**

e compilar os arquivos .cpp via linha de comando:

**```g++ *.cpp -o [nomedoexecutavel] -lncurses```**

ou

```g++ cmds.cpp main.cpp support.cpp -o [nomedoexecutavel] -lncurses```

## BUGS CONHECIDOS
[x] Pipe interrompe o looping do Shell;
[x] Às vezes a saída dos comandos ocorre apenas após o encerramento do Shell
[x] Argumentos com aspas não são aceitos nos comandos ```more``` e ```grep```
[x] Formatação não funciona nos comandos ```ls```, ```more``` e ```grep```, e nem nas mensagens de erro; 








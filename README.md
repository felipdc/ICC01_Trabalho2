# Trabalho ICC-1 - Sistema de gerenciamento de alunos
Programa que permite consultar, inserir e remover informações de um arquivo csv de alunos na disciplina de ICC.

## Primeiras intruções
As instruçes a seguir foram feitas para gerar uma cópia funcional do programa em sua máquina local para propósitos de teste. 

### Pré-requisitos
É necessário ter um compilador de C instalado e com a lib math.h instalada na máquina

### Compilação

```
gcc -o main main.c csv_parser.c data_manager.c interface.c utils.c -lm 
```
### Execução

Windows:

```
main
```

Linux:

```
./main
```

Para testes, execute com o arquivo students.csv já na pasta do projeto.

## Ferramentas usadas

* Sublime-Text 3 - IDE Utilizada
* Math Lib - Biblioteca utilizada

## Autor

* **Felipe Tiago De Carli** - 10525686

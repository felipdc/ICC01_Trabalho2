#include <stdio.h>
#include <stdlib.h>
#include "data_manager.h"
#include "csv_parser.h"
#include "interface.h"

	
void display_splash_screen () {

	printf ("\n\t##### Sistema de Consulta de alunos da discplina ICC-01 ####\n"
			"\t# \n\t#  Comandos:"
			"\n\t#\n\t#  0 - Sair\n"
			"\t#  1 - Mostrar alunos cadastrados\n"
			"\t#  2 - Mostrar alunos e notas das provas\n"
			"\t#  3 - Mostrar alunos e notas dos trabalhos + grupos\n"
			"\t#  3 - Consultar nota das provas de um aluno específico\n"
			"\t#  4 - Consultar nota dos trabalhos e grupos de um aluno específico\n"
			"\t#  5 - Incluir/Remover nota de trabalho\n"
			"\t#  6 - Incluir/Remover nota de prova\n"
			"\t#  7 - Incluir/Remover novo aluno\n");
}
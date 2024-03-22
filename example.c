/*
	LEONARDO MATTHEW KNIGHT
	CIENCIA DA COMPUTACAO
*/

#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"

const TickType_t ONE_SEC_DELAY = 1000 / portTICK_PERIOD_MS; // 1 segundo baseado na taxa de ticks da kernel

void taskBatimentoCardiaco(void* parameters);
void taskFebre(void* parameters);
void taskSaturacaoOxigenio(void* parameters);

struct VitalData {
	uint32_t batimento_cardicado;
	uint32_t febre;
	uint32_t saturacao_oxigenio;
};


int generateRandomInt(int min, int max) {
	// gera um numero inteiro aleatorio entre min e max
	return (rand() % (max - min + 1)) + min;
}

double generateRandomDouble(double min, double max) {
	// gera um numero decimal aleatorio entre min e max
	double div = RAND_MAX / (max - min);
	return min + (rand() / div);
}

int main_(void)
{
	struct VitalData vd = { 0, 0, 0 }; // inicia a struct dos dados vitais com seus valores padroes sendo 0
	srand(21); // inicia o gerador de numero aleatorio com uma seed qualquer
	// cria as tasks passando como parametro a funcao, nome, tamanho da stack, valor para passar o ponteiro, a prioridade, e o handle, que n precisamos por agr
	xTaskCreate(taskBatimentoCardiaco, "Task batimento cardiaco", 10, vd.batimento_cardicado, 1, NULL);
	xTaskCreate(taskFebre, "Task Febre", 1000, vd.febre, 1, NULL);
	xTaskCreate(taskSaturacaoOxigenio, "Task saturacao oxigenio", 10, vd.saturacao_oxigenio, 1, NULL);
	// Inicia o escalonador de tarefas
	vTaskStartScheduler();

	for (;; );
	return 0;
}

void taskBatimentoCardiaco(void* parameters) {
	long batimento = (long*) parameters; // recebe o ponteiro do valor do parametro
	for (;;) {
		batimento = generateRandomInt(20, 140); // pega o proximo numero entre 20 e 140
		if (batimento < 50) {
			vPrintStringAndNumber("batimento (BAIXO): ", batimento);
		}
		else if (batimento > 90) {
			vPrintStringAndNumber("batimento (ALTO): ", batimento);
		} else
			vPrintStringAndNumber("batimento (NORMAL): ", batimento);
		vTaskDelay(ONE_SEC_DELAY); // faz o tick de 1 segundo (= ONE_SEC_DELAY)
	}
	vTaskDelete(NULL);
}

// as outras tasks sao iguais, so muda o valor gerado e os if

void taskFebre(void* parameters) {
	long temperatura = (long*)parameters;
	for (;;) {
		temperatura = generateRandomDouble(34.0, 41.0)*10; // multiplicamos por 10 para nao perdermos o numero decimal, ja que o print so funciona pra long
		// quando printar vai aparecer como 340, porem o 0 vai ser o valor deciamal (340 == 34.0)
		if (temperatura > 37.5) {
			vPrintStringAndNumber("temperatura (FEBRE): ", temperatura);
		}
		else if (temperatura < 35.0) {
			vPrintStringAndNumber("temperatura (HIPOTERMIA): ", temperatura);
		}
		else
			vPrintStringAndNumber("temperatura (NORMAL): ", temperatura);
		vTaskDelay(ONE_SEC_DELAY);
	}
	vTaskDelete(NULL);
}
void taskSaturacaoOxigenio(void* parameters) {
	long saturacao = (long*)parameters;
	for (;;) {
		saturacao = generateRandomInt(80, 100);
		if (saturacao < 90) {
			vPrintStringAndNumber("Saturacao do oxigenio (SATURACAO BAIXA): ", saturacao);
		}
		else
			vPrintStringAndNumber("Saturacao do oxigenio (NORMAL): ", saturacao);
		vTaskDelay(ONE_SEC_DELAY);
	}
	vTaskDelete(NULL);
}

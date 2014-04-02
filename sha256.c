#include "sha256.h"

uint32_t* sha256(uint8_t* data, uint64_t length)
{
	int padd_quant = (448 - (length + 8) % 512) / 8;
	uint64_t n_length = length/8 + padd_quant;

	uint8_t message[n_length]; // Creamos el nuevo array
	memcpy(message, data, length/8); // Copiamos la información
	message[length/8] = append; // Añadimos el bit 1 y los 0s

	for (int i = 1; i < pass_quant; i++) message[length/8+i] = 0; // Añadimos los 0s necesarios

	// ------ Ya tenemos el mensaje procesado para hashearlo ------ //

	for (int i = 0; i < n_length / 512; i++)
	{
		uint32_t schedule[64];
		memcpy(schedule, &message[i*64], 16);

		for (int h = 16; h < 64; h++)
		{
			//
		}

	}
}
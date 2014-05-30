#include "sha256.h"

void sha256(char* data, uint8_t length, uint32_t* digest)
{
	int padd_quant = 64 - ((length+1) % 64);
	uint64_t n_length = length + padd_quant + 1;

	uint8_t message[n_length]; // Creamos el nuevo array
	memcpy(message, data, length); // Copiamos la información
	message[length] = append; // Añadimos el bit 1 y los 0s

	int i;

	for (i = 1; i <= padd_quant; i++) message[length+i] = 0; // Añadimos los 0s necesarios

	// ------ Ya tenemos el mensaje procesado para hashearlo ------ //

	uint32_t h0 = sha256_init_h[0], h1 = sha256_init_h[1],
				h2 = sha256_init_h[2], h3 = sha256_init_h[3],
				h4 = sha256_init_h[4], h5 = sha256_init_h[5],
				h6 = sha256_init_h[6], h7 = sha256_init_h[7];

	// ------ Dividimos el mensaje en bloques de 512 bits (64 bytes) ------ //
	for (i = 0; i < n_length / 64; i++)
	{
		uint32_t w[64];
		memcpy(w, &message[i*64], 64); // Copiamos el bloque

		// ------ Extendemos el bloque con el algoritmo ------ //
		for (int n = 16; n < 64; n++)
		{
			uint32_t s0, s1;

			s0 = rir(w[n-15], 7) ^ rir(w[n-15], 18) ^ (w[n-15] >> 3);
			s1 = rir(w[n-2], 17) ^ rir(w[n-2], 19) ^ (w[n-2] >> 10);
			w[i] = w[n-16] + s0 + w[n-7] + s1;
		}

		uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;

		// ------ Comprimimos el hash ------ //
		for (int f = 0; f < 64; f++)
		{
			uint32_t S1 = rir(e, 6) ^ rir(e, 11) ^ rir(e, 25);
			uint32_t ch = (e & f) ^ ((~ e) & g);
			uint32_t temp1 = h + S1 + ch + k[f] + w[f];
			uint32_t S0 = rir(a, 2) ^ rir(a, 13) ^ rir(a, 22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t temp2 = S0 + maj;

			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}

		// ------ Añadimos lo comprimido al hash ------ //
		h0 = h0 + a;
		h1 = h1 + b;
		h2 = h2 + c;
		h3 = h3 + d;
		h4 = h4 + e;
		h5 = h5 + f;
		h6 = h6 + g;
		h7 = h7 + h;
	}

	digest[0] = h0;
	digest[1] = h1;
	digest[2] = h2;
	digest[3] = h3;
	digest[4] = h4;
	digest[5] = h5;
	digest[6] = h6;
	digest[7] = h7;
}

uint32_t rir(uint32_t a, int n)
{
	 return (a >> n) | (a << (32-n));
}

int main(void)
{
	// -- TEST 1 -- //
	printf("\nCadena:\t12345\n");
	printf("Hash:\t");

	char* string = "12345";
	uint32_t hash[8];
	sha256(string, 5, hash);

	printf("%x", hash[0]);
	printf("%x", hash[1]);
	printf("%x", hash[2]);
	printf("%x", hash[3]);
	printf("%x", hash[4]);
	printf("%x", hash[5]);
	printf("%x", hash[6]);
	printf("%x\n\n", hash[7]);


	// -- TEST 2 -- //
	printf("\nCadena:\tabcde\n");
	printf("Hash:\t");

	string = "abcde";
	sha256(string, 5, hash);

	printf("%x", hash[0]);
	printf("%x", hash[1]);
	printf("%x", hash[2]);
	printf("%x", hash[3]);
	printf("%x", hash[4]);
	printf("%x", hash[5]);
	printf("%x", hash[6]);
	printf("%x\n\n", hash[7]);

	return 0;
}
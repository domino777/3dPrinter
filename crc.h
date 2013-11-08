/*
 * crc.h
 *
 * Created: 25/09/2013 23:30:41
 *  Author: winShit
 */ 


#ifndef CRC_H_
#define CRC_H_

#define PG 0x89;

int crc(int oldcrc, unsigned int toadd);

int getCRC (unsigned int *data) 
{
	
	int resto=0;	// CRC
	int c;		// Carattere letto
	int i = 0;	// Contatore dei caratteri
	
	do
	{
	    resto = crc(resto, data[0]);		// Agginge il carattere letto al CRC dei precedenti
	    i++;							// Conta i caratteri letti
	}
	while(i < 5);
	
	resto = crc(resto,0);		// Agginge al CRC i primi otto zeri
	resto = crc(resto,0);		// Agginge al CRC i secondi otto zeri in fondo

	return resto;	
}
	
	/* Aggiunge i bit del codice oldcrc al dividendo, per
	* calcolare il nuovo CRC
	*/		
int crc(int oldcrc, unsigned int toadd)
{
	int i;	// Indice del bit
	
	// I bit del carattere vanno trattati dal piu' significativo al meno
	for(i = 0; i < 8; i++)	// Per ogni bit del byte
	{
		oldcrc= (oldcrc<<1) | (toadd>>7);	// Aggiunge il bit piu' significativo
					// del codice in fondo al CRC,
					// spostando a sinistra i bit del CRC
		toadd <<= 1;			// Toglie il bit gestito dal codice
		if((oldcrc & 0x10000) != 0)		// Se il divisore ci sta' (alla sua maniera)
		{
			oldcrc = oldcrc ^ PG;			// Allora lo toglie (sottrazione senza riporti,
					// quindi XOR
		}
	}
  return oldcrc;			// Restituisce il CRC ricalcolato
}



#endif /* CRC_H_ */
/*
 * Programme fait par : Jeff Truong
 * Date : 4 Mars 2025
 * Description : un programme compte le temps un bouton est appuyer.
 * 
*/

#include "mcc_generated_files/mcc.h"

#define ADDRESSE_I2C_ECRAN  40			//0x28
#define ADDRESSE_I2C_EEPROM 80        //0x50 0101 0000

/*
    D�but de l'application principale
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    uint8_t message[20];
    uint8_t addr[3];    //l'adresse m�moire interne de l'EEPROM
    uint8_t addr2[3];   //les donn�es lues depuis l'EEPROM

    message[0]='0';
    message[1]='1';
    message[2]='2';
    
    // D�finition de l'adresse m�moire interne o� stocker les donn�es dans l'EEPROM
    addr [0] =  0x00;
    addr [1] =  0x02;
    addr [2] =  0x3F;

    
    while (1)
    {

        
               
        //Code qui lit 3 octets de la m�moire EEPROM
        // �Criture de deux octets de donn�es � la EEPROM
        while(I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);   //passage de l?adresse I2C
        I2C_SetBuffer(addr, 3);				// Chargement de l'adresse m�moire interne	
        I2C_MasterOperation(0);				//op�ration d?�criture pour l?adresse interne
        while (I2C_Close() == I2C_BUSY);
        __delay_ms(10);
        
        // Lecture de 3 octets de la EEPROM
        while(I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);	//passage de l?adresse I2C
        I2C_SetBuffer(addr, 2);		// Chargement de l'adresse m�moire interne
        I2C_MasterOperation(0);		//op�ration de lecture
        I2C_SetBuffer(addr2, 1);    //passage du tampon et du nombre de //lectures � faire
        I2C_MasterOperation(1);     // Ex�cution de la lecture
        while (I2C_Close() == I2C_BUSY);
        __delay_ms(990);            // Pause pour �viter un envoi trop rapide des requ�tes I2C
        
        // Code pour afficher les donn�es lues sur l'�cran LCD
        while(I2C_Open(ADDRESSE_I2C_ECRAN) == I2C_BUSY); // Attente de la disponibilit� du bus I2C
        I2C_SetBuffer(addr2, 1);                         // Chargement des donn�es � afficher
        I2C_MasterOperation(0);                          // op�ration d?�critur
        while (I2C_Close() == I2C_BUSY);                 // Attente de la fin de l'op�ration
        __delay_ms(1000);
    }
    
}

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
    Début de l'application principale
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    uint8_t message[20];
    uint8_t addr[3];    //l'adresse mémoire interne de l'EEPROM
    uint8_t addr2[3];   //les données lues depuis l'EEPROM

    message[0]='0';
    message[1]='1';
    message[2]='2';
    
    // Définition de l'adresse mémoire interne où stocker les données dans l'EEPROM
    addr [0] =  0x00;
    addr [1] =  0x02;
    addr [2] =  0x3F;

    
    while (1)
    {

        
               
        //Code qui lit 3 octets de la mémoire EEPROM
        // ÉCriture de deux octets de données à la EEPROM
        while(I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);   //passage de l?adresse I2C
        I2C_SetBuffer(addr, 3);				// Chargement de l'adresse mémoire interne	
        I2C_MasterOperation(0);				//opération d?écriture pour l?adresse interne
        while (I2C_Close() == I2C_BUSY);
        __delay_ms(10);
        
        // Lecture de 3 octets de la EEPROM
        while(I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);	//passage de l?adresse I2C
        I2C_SetBuffer(addr, 2);		// Chargement de l'adresse mémoire interne
        I2C_MasterOperation(0);		//opération de lecture
        I2C_SetBuffer(addr2, 1);    //passage du tampon et du nombre de //lectures à faire
        I2C_MasterOperation(1);     // Exécution de la lecture
        while (I2C_Close() == I2C_BUSY);
        __delay_ms(990);            // Pause pour éviter un envoi trop rapide des requêtes I2C
        
        // Code pour afficher les données lues sur l'écran LCD
        while(I2C_Open(ADDRESSE_I2C_ECRAN) == I2C_BUSY); // Attente de la disponibilité du bus I2C
        I2C_SetBuffer(addr2, 1);                         // Chargement des données à afficher
        I2C_MasterOperation(0);                          // opération d?écritur
        while (I2C_Close() == I2C_BUSY);                 // Attente de la fin de l'opération
        __delay_ms(1000);
    }
    
}

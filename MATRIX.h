#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif



const int hauteur_matrice = 8;
/////////// Definition de l'alphabet //////////


const int A[hauteur_matrice] = {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66} ;
const int B[hauteur_matrice] = {0x3C, 0x32, 0x32, 0x3C, 0x3C, 0x32, 0x32, 0x3C} ;
const int C[hauteur_matrice] = {0x1E, 0x3E, 0x70, 0x60, 0x60, 0x70, 0x3E, 0x1E} ;
const int D[hauteur_matrice] = {0x7C, 0x7E, 0x67, 0x63, 0x63, 0x67, 0x7E, 0x7C} ;
const int E[hauteur_matrice] = {0x7E, 0x7E, 0x60, 0x78, 0x78, 0x60, 0x7E, 0x7E} ;
const int F[hauteur_matrice] = {0x7E, 0x7E, 0x60, 0x78, 0x78, 0x60, 0x60, 0x60} ;
const int G[hauteur_matrice] = {0x3C, 0x7E, 0x66, 0x60, 0x6C, 0x66, 0x66, 0x3C} ;
const int H[hauteur_matrice] = {0x66, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66, 0x66} ;
const int I[hauteur_matrice] = {0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x7E} ;
const int J[hauteur_matrice] = {0x1F, 0x1F, 0x06, 0x06, 0x46, 0x66, 0x3C, 0x18} ;
const int K[hauteur_matrice] = {0x66, 0x66, 0x6C, 0x78, 0x78, 0x6C, 0x66, 0x66} ;
const int L[hauteur_matrice] = {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x7E} ;
const int M[hauteur_matrice] = {0xE7, 0xFF, 0xFF, 0xDB, 0xC3, 0xC3, 0xC3, 0xC3} ;
const int N[hauteur_matrice] = {0xC3, 0xE3, 0xF3, 0xFB, 0xDF, 0xCF, 0xC7, 0xC3} ;
const int O[hauteur_matrice] = {0x3C, 0x7E, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x3C} ;
const int R[hauteur_matrice] = {0x3C, 0x7E, 0x66, 0x66, 0x7C, 0x7C, 0x6E, 0x66} ;
const int T[hauteur_matrice] = {0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18} ;
const int U[hauteur_matrice] = {0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7F, 0x3E} ;
const int Y[hauteur_matrice] = {0xC3, 0xE7, 0x7E, 0x3C, 0x18, 0x18, 0x18, 0x18} ;

const int esp[hauteur_matrice]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;
const int coeur[hauteur_matrice]={0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x18} ;
const int apostrophe[hauteur_matrice] = {0x0C, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00} ;




class LedControl {
 private :
    /* The array for shifting the data to the devices */
    byte spidata[16];
    /* Send out a single command to the device */
    void spiTransfer(int addr, byte opcode, byte data);

	/* We keep track of the led-status for all 8 devices in this array */
    byte status[64];
     /* Data is shifted out of this pin*/
    int LEDCONTROL_SPI_MOSI;
    /* The clock is signaled on this pin */
    int LEDCONTROL_SPI_CLK;
    /* This one is driven LOW for chip selectzion */
    int LEDCONTROL_SPI_CS;
    /* The maximum number of devices we use */
    int maxDevices;
	
   
 public:
    /* 
     * Create a new controler 
     * Params :
     * dataPin		pin on the Arduino where data gets shifted out
     * clockPin		pin for the clock
     * csPin		pin for selecting the device 
     * numDevices	maximum number of devices that can be controled
     */
    LedControl(int dataPin, int clkPin, int csPin, int numDevices=1);



    /* 
     * Set the shutdown (power saving) mode for the device
     * Params :
     * addr	The address of the display to control
     * status	If true the device goes into power-down mode. Set to false
     *		for normal operation.
     */
    void shutdown(int addr, bool status);

    /* 
     * Set the number of digits (or rows) to be displayed.
     * See datasheet for sideeffects of the scanlimit on the brightness
     * of the display.
     * Params :
     * addr	address of the display to control
     * limit	number of digits to be displayed (1..8)
     */
    void setScanLimit(int addr, int limit);

    /* 
     * Set the brightness of the display.
     * Params:
     * addr		the address of the display to control
     * intensity	the brightness of the display. (0..15)
     */
    void setIntensity(int addr, int intensity);

    /* 
     * Switch all Leds on the display off. 
     * Params:
     * addr	address of the display to control
     */
    void clearDisplay(int addr);
	
    void clearAll();

    /* 
     * Set the status of a single Led.
     * Params :
     * addr	address of the display 
     * row	the row of the Led (0..7)
     * col	the column of the Led (0..7)
     * state	If true the led is switched on, 
     *		if false it is switched off
     */
    void setLed(int addr, int row, int col, boolean state);

    /* 
     * Set all 8 Led's in a row to a new state
     * Params:
     * addr	address of the display
     * row	row which is to be set (0..7)
     * value	each bit set to 1 will light up the
     *		corresponding Led.
     */
    void setRow(int addr, int row, byte value);

};



#include <msp430.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    char uart_buf[40];
    int i, uart_buf_n;
    uint16_t temperature;

    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    // UART UCA3 9600
    // P2.0 UCA1TXD, P2.1 UCA1RXD (RX not used)
    UCA3CTLW0 |= UCSWRST;
    UCA3CTLW0 |= UCSSEL__SMCLK;     // clock source SMCLK
    UCA3BRW = 6;                    // baud rate 9600
    UCA3MCTLW |= 0x11 << 8 | UCBRF_8 | UCOS16;
    P2SEL0 &= ~BIT0;                // port function
    P2SEL1 |= BIT0;
    UCA3CTLW0 &= ~UCSWRST;

    // P1.6 UCB0SDA, P1.7 UCB0SCL
    UCB0CTLW0 |= UCSWRST;
    UCB0CTLW0 |= UCSSEL_3;          // clock source SMCLK
    UCB0BRW = 16;                   // I2C clock, SMCLK/16 = 62.5kHz
    UCB0CTLW0 |= UCMODE_3;          // port mode I2C
    UCB0CTLW0 |= UCMST;             // I2C mode master
    UCB0I2CSA = 0x48;               // LM75A I2C address
    UCB0CTLW1 |= UCASTP_2;          // I2C auto stop when read byte count reaches UCB0TBCNT
    UCB0TBCNT = 1;                  // I2C read count
    P1SEL1 |= BIT6;                 // port function
    P1SEL0 &= ~BIT6;
    P1SEL1 |= BIT7;
    P1SEL0 &= ~BIT7;
    UCB0CTLW0 &= ~UCSWRST;

    for (;;) {
        /*
         * Read temperature sensor
         * LM75A temperature sensor on I2C bus
         */

        __delay_cycles(1000000);
        UCB0CTLW0 |= UCTXSTT; // Start bit
        __delay_cycles(5000);

        // read I2C RX buffer
        temperature = UCB0RXBUF;

#if 1
        uart_buf_n = sprintf(uart_buf, "lm75 %d Celsius\r\n", temperature);
        for (i = 0; i < uart_buf_n; i++) {
            UCA3TXBUF = uart_buf[i];
            __delay_cycles(200000);
        }
#endif
        /*
         * Bluetooth beacon
         * Transmit temperature over Bluetooth
         * Microchip RN4871 Bluetooth module over UART
         *
         * BTHome Bluetooth Data Protocol
         * https://bthome.io/
         *
         * It should be read reply for each RN4871 command, but as we don't
         * lets wait a little bit and hope all is ok.
         */

        temperature = 100 * temperature;

        // Open command mode
        i = 0;
        uart_buf[i++] = '$';
        uart_buf[i++] = '$';
        uart_buf[i++] = '$';
        uart_buf[i++] = '\r';
        uart_buf[i++] = '\n';

        uart_buf_n = i;

        for (i = 0; i < uart_buf_n; i++) {
            UCA3TXBUF = uart_buf[i];
            __delay_cycles(200000);
        }
        __delay_cycles(1000000);

        // Clear advertisement
        i = 0;
        uart_buf[i++] = 'I';
        uart_buf[i++] = 'A';
        uart_buf[i++] = ',';
        uart_buf[i++] = 'Z';
        uart_buf[i++] = '\r';
        uart_buf[i++] = '\n';

        uart_buf_n = i;

        for (i = 0; i < uart_buf_n; i++) {
            UCA3TXBUF = uart_buf[i];
            __delay_cycles(200000);
        }
        __delay_cycles(1000000);


        // Set advertisement, BTHome API payload
        i = 0;
        uart_buf[i++] = 'I';
        uart_buf[i++] = 'A';
        uart_buf[i++] = ',';
        uart_buf[i++] = '1';
        uart_buf[i++] = '6';
        uart_buf[i++] = ',';
        uart_buf[i++] = '1';
        uart_buf[i++] = 'C';
        uart_buf[i++] = '1';
        uart_buf[i++] = '8';
        uart_buf[i++] = '2';
        uart_buf[i++] = '3';
        uart_buf[i++] = '0';
        uart_buf[i++] = '2';
        sprintf(&uart_buf[i++], "%x", ((temperature >>  4) & 0xf));
        sprintf(&uart_buf[i++], "%x", ((temperature >>  0) & 0xf));
        sprintf(&uart_buf[i++], "%x", ((temperature >> 12) & 0xf));
        sprintf(&uart_buf[i++], "%x", ((temperature >>  8) & 0xf));
        uart_buf[i++] = '\r';
        uart_buf[i++] = '\n';

        uart_buf_n = i;

        for (i = 0; i < uart_buf_n; i++) {
            UCA3TXBUF = uart_buf[i];
            __delay_cycles(200000);
        }
        __delay_cycles(1000000);

        // Close command mode
        i = 0;
        uart_buf[i++] = '-';
        uart_buf[i++] = '-';
        uart_buf[i++] = '-';
        uart_buf[i++] = '\r';
        uart_buf[i++] = '\n';

        uart_buf_n = i;

        for (i = 0; i < uart_buf_n; i++) {
            UCA3TXBUF = uart_buf[i];
            __delay_cycles(200000);
        }
        __delay_cycles(1000000);
    }
}



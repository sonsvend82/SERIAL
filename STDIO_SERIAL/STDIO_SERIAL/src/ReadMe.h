/**
 * \defgroup group_common_utils_stdio_stdio_serial_stdio_serial_example Serial Standard I/O (stdio) Example
 *
 * \section intro Introduction
 * This example demonstrates how to use the Serial Stdio.
 *
 * \section files Main Files
 * - stdio_serial_example.c: the example application.
 * - conf_board.h: board configuration
 * - conf_clock.h: clock configuration
 * - conf_usart_serial.h: configuration of the stdio serial used by this example
 * - stdio_serial.h: Part Specific Stdio Serial Implementation
 * - read.c : System implementation function used by standard library
 * - write.c : System implementation function used by standard library
 *
 * \section stdio_serialapiinfo utils/stdio/stdio_serial API
 * The stdio_serial API can be found \ref stdio_serial.h "here".
 *
 * \section deviceinfo Device Info
 * All AVR devices can be used. This example has been tested
 * with the following setup:
 *   - ATXMEGA128A1 XMEGA-A1 Xplained (USB connection to host virtual com port).
 *   - AT32UC3L064 UC3-L0 Xplained (USB connection to host virtual com port).
 *
 * \section exampledescription Description of the example
 *   - Send message on serial communication port.
 *   - Performs echo of any received character
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/avr">Atmel AVR</A>.\n
 */
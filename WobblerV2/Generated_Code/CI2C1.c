/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : CI2C1.c
**     Project     : WobblerV2
**     Processor   : MKL02Z32VFM4
**     Component   : InternalI2C
**     Version     : Component 01.287, Driver 01.01, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-04-11, 03:18, # CodeGen: 39
**     Abstract    :
**          This component encapsulates the internal I2C communication 
**          interface. The implementation of the interface is based 
**          on the Philips I2C-bus specification version 2.0. 
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible 
**              (see "Automatic stop condition" property)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
**     Settings    :
**          Component name                                 : CI2C1
**          I2C_LDD                                        : I2C_LDD
**          I2C channel                                    : I2C0
**          Mode selection                                 : MASTER
**          Interrupt service/event                        : Disabled
**          MASTER mode                                    : Enabled
**            Polling trials                               : 2000
**            Automatic stop condition                     : no
**            Initialization                               : 
**              Address mode                               : 7-bit addressing
**              Target slave address init                  : 8
**          SLAVE mode                                     : Disabled
**          Data and Clock                                 : 
**            SDA pin                                      : PTB4/IRQ_11/I2C0_SDA/UART0_RX
**            SDA pin signal                               : 
**            SCL pin                                      : PTB3/IRQ_10/I2C0_SCL/UART0_TX
**            SCL pin signal                               : 
**            High drive select                            : Disabled
**          Internal frequency (multiplier factor)         : 23.986176 MHz
**          Bits 0-2 of Frequency divider register         : 010
**          Bits 3-5 of Frequency divider register         : 111
**          SCL frequency                                  : 13.385 kHz
**          SDA Hold                                       : 10.715 us
**          Noise (glitch) filter                          : 0
**          Wake-up                                        : Disabled
**          Initialization                                 : 
**            Enabled in init code                         : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : Enabled
**            Low speed mode                               : Disabled
**            Slow speed mode                              : Disabled
**     Contents    :
**         SendChar    - byte CI2C1_SendChar(byte Chr);
**         RecvChar    - byte CI2C1_RecvChar(byte *Chr);
**         SendBlock   - byte CI2C1_SendBlock(void* Ptr, word Siz, word *Snt);
**         RecvBlock   - byte CI2C1_RecvBlock(void* Ptr, word Siz, word *Rcv);
**         SendStop    - byte CI2C1_SendStop(void);
**         SelectSlave - byte CI2C1_SelectSlave(byte Slv);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file CI2C1.c
** @version 01.01
** @brief
**          This component encapsulates the internal I2C communication 
**          interface. The implementation of the interface is based 
**          on the Philips I2C-bus specification version 2.0. 
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible 
**              (see "Automatic stop condition" property)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
*/         
/*!
**  @addtogroup CI2C1_module CI2C1 module documentation
**  @{
*/         


/* MODULE CI2C1. */


#include "CI2C1.h"
#include "I2C_PDD.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* SerFlag bits */
#define OVERRUN_ERR      0x01U         /* Overrun error flag bit */
#define WAIT_RX_CHAR     0x02U         /* Wait for received char. flag bit (Master)  */
#define CHAR_IN_TX       0x04U         /* Char is in TX buffer (Master)    */
#define CHAR_IN_RX       0x08U         /* Char is in RX buffer     */
#define FULL_TX          0x10U         /* Full transmit buffer     */
#define IN_PROGRES       0x20U         /* Communication is in progress (Master) */
#define FULL_RX          0x40U         /* Full receive buffer      */
#define MSxSL            0x80U         /* Master x Slave flag bit  */

LDD_TDeviceData *IntI2cLdd1_DeviceDataPtr; /* Device data pointer */
word CI2C1_SndRcvTemp;                 /* Temporary variable for SendChar (RecvChar) when they call SendBlock (RecvBlock) */
static byte ChrTemp;                   /* Temporary variable for SendChar method */
static byte CI2C1_SerFlag;             /* Flags for serial communication */
                                       /* Bits: 0 - OverRun error */
                                       /*       1 - Wait for received char. flag bit (Master) */
                                       /*       2 - Char is in TX buffer (Master) */
                                       /*       3 - Char in RX buffer */
                                       /*       4 - Full TX buffer */
                                       /*       5 - Running int from TX */
                                       /*       6 - Full RX buffer */
                                       /*       7 - Master x Slave */

/*
** ===================================================================
**     Method      :  CI2C1_SendChar (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 0 to the I2C bus and then writes one
**         character (byte) to the bus. The slave address must be
**         specified before, by the "SelectSlave" or "SelectSlave10"
**         method or in the component initialization section, "Target
**         slave address init" property. If interrupt service is
**         enabled and the method returns ERR_OK, it doesn't mean that
**         transmission was successful. The state of transmission is
**         obtainable from (OnTransmitData, OnError or OnArbitLost)
**         events. 
**         When working as a SLAVE, this method writes a character to
**         the internal output slave buffer and, after the master
**         starts the communication, to the I2C bus. If no character is
**         ready for a transmission (internal output slave buffer is
**         empty), the Empty character will be sent (see "Empty
**         character" property).
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by an acknowledge (only in
**                           master mode and when interrupt service is
**                           disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot transmit data
**                           ERR_TXFULL - Transmitter is full (slave
**                           mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
** ===================================================================
*/
byte CI2C1_SendChar(byte Chr)
{
  ChrTemp = Chr;                       /* Save character */
  return (CI2C1_SendBlock(&ChrTemp, 1U, &CI2C1_SndRcvTemp)); /* Send character and return */
}

/*
** ===================================================================
**     Method      :  CI2C1_RecvChar (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 1 to the I2C bus, then reads one
**         character (byte) from the bus and then sends the stop
**         condition. The slave address must be specified before, by
**         the "SelectSlave" or "SelectSlave10" method or in component
**         initialization section, property "Target slave address init".
**         If interrupt service is enabled and the method returns
**         ERR_OK, it doesn't mean that transmission was finished
**         successfully. The state of transmission must be tested by
**         means of events (OnReceiveData, OnError or OnArbitLost). In
**         case of successful transmission, received data is ready
**         after OnReceiveData event is called. 
**         When working as a SLAVE, this method reads a character from
**         the input slave buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Received character.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledge (only
**                           in master mode and when interrupt service
**                           is disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot receive data
**                           ERR_RXEMPTY - No data in receiver (slave
**                           mode only)
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last character or block received
**                           (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
**                           ERR_NOTAVAIL - Method is not available in
**                           current mode - see the comment in the
**                           generated code
** ===================================================================
*/
/*
byte CI2C1_RecvChar(byte *Chr)

**  This method is implemented as a macro. See CI2C1.h file.  **
*/

/*
** ===================================================================
**     Method      :  CI2C1_SendBlock (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 0 to the I2C bus and then writes the
**         block of characters to the bus. The slave address must be
**         specified before, by the "SelectSlave" or "SlaveSelect10"
**         method or in component initialization section, "Target slave
**         address init" property. If interrupt service is enabled and
**         the method returns ERR_OK, it doesn't mean that transmission
**         was successful. The state of transmission is detectable by
**         means of events (OnTransmitData, OnError or OnArbitLost).
**         Data to be send is not copied to an internal buffer and
**         remains in the original location. Therefore the content of
**         the buffer should not be changed until the transmission is
**         complete. Event OnTransmitData can be used to detect the end
**         of the transmission.
**         When working as a SLAVE, this method writes a block of
**         characters to the internal output slave buffer and then,
**         after the master starts the communication, to the I2C bus.
**         If no character is ready for a transmission (internal output
**         slave buffer is empty), the "Empty character" will be sent
**         (see "Empty character" property). In SLAVE mode the data are
**         copied to an internal buffer, if specified by "Output buffer
**         size" property.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of data to send.
**         Siz             - Size of the block.
**       * Snt             - Amount of data sent (moved to a buffer).
**                           In master mode, if interrupt support is
**                           enabled, the parameter always returns the
**                           same value as the parameter 'Siz' of this
**                           method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledge (only
**                           in master mode and when interrupt service
**                           is disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot transmit data
**                           ERR_TXFULL - Transmitter is full. Some data
**                           has not been sent. (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
** ===================================================================
*/
byte CI2C1_SendBlock(void *Ptr,word Siz,word *Snt)
{
  LDD_TError Error;
  LDD_I2C_TErrorMask ErrorMask;
  word TmpSnt = 0x00U;
  word Tr;

  if (Siz == 0U) {                     /* Test variable Size on zero */
    *Snt = 0U;
    return ERR_OK;                     /* If zero then OK */
  }
  Error = IntI2cLdd1_MasterSendBlock(IntI2cLdd1_DeviceDataPtr, (LDD_TData *)Ptr, (LDD_I2C_TSize)Siz, LDD_I2C_NO_SEND_STOP); /* Send one data byte */
  if (Error == ERR_BUSY) {
    return ERR_BUSOFF;
  }
  for (Tr=0U; Tr<0x07D0U; Tr++) {
    IntI2cLdd1_Main(IntI2cLdd1_DeviceDataPtr); /* Call main communication method */
    if (IntI2cLdd1_MasterGetBlockSentStatus(IntI2cLdd1_DeviceDataPtr)) { /* Are all a data transmitted? */
      break;
    }
    if (TmpSnt != (word)IntI2cLdd1_MasterGetSentDataNum(IntI2cLdd1_DeviceDataPtr)) { /* Is a data byte sent? */
      Tr = (word)-1;                   /* Clear trials */
      TmpSnt = (word)IntI2cLdd1_MasterGetSentDataNum(IntI2cLdd1_DeviceDataPtr); /* Set TmpSnt on a new value */
    }
  }
  *Snt = (word)IntI2cLdd1_MasterGetSentDataNum(IntI2cLdd1_DeviceDataPtr); /* Return sent data number */
  (void)IntI2cLdd1_GetError(IntI2cLdd1_DeviceDataPtr, &ErrorMask);
  if (ErrorMask != 0U) {               /* Is any error detected after transfer? */
    if ((ErrorMask & LDD_I2C_MASTER_NACK) != 0U) { /* If yes, decode error and return error code */
      return ERR_BUSY;
    } else if ((ErrorMask & LDD_I2C_ARBIT_LOST) != 0U) {
      return ERR_ARBITR;
    }
  }
  if (Tr == 0x07D0U) {                 /* Is Tr == 'Polling trials'? */
    return ERR_BUSOFF;                 /* Return with error */
  }
  return ERR_OK;                       /* Return ERR_OK */
}

/*
** ===================================================================
**     Method      :  CI2C1_RecvBlock (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 1 to the I2C bus, then reads the
**         block of characters from the bus and then sends the stop
**         condition. The slave address must be specified before, by
**         the "SelectSlave" or "SelectSlave10" method or in component
**         initialization section, "Target slave address init" property.
**         If interrupt service is enabled and the method returns
**         ERR_OK, it doesn't mean that transmission was finished
**         successfully. The state of transmission must be tested by
**         means of events (OnReceiveData, OnError or OnArbitLost). In
**         case of successful transmission, received data is ready
**         after OnReceiveData event is called. 
**         When working as a SLAVE, this method reads a block of
**         characters from the input slave buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block space for received
**                           data.
**         Siz             - The size of the block.
**       * Rcv             - Amount of received data. In master mode,
**                           if interrupt support is enabled, the
**                           parameter always returns the same value as
**                           the parameter 'Siz' of this method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by an acknowledge (only in
**                           master mode and when interrupt service is
**                           disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot receive data
**                           ERR_RXEMPTY - The receive buffer didn't
**                           contain the requested number of data. Only
**                           available data (or no data) has been
**                           returned  (slave mode only).
**                           ERR_OVERRUN - Overrun error was detected
**                           from last character or block receiving
**                           (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
**                           ERR_NOTAVAIL - Method is not available in
**                           current mode - see the comment in the
**                           generated code.
** ===================================================================
*/
byte CI2C1_RecvBlock(void* Ptr,word Siz,word *Rcv)
{
  LDD_TError Error;
  LDD_I2C_TErrorMask ErrorMask;
  LDD_I2C_TBusState BusState;
  word TmpRcv = 0x00U;
  word Tr;

  if (Siz == 0U) {                     /* Test variable Size on zero */
    *Rcv = 0U;
    return ERR_OK;                     /* If zero then OK */
  }
  Error = IntI2cLdd1_MasterReceiveBlock(IntI2cLdd1_DeviceDataPtr, (LDD_TData *)Ptr, (LDD_I2C_TSize)Siz, LDD_I2C_SEND_STOP); /* Receive a data block */
  if (Error == ERR_BUSY) {
    return ERR_BUSOFF;
  }
  for (Tr=0U; Tr<0x07D0U; Tr++) {
    IntI2cLdd1_Main(IntI2cLdd1_DeviceDataPtr); /* Call main communication method */
    if (IntI2cLdd1_MasterGetBlockReceivedStatus(IntI2cLdd1_DeviceDataPtr)) { /* Are all a data received? */
      break;
    }
    if (TmpRcv != (word)IntI2cLdd1_MasterGetReceivedDataNum(IntI2cLdd1_DeviceDataPtr)) { /* Is a data byte received? */
      Tr = (word)-1;                   /* Clear trials counter */
      TmpRcv = (word)IntI2cLdd1_MasterGetReceivedDataNum(IntI2cLdd1_DeviceDataPtr); /* Set TmpRcv on a new value */
    }
  }
  *Rcv = (word)IntI2cLdd1_MasterGetReceivedDataNum(IntI2cLdd1_DeviceDataPtr); /* Return received data number */
  (void)IntI2cLdd1_GetError(IntI2cLdd1_DeviceDataPtr, &ErrorMask);
  if (ErrorMask != 0U) {               /* Is any error detected after transfer? */
    if ((ErrorMask & LDD_I2C_MASTER_NACK) != 0U) { /* If yes, decode error and return error code */
      return ERR_BUSY;
    } else if ((ErrorMask & LDD_I2C_ARBIT_LOST) != 0U) {
      return ERR_ARBITR;
    }
  }
  if (Tr == 0x07D0U) {                 /* Is Tr == 'Polling trials'? */
    return ERR_BUSOFF;                 /* Return with error */
  }
  for (Tr=0U; Tr<0x07D0U; Tr++) {
    (void)IntI2cLdd1_CheckBus(IntI2cLdd1_DeviceDataPtr, &BusState); /* Get bus state */
    if (BusState == LDD_I2C_IDLE) {    /* Is stop condition generated after transfer? */
      return ERR_OK;                   /* Return ERR_OK */
    }
  }
  return ERR_BUSOFF;                   /* Return error */
}

/*
** ===================================================================
**     Method      :  CI2C1_SendStop (component InternalI2C)
**     Description :
**         If the "Automatic stop condition" property value is 'no',
**         this method sends a valid stop condition to the serial data
**         line of the I2C bus to terminate the communication on the
**         bus after using send methods. This method is enabled only if
**         "Automatic stop condition" property is set to 'no'.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed - bus is
**                           busy
** ===================================================================
*/
byte CI2C1_SendStop(void)
{
  LDD_I2C_TBusState BusState;
  word Tr;

  (void)CI2C1_SerFlag;                 /* Suppress unused variable warning if needed */
  I2C_PDD_SetMasterMode(I2C0_BASE_PTR, I2C_PDD_SLAVE_MODE); /* Switch device to slave mode (stop signal sent) */
  I2C_PDD_SetTransmitMode(I2C0_BASE_PTR, I2C_PDD_RX_DIRECTION); /* Switch to Rx mode */
  for(Tr=0x07D0U; Tr!=0U; Tr--) {
    (void)IntI2cLdd1_CheckBus(IntI2cLdd1_DeviceDataPtr, &BusState); /* Get I2C line state */
    if(BusState == LDD_I2C_IDLE) {     /* Bus is idle? */
      return ERR_OK;                   /* Return without error */
    }
  }
  return ERR_BUSOFF;                   /* Return with error */
}

/*
** ===================================================================
**     Method      :  CI2C1_SelectSlave (component InternalI2C)
**     Description :
**         This method selects a new slave for communication by its
**         7-bit slave address value. Any send or receive method
**         directs to or from selected device, until a new slave device
**         is selected by this method. This method is not available for
**         the SLAVE mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Slv             - 7-bit slave address value.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_BUSY - The device is busy, wait until
**                           the current operation is finished.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  The device is disabled
** ===================================================================
*/
byte CI2C1_SelectSlave(byte Slv)
{
  return (byte)IntI2cLdd1_SelectSlaveDevice(IntI2cLdd1_DeviceDataPtr, LDD_I2C_ADDRTYPE_7BITS, (LDD_I2C_TAddr)(Slv & 0x7FU)); /* Set 7 bits slave device address. */
}

/*
** ===================================================================
**     Method      :  CI2C1_Init (component InternalI2C)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void CI2C1_Init(void)
{
  IntI2cLdd1_DeviceDataPtr = IntI2cLdd1_Init(NULL); /* Calling init method of the inherited component */
}


/* END CI2C1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

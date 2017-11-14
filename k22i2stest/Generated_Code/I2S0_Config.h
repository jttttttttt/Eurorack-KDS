/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : I2S0_Config.h
**     Project     : k22i2stest
**     Processor   : MK22FN256VLH12
**     Component   : Init_I2S
**     Version     : Component 01.002, Driver 01.02, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-05-24, 22:27, # CodeGen: 2
**     Abstract    :
**          This file implements the I2S (I2S0) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
**     Settings    :
**          Component name                                 : I2S0
**          Device                                         : I2S0
**          Settings                                       : 
**            Clock gate                                   : <Automatic>
**            Clock setting                                : 
**              Clock source                               : Core/System clock
**              Clock multiplier                           : multiply by 1
**              Clock divider                              : divide by 1
**              Clock ratio                                : 1
**              MCLK clock source/direction                : External
**              MCLK out frequency                         : I2S0_MCLK_Pin
**              Transmit clock setting                     : 
**                Clock source                             : Bus_clock
**                Bit clock divider                        : divide by 2
**                Bit clock source/direction               : External
**                Bit clock frequency                      : I2S0_BCLK_Pin
**                Synchronous mode                         : Asynchronous
**                Bit clock swap                           : no
**                Bit clock input                          : internal
**              Receive clock setting                      : 
**                Clock source                             : Bus_clock
**                Bit clock divider                        : divide by 2
**                Bit clock source/direction               : External
**                Bit clock frequency                      : I2S0_BCLK_Pin
**                Synchronous mode                         : Asynchronous
**                Bit clock swap                           : no
**                Bit clock input                          : internal
**            Transmit configuration                       : 
**              Frame sync source/direction                : External
**              Frame sync mode                            : Continuous
**              Frame sync active state                    : High
**              Frame sync initiated                       : first bit of data
**              Frame sync width [bits]                    : 1
**              Frame size [words]                         : 1
**              Shift direction                            : LSB first
**              Data clocked out on                        : rising edge
**              First bit shifted index                    : 0
**              Word 0 width [bits]                        : 8
**              Word N width [bits]                        : 8
**              Word flag configuration [words]            : 1
**              Data channel                               : Disabled
**              FIFO empty watermark                       : 0
**              FIFO packing mode                          : Disabled
**              FIFO function after error                  : Next frame
**              Time slot mask                             : 0
**              Stop in wait mode                          : yes
**              Stop in debug mode                         : yes
**            Receive configuration                        : 
**              Frame sync source/direction                : External
**              Frame sync mode                            : Continuous
**              Frame sync active state                    : High
**              Frame sync initiated                       : first_bit_of_data
**              Frame sync width [bits]                    : 1
**              Frame size [words]                         : 1
**              Shift direction                            : LSB first
**              Data clocked in on                         : rising edge
**              First bit shifted index                    : 0
**              Word 0 width [bits]                        : 8
**              Word N width [bits]                        : 8
**              Word flag configuration [words]            : 1
**              Data channel                               : Disabled
**              FIFO full watermark                        : 1
**              FIFO packing mode                          : Disabled
**              FIFO function after error                  : Next frame
**              Time slot mask                             : 0
**              Stop in wait mode                          : yes
**              Stop in debug mode                         : yes
**          Pins                                           : 
**            Transmit pins                                : 
**              Serial transmit data pin                   : Disabled
**              Serial bit clock pin                       : Disabled
**              Serial frame sync pin                      : Disabled
**            Receive pins                                 : 
**              Serial receive data pin                    : Disabled
**              Serial bit clock pin                       : Disabled
**              Serial frame sync pin                      : Disabled
**            Serial master clock pin                      : Disabled
**          Interrupts/DMA                                 : 
**            Transmit                                     : 
**              Tx interrupt                               : INT_I2S0_Tx
**              Interrupt request                          : <Automatic>
**              Interrupt priority                         : <Automatic>
**              Tx ISR Name                                : 
**              Tx Word start interrupt                    : Disabled
**              Tx sync error interrupt                    : Disabled
**              Tx FIFO error interrupt                    : Disabled
**              Tx FIFO warning interrupt                  : Disabled
**              Tx FIFO request interrupt                  : Disabled
**              Tx FIFO warning DMA                        : Disabled
**              Tx FIFO request DMA                        : Disabled
**            Receive                                      : 
**              Rx interrupt                               : INT_I2S0_Rx
**              Interrupt request                          : <Automatic>
**              Interrupt priority                         : <Automatic>
**              Rx ISR Name                                : 
**              Rx Word start interrupt                    : Disabled
**              Rx sync error interrupt                    : Disabled
**              Rx FIFO error interrupt                    : Disabled
**              Rx FIFO warning interrupt                  : Disabled
**              Rx FIFO request interrupt                  : Disabled
**              Rx FIFO warning DMA                        : Disabled
**              Rx FIFO request DMA                        : Disabled
**          Initialization                                 : 
**            Transmitter                                  : Disabled
**            Transmitter bit clock                        : Disabled
**            Receiver                                     : Disabled
**            Receiver bit clock                           : Disabled
**            Call Init method                             : yes
**            Utilize after reset values                   : default
**     Contents    :
**         Init - void I2S0_Init(void);
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
** @file I2S0_Config.h                                                  
** @version 01.02
** @brief
**          This file implements the I2S (I2S0) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
*/         
/*!
**  @addtogroup I2S0_Config_module I2S0_Config module documentation
**  @{
*/         

#ifndef I2S0_Config_H_
#define I2S0_Config_H_

/* MODULE I2S0. */

/* I2S0_MCR: DUF=0,MOE=0,??=0,??=0,??=0,??=0,MICS=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
#define I2S0_MCR_VALUE_1     0x00U
#define I2S0_WAIT_FOR_MCLK
/* I2S0_MCR: DUF=0,MOE=0,??=0,??=0,??=0,??=0,MICS=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
#define I2S0_MCR_VALUE_3     0x00U
/* I2S0_MDR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,FRACT=0,DIVIDE=0 */
#define I2S0_MDR_VALUE       0x00U
/* I2S0_MCR: MOE=0 */
#define I2S0_MCR_VALUE_4     0x00U
#define I2S0_MCR_MASK_4      0x40000000U
/* I2S0_TCSR: TE=0,STOPE=0,DBGE=0,BCE=0,??=0,??=0,FR=1,SR=0,??=0,??=0,??=0,WSF=1,SEF=1,FEF=1,FWF=1,FRF=1,??=1,??=1,??=1,WSIE=0,SEIE=0,FEIE=0,FWIE=0,FRIE=0,??=0,??=0,??=0,??=0,??=0,??=0,FWDE=0,FRDE=0 */
#define I2S0_TCSR_VALUE_1    0x021FE000U
#define I2S0_WAIT_FOR_TRANSMITTER
/* I2S0_RCSR: RE=0,STOPE=0,DBGE=0,BCE=0,??=0,??=0,FR=1,SR=0,??=0,??=0,??=0,WSF=1,SEF=1,FEF=1,FWF=0,FRF=0,??=0,??=0,??=0,WSIE=0,SEIE=0,FEIE=0,FWIE=0,FRIE=0,??=0,??=0,??=0,??=0,??=0,??=0,FWDE=0,FRDE=0 */
#define I2S0_RCSR_VALUE_1    0x021C0000U
#define I2S0_WAIT_FOR_RECEIVER
/* I2S0_TCR1: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TFW=0 */
#define I2S0_TCR1_VALUE      0x00U
/* I2S0_RCR1: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,RFW=0 */
#define I2S0_RCR1_VALUE      0x00U
/* I2S0_TCR2: SYNC=0,BCS=0,BCI=0,MSEL=0,BCP=0,BCD=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DIV=0 */
#define I2S0_TCR2_VALUE      0x00U
/* I2S0_RCR2: SYNC=0,BCS=0,BCI=0,MSEL=0,BCP=0,BCD=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DIV=0 */
#define I2S0_RCR2_VALUE      0x00U
/* I2S0_TCR3: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TCE=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,WDFL=0 */
#define I2S0_TCR3_VALUE      0x00U
/* I2S0_RCR3: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,RCE=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,WDFL=0 */
#define I2S0_RCR3_VALUE      0x00U
/* I2S0_TCR4: ??=0,??=0,??=0,FCONT=0,??=0,??=0,FPACK=0,??=0,??=0,??=0,??=0,FRSZ=0,??=0,??=0,??=0,SYWD=0,??=0,??=0,??=0,MF=0,FSE=0,ONDEM=0,FSP=0,FSD=0 */
#define I2S0_TCR4_VALUE      0x00U
/* I2S0_RCR4: ??=0,??=0,??=0,FCONT=0,??=0,??=0,FPACK=0,??=0,??=0,??=0,??=0,FRSZ=0,??=0,??=0,??=0,SYWD=0,??=0,??=0,??=0,MF=0,FSE=0,ONDEM=0,FSP=0,FSD=0 */
#define I2S0_RCR4_VALUE      0x00U
/* I2S0_TCR5: ??=0,??=0,??=0,WNW=7,??=0,??=0,??=0,W0W=7,??=0,??=0,??=0,FBT=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
#define I2S0_TCR5_VALUE      0x07070000U
/* I2S0_RCR5: ??=0,??=0,??=0,WNW=7,??=0,??=0,??=0,W0W=7,??=0,??=0,??=0,FBT=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
#define I2S0_RCR5_VALUE      0x07070000U
/* I2S0_TMR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TWM=0 */
#define I2S0_TMR_VALUE       0x00U
/* I2S0_RMR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,RWM=0 */
#define I2S0_RMR_VALUE       0x00U
/* I2S0_TCSR: TE=0,STOPE=0,DBGE=0,BCE=0,??=0,??=0,FR=0,SR=0,??=0,??=0,??=0,WSF=0,SEF=0,FEF=0,FWF=0,FRF=0,??=0,??=0,??=0,WSIE=0,SEIE=0,FEIE=0,FWIE=0,FRIE=0,??=0,??=0,??=0,??=0,??=0,??=0,FWDE=0,FRDE=0 */
#define I2S0_TCSR_VALUE_3    0x00U
/* I2S0_RCSR: RE=0,STOPE=0,DBGE=0,BCE=0,??=0,??=0,FR=0,SR=0,??=0,??=0,??=0,WSF=0,SEF=0,FEF=0,FWF=0,FRF=0,??=0,??=0,??=0,WSIE=0,SEIE=0,FEIE=0,FWIE=0,FRIE=0,??=0,??=0,??=0,??=0,??=0,??=0,FWDE=0,FRDE=0 */
#define I2S0_RCSR_VALUE_3    0x00U

#define I2S0_AUTOINIT

/* END I2S0. */
#endif /* #ifndef __I2S0_Config_H_ */
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
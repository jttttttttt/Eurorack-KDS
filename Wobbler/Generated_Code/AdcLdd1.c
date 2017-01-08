/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : AdcLdd1.c
**     Project     : Wobbler
**     Processor   : MKL02Z32VFM4
**     Component   : ADC_LDD
**     Version     : Component 01.183, Driver 01.08, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-12-28, 02:02, # CodeGen: 1
**     Abstract    :
**         This device "ADC_LDD" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : AdcLdd1
**          A/D converter                                  : ADC0
**          Discontinuous mode                             : no
**          Interrupt service/event                        : Enabled
**            A/D interrupt                                : INT_ADC0
**            A/D interrupt priority                       : medium priority
**          DMA                                            : Disabled
**          A/D channel list                               : 4
**            Channel 0                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE13/PTB13/TPM1_CH1
**                  A/D channel (pin) signal               : 
**            Channel 1                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE8/PTB11/TPM0_CH0
**                  A/D channel (pin) signal               : 
**            Channel 2                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE3/PTA8/I2C1_SCL
**                  A/D channel (pin) signal               : 
**            Channel 3                                    : 
**              Channel mode                               : Single Ended
**                Input                                    : 
**                  A/D channel (pin)                      : ADC0_SE2/PTA9/I2C1_SDA
**                  A/D channel (pin) signal               : 
**          Static sample groups                           : Disabled
**          Max. samples                                   : 8
**          A/D resolution                                 : Autoselect
**          Low-power mode                                 : Disabled
**          High-speed conversion mode                     : Disabled
**          Asynchro clock output                          : Disabled
**          Sample time                                    : 24 clock periods
**          Number of conversions                          : 1
**          Conversion time                                : 30.769231 �s
**          ADC clock                                      : 1.299 MHz (769.231 ns)
**          Single conversion time - Single-ended          : 38.285 us
**          Single conversion time - Differential          : Differential mode not supported
**          Additional conversion time - Single-ended      : 30.769 us
**          Additional conversion time - Differential      : Differential mode not supported
**          Result type                                    : unsigned 16 bits, right justified
**          Trigger                                        : Disabled
**          Voltage reference                              : 
**            High voltage reference                       : 
**              Volt. ref. pin                             : VREFH
**              Volt. ref pin signal                       : 
**            Low voltage reference                        : 
**              Volt. ref. pin                             : VREFL
**              Volt. ref pin signal                       : 
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnMeasurementComplete                      : Enabled
**              OnError                                    : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init                         - LDD_TDeviceData* AdcLdd1_Init(LDD_TUserData *UserDataPtr);
**         StartSingleMeasurement       - LDD_TError AdcLdd1_StartSingleMeasurement(LDD_TDeviceData *DeviceDataPtr);
**         CancelMeasurement            - LDD_TError AdcLdd1_CancelMeasurement(LDD_TDeviceData *DeviceDataPtr);
**         GetMeasuredValues            - LDD_TError AdcLdd1_GetMeasuredValues(LDD_TDeviceData *DeviceDataPtr,...
**         CreateSampleGroup            - LDD_TError AdcLdd1_CreateSampleGroup(LDD_TDeviceData *DeviceDataPtr,...
**         GetMeasurementCompleteStatus - bool AdcLdd1_GetMeasurementCompleteStatus(LDD_TDeviceData *DeviceDataPtr);
**         StartCalibration             - LDD_TError AdcLdd1_StartCalibration(LDD_TDeviceData *DeviceDataPtr);
**         GetCalibrationResultStatus   - LDD_TError AdcLdd1_GetCalibrationResultStatus(LDD_TDeviceData *DeviceDataPtr);
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
** @file AdcLdd1.c
** @version 01.08
** @brief
**         This device "ADC_LDD" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup AdcLdd1_module AdcLdd1 module documentation
**  @{
*/         

/* MODULE AdcLdd1. */

#include "AD1.h"
#include "AdcLdd1.h"
/* {Default RTOS Adapter} No RTOS includes */

#ifdef __cplusplus
extern "C" { 
#endif

#define AdcLdd1_AVAILABLE_CHANNEL0_31_PIN_MASK (LDD_ADC_CHANNEL_0_PIN | LDD_ADC_CHANNEL_1_PIN | LDD_ADC_CHANNEL_2_PIN | LDD_ADC_CHANNEL_3_PIN) /*!< Mask of all allocated channel pins from 0 to 31 */
#define AdcLdd1_AVAILABLE_CHANNEL32_63_PIN_MASK 0x00U /*!< Mask of all allocated channel pins from 32 to 63 */
#define AdcLdd1_AVAILABLE_TRIGGER_PIN_MASK 0x00U /*!< Mask of all allocated trigger pins */
#define AdcLdd1_AVAILABLE_VOLT_REF_PIN_MASK (LDD_ADC_LOW_VOLT_REF_PIN | LDD_ADC_HIGH_VOLT_REF_PIN) /*!< Mask of all allocated voltage reference pins */

static const uint8_t ChannelToPin[] = { /* Channel to pin conversion table */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=1,??=0,ADCH=0x10 */
  0x50U,                               /* Status and control register value */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=1,??=0,ADCH=0x0B */
  0x4BU,                               /* Status and control register value */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=1,??=0,ADCH=3 */
  0x43U,                               /* Status and control register value */
  /* ADC0_SC1A: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COCO=0,AIEN=1,??=0,ADCH=2 */
  0x42U                                /* Status and control register value */
};

typedef struct {
  uint8_t SampleCount;                 /* Number of samples in the last selected/created sample group */
  uint8_t FirstSample;                 /* First sample of group store */
  uint8_t CompleteStatus;              /* Measurement complete status flag */
  LDD_TUserData *UserData;             /* RTOS device data structure */
} AdcLdd1_TDeviceData;                 /* Device data structure type */

typedef AdcLdd1_TDeviceData* AdcLdd1_TDeviceDataPtr ; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static AdcLdd1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static AdcLdd1_TDeviceDataPtr INT_ADC0__DEFAULT_RTOS_ISRPARAM;
/*
** ===================================================================
**     Method      :  AdcLdd1_Init (component ADC_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc.
**         If the "Enable in init. code" is set to "yes" value then the
**         device is also enabled(see the description of the Enable()
**         method). In this case the Enable() method is not necessary
**         and needn't to be generated. 
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* AdcLdd1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  AdcLdd1_TDeviceDataPtr DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_ADC0__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  DeviceDataPrv->SampleCount = 0U;     /* Initializing SampleCount for right access of some methods to SC1n registers before first conversion is done */
  DeviceDataPrv->CompleteStatus = FALSE; /* Clear measurement complete status flag */
  /* SIM_SCGC6: ADC0=1 */
  SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
  /* Interrupt vector(s) priority setting */
  /* NVIC_IPR3: PRI_15=0x80 */
  NVIC_IPR3 = (uint32_t)((NVIC_IPR3 & (uint32_t)~(uint32_t)(
               NVIC_IP_PRI_15(0x7F)
              )) | (uint32_t)(
               NVIC_IP_PRI_15(0x80)
              ));
  /* NVIC_ISER: SETENA|=0x8000 */
  NVIC_ISER |= NVIC_ISER_SETENA(0x8000);
  /* PORTB_PCR13: ISF=0,MUX=0 */
  PORTB_PCR13 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTB_PCR11: ISF=0,MUX=0 */
  PORTB_PCR11 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTA_PCR8: ISF=0,MUX=0 */
  PORTA_PCR8 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTA_PCR9: ISF=0,MUX=0 */
  PORTA_PCR9 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* ADC0_CFG1: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,ADLPC=0,ADIV=2,ADLSMP=1,MODE=1,ADICLK=3 */
  ADC0_CFG1 = ADC_CFG1_ADIV(0x02) |
              ADC_CFG1_ADLSMP_MASK |
              ADC_CFG1_MODE(0x01) |
              ADC_CFG1_ADICLK(0x03);

  /* ADC0_CFG2: ADACKEN=0,ADHSC=0,ADLSTS=0 */
  ADC0_CFG2 &= (uint32_t)~(uint32_t)(
                ADC_CFG2_ADACKEN_MASK |
                ADC_CFG2_ADHSC_MASK |
                ADC_CFG2_ADLSTS(0x03)
               );
  /* ADC0_SC2: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,ADACT=0,ADTRG=0,ACFE=0,ACFGT=0,ACREN=0,DMAEN=0,REFSEL=0 */
  ADC0_SC2 = ADC_SC2_REFSEL(0x00);
  /* ADC0_SC3: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CAL=0,CALF=1,??=0,??=0,ADCO=0,AVGE=0,AVGS=0 */
  ADC0_SC3 = (ADC_SC3_CALF_MASK | ADC_SC3_AVGS(0x00));
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_AdcLdd1_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the data data structure */
}

/*
** ===================================================================
**     Method      :  AdcLdd1_StartSingleMeasurement (component ADC_LDD)
*/
/*!
**     @brief
**         This method starts one measurement of the selected group of
**         samples and exits immediately. This is ADC SW trigger method.
**         The group of samples for measurement is specified by
**         preceding call to [SelectSampleGroup()] or
**         [CreateSampleGroup] method. 
**         DMA disabled: The [OnMeasurementComplete() ] event is
**         invoked after the measurement is done and if the event is
**         enabled. Results of the measurement can be read by the
**         [GetMeasuredValues()] method. 
**         DMA enabled: DMA request from configured ADC is enabled
**         automatically. The [OnMeasurementComplete() ] event is
**         invoked after the requested number of results are
**         transferred to destination buffer by DMA and if the event is
**         enabled. [GetMeasuredValues()] method is not available if
**         DMA mode is enabled. If the DMA transfer was completed
**         before and DMA is not recofingured, DMA error can occur. See
**         also [SetBuffer()] method. 
**         The state of the measurement can be also polled by the
**         [GetMeasurementCompleteStatus()] method. The [Discontinuous
**         mode] doesn't support this method.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_BUSY - A measurement is in progress 
*/
/* ===================================================================*/
LDD_TError AdcLdd1_StartSingleMeasurement(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if (ADC_PDD_GetConversionActiveFlag(ADC0_BASE_PTR) != 0U) { /* Last measurement still pending? */
    return ERR_BUSY;                   /* Yes, return ERR_BUSY */
  }
  ADC_PDD_SetContinuousMode(ADC0_BASE_PTR, ADC_PDD_ONE_CONVERSION); /* Set one conversion mode */
  ADC_PDD_SetConversionTriggerType(ADC0_BASE_PTR, ADC_PDD_SW_TRIGGER); /* Select SW triggering */
  ADC_PDD_WriteStatusControl1Reg(ADC0_BASE_PTR, 0U, ((AdcLdd1_TDeviceDataPtr)DeviceDataPtr)->FirstSample); /* Set sample 0 and start conversion */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AdcLdd1_CancelMeasurement (component ADC_LDD)
*/
/*!
**     @brief
**         This method cancels the measurement in progress. Typically
**         the OnMeasurementComplete() event is not invoked for
**         cancelled measurement. If DMA mode is enabled, DMA request
**         from ADC is disabled and DMA transfer is cancelled. 
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
**                           ERR_DISABLED - Component is disabled
*/
/* ===================================================================*/
LDD_TError AdcLdd1_CancelMeasurement(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  ADC_PDD_SetConversionTriggerType(ADC0_BASE_PTR, ADC_PDD_SW_TRIGGER); /* Select SW triggering */
  ADC_PDD_WriteStatusControl1Reg(ADC0_BASE_PTR, 0U, 0x1FU); /* Disable device - A */
  
  return ERR_OK;                       /* If yes then set the flag "device enabled" */  
}

/*
** ===================================================================
**     Method      :  AdcLdd1_CreateSampleGroup (component ADC_LDD)
*/
/*!
**     @brief
**         This method prepares HW for next measurement according to
**         array of samples defined during run-time. The array of
**         samples should be prepared prior to calling this method.
**         Pointer to the array is passed into this method in parameter
**         SampleGroupPtr. The number of samples is defined by
**         parameter SampleCount. Once any group is prepared, the
**         measurement can be started multiple times. Note: This method
**         works only with the sample groups defined during run-time.
**         For design-time defined groups use [SelectSampleGroup()]
**         method.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         SampleGroupPtr  - Pointer to the
**                           sample definition array. This array can be
**                           released as soon as the method ends.
**     @param
**         SampleCount     - Number of items in the
**                           sample definition array. Must be less than
**                           or equal to
**                           ComponentName_MAX_HW_SAMPLE_COUNT.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_PARAM_INDEX - Channel index in
**                           SampleGroup structure is out of range
**                           ERR_PARAM_SAMPLE_COUNT - SampleCount
**                           variable value is out of range
**                           ERR_BUSY - Measurement is in progress 
*/
/* ===================================================================*/
LDD_TError AdcLdd1_CreateSampleGroup(LDD_TDeviceData *DeviceDataPtr, LDD_ADC_TSample *SampleGroupPtr, uint8_t SampleCount)
{
  AdcLdd1_TDeviceDataPtr DeviceDataPrv = (AdcLdd1_TDeviceDataPtr)DeviceDataPtr;

  /* Sample count test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if ((SampleCount > AdcLdd1_MAX_HW_SAMPLE_COUNT) || (SampleCount == 0U)) { /* Is number of sample greater then supported by the HW? */
    return ERR_PARAM_SAMPLE_COUNT;     /* Yes, return ERR_PARAM_SAMPLE_COUNT */
  }
  if (ADC_PDD_GetConversionActiveFlag(ADC0_BASE_PTR) != 0U) { /* Last measurement still pending? */
    return ERR_BUSY;                   /* Yes, return ERR_BUSY */
  }
  DeviceDataPrv->SampleCount = SampleCount; /* Remember sample count */
  /* Channel index test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (SampleGroupPtr[0].ChannelIdx >= AdcLdd1_CHANNEL_COUNT) { /* Is channel index out of range? */
    return ERR_PARAM_INDEX;            /* Yes, return ERR_PARAM_INDEX */
  }
  DeviceDataPrv->FirstSample = (ChannelToPin[SampleGroupPtr[0].ChannelIdx]) | (uint8_t)(LDD_ADC_ON_MEASUREMENT_COMPLETE); /* Remember first sample */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AdcLdd1_GetMeasuredValues (component ADC_LDD)
*/
/*!
**     @brief
**         This method copies results of the last measurement to the
**         user supplied buffer. Data size depends on the size of
**         measured sample group (see [SelectSampleGroup()] or
**         [CreateSampleGroup()] method). Data representation is
**         defined by the [Result type] property. Typically this method
**         is called from [OnMeasurementComplete] event to get results
**         of the last measurement. This method is not available if DMA
**         is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         BufferPtr       - Pointer to the start of the
**                           buffer for new results. Count of stored
**                           measured values equals to the count of the
**                           samples in the active sample group. It is
**                           in the user responsibility to provide
**                           buffer with appropriate size.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
**                           ERR_DISABLED - Component is disabled
*/
/* ===================================================================*/
LDD_TError AdcLdd1_GetMeasuredValues(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr)
{
  uint8_t Sample;
  AdcLdd1_TResultData *pBuffer = (AdcLdd1_TResultData *)BufferPtr;

  /* Copy values from result registers defined in the active sample
     group to the user supplied buffer */
  for (Sample = 0U; Sample < ((AdcLdd1_TDeviceDataPtr)DeviceDataPtr)->SampleCount; Sample++) {
    pBuffer[Sample] =(uint16_t)(ADC_PDD_GetResultValueRaw(ADC0_BASE_PTR, Sample));
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AdcLdd1_GetMeasurementCompleteStatus (component ADC_LDD)
*/
/*!
**     @brief
**         Returns whether the measurement is done and the results can
**         be read by the user. It can be used to poll the state of
**         measurement if [Interrupt service/event] is disabled or if
**         [OnMeasurementComplete] event is disabled by the
**         [SetEventMask()] methods.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code
**                           true - Measurement is done
**                           false - Measurement is in progress
*/
/* ===================================================================*/
bool AdcLdd1_GetMeasurementCompleteStatus(LDD_TDeviceData *DeviceDataPtr)
{
  uint8_t Status;
  AdcLdd1_TDeviceDataPtr DeviceDataPrv = (AdcLdd1_TDeviceDataPtr)DeviceDataPtr;
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  Status = DeviceDataPrv->CompleteStatus; /* Save flag for return */
  DeviceDataPrv->CompleteStatus = FALSE; /* Clear measurement complete status flag */
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return (bool)((Status)? TRUE : FALSE); /* Return saved status */
}

/*
** ===================================================================
**     Method      :  AdcLdd1_StartCalibration (component ADC_LDD)
*/
/*!
**     @brief
**         This method starts self calibration process. Calibration is
**         typically used to remove the effects of the gain and offset
**         from a specific reading.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_BUSY - A conversion is already running 
*/
/* ===================================================================*/
LDD_TError AdcLdd1_StartCalibration(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if (ADC_PDD_GetConversionActiveFlag(ADC0_BASE_PTR) != 0U) { /* Last measurement still pending? */
    return ERR_BUSY;                   /* Yes, return ERR_BUSY */
  }
  ADC_PDD_SetConversionTriggerType(ADC0_BASE_PTR, ADC_PDD_SW_TRIGGER); /* Select SW triggering */
  ADC_PDD_WriteStatusControl1Reg(ADC0_BASE_PTR, 0U, ADC_PDD_MODULE_DISABLED | ((uint32_t)LDD_ADC_ON_MEASUREMENT_COMPLETE)); /* Set Control 1 register */
  ADC_PDD_StartCalibration(ADC0_BASE_PTR); /* Start calibration */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  AdcLdd1_GetCalibrationResultStatus (component ADC_LDD)
*/
/*!
**     @brief
**         This method should be used for check the last calibration
**         result. If calibration completed normally the method finish
**         calibration process by writing gain calibration values.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code
**                           ERR_OK - OK 
**                           ERR_FAILED - Last calibration hasn't been
**                           finished correctly
*/
/* ===================================================================*/
LDD_TError AdcLdd1_GetCalibrationResultStatus(LDD_TDeviceData *DeviceDataPtr)
{
  uint32_t GainValue;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if (ADC_PDD_GetCalibrationFailedStatusFlag(ADC0_BASE_PTR)) {
    return ERR_FAILED;
  }
  /* If calibration is successfully passed place calibrated value into gain registers */
  /* Cumulated gradually because of undefined behavior: the order of volatile accesses is undefined in this statement */
  GainValue = ADC_PDD_GetPlus0CalibrationValue(ADC0_BASE_PTR); /* Find plus gain value */
  GainValue += ADC_PDD_GetPlus1CalibrationValue(ADC0_BASE_PTR);
  GainValue += ADC_PDD_GetPlus2CalibrationValue(ADC0_BASE_PTR);
  GainValue += ADC_PDD_GetPlus3CalibrationValue(ADC0_BASE_PTR);
  GainValue += ADC_PDD_GetPlus4CalibrationValue(ADC0_BASE_PTR);
  GainValue += ADC_PDD_GetPlusSCalibrationValue(ADC0_BASE_PTR);
  GainValue = (GainValue >> 1U) | 0x8000U;
  ADC_PDD_SetPlusGainValue(ADC0_BASE_PTR,GainValue); /* Set plus gain value */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  AdcLdd1_MeasurementCompleteInterrupt (component ADC_LDD)
**
**     Description :
**         Measurement complete interrupt handler
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(AdcLdd1_MeasurementCompleteInterrupt)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  AdcLdd1_TDeviceDataPtr DeviceDataPrv = INT_ADC0__DEFAULT_RTOS_ISRPARAM;
  DeviceDataPrv->CompleteStatus = TRUE; /* Set measurement complete status flag */
  AdcLdd1_OnMeasurementComplete(DeviceDataPrv->UserData);
  (void)ADC_PDD_GetResultValueRaw(ADC0_BASE_PTR, 0U); /* Clear conversion complete flag */
}

/* END AdcLdd1. */

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

/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "DrvAsc.h"
#include "DrvAscTypes.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Static Function Prototype                  */
/*----------------------------------------------------------------*/
static void DrvAsc0Init(void);


/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/
App_AsclinAsc g_AsclinAsc; /**< \brief Demo information */
uint32_t gu32nuAscRxData = 0u;

/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/
/*---------------------Interrupt Define--------------------------*/
IFX_INTERRUPT(ASCTxInt0Handler, 0, ISR_PRIORITY_ASC_0_TX);
IFX_INTERRUPT(ASCRxInt0Handler, 0, ISR_PRIORITY_ASC_0_RX);
IFX_INTERRUPT(ASCExInt0Handler, 0, ISR_PRIORITY_ASC_0_EX);

/*---------------------Interrupt Service Routine--------------------------*/
void ASCTxInt0Handler(void)
{
    IfxAsclin_Asc_isrTransmit(&g_AsclinAsc.drivers.asc0);
}

void ASCRxInt0Handler(void)
{
    IfxAsclin_Asc_isrReceive(&g_AsclinAsc.drivers.asc0);
    IfxAsclin_Asc_read(&g_AsclinAsc.drivers.asc0, g_AsclinAsc.rxData, &g_AsclinAsc.count, TIME_INFINITE);    
    gu32nuAscRxData = g_AsclinAsc.rxData[0];

    #if 0
    g_AsclinAsc.txData[0] = gu32nuAscRxData;    
    IfxAsclin_Asc_write(&g_AsclinAsc.drivers.asc0, g_AsclinAsc.txData, &g_AsclinAsc.count, TIME_INFINITE);
    #endif
}

void ASCExInt0Handler(void)
{
    IfxAsclin_Asc_isrError(&g_AsclinAsc.drivers.asc0);
}

/*---------------------Init Function--------------------------*/
void DrvAscInit(void)
{
    DrvAsc0Init();
}

static void DrvAsc0Init(void)
{
    /* create module config */
    IfxAsclin_Asc_Config ascConfig;
    IfxAsclin_Asc_initModuleConfig(&ascConfig, &MODULE_ASCLIN0);

    /* set the desired baudrate */
    ascConfig.baudrate.prescaler    = 1;
    ascConfig.baudrate.baudrate     = 9600; /* FDR values will be calculated in initModule */
    ascConfig.baudrate.oversampling = IfxAsclin_OversamplingFactor_4;

    /* ISR priorities and interrupt target */
    ascConfig.interrupt.txPriority    = ISR_PRIORITY_ASC_0_TX;
    ascConfig.interrupt.rxPriority    = ISR_PRIORITY_ASC_0_RX;
    ascConfig.interrupt.erPriority    = ISR_PRIORITY_ASC_0_EX;
    ascConfig.interrupt.typeOfService = (IfxSrc_Tos)IfxCpu_getCoreIndex();

    /* FIFO configuration */
    ascConfig.txBuffer     = g_AsclinAsc.ascBuffer.tx;
    ascConfig.txBufferSize = ASC_TX_BUFFER_SIZE;

    ascConfig.rxBuffer     = g_AsclinAsc.ascBuffer.rx;
    ascConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;

    /* pin configuration */    
    const IfxAsclin_Asc_Pins pins = {
        NULL_PTR,                     IfxPort_InputMode_pullUp,        // CTS pin not used
        &IfxAsclin0_RXB_P15_3_IN, IfxPort_InputMode_pullUp,        // Rx pin
        NULL_PTR,                     IfxPort_OutputMode_pushPull,     //RTS pin not used
        &IfxAsclin0_TX_P15_2_OUT, IfxPort_OutputMode_pushPull,     // Tx pin
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };        
    ascConfig.pins = &pins;

    /* initialize module */
    IfxAsclin_Asc_initModule(&g_AsclinAsc.drivers.asc0, &ascConfig);

    g_AsclinAsc.count = 1;    
}

/*---------------------Driver API--------------------------*/
#if 1

extern float32_t testrpm;

void DrvAsc_Test1(void)
{
    static uint16_t TestCnt1 = 0u;
    static uint16_t TestCnt2 = 50u;
    
    g_AsclinAsc.count = 2;

    TestCnt1 = (uint16_t)testrpm;
    
    g_AsclinAsc.txData[0] = (uint8_t)((TestCnt1 & 0xFF00) >> 8);
    g_AsclinAsc.txData[1] = (uint8_t)(TestCnt1 & 0x00FF);
    //g_AsclinAsc.txData[2] = (uint8_t)((TestCnt2 & 0xFF00) >> 8);
    //g_AsclinAsc.txData[3] = (uint8_t)(TestCnt2 & 0x00FF);
   
    /* Transmit data */
    IfxAsclin_Asc_write(&g_AsclinAsc.drivers.asc0, g_AsclinAsc.txData, &g_AsclinAsc.count, TIME_INFINITE);
}
#endif


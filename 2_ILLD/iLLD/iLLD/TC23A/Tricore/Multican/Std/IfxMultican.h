/**
 * \file IfxMultican.h
 * \brief MULTICAN  basic functionality
 * \ingroup IfxLld_Multican
 *
 * \version iLLD_1_0_1_8_0
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Multican_Std_Enum Enumerations
 * \ingroup IfxLld_Multican_Std
 * \defgroup IfxLld_Multican_Std_General General functions
 * \ingroup IfxLld_Multican_Std
 * \defgroup IfxLld_Multican_Std_Node CAN Nodes
 * \ingroup IfxLld_Multican_Std
 * \defgroup IfxLld_Multican_Std_Message Message
 * \ingroup IfxLld_Multican_Std
 * \defgroup IfxLld_Multican_Std_Message_Objects Message Objects
 * \ingroup IfxLld_Multican_Std
 * \defgroup IfxLld_Multican_Std_Interrupts Interrupts
 * \ingroup IfxLld_Multican_Std
 */

#ifndef IFXMULTICAN_H
#define IFXMULTICAN_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxMultican_cfg.h"
#include "Src/Std/IfxSrc.h"
#include "_PinMap/IfxMultican_PinMap.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "IfxCan_bf.h"
#include "Scu/Std/IfxScuWdt.h"
#include "_Utilities/Ifx_Assert.h"
#include "_Utilities/Ifx_Assert.h"

/******************************************************************************/
/*------------------------------Type Definitions------------------------------*/
/******************************************************************************/

/** \brief Message object ID, 0 .. \ref IFXMULTICAN_NUM_MESSAGE_OBJECTS
 */
typedef sint32 IfxMultican_MsgObjId;

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Multican_Std_Enum
 * \{ */
/** \brief CAN input clock selection
 */
typedef enum
{
    IfxMultican_ClockSelect_noClock  = 0, /**< \brief No clock supplied */
    IfxMultican_ClockSelect_fclc     = 1, /**< \brief fMULTICAN */
    IfxMultican_ClockSelect_fosc0    = 2, /**< \brief Oscillator Clock */
    IfxMultican_ClockSelect_fErayPll = 4  /**< \brief E-Ray clock */
} IfxMultican_ClockSelect;

/** \brief CAN frame data length code
 * Definition in Ifx_CAN.MOFCRx.DLC
 */
typedef enum
{
    IfxMultican_DataLengthCode_0 = 0,    /**< \brief 0 data bytes  */
    IfxMultican_DataLengthCode_1,        /**< \brief 1 data bytes  */
    IfxMultican_DataLengthCode_2,        /**< \brief 2 data bytes  */
    IfxMultican_DataLengthCode_3,        /**< \brief 3 data bytes  */
    IfxMultican_DataLengthCode_4,        /**< \brief 4 data bytes  */
    IfxMultican_DataLengthCode_5,        /**< \brief 5 data bytes  */
    IfxMultican_DataLengthCode_6,        /**< \brief 6 data bytes  */
    IfxMultican_DataLengthCode_7,        /**< \brief 7 data bytes  */
    IfxMultican_DataLengthCode_8,        /**< \brief 8 data bytes  */
    IfxMultican_DataLengthCode_12 = 9,   /**< \brief 12 data bytes */
    IfxMultican_DataLengthCode_16 = 10,  /**< \brief 16 data bytes */
    IfxMultican_DataLengthCode_20 = 11,  /**< \brief 20 data bytes */
    IfxMultican_DataLengthCode_24 = 12,  /**< \brief 24 data bytes */
    IfxMultican_DataLengthCode_32 = 13,  /**< \brief 32 data bytes */
    IfxMultican_DataLengthCode_48 = 14,  /**< \brief 48 data bytes */
    IfxMultican_DataLengthCode_64 = 15   /**< \brief 64 data bytes */
} IfxMultican_DataLengthCode;

/** \brief CAN frame type
 */
typedef enum
{
    IfxMultican_Frame_receive,        /**< \brief Data frame is received */
    IfxMultican_Frame_transmit,       /**< \brief Data frame is generated */
    IfxMultican_Frame_remoteRequest,  /**< \brief Remote request frame is generated */
    IfxMultican_Frame_remoteAnswer    /**< \brief Answer frame is generated on reception of the corresponding remote request */
} IfxMultican_Frame;

/** \brief Determines the operation mode of the frame counter\n
 * Definition in Ifx_CAN.NFCRx.B.CFMOD, (x= node Id)
 */
typedef enum
{
    IfxMultican_FrameCounterMode_frameCountMode = 0,  /**< \brief The frame counter is incremented
                                                       * upon the reception and transmission of frames */
    IfxMultican_FrameCounterMode_timeStampMode  = 1,  /**< \brief The frame counter is used to count
                                                       * bit times. */
    IfxMultican_FrameCounterMode_bitTimingMode  = 2,  /**< \brief The frame counter is used for
                                                       * analysis of the bit timing. */
    IfxMultican_FrameCounterMode_errorCountMode = 3   /**< \brief The frame counter is used for
                                                       * counting when an error frame is received or an error is
                                                       * detected by the node. */
} IfxMultican_FrameCounterMode;

/** \brief CAN message object group\n
 * Each group consists of 32 consecutive message objects
 */
typedef enum
{
    IfxMultican_MsgObjGroup_0 = 0,
    IfxMultican_MsgObjGroup_1,
    IfxMultican_MsgObjGroup_2,
    IfxMultican_MsgObjGroup_3,
    IfxMultican_MsgObjGroup_4,
    IfxMultican_MsgObjGroup_5,
    IfxMultican_MsgObjGroup_6,
    IfxMultican_MsgObjGroup_7
} IfxMultican_MsgObjGroup;

/** \brief CAN Message Object Mode
 */
typedef enum
{
    IfxMultican_MsgObjMode_standard          = 0,  /**< \brief Standard Message Object */
    IfxMultican_MsgObjMode_receiveFifoBase   = 1,  /**< \brief Receive FIFO Base Object */
    IfxMultican_MsgObjMode_transmitFifoBase  = 2,  /**< \brief Transmit FIFO Base Object */
    IfxMultican_MsgObjMode_transmitFifoSlave = 3,  /**< \brief Transmit FIFO Slave Object */
    IfxMultican_MsgObjMode_gatewaySource     = 4,  /**< \brief Gateway Source Object */
    IfxMultican_MsgObjMode_canFD64           = 5   /**< \brief CANFD 64 bytes Message Mode */
} IfxMultican_MsgObjMode;

/** \brief CAN Message Object status flag
 * Definition in Ifx_CAN.MOSTATx (x: 0 to max number of msg objs)
 */
typedef enum
{
    IfxMultican_MsgObjStatusFlag_receivePending          = IFX_CAN_MO_STAT_RXPND_OFF,  /**< \brief Receive pending status flag */
    IfxMultican_MsgObjStatusFlag_transmitPending         = IFX_CAN_MO_STAT_TXPND_OFF,  /**< \brief Transmit pending status flag */
    IfxMultican_MsgObjStatusFlag_receiveUpdating         = IFX_CAN_MO_STAT_RXUPD_OFF,  /**< \brief Receive updating status flag */
    IfxMultican_MsgObjStatusFlag_newData                 = IFX_CAN_MO_STAT_NEWDAT_OFF, /**< \brief New data status flag */
    IfxMultican_MsgObjStatusFlag_messageLost             = IFX_CAN_MO_STAT_MSGLST_OFF, /**< \brief Message lost status flag */
    IfxMultican_MsgObjStatusFlag_messageValid            = IFX_CAN_MO_STAT_MSGVAL_OFF, /**< \brief Message valid status flag */
    IfxMultican_MsgObjStatusFlag_receiveTransmitSelected = IFX_CAN_MO_STAT_RTSEL_OFF,  /**< \brief Receive transmit selected status flag */
    IfxMultican_MsgObjStatusFlag_receiveEnable           = IFX_CAN_MO_STAT_RXEN_OFF,   /**< \brief Receive enable status flag */
    IfxMultican_MsgObjStatusFlag_transmitRequest         = IFX_CAN_MO_STAT_TXRQ_OFF,   /**< \brief Transmit request status flag */
    IfxMultican_MsgObjStatusFlag_transmitEnable0         = IFX_CAN_MO_STAT_TXEN0_OFF,  /**< \brief Transmit enable 0 status flag */
    IfxMultican_MsgObjStatusFlag_transmitEnable1         = IFX_CAN_MO_STAT_TXEN1_OFF,  /**< \brief Transmit enable 1 status flag */
    IfxMultican_MsgObjStatusFlag_messageDirection        = IFX_CAN_MO_STAT_DIR_OFF     /**< \brief Message direction status flag */
} IfxMultican_MsgObjStatusFlag;

/** \brief CAN priorities
 */
typedef enum
{
    IfxMultican_Priority_ListOrder = 1,  /**< \brief List order */
    IfxMultican_Priority_CAN_ID    = 2   /**< \brief CAN ID */
} IfxMultican_Priority;

/** \brief Enable/disable the sensitivity of the module to sleep signal\n
 * Definition in Ifx_CAN.CLC.B.EDIS
 */
typedef enum
{
    IfxMultican_SleepMode_enable  = 0, /**< \brief enables sleep mode */
    IfxMultican_SleepMode_disable = 1  /**< \brief disables sleep mode */
} IfxMultican_SleepMode;

/** \brief CAN API status definition
 */
typedef enum
{
    IfxMultican_Status_ok                = 0x00000000,
    IfxMultican_Status_notInitialised    = 0x00000001,
    IfxMultican_Status_wrongParam        = 0x00000002,
    IfxMultican_Status_wrongPin          = 0x00000004,
    IfxMultican_Status_busHeavy          = 0x00000008,
    IfxMultican_Status_busOff            = 0x00000010,
    IfxMultican_Status_notSentBusy       = 0x00000020,
    IfxMultican_Status_receiveEmpty      = 0x00000040,
    IfxMultican_Status_messageLost       = 0x00000080,
    IfxMultican_Status_newData           = 0x00000100,
    IfxMultican_Status_newDataButOneLost = IfxMultican_Status_messageLost | IfxMultican_Status_newData
} IfxMultican_Status;

/** \brief OCDS Suspend Control (OCDS.SUS)
 */
typedef enum
{
    IfxMultican_SuspendMode_none = 0,  /**< \brief No suspend */
    IfxMultican_SuspendMode_hard = 1,  /**< \brief Hard Suspend */
    IfxMultican_SuspendMode_soft = 2   /**< \brief Soft Suspend */
} IfxMultican_SuspendMode;

/** \} */

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \brief CAN message definition
 */
typedef struct
{
    uint32                     id;                /**< \brief CAN message ID */
    IfxMultican_DataLengthCode lengthCode;        /**< \brief CAN message data length code */
    uint32                     data[2];           /**< \brief CAN message data */
    boolean                    fastBitRate;       /**< \brief CAN FD fast bit rate enable/disable */
} IfxMultican_Message;

/** \brief Message object status bit-fields
 */
typedef union
{
    Ifx_CAN_MO_STAT_Bits B;
    unsigned int         U;
} IfxMultican_MsgObjStat;

/** \addtogroup IfxLld_Multican_Std_General
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief clears the message pending interrupt notification of a given list
 * \param mcan mcan Specifies the CAN module
 * \return None
 */
IFX_INLINE void IfxMultican_clearMessagePendingSeletor(Ifx_CAN *mcan);

/** \brief clears the message pending interrupt notification of a given list
 * \param mcan mcan Specifies the CAN module
 * \param list List number
 * \return None
 */
IFX_INLINE void IfxMultican_clearPendingMessageNotification(Ifx_CAN *mcan, uint16 list);

/** \brief Disables the module (sets the disable request)
 * \param mcan mcan Specifies the CAN module
 * \return None
 */
IFX_INLINE void IfxMultican_disableModule(Ifx_CAN *mcan);

/** \brief Disregards the sleep mode of the module
 * \param mcan mcan Specifies the CAN module
 * \return None
 */
IFX_INLINE void IfxMultican_disableSleepMode(Ifx_CAN *mcan);

/** \brief Enables the module (clears the disable request)
 * \param mcan mcan Specifies the CAN module
 * \return None
 */
IFX_INLINE void IfxMultican_enableModule(Ifx_CAN *mcan);

/** \brief Enables the sleep mode of the module
 * \param mcan mcan Specifies the CAN module
 * \return None
 */
IFX_INLINE void IfxMultican_enableSleepMode(Ifx_CAN *mcan);

/** \brief Returns the selected fractional divider mode
 * \param mcan mcan Specifies the CAN module
 * \return Divider mode
 */
IFX_INLINE uint16 IfxMultican_getFractionalDividerMode(Ifx_CAN *mcan);

/** \brief Returns the reload or addition value for the result.
 * \param mcan mcan Specifies the CAN module
 * \return Step Value
 */
IFX_INLINE uint16 IfxMultican_getFractionalDividerStepValue(Ifx_CAN *mcan);

/** \brief Returns the selected input clock source
 * \param mcan mcan Specifies the CAN module
 * \return Clock selection
 */
IFX_INLINE IfxMultican_ClockSelect IfxMultican_getInputClock(Ifx_CAN *mcan);

/** \brief Returns the status of module enabled or disabled
 * \param mcan mcan Specifies the CAN module
 * \return Status (TRUE / FALSE)
 */
IFX_INLINE boolean IfxMultican_isModuleEnabled(Ifx_CAN *mcan);

/** \brief sets the fractional divider mode
 * \param mcan mcan Specifies the CAN module
 * \param mode Divider mode
 * \return None
 */
IFX_INLINE void IfxMultican_setFractionalDividerMode(Ifx_CAN *mcan, uint16 mode);

/** \brief sets reload or addition value for the result.
 * \param mcan mcan Specifies the CAN module
 * \param stepValue Step Value
 * \return None
 */
IFX_INLINE void IfxMultican_setFractionalDividerStepValue(Ifx_CAN *mcan, uint16 stepValue);

/** \brief Sets the input clock source
 * \param mcan mcan Specifies the CAN module
 * \param clockSelect Clock selection
 * \return None
 */
IFX_INLINE void IfxMultican_setInputClock(Ifx_CAN *mcan, IfxMultican_ClockSelect clockSelect);

/** \brief clears the message pending interrupt notification of a given list
 * \param mcan mcan Specifies the CAN module
 * \param mask Message Index mask
 * \return None
 */
IFX_INLINE void IfxMultican_setMessageIndexMask(Ifx_CAN *mcan, uint32 mask);

/** \brief Sets the sensitivity of the module to sleep signal
 * \param can pointer to CAN registers
 * \param mode mode selection (enable / disable)
 * \return None
 */
IFX_INLINE void IfxMultican_setSleepMode(Ifx_CAN *can, IfxMultican_SleepMode mode);

/** \brief Wait until the list panel is ready
 * \param mcan mcan Specifies the CAN module
 * \return None
 */
IFX_INLINE void IfxMultican_waitListReady(Ifx_CAN *mcan);

/** \brief Returns the module's suspend state.
 * TRUE :if module is suspended.
 * FALSE:if module is not yet suspended.
 * \param mcan Pointer to MULTICAN module registers
 * \return Suspend status (TRUE / FALSE)
 */
IFX_INLINE boolean IfxMultican_isModuleSuspended(Ifx_CAN *mcan);

/** \brief Set the Module to Hard/Soft suspend mode.
 * Note: The api works only when the OCDS is enabled and in Supervisor Mode. When OCDS is disabled the OCS suspend control is ineffective.
 * \param mcan Pointer to MULTICAN module registers
 * \param mode Module suspend mode
 * \return None
 */
IFX_INLINE void IfxMultican_setSuspendMode(Ifx_CAN *mcan, IfxMultican_SuspendMode mode);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Calculates the best posible values and configures FBTR register
 * \param hwNode Pointer to CAN Node registers
 * \param moduleFreq Specifies the CAN module frequency
 * \param baudrate Specifies the node baud rate. Unit: baud
 * \param samplePoint Specifies the sample point. Range = [0, 10000] resp. [0%, 100%] of the total bit time.
 * \param synchJumpWidth synchJumpWidth Specifies the re-synchronization jump width.\n
 * Range = [0, 10000] resp. [0%, 100%] of the total bit time.
 * \return None
 */
IFX_EXTERN void IfxMultican_Node_setFastBitTiming(Ifx_CAN_N *hwNode, float32 moduleFreq, uint32 baudrate, uint16 samplePoint, uint16 synchJumpWidth);

/** \brief Calculates the best posible values and configures BTEVR register
 * \param hwNode Pointer to CAN Node registers
 * \param moduleFreq Specifies the CAN module frequency
 * \param baudrate Specifies the node baud rate. Unit: baud
 * \param samplePoint Specifies the sample point. Range = [0, 10000] resp. [0%, 100%] of the total bit time.
 * \param synchJumpWidth synchJumpWidth Specifies the re-synchronization jump width.\n
 * Range = [0, 10000] resp. [0%, 100%] of the total bit time.
 * \return None
 */
IFX_EXTERN void IfxMultican_Node_setNominalBitTiming(Ifx_CAN_N *hwNode, float32 moduleFreq, uint32 baudrate, uint16 samplePoint, uint16 synchJumpWidth);

/** \brief Reset the CAN module\n
 * Reset and disable the CAN module, inclusive message object and node registers.
 * \param mcan Specifies the CAN module
 * \return None
 */
IFX_EXTERN void IfxMultican_deinit(Ifx_CAN *mcan);

/** \brief resets Multican kernel
 * \param can pointer to CAN registers
 * \return None
 */
IFX_EXTERN void IfxMultican_resetModule(Ifx_CAN *can);

/** \brief Execute a command from the command panel
 * \param mcan Specifies the CAN module
 * \param cmd Specifies the command
 * \param arg2 Specifies the second argument
 * \param arg1 Specifies the first argument
 * \return None
 */
IFX_EXTERN void IfxMultican_setListCommand(Ifx_CAN *mcan, uint32 cmd, uint32 arg2, uint32 arg1);

/** \brief API to get the resource index of the CAN specified.
 * \return multican resource index
 */
IFX_EXTERN IfxMultican_Index IfxMultican_getIndex(Ifx_CAN *multican);

/**
 * \param multican Module index of the MULTICAN
 * \return MULTICAN module register address
 */
IFX_EXTERN Ifx_CAN *IfxMultican_getAddress(IfxMultican_Index multican);

/** \} */

/** \addtogroup IfxLld_Multican_Std_Node
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Activate the CAN Node. Participate in the CAN bus activities
 * \param hwNode Pointer to CAN Node registers
 * \return None
 */
IFX_INLINE void IfxMultican_Node_activate(Ifx_CAN_N *hwNode);

/** \brief Deactivate the CAN Node. Take out from participation in the CAN bus activities
 * \param hwNode Pointer to CAN Node registers
 * \return None
 */
IFX_INLINE void IfxMultican_Node_deactivate(Ifx_CAN_N *hwNode);

/** \brief Disables the configuration changes for the Bit Timing Register, the Port Control Register, and the Error Counter Register of a CAN Node.
 * \param hwNode Pointer to CAN Node registers
 * \return None
 */
IFX_INLINE void IfxMultican_Node_disableConfigurationChange(Ifx_CAN_N *hwNode);

/** \brief Enables the configuration changes for the Bit Timing Register, the Port Control Register, and the Error Counter Register of a CAN Node.
 * \param hwNode Pointer to CAN Node registers
 * \return None
 */
IFX_INLINE void IfxMultican_Node_enableConfigurationChange(Ifx_CAN_N *hwNode);

/** \brief Returns the base address to a given CAN node number
 * \param mcan Specifies the CAN module
 * \param node Specifies the CAN node
 * \return base pointer to CAN node
 */
IFX_INLINE Ifx_CAN_N *IfxMultican_Node_getPointer(Ifx_CAN *mcan, IfxMultican_NodeId node);

/** \brief Resets the control register of CAN Node x.
 * \param hwNode Pointer to CAN Node registers
 * \return None
 */
IFX_INLINE void IfxMultican_Node_resetControlRegister(Ifx_CAN_N *hwNode);

/** \brief Resets the error counters of CAN Node x.
 * \param hwNode Pointer to CAN Node registers
 * \return None
 */
IFX_INLINE void IfxMultican_Node_resetErrorCounters(Ifx_CAN_N *hwNode);

/** \brief Resets the interrupt pointers of CAN Node x.
 * \param hwNode Pointer to CAN Node registers
 * \return None
 */
IFX_INLINE void IfxMultican_Node_resetInterruptPointers(Ifx_CAN_N *hwNode);

/** \brief Enables / Disables the alert interrupt of CAN node x.
 * \param hwNode Pointer to CAN Node registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setAlertInterrupt(Ifx_CAN_N *hwNode, boolean enabled);

/** \brief Selects the interrupt output line INT_Om
 * (m = 0-15) for an alert interrupt of CAN Node x.
 * \param hwNode Pointer to CAN Node registers
 * \param srcId Service request ID
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setAlertInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId);

/** \brief Enables / Disables the analyzer mode of CAN node x.
 * \param hwNode Pointer to CAN Node registers
 * \param mode Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setAnalyzerMode(Ifx_CAN_N *hwNode, boolean mode);

/** \brief Determines the threshold value (warning level, default 96) to be reached\n
 * in order to set the corresponding error warning bit EWRN.
 * \param hwNode Pointer to CAN Node registers
 * \param level Error warning level
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setErrorWarningLevel(Ifx_CAN_N *hwNode, uint8 level);

/** \brief Enables / Disables the flexible data rate of CAN node x.
 * \param hwNode Pointer to CAN Node registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setFastNode(Ifx_CAN_N *hwNode, boolean enabled);

/** \brief Enables / Disables the CAN frame counter overflow interrupt of CAN node x.
 * \param hwNode Pointer to CAN Node registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setFrameCounterInterrupt(Ifx_CAN_N *hwNode, boolean enabled);

/** \brief Selects the interrupt output line INT_Om
 * (m = 0-15) for a frame counter overflow interrupt of CAN Node x.
 * \param hwNode Pointer to CAN Node registers
 * \param srcId Service request ID
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setFrameCounterInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId);

/** \brief Sets the operation mode of the frame counter of the CAN Node x
 * \param hwNode Pointer to CAN Node registers
 * \param mode Determines the operation mode of the frame counter
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setFrameCounterMode(Ifx_CAN_N *hwNode, IfxMultican_FrameCounterMode mode);

/** \brief Enables / Disables the last error code interrupt of CAN node x. \n
 * This interrupt is generated with each hardware update of bit field NSRx.LEC with LEC > 0 (CAN protocol error).
 * \param hwNode Pointer to CAN Node registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setLastErrorCodeInterrupt(Ifx_CAN_N *hwNode, boolean enabled);

/** \brief Selects the interrupt output line INT_Om
 * (m = 0-15) for an LEC interrupt of CAN Node x.
 * \param hwNode Pointer to CAN Node registers
 * \param srcId Service request ID
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setLastErrorCodeInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId);

/** \brief Enables / Disables the loopback mode of CAN node x.
 * \param hwNode Pointer to CAN Node registers
 * \param mode Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setLoopBackMode(Ifx_CAN_N *hwNode, boolean mode);

/** \brief Sets the value of the receive error counter of CAN node x.
 * \param hwNode Pointer to CAN Node registers
 * \param value Receive error counter value
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setReceiveErrorCounter(Ifx_CAN_N *hwNode, uint8 value);

/** \brief Selects the interrupt output line INT_Om
 * (m = 0-15) for a timer event interrupt of CAN Node x.
 * \param hwNode Pointer to CAN Node registers
 * \param srcId Service request ID
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setTimerEventInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId);

/** \brief Enables / Disables the transceiver delay compensation of CAN node x.
 * \param hwNode Pointer to CAN Node registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setTransceiverDelayCompensation(Ifx_CAN_N *hwNode, boolean enabled);

/** \brief Sets transceiver delay ompensation offset of CAN node x.
 * \param hwNode Pointer to CAN Node registers
 * \param value transceiver delay ompensation offset that is added to the measured transceiver delay. Range = [0, 15]
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setTransceiverDelayCompensationOffset(Ifx_CAN_N *hwNode, uint16 value);

/** \brief Enables / Disables the transfer interrupt of CAN node x. \n
 * This interrupt is generated after the successful reception or transmission of a CAN frame in node x
 * \param hwNode Pointer to CAN Node registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setTransferInterrupt(Ifx_CAN_N *hwNode, boolean enabled);

/** \brief Selects the interrupt output line INT_Om
 * (m = 0-15) for a transfer OK interrupt of CAN Node x.
 * \param hwNode Pointer to CAN Node registers
 * \param srcId Service request ID
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setTransferInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId);

/** \brief Sets the value of the transmit error counter of CAN node x.
 * \param hwNode Pointer to CAN Node registers
 * \param value Transmit error counter value
 * \return None
 */
IFX_INLINE void IfxMultican_Node_setTransmitErrorCounter(Ifx_CAN_N *hwNode, uint8 value);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Reset the CAN node
 * \param hwNode Pointer to CAN Node registers
 * \return None
 */
IFX_EXTERN void IfxMultican_Node_deinit(Ifx_CAN_N *hwNode);

/** \brief Select and initialise the CAN node receive pin
 * \param hwNode Pointer to CAN Node registers
 * \param rxd Rx pin
 * \param mode Input mode
 * \return TRUE: Returns TRUE if the operation was successful\n
 * FALSE: Returns FALSE if the operation was errorneous
 */
IFX_EXTERN boolean IfxMultican_Node_initRxPin(Ifx_CAN_N *hwNode, IfxMultican_Rxd_In *rxd, IfxPort_InputMode mode, IfxPort_PadDriver padDriver);

/** \brief Select and initialise the CAN node transmit pin
 * \param hwNode Pointer to CAN Node registers
 * \param txd Tx pin
 * \param mode Output mode
 * \return TRUE: Returns TRUE if the operation was successful\n
 * FALSE: Returns FALSE if the operation was errorneous
 */
IFX_EXTERN boolean IfxMultican_Node_initTxPin(Ifx_CAN_N *hwNode, IfxMultican_Txd_Out *txd, IfxPort_OutputMode mode, IfxPort_PadDriver padDriver);

/** \brief Recovers the CAN node from bus off
 * \param hwNode Pointer to CAN Node registers
 * \return Status
 */
IFX_EXTERN IfxMultican_Status IfxMultican_Node_recoverBusOff(Ifx_CAN_N *hwNode);

/** \brief Calculates the best posible values and configures BTR register
 * \param hwNode Pointer to CAN Node registers
 * \param moduleFreq Specifies the CAN module frequency
 * \param baudrate Specifies the node baud rate. Unit: baud
 * \param samplePoint Specifies the sample point. Range = [0, 10000] resp. [0%, 100%] of the total bit time.
 * \param synchJumpWidth synchJumpWidth Specifies the re-synchronization jump width.\n
 * Range = [0, 10000] resp. [0%, 100%] of the total bit time.
 * \return None
 */
IFX_EXTERN void IfxMultican_Node_setBitTiming(Ifx_CAN_N *hwNode, float32 moduleFreq, uint32 baudrate, uint16 samplePoint, uint16 synchJumpWidth);

/** \brief Returns the CAN node timing
 * \param moduleFreq Specifies the CAN module frequency
 * \param btr BTR
 * \param baudrate Baudrate
 * \param samplePoint Sample point
 * \param synchJumpWidth Sync Jump Width
 * \return None
 */
IFX_EXTERN void IfxMultican_calcTimingFromBTR(float32 moduleFreq, uint32 btr, uint32 *baudrate, uint16 *samplePoint, uint16 *synchJumpWidth);

/** \} */

/** \addtogroup IfxLld_Multican_Std_Message
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Initializes a CAN message
 * \param msg The message which should be initialized
 * \param id The message ID
 * \param dataLow The lower part of the 64bit data value
 * \param dataHigh The upper part of the 64bit data value
 * \param lengthCode number of bytes (data length code) which should be transmitted (0..8)
 * \return None
 */
IFX_INLINE void IfxMultican_Message_init(IfxMultican_Message *msg, uint32 id, uint32 dataLow, uint32 dataHigh, IfxMultican_DataLengthCode lengthCode);

/** \brief Initializes a CAN message long frame
 * \param msg The message which should be initialized
 * \param id The message ID
 * \param lengthCode number of bytes (data length code) which should be transmitted (0..8)
 * \param fastBitRate Fast bit rate (FCR.BRS) enable/ disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_Message_longFrameInit(IfxMultican_Message *msg, uint32 id, IfxMultican_DataLengthCode lengthCode, boolean fastBitRate);

/** \} */

/** \addtogroup IfxLld_Multican_Std_Message_Objects
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Sets priority class of message object
 * \param hwObj Pointer to CAN message object registers
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_clearDataRegisters(Ifx_CAN_MO *hwObj);

/** \brief Clears the FIFO/GateWay pointers of a message object
 * \param hwObj Pointer to CAN message object registers
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_clearFifoGatewayPointers(Ifx_CAN_MO *hwObj);

/** \brief Clear the RX pending flag of a message object
 * \param hwObj Pointer to CAN message object registers
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_clearRxPending(Ifx_CAN_MO *hwObj);

/** \brief Clear the TX pending flag of a message object
 * \param hwObj Pointer to CAN message object registers
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_clearTxPending(Ifx_CAN_MO *hwObj);

/** \brief Gets bottom object pointer of the base message object
 * \param hwObj Pointer to CAN message object registers
 * \return Bottom message object number
 */
IFX_INLINE IfxMultican_MsgObjId IfxMultican_MsgObj_getBottomObjectPointer(Ifx_CAN_MO *hwObj);

/** \brief Gets data length code of a message object
 * \param hwObj Pointer to CAN message object registers
 * \return CAN frame data length code
 */
IFX_INLINE IfxMultican_DataLengthCode IfxMultican_MsgObj_getDataLengthCode(Ifx_CAN_MO *hwObj);

/** \brief Gets message identifier of message object
 * \param hwObj Pointer to CAN message object registers
 * \return messageId
 */
IFX_INLINE uint32 IfxMultican_MsgObj_getMessageId(Ifx_CAN_MO *hwObj);

/** \brief Returns next object pointer (PNEXT) of the current message object
 * \param hwObj Pointer to CAN message object registers
 * \return Next message object number
 */
IFX_INLINE IfxMultican_MsgObjId IfxMultican_MsgObj_getNextObjectPointer(Ifx_CAN_MO *hwObj);

/** \brief Get base address of a message object register
 * \param mcan Specifies the CAN module
 * \param msgObjId Specifies the message object index. Range = [0, \ref IFXMULTICAN_NUM_MESSAGE_OBJECTS - 1]
 * \return Pointer to Message Object registers
 */
IFX_INLINE Ifx_CAN_MO *IfxMultican_MsgObj_getPointer(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId);

/** \brief Get the message object status
 * \param hwObj Pointer to CAN message object registers
 * \return Extended frame: True
 * Standard frame: False
 */
IFX_INLINE boolean IfxMultican_MsgObj_isExtendedFrame(Ifx_CAN_MO *hwObj);

/** \brief Returns the RX pending flag of a message object.
 * \param hwObj Pointer to CAN message object registers
 * \return TRUE of the RX pending flag of a message object is set
 */
IFX_INLINE boolean IfxMultican_MsgObj_isRxPending(Ifx_CAN_MO *hwObj);

/** \brief Returns the TX Request flag of a message object.
 * \param hwObj Pointer to CAN message object registers
 * \return TRUE of the TX Request flag of a message object is set
 */
IFX_INLINE boolean IfxMultican_MsgObj_isTransmitRequested(Ifx_CAN_MO *hwObj);

/** \brief Returns the TX pending flag of a message object.
 * \param hwObj Pointer to CAN message object registers
 * \return TRUE of the TX pending flag of a message object is set
 */
IFX_INLINE boolean IfxMultican_MsgObj_isTxPending(Ifx_CAN_MO *hwObj);

/** \brief Sets acceptance mask for the message identifier
 * \param hwObj Pointer to CAN message object registers
 * \param mask Acceptance Mask for the message identifier
 * \param extendedFrame Extended frame enabled / disabled
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setAcceptanceMask(Ifx_CAN_MO *hwObj, uint32 mask, boolean extendedFrame);

/** \brief Enable / Disable bit rate switch of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setBitRateSwitch(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Sets bottom object pointer of the base message object
 * \param hwObj Pointer to CAN message object registers
 * \param objNumber Bottom message object number
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setBottomObjectPointer(Ifx_CAN_MO *hwObj, sint32 objNumber);

/** \brief Sets bottom current pointer of the base message object
 * \param hwObj Pointer to CAN message object registers
 * \param objNumber Current message object number
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setCurrentObjectPointer(Ifx_CAN_MO *hwObj, sint32 objNumber);

/** \brief Enable / Disable data copy of a gateway source message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setDataCopy(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Sets data length code of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param code CAN frame data length code
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setDataLengthCode(Ifx_CAN_MO *hwObj, IfxMultican_DataLengthCode code);

/** \brief Enable / Disable data length code copy of a gateway source message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setDataLengthCodeCopy(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Enable / Disable extended data length of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setExtendedDataLength(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Enable / Disable gateway data frame send of a gateway source message object
 * which in turn sets the TXRQ of the gateway deatination object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setGatewayDataFrameSend(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Enable / Disable identifier copy of a gateway source message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setIdentifierCopy(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Sets identifier extension of message object
 * \param hwObj Pointer to CAN message object registers
 * \param extension Acceptance Mask for the message IDE bit
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setIdentifierExtension(Ifx_CAN_MO *hwObj, boolean extension);

/** \brief Sets acceptance mask for the message IDE bit
 * \param hwObj Pointer to CAN message object registers
 * \param matchingId Acceptance Mask for the message IDE bit
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setMatchingId(Ifx_CAN_MO *hwObj, boolean matchingId);

/** \brief Sets message identifier of message object
 * \param hwObj Pointer to CAN message object registers
 * \param messageId CAN Identifier of message object
 * \param extendedFrame Extended frame enabled / disabled
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setMessageId(Ifx_CAN_MO *hwObj, uint32 messageId, boolean extendedFrame);

/** \brief Sets the message mode of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param mode CAN Message Object Mode
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setMessageMode(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjMode mode);

/** \brief Sets message pending number that selects the bit position of the bit in the Message Pending Register\n
 * that is set upon a message object n receive/transmit interrupt
 * \param hwObj Pointer to CAN message object registers
 * \param messageNumber Message pending number
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setMessagePendingNumber(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjId messageNumber);

/** \brief Enable / Disable overflow interrupt of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setOverflowInterrupt(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Sets priority class of message object
 * \param hwObj Pointer to CAN message object registers
 * \param priority One of the priority classes 0, 1, 2, 3 to message object n
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setPriorityClass(Ifx_CAN_MO *hwObj, IfxMultican_Priority priority);

/** \brief Enable / Disable receive interrupt of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setReceiveInterrupt(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Sets receive interrupt node pointer of message object
 * \param hwObj Pointer to CAN message object registers
 * \param srcId Service request ID
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setReceiveInterruptNodePointer(Ifx_CAN_MO *hwObj, IfxMultican_SrcId srcId);

/** \brief Enable / Disable transmit object remote monitoring of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setRemoteMonitoring(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Sets bottom object select pointer of the base message object
 * \param hwObj Pointer to CAN message object registers
 * \param objNumber Select message object number
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setSelectObjectPointer(Ifx_CAN_MO *hwObj, sint32 objNumber);

/** \brief Enable / Disable single data transfer of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setSingleDataTransfer(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Enable / Disable single transmit trial of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setSingleTransmitTrial(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Sets top object pointer of the base message object
 * \param hwObj Pointer to CAN message object registers
 * \param objNumber Top message object number
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setTopObjectPointer(Ifx_CAN_MO *hwObj, sint32 objNumber);

/** \brief Enable / Disable transmit interrupt of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param enabled Enable / disable choice
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setTransmitInterrupt(Ifx_CAN_MO *hwObj, boolean enabled);

/** \brief Sets transmit interrupt node pointer of message object
 * \param hwObj Pointer to CAN message object registers
 * \param srcId Service request ID
 * \return None
 */
IFX_INLINE void IfxMultican_MsgObj_setTransmitInterruptNodePointer(Ifx_CAN_MO *hwObj, IfxMultican_SrcId srcId);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Cancel pending TX request by invalidating the request, only when frame transmission has not been started.
 * \param hwObj Pointer to CAN message object registers
 * \return TRUE if cancellation was successfully executed
 */
IFX_EXTERN boolean IfxMultican_MsgObj_cancelSend(Ifx_CAN_MO *hwObj);

/** \brief Clears the selected status flag of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param flag Message Object status flag
 * \return None
 */
IFX_EXTERN void IfxMultican_MsgObj_clearStatusFlag(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjStatusFlag flag);

/** \brief Reset the message object\n
 * Append the message object to the end of idle list and reset message object registers
 * \param mcan Specifies the CAN module
 * \param msgObjId Specifies the message object index. Range = [0, \ref IFXMULTICAN_NUM_MESSAGE_OBJECTS - 1]
 * \return None
 */
IFX_EXTERN void IfxMultican_MsgObj_deinit(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId);

/** \brief Get message object ID which has TX/RX pending flag from a message object group
 * \param mcan Specifies the CAN module
 * \param msgObjGroup Message object group
 * \return Message object index
 */
IFX_EXTERN IfxMultican_MsgObjId IfxMultican_MsgObj_getPendingId(Ifx_CAN *mcan, IfxMultican_MsgObjGroup msgObjGroup);

/** \brief Get the message object status
 * \param hwObj Pointer to CAN message object registers
 * \return \ref IfxMultican_MsgObjStat bitfield
 */
IFX_EXTERN IfxMultican_MsgObjStat IfxMultican_MsgObj_getStatus(Ifx_CAN_MO *hwObj);

/** \brief Gets the status of the selected status flag of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param flag Message Object status flag
 * \return Status (TRUE / FALSE)
 */
IFX_EXTERN boolean IfxMultican_MsgObj_getStatusFlag(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjStatusFlag flag);

/** \brief Read a received CAN long frame
 * \param mcan Specifies the CAN module
 * \param msgObjId Specifies the message object index. Range = [0, \ref IFXMULTICAN_NUM_MESSAGE_OBJECTS - 1]
 * \param msg The message which should be initialized
 * \param data Pointer to data (in words)
 * \return IfxMultican_Status_newData: if the operation was successful\n
 * IfxMultican_Status_newDataButMessageLost: if the one message lost and last new data is retrieved successfully\n
 * IfxMultican_Status_messageLost: if the message lost and new data is not yet ready\n
 * IfxMultican_Status_receiveEmpty: if no message is been received
 */
IFX_EXTERN IfxMultican_Status IfxMultican_MsgObj_readLongFrame(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId, IfxMultican_Message *msg, uint32 *data);

/** \brief Read a received CAN message
 * \param hwObj Pointer to CAN message object registers
 * \param msg This parameter is filled in by the function with the received message. Also when reading is not successful.
 * \return IfxMultican_Status_newData: if the operation was successful\n
 * IfxMultican_Status_newDataButMessageLost: if the one message lost and last new data is retrieved successfully\n
 * IfxMultican_Status_messageLost: if the message lost and new data is not yet ready\n
 * IfxMultican_Status_receiveEmpty: if no message is been received
 */
IFX_EXTERN IfxMultican_Status IfxMultican_MsgObj_readMessage(Ifx_CAN_MO *hwObj, IfxMultican_Message *msg);

/** \brief Send a CAN Long frame message
 * \param mcan Specifies the CAN module
 * \param msgObjId Specifies the message object index. Range = [0, \ref IFXMULTICAN_NUM_MESSAGE_OBJECTS - 1]
 * \param msg The message which should be initialized
 * \param data Pointer to data (in words)
 * \return IfxMultican_Status_ok: if the operation was successful
 * IfxMultican_Status_notSentBusy: if the operation was unsuccessful due to hardware is busy
 */
IFX_EXTERN IfxMultican_Status IfxMultican_MsgObj_sendLongFrame(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId, IfxMultican_Message *msg, uint32 *data);

/** \brief Send a CAN message
 * \param hwObj Pointer to CAN message object registers
 * \param msg Specifies the message to be send
 * \return IfxMultican_Status_ok: if the operation was successful
 * IfxMultican_Status_notSentBusy: if the operation was unsuccessful due to hardware is busy
 */
IFX_EXTERN IfxMultican_Status IfxMultican_MsgObj_sendMessage(Ifx_CAN_MO *hwObj, const IfxMultican_Message *msg);

/** \brief Set message object filter
 * \param hwObj Pointer to CAN message object registers
 * \param extend TRUE/FALSE : extended ID
 * \param id ID
 * \param accMask acceptance mask
 * \return None
 */
IFX_EXTERN void IfxMultican_MsgObj_setFilter(Ifx_CAN_MO *hwObj, boolean extend, uint32 id, uint32 accMask);

/** \brief Sets the selected status flag of a message object
 * \param hwObj Pointer to CAN message object registers
 * \param flag Message Object status flag
 * \return None
 */
IFX_EXTERN void IfxMultican_MsgObj_setStatusFlag(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjStatusFlag flag);

/** \} */

/** \addtogroup IfxLld_Multican_Std_Interrupts
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Get the interrupt source register
 * \param mcan Specifies the CAN module
 * \param srcId Specifies the service request ID
 * \return Address of the interrupt source register\n
 */
IFX_EXTERN volatile Ifx_SRC_SRCR *IfxMultican_getSrcPointer(Ifx_CAN *mcan, IfxMultican_SrcId srcId);

/** \} */

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE void IfxMultican_Message_init(IfxMultican_Message *msg, uint32 id, uint32 dataLow, uint32 dataHigh, IfxMultican_DataLengthCode lengthCode)
{
    msg->id          = id;
    msg->data[0]     = dataLow;
    msg->data[1]     = dataHigh;
    msg->lengthCode  = lengthCode;

    msg->fastBitRate = FALSE;
}


IFX_INLINE void IfxMultican_Message_longFrameInit(IfxMultican_Message *msg, uint32 id, IfxMultican_DataLengthCode lengthCode, boolean fastBitRate)
{
    msg->id          = id;
    msg->data[0]     = 0; /* not being used */
    msg->data[1]     = 0; /* not being used */
    msg->lengthCode  = lengthCode;
    msg->fastBitRate = fastBitRate;
}


IFX_INLINE void IfxMultican_MsgObj_clearDataRegisters(Ifx_CAN_MO *hwObj)
{
    hwObj->DATAL.U = 0;
    hwObj->DATAH.U = 0;
}


IFX_INLINE void IfxMultican_MsgObj_clearFifoGatewayPointers(Ifx_CAN_MO *hwObj)
{
    hwObj->FGPR.U = 0x0000000U;
}


IFX_INLINE void IfxMultican_MsgObj_clearRxPending(Ifx_CAN_MO *hwObj)
{
    IfxMultican_MsgObj_clearStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_receivePending);
}


IFX_INLINE void IfxMultican_MsgObj_clearTxPending(Ifx_CAN_MO *hwObj)
{
    IfxMultican_MsgObj_clearStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_transmitPending);
}


IFX_INLINE IfxMultican_MsgObjId IfxMultican_MsgObj_getBottomObjectPointer(Ifx_CAN_MO *hwObj)
{
    return (IfxMultican_MsgObjId)(hwObj->FGPR.B.BOT);
}


IFX_INLINE IfxMultican_DataLengthCode IfxMultican_MsgObj_getDataLengthCode(Ifx_CAN_MO *hwObj)
{
    return (IfxMultican_DataLengthCode)(hwObj->FCR.B.DLC);
}


IFX_INLINE uint32 IfxMultican_MsgObj_getMessageId(Ifx_CAN_MO *hwObj)
{
    Ifx_CAN_MO_AR ar;
    ar.U = hwObj->AR.U;
    return ar.B.ID >> ((ar.B.IDE != 0) ? 0 : 18);
}


IFX_INLINE IfxMultican_MsgObjId IfxMultican_MsgObj_getNextObjectPointer(Ifx_CAN_MO *hwObj)
{
    return (IfxMultican_MsgObjId)(hwObj->STAT.B.PNEXT);
}


IFX_INLINE Ifx_CAN_MO *IfxMultican_MsgObj_getPointer(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId)
{
    return &(mcan->MO[msgObjId]);
}


IFX_INLINE boolean IfxMultican_MsgObj_isExtendedFrame(Ifx_CAN_MO *hwObj)
{
    return hwObj->AR.B.IDE != 0;
}


IFX_INLINE boolean IfxMultican_MsgObj_isRxPending(Ifx_CAN_MO *hwObj)
{
    IfxMultican_MsgObjStat msgStatus = IfxMultican_MsgObj_getStatus(hwObj);
    return msgStatus.B.RXPND ? TRUE : FALSE;
}


IFX_INLINE boolean IfxMultican_MsgObj_isTransmitRequested(Ifx_CAN_MO *hwObj)
{
    IfxMultican_MsgObjStat msgStatus = IfxMultican_MsgObj_getStatus(hwObj);
    return msgStatus.B.TXRQ ? TRUE : FALSE;
}


IFX_INLINE boolean IfxMultican_MsgObj_isTxPending(Ifx_CAN_MO *hwObj)
{
    IfxMultican_MsgObjStat msgStatus = IfxMultican_MsgObj_getStatus(hwObj);
    return msgStatus.B.TXPND ? TRUE : FALSE;
}


IFX_INLINE void IfxMultican_MsgObj_setAcceptanceMask(Ifx_CAN_MO *hwObj, uint32 mask, boolean extendedFrame)
{
    hwObj->AMR.B.AM = mask << ((extendedFrame != 0) ? 0 : 18);
}


IFX_INLINE void IfxMultican_MsgObj_setBitRateSwitch(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.BRS = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setBottomObjectPointer(Ifx_CAN_MO *hwObj, sint32 objNumber)
{
    hwObj->FGPR.B.BOT = objNumber;
}


IFX_INLINE void IfxMultican_MsgObj_setCurrentObjectPointer(Ifx_CAN_MO *hwObj, sint32 objNumber)
{
    hwObj->FGPR.B.CUR = objNumber;
}


IFX_INLINE void IfxMultican_MsgObj_setDataCopy(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.DATC = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setDataLengthCode(Ifx_CAN_MO *hwObj, IfxMultican_DataLengthCode code)
{
    hwObj->FCR.B.DLC = code;
}


IFX_INLINE void IfxMultican_MsgObj_setDataLengthCodeCopy(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.DLCC = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setExtendedDataLength(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.FDF = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setGatewayDataFrameSend(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.GDFS = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setIdentifierCopy(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.IDC = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setIdentifierExtension(Ifx_CAN_MO *hwObj, boolean extension)
{
    hwObj->AR.B.IDE = extension;
}


IFX_INLINE void IfxMultican_MsgObj_setMatchingId(Ifx_CAN_MO *hwObj, boolean matchingId)
{
    hwObj->AMR.B.MIDE = matchingId;
}


IFX_INLINE void IfxMultican_MsgObj_setMessageId(Ifx_CAN_MO *hwObj, uint32 messageId, boolean extendedFrame)
{
    hwObj->AR.B.ID = messageId << ((extendedFrame != 0) ? 0 : 18);
}


IFX_INLINE void IfxMultican_MsgObj_setMessageMode(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjMode mode)
{
    hwObj->FCR.B.MMC = mode;
}


IFX_INLINE void IfxMultican_MsgObj_setMessagePendingNumber(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjId messageNumber)
{
    hwObj->IPR.B.MPN = messageNumber;
}


IFX_INLINE void IfxMultican_MsgObj_setOverflowInterrupt(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.OVIE = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setPriorityClass(Ifx_CAN_MO *hwObj, IfxMultican_Priority priority)
{
    hwObj->AR.B.PRI = priority;
}


IFX_INLINE void IfxMultican_MsgObj_setReceiveInterrupt(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.RXIE = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setReceiveInterruptNodePointer(Ifx_CAN_MO *hwObj, IfxMultican_SrcId srcId)
{
    hwObj->IPR.B.RXINP = srcId;
}


IFX_INLINE void IfxMultican_MsgObj_setRemoteMonitoring(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.RMM = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setSelectObjectPointer(Ifx_CAN_MO *hwObj, sint32 objNumber)
{
    hwObj->FGPR.B.SEL = objNumber;
}


IFX_INLINE void IfxMultican_MsgObj_setSingleDataTransfer(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.SDT = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setSingleTransmitTrial(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.STT = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setTopObjectPointer(Ifx_CAN_MO *hwObj, sint32 objNumber)
{
    hwObj->FGPR.B.TOP = objNumber;
}


IFX_INLINE void IfxMultican_MsgObj_setTransmitInterrupt(Ifx_CAN_MO *hwObj, boolean enabled)
{
    hwObj->FCR.B.TXIE = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_MsgObj_setTransmitInterruptNodePointer(Ifx_CAN_MO *hwObj, IfxMultican_SrcId srcId)
{
    hwObj->IPR.B.TXINP = srcId;
}


IFX_INLINE void IfxMultican_Node_activate(Ifx_CAN_N *hwNode)
{
    hwNode->CR.B.INIT = 0;
}


IFX_INLINE void IfxMultican_Node_deactivate(Ifx_CAN_N *hwNode)
{
    hwNode->CR.B.INIT = 1;
}


IFX_INLINE void IfxMultican_Node_disableConfigurationChange(Ifx_CAN_N *hwNode)
{
    hwNode->CR.B.CCE = 0U;
}


IFX_INLINE void IfxMultican_Node_enableConfigurationChange(Ifx_CAN_N *hwNode)
{
    hwNode->CR.B.CCE = 1U;
}


IFX_INLINE Ifx_CAN_N *IfxMultican_Node_getPointer(Ifx_CAN *mcan, IfxMultican_NodeId node)
{
    return &(mcan->N[node]);
}


IFX_INLINE void IfxMultican_Node_resetControlRegister(Ifx_CAN_N *hwNode)
{
    hwNode->CR.U = 0x00000041U;
}


IFX_INLINE void IfxMultican_Node_resetErrorCounters(Ifx_CAN_N *hwNode)
{
    hwNode->ECNT.U = 0x00600000U;
}


IFX_INLINE void IfxMultican_Node_resetInterruptPointers(Ifx_CAN_N *hwNode)
{
    hwNode->IPR.U = 0x00000000U;
}


IFX_INLINE void IfxMultican_Node_setAlertInterrupt(Ifx_CAN_N *hwNode, boolean enabled)
{
    hwNode->CR.B.ALIE = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_Node_setAlertInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId)
{
    hwNode->IPR.B.ALINP = srcId;
}


IFX_INLINE void IfxMultican_Node_setAnalyzerMode(Ifx_CAN_N *hwNode, boolean mode)
{
    hwNode->CR.B.CALM = mode != FALSE;
}


IFX_INLINE void IfxMultican_Node_setErrorWarningLevel(Ifx_CAN_N *hwNode, uint8 level)
{
    hwNode->ECNT.B.EWRNLVL = level;
}


IFX_INLINE void IfxMultican_Node_setFastNode(Ifx_CAN_N *hwNode, boolean enabled)
{
    hwNode->CR.B.INIT = 1;
    hwNode->CR.B.FDEN = enabled ? 1 : 0;
    hwNode->CR.B.INIT = 0;
}


IFX_INLINE void IfxMultican_Node_setFrameCounterInterrupt(Ifx_CAN_N *hwNode, boolean enabled)
{
    hwNode->FCR.B.CFCIE = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_Node_setFrameCounterInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId)
{
    hwNode->IPR.B.CFCINP = srcId;
}


IFX_INLINE void IfxMultican_Node_setFrameCounterMode(Ifx_CAN_N *hwNode, IfxMultican_FrameCounterMode mode)
{
    hwNode->FCR.B.CFMOD = mode;
}


IFX_INLINE void IfxMultican_Node_setLastErrorCodeInterrupt(Ifx_CAN_N *hwNode, boolean enabled)
{
    hwNode->CR.B.LECIE = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_Node_setLastErrorCodeInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId)
{
    hwNode->IPR.B.LECINP = srcId;
}


IFX_INLINE void IfxMultican_Node_setLoopBackMode(Ifx_CAN_N *hwNode, boolean mode)
{
    hwNode->PCR.B.LBM = mode != FALSE;
}


IFX_INLINE void IfxMultican_Node_setReceiveErrorCounter(Ifx_CAN_N *hwNode, uint8 value)
{
    hwNode->ECNT.B.REC = value;
}


IFX_INLINE void IfxMultican_Node_setTimerEventInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId)
{
    hwNode->IPR.B.TEINP = srcId;
}


IFX_INLINE void IfxMultican_Node_setTransceiverDelayCompensation(Ifx_CAN_N *hwNode, boolean enabled)
{
    hwNode->TDCR.B.TDC = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_Node_setTransceiverDelayCompensationOffset(Ifx_CAN_N *hwNode, uint16 value)
{
    hwNode->TDCR.B.TDCO = value;
}


IFX_INLINE void IfxMultican_Node_setTransferInterrupt(Ifx_CAN_N *hwNode, boolean enabled)
{
    hwNode->CR.B.TRIE = enabled ? 1 : 0;
}


IFX_INLINE void IfxMultican_Node_setTransferInterruptPointer(Ifx_CAN_N *hwNode, IfxMultican_SrcId srcId)
{
    hwNode->IPR.B.TRINP = srcId;
}


IFX_INLINE void IfxMultican_Node_setTransmitErrorCounter(Ifx_CAN_N *hwNode, uint8 value)
{
    hwNode->ECNT.B.TEC = value;
}


IFX_INLINE void IfxMultican_clearMessagePendingSeletor(Ifx_CAN *mcan)
{
    mcan->MCR.B.MPSEL = 0x0U;
}


IFX_INLINE void IfxMultican_clearPendingMessageNotification(Ifx_CAN *mcan, uint16 list)
{
    mcan->MSPND[list].U = 0x0;
}


IFX_INLINE void IfxMultican_disableModule(Ifx_CAN *mcan)
{
    mcan->CLC.B.DISR = 1U;
}


IFX_INLINE void IfxMultican_disableSleepMode(Ifx_CAN *mcan)
{
    mcan->CLC.B.EDIS = 1U;
}


IFX_INLINE void IfxMultican_enableModule(Ifx_CAN *mcan)
{
    mcan->CLC.B.DISR = 0U;
}


IFX_INLINE void IfxMultican_enableSleepMode(Ifx_CAN *mcan)
{
    mcan->CLC.B.EDIS = 0U;
}


IFX_INLINE uint16 IfxMultican_getFractionalDividerMode(Ifx_CAN *mcan)
{
    return mcan->FDR.B.DM;
}


IFX_INLINE uint16 IfxMultican_getFractionalDividerStepValue(Ifx_CAN *mcan)
{
    return mcan->FDR.B.STEP;
}


IFX_INLINE IfxMultican_ClockSelect IfxMultican_getInputClock(Ifx_CAN *mcan)
{
    return (IfxMultican_ClockSelect)mcan->MCR.B.CLKSEL;
}


IFX_INLINE boolean IfxMultican_isModuleEnabled(Ifx_CAN *mcan)
{
    return mcan->CLC.B.DISS == 0;
}


IFX_INLINE void IfxMultican_setFractionalDividerMode(Ifx_CAN *mcan, uint16 mode)
{
    mcan->FDR.B.DM = mode;
}


IFX_INLINE void IfxMultican_setFractionalDividerStepValue(Ifx_CAN *mcan, uint16 stepValue)
{
    mcan->FDR.B.STEP = stepValue;
}


IFX_INLINE void IfxMultican_setInputClock(Ifx_CAN *mcan, IfxMultican_ClockSelect clockSelect)
{
    mcan->MCR.B.CLKSEL = clockSelect;
}


IFX_INLINE void IfxMultican_setMessageIndexMask(Ifx_CAN *mcan, uint32 mask)
{
    mcan->MSIMASK.U = mask;
}


IFX_INLINE void IfxMultican_setSleepMode(Ifx_CAN *can, IfxMultican_SleepMode mode)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    can->CLC.B.EDIS = mode;
    IfxScuWdt_setCpuEndinit(passwd);
}


IFX_INLINE void IfxMultican_waitListReady(Ifx_CAN *mcan)
{
    while (mcan->PANCTR.B.BUSY != 0)
    {}
}


IFX_INLINE boolean IfxMultican_isModuleSuspended(Ifx_CAN *mcan)
{
    Ifx_CAN_OCS ocs;

    // read the status
    ocs.U = mcan->OCS.U;

    // return the status
    return ocs.B.SUSSTA;
}


IFX_INLINE void IfxMultican_setSuspendMode(Ifx_CAN *mcan, IfxMultican_SuspendMode mode)
{
    Ifx_CAN_OCS ocs;

    // remove protection and configure the suspend mode.
    ocs.B.SUS_P = 1;
    ocs.B.SUS   = mode;
    mcan->OCS.U = ocs.U;
}


#endif /* IFXMULTICAN_H */

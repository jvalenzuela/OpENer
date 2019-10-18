/*******************************************************************************
 * Copyright (c) 2009, Rockwell Automation, Inc.
 * All rights reserved.
 *
 ******************************************************************************/
#ifndef OPENER_CIPETHERNETLINK_H_
#define OPENER_CIPETHERNETLINK_H_

#include "typedefs.h"
#include "ciptypes.h"

/** @brief This Ethernet Link class code as #define is still needed for a static
 *  initialization. */
#define CIP_ETHERNETLINK_CLASS_CODE   0xF6u
/** @brief Ethernet Link class code */
static const CipUint kCipEthernetLinkClassCode = CIP_ETHERNETLINK_CLASS_CODE;

/* public type definitions */

/** @brief Provide bit masks for the Interface Capability (#11) attribute's Capability Bits */
typedef enum {
  /** Interface needs reset to activate attribute #6 */
  kEthLinkCapManualReset = 0x01,
  /** Interface supports link auto-negotiation */
  kEthLinkCapAutoNeg = 0x02,
  /** Interface supports link auto-crossover */
  kEthLinkCapAutoMDX = 0x04,
  /** Interface supports setting of Interface Control attribute(#6) */
  kEthLinkCapManualSpeed = 0x08,
} CipEthLinkCapabilityBits;


/** @brief Provide bit masks to select available speed / duplex combinations
 *
 *  Keep the bit index of these bit masks in sync with the array index of the
 *  matching speed / duplex structure in the internal @p speed_duplex_table
 *  of cipethernetlink.c
 */
typedef enum {
  kEthLinkSpeedDpx_10_HD = 0x01,
  kEthLinkSpeedDpx_10_FD = 0x02,
  kEthLinkSpeedDpx_100_HD = 0x04,
  kEthLinkSpeedDpx_100_FD = 0x08,
  kEthLinkSpeedDpx_1000_HD = 0x10,
  kEthLinkSpeedDpx_1000_FD = 0x20,
} CipEthLinkSpeedDpxSelect;


/** @brief Type definition to describe the Interface Capability
 *
 *  This structure is not a direct representation of the Interface Capability
 *  attribute (#11) but replaces the needed array of speed / duplex list entries
 *  by @ref speed_duplex_selector to create the needed array on the fly.
 */
typedef struct {
  /** Capability flags of CipEthLinkCapabilityBits group */
  CipDword capability_bits;
  /** Speed / duplex selector bit map of CipEthLinkSpeedDpxSelect */
  uint16_t speed_duplex_selector;
} CipEthernetLinkMetaInterfaceCapability;

/** @brief Data of an CIP Ethernet Link object */
typedef struct {
  EipUint32 interface_speed; /**< Attribute #1: 10/100/1000 Mbit/sec */
  EipUint32 interface_flags; /**< Attribute #2: Interface flags as defined in the CIP specification */
  EipUint8 physical_address[6]; /**< Attribute #3: MAC address of the Ethernet link */
  CipShortString interface_label; /**< Attribute #10: Interface label */
  CipEthernetLinkMetaInterfaceCapability interface_caps; /**< Attribute #11: Interface capabilities */
} CipEthernetLinkObject;


/* public functions */
/** @brief Initialize the Ethernet Link Objects data
 *
 *  @return kEipStatusOk if initialization was successful, otherwise kEipStatusError
 */
EipStatus CipEthernetLinkInit(void);

/** @brief Initialize the Ethernet MAC of the Ethernet Link object instances
 *
 *  @param  p_physical_address pointer to 6 bytes of MAC address
 *
 * This function sets the MAC address of all involved Ethernet Link objects.
 */
void CipEthernetLinkSetMac(EipUint8 *p_physical_address);


/* global object instance(s) */

extern CipEthernetLinkObject g_ethernet_link;

#endif /* OPENER_CIPETHERNETLINK_H_*/

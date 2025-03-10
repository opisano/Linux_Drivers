/*
 *  Copyright (c) 2015 Warren J. Jasper <wjasper@ncsu.edu>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef USB_1616FS_H

#define USB_1616FS_H
#ifdef __cplusplus
extern "C" {
#endif

#define USB1616FS_PID (0x0081)

#define DIO_DIR_IN  (0x01)
#define DIO_DIR_OUT (0x00)

#define EXT_TRIG_FAILING_EDGE 0;
#define EXT_TRIG_RAISING_EDGE 1;
#define SYNC_MASTER 0
#define SYNC_SLAVE  1

#define NCHAN_USB1616FS  16           // max number of A/D channels in the device
#define NGAINS_USB1616FS  4           // max number of gain levels
#define EEPROM            0           // read from EEPROM
#define SRAM              1           // read from SRAM

// Gain Ranges
#define BP_10_00V  (0x0)           // Single Ended +/- 10.0 V
#define BP_5_00V   (0x1)           // Single Ended +/- 5.00 V
#define BP_2_50V   (0x2)           // Single Ended +/- 2.50 V
#define BP_2_00V   (0x3)           // Single Ended +/- 2.00 V
#define BP_1_25V   (0x4)           // Single Ended +/- 1.25 V
#define BP_1_00V   (0x5)           // Single Ended +/- 1.00 V
#define BP_0_625V  (0x6)           // Single Ended +/- 0.625 V
#define BP_0_3125V (0x7)           // Single Ended +/- 0.3125 V

// Option values for AInScan
#define AIN_EXECUTION     0x1  // 1 = single execution, 0 = continuous execution
#define AIN_BURST_MODE    0x2  // 1 = burst I/O mode,   0 = normal I/O mode
#define AIN_TRANSFER_MODE 0x4  // 1 = Immediate Transfer mode  0 = block transfer mode
#define AIN_TRIGGER       0x8  // 1 = Use External Trigger
#define AIN_EXTERN_SYNC   0x10 // 1 = Use External Sync
#define AIN_DEBUG_MODE    0x20 // 1 = debug mode

/* function prototypes for the PMD-1608FS */
void usbDConfigPort_USB1616FS(libusb_device_handle *udev, uint8_t direction);
void usbDConfigBit_USB1616FS(libusb_device_handle *udev, uint8_t bit_num, uint8_t direction);
uint8_t usbDIn_USB1616FS(libusb_device_handle *udev);
uint8_t usbDInBit_USB1616FS(libusb_device_handle *udev, uint8_t bit_num);
void usbDOut_USB1616FS(libusb_device_handle *udev, uint8_t value);
void usbDOutBit_USB1616FS(libusb_device_handle *udev, uint8_t bit_num, uint8_t value);

signed short usbAIn_USB1616FS(libusb_device_handle *udev, uint8_t channel, uint8_t range, float table[NGAINS_USB1616FS][NCHAN_USB1616FS][2]);
void usbAOut_USB1616FS(libusb_device_handle *udev, uint8_t channel, uint16_t value);
void usbAOutStop_USB1616FS(libusb_device_handle *udev);
void usbAInStop_USB1616FS(libusb_device_handle *udev);
int usbAInScan_USB1616FS(libusb_device_handle *udev, uint8_t lowchannel, uint8_t highchannel, uint32_t nScan,
			 float *frequency, uint8_t options, int16_t sdata[], float table_AIN[NGAINS_USB1616FS][NCHAN_USB1616FS][2], uint8_t gainArray[NCHAN_USB1616FS]);
void usbAInLoadQueue_USB1616FS(libusb_device_handle *udev, uint8_t gainArray[NCHAN_USB1616FS]);
void usbInitCounter_USB1616FS(libusb_device_handle *udev);
uint32_t usbReadCounter_USB1616FS(libusb_device_handle *udev);

void usbReadMemory_USB1616FS( libusb_device_handle *udev, uint16_t address, uint8_t type, uint8_t count, uint8_t* memory);
int usbWriteMemory_USB1616FS(libusb_device_handle *udev, uint16_t address,  uint8_t count, uint8_t data[]);
void usbBlink_USB1616FS(libusb_device_handle *udev);
int usbReset_USB1616FS(libusb_device_handle *udev);
uint16_t usbGetStatus_USB1616FS(libusb_device_handle *udev);
void usbSetTrigger_USB1616FS(libusb_device_handle *udev, uint8_t type);
void usbSetSync_USB1616FS(libusb_device_handle *udev, uint8_t type);
float volts_USB1616FS(const int gain, const signed short num);
void usbPrepareDownload_USB1616FS(libusb_device_handle *udev);
uint16_t usbReadChecksum_USB1616FS(libusb_device_handle *udev);
void usbWriteSerial_USB1616FS(libusb_device_handle *udev, uint8_t serial[8]);
void usbUpdateCode_USB1616FS(libusb_device_handle *udev);
int usbReadCode_USB1616FS(libusb_device_handle *udev, uint32_t address, uint8_t count, uint8_t data[]);
void usbBuildCalTable_USB1616FS(libusb_device_handle *udev, float table[NGAINS_USB1616FS][NCHAN_USB1616FS][2]);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif // USB-1616FS_H

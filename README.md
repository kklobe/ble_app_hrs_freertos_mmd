# Nordic FreeRTOS SEGGER Example

This project is a copy of ble\_app\_hrs\_freertos with the addition of monitor mode debugging and thread awareness scripts for use with SEGGER Embedded Studio.

## Requirements

- Nordic nRF52840 DK
- SEGGER Embedded Studio 5.10b
- Nordic SDK 17.0.2

## Installation

- Install SEGGER Embedded Studio 5.10b.
- Download the Nordic SDK 17.0.2 and uncompress it somewhere.
- Clone this project to $NORDICSDKROOT/examples/ble\_peripheral.

## Usage

- Open ble\_app\_hrs\_freertos\_pca10056_s140.emProject in SEGGER Embedded Studio.
- Ensure your DK is connected.
- Open the Threads window from the menu View / More Debug Windows / Threads.
- Run the project.
- Use your favorite Bluetooth utility (LightBlue, nRF Connect, etc.) from another device (iOS or Android) to connect to the running Nordic\_HRM peripheral.
- Enable Notifications on the Heart Rate Service.
- Verify HRS notifications are being received.
- Set a breakpoint in a thread, for example the NRF\_LOG\_FLUSH() in logger\_thread().
- When the breakpoint is hit, verify that your Bluetooth utility stays connected, and that you can see four threads in the Threads window: LOG, IDL, Tmr, and BLE.
- Disable the breakpoint and resume the app. Everything should continue working and HRS notifications should resume.

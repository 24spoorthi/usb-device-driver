# usb-device-driver
USB Device Driver for Linux

Simple Device driver to probe and disconnect USB devices.

This code detects new USB devices when connected to the laptop. Here, I've hard-coded the product and vendor id of Sandisk 32GB USB pendrive. When the module is loaded and the pendrive is connected, the driver detects, registers and probes the device with usbcore. On removing the pendrive it, the pendrive is disconnected.

This particular code only probes the USB device and no tmounts it on the file system.

To exeute the code run the following command:

1. TO UNMOUNT THE EXISTING USB DEVICE DRVIER:
	
		%sudo rmmod uas
		%sudo rmmod usb-storage

2. TO LOAD THE MODULE INVOKE make FROM THE DIRECTORY CONSISTING THE FILE:

		%make

3. LOAD THE MODULE:

		%sudo insmod device-driver.ko

4. CONNECT THE 	USB PENDRIVE AND CHECK THE LOGFILE:

		%tail -f /var/log/syslog

		or
		
		%dmesg

5. TO UNLOAD THE MODULE:

		%sudo rmmod device_driver

6. LOAD THE DEFAULT USB DEVICE DRIVERS.

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/usb.h>
#define PRINT_USB_INTERFACE_DESCRIPTOR( i )                         \
{                                                                   \
    pr_info("USB_INTERFACE_DESCRIPTOR:\n");                         \
    pr_info("-----------------------------\n");                     \
    pr_info("bLength: 0x%x\n", i.bLength);                          \
    pr_info("bDescriptorType: 0x%x\n", i.bDescriptorType);          \
    pr_info("bInterfaceNumber: 0x%x\n", i.bInterfaceNumber);        \
    pr_info("bAlternateSetting: 0x%x\n", i.bAlternateSetting);      \
    pr_info("bNumEndpoints: 0x%x\n", i.bNumEndpoints);              \
    pr_info("bInterfaceClass: 0x%x\n", i.bInterfaceClass);          \
    pr_info("bInterfaceSubClass: 0x%x\n", i.bInterfaceSubClass);    \
    pr_info("bInterfaceProtocol: 0x%x\n", i.bInterfaceProtocol);    \
    pr_info("iInterface: 0x%x\n", i.iInterface);                    \
    pr_info("\n");                                                  \
}
#define PRINT_USB_ENDPOINT_DESCRIPTOR( e )                          \
{                                                                   \
    pr_info("USB_ENDPOINT_DESCRIPTOR:\n");                          \
    pr_info("------------------------\n");                          \
    pr_info("bLength: 0x%x\n", e.bLength);                          \
    pr_info("bDescriptorType: 0x%x\n", e.bDescriptorType);          \
    pr_info("bEndPointAddress: 0x%x\n", e.bEndpointAddress);        \
    pr_info("bmAttributes: 0x%x\n", e.bmAttributes);                \
    pr_info("wMaxPacketSize: 0x%x\n", e.wMaxPacketSize);            \
    pr_info("bInterval: 0x%x\n", e.bInterval);                      \
    pr_info("\n");                                                  \
}

MODULE_AUTHOR("SPOORTHI NAIK");
MODULE_LICENSE("GPL");

int dev_probe_func(struct usb_interface *intf, const struct usb_device_id *id);
void dev_disconnect(struct usb_interface *intf);

struct usb_device_id dev_id_table[]={
  { USB_DEVICE(0x0781,0x558A)},
  { USB_DEVICE(0x046d,0xc534)},
  {}
};

MODULE_DEVICE_TABLE(usb,dev_id_table);

struct usb_driver dev_dr ={
  .name = "USB device driver",
  .id_table = dev_id_table,
  .probe = dev_probe_func,
  .disconnect = dev_disconnect
};


static int __init usb_init(void){
  int res;
  printk(KERN_ALERT "Registerstion of module\n");
  res = usb_register(&dev_dr);
  if(res)
    printk(KERN_ALERT "Registerstion unsuccessful with error number: %d",res);
  return res;
}

static void __exit usb_exit(void){
  usb_deregister(&dev_dr);
}

int dev_probe_func(struct usb_interface *interface, const struct usb_device_id *id){
  //struct usb_device *udev = interface_to_usbdev(intf);
  unsigned int i;
  unsigned int endpoints_count;
  struct usb_host_interface *iface_desc = interface->cur_altsetting;
  dev_info(&interface->dev, "USB Driver Probed: Vendor ID : 0x%02x,\t" "Product ID : 0x%02x\n", id->idVendor, id->idProduct);
  
  endpoints_count = iface_desc->desc.bNumEndpoints;
  
  PRINT_USB_INTERFACE_DESCRIPTOR(iface_desc->desc);
  
  for ( i = 0; i < endpoints_count; i++ )
    PRINT_USB_ENDPOINT_DESCRIPTOR(iface_desc->endpoint[i].desc);
  return 0;
}

void dev_disconnect(struct usb_interface *intf){
  printk(KERN_INFO "USB removed\n");
}
module_init(usb_init);
module_exit(usb_exit);
			   

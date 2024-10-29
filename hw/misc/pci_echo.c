// hw/pci/pci_echo.c

#include "qemu/osdep.h"
#include "hw/pci/pci.h"
#include "hw/pci/pci.h"
#include "hw/hw.h"
#include "sysemu/sysemu.h"
#include "qapi/error.h"

#define PCI_ECHO_DEVICE_ID 0x1234

typedef struct PCIEchoDevice {
    PCIDevice parent_obj;
    uint8_t echo_value;  // Store the value to echo back
} PCIEchoDevice;

static void pci_echo_write(PCIEchoDevice *dev, uint32_t offset, uint32_t value) {
    // Echo the value back to the register
    dev->echo_value = value;
}

static uint32_t pci_echo_read(PCIEchoDevice *dev, uint32_t offset) {
    // Read the echo value from the register
    return dev->echo_value;
}

static void pci_echo_realize(DeviceState *dev, Error **errp) {
    PCIEchoDevice *pci_echo = PCI_ECHO(dev);
    // Additional initialization can go here
}

static void pci_echo_init(Object *obj) {
    PCIEchoDevice *pci_echo = PCI_ECHO(obj);
    pci_set_id(PCI_DEVICE(pci_echo), PCI_ECHO_DEVICE_ID);
    // Set other device properties if necessary
}

static const Property pci_echo_properties[] = {
    DEFINE_PROP_UINT8("echo-value", PCIEchoDevice, echo_value, 0),
    {}
};

static void pci_echo_class_init(ObjectClass *oc, void *data) {
    DeviceClass *dc = DEVICE_CLASS(oc);
    dc->realize = pci_echo_realize;
    dc->props = pci_echo_properties;
    dc->desc = "PCI Echo Device";
}

static TypeInfo pci_echo_type_info = {
    .name = "pci_echo_device",
    .parent = TYPE_PCI_DEVICE,
    .instance_size = sizeof(PCIEchoDevice),
    .class_init = pci_echo_class_init,
};

static void pci_echo_register_types(void) {
    type_register_static(&pci_echo_type_info);
}

type_init(pci_echo_register_types);

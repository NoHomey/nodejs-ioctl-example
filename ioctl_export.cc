#define IOCTL_ENUM_TS
#include "node_modules/ioctl-enum/ioctl-enum.h"
#include "ioctl_example.h"

IOCTL_ENUM("IOCTL_EXAMPLE");
IOCTL_ENUM_IOCTL("IOCTL_EXAMPLE_ADDITION", IOCTL_EXAMPLE_ADDITION);
IOCTL_ENUM_IOCTL("IOCTL_EXAMPLE_SET", IOCTL_EXAMPLE_SET);
IOCTL_ENUM_IOCTL("IOCTL_EXAMPLE_GET", IOCTL_EXAMPLE_GET);
IOCTL_ENUM_IOCTL("IOCTL_EXAMPLE_ADD", IOCTL_EXAMPLE_ADD);
IOCTL_ENUM_EXPORT();

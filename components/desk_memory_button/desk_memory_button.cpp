#include "desk_memory_button.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace memory_button
  {

    static const char *const TAG = "Desk.memoryButton";

    void MemoryButton::dump_config()
    {
      LOG_BUTTON("", "Memory Button", this);
    }

    void MemoryButton::press_action()
    {
      switch (this->memory_id)
      {
      case 0:
        uart_device->write_array({0xD8, 0xD8, 0x66, 0x04, 0x04});
        uart_device->flush();
        break;
      case 1:
        uart_device->write_array({0xD8, 0xD8, 0x66, 0x08, 0x08});
        uart_device->flush();
        break;
      case 2:
        uart_device->write_array({0xD8, 0xD8, 0x66, 0x10, 0x10});
        uart_device->flush();
        break;
      case 3:
        uart_device->write_array({0xD8, 0xD8, 0x66, 0x20, 0x20});
        uart_device->flush();
        break;

      default:
        break;
      }
    }

  } // namespace output
} // namespace esphome

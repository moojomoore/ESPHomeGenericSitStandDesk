#include "esphome/core/log.h"
#include "desk_switch.h"

namespace esphome
{
    namespace desk_switch
    {

        static const char *TAG = "desk.switch";

        void DeskSwitch::loop()
        {
            // Repeatedly sends the according command to move the desk in the desired direction
            uint32_t time = millis();
            if (this->state && time - last_send > 250)
            {
                if (this->direction)
                    uart_device->write_array({0xD8, 0xD8, 0x66, 0x02, 0x02, 0xD8, 0xD8, 0x66, 0x02, 0x02});
                else
                    uart_device->write_array({0xD8, 0xD8, 0x66, 0x01, 0x01, 0xD8, 0xD8, 0x66, 0x02, 0x01});
                uart_device->flush();
                last_send = millis();
            }
        }

        void DeskSwitch::setup()
        {
        }

        void DeskSwitch::write_state(bool state)
        {
            this->publish_state(state);
            if (!state)
            {
                // Send a Idle command to cancle the execution of the current desk movement.
                uart_device->write_array({0xD8, 0xD8, 0x66, 0x01, 0x00});
                uart_device->flush();
            }
        }

        void DeskSwitch::dump_config()
        {
            ESP_LOGCONFIG(TAG, "Desk switch %s", (this->direction ? "up" : "down"));
        }

    } // namespace desk_switch
} // namespace esphome

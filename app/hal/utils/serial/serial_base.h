/**
 * @file serial_base.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstddef>
#include <cstdint>
#include <string>

namespace HAL_SERIAL
{
    class SerialBase
    {
    public:
        virtual bool init() { return false; };
        virtual bool deInit() { return false; };
        virtual void setBaudrate(uint32_t baudrate){};

        virtual size_t write(uint8_t* dataBuffer, size_t dataLen) { return 0; };
        virtual size_t write(const std::string& data) { return 0; };
        virtual size_t available() { return 0; };
        virtual size_t read(uint8_t* dataBuffer, size_t dataLen) { return 0; };
    };

/**
 * @brief Serial desktop
 *
 */
#ifdef PLATFORM_BUILD_DESKTOP
#ifdef ENABLE_SERIAL_DESKTOP
    class SerialDesktop : public SerialBase
    {
    public:
        bool init() override { return init("/dev/ttyACM0"); }
        bool init(const std::string& port = "", uint32_t baudrate = 115200);
        bool deInit() override;
        void setBaudrate(uint32_t baudrate) override;

        size_t write(uint8_t* dataBuffer, size_t dataLen) override;
        size_t write(const std::string& data) override;

        size_t available() override;
        size_t read(uint8_t* dataBuffer, size_t dataLen) override;
    };
#endif
#endif
} // namespace HAL_SERIAL

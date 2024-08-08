/**
 * @file serial_desktop.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifdef PLATFORM_BUILD_DESKTOP
#ifdef ENABLE_SERIAL_DESKTOP
#include "serial_base.h"
#include <mooncake.h>
#include <serial/serial.h>
#include <string>
#include <iostream>
#include <cstdio>
// Require: https://github.com/wjwwood/serial installed
// http://wjwwood.io/serial/doc/1.1.0/index.html
// https://github.com/wjwwood/serial/blob/main/examples/serial_example.cc

using namespace HAL_SERIAL;

static serial::Serial* _serial = nullptr;

static void _enumerate_ports()
{
    spdlog::info("found serial ports:");
    std::vector<serial::PortInfo> devices_found = serial::list_ports();
    std::vector<serial::PortInfo>::iterator iter = devices_found.begin();
    while (iter != devices_found.end())
    {
        serial::PortInfo device = *iter++;
        spdlog::info("({}, {}, {})", device.port, device.description, device.hardware_id);
    }
}

bool SerialDesktop::init(const std::string& port, uint32_t baudrate)
{
    _enumerate_ports();

    if (_serial != nullptr)
    {
        spdlog::error("serial instance already exist");
        return false;
    }
    // port, baudrate, timeout in milliseconds
    _serial = new serial::Serial(port, baudrate, serial::Timeout::simpleTimeout(1000));

    if (!_serial->isOpen())
    {
        spdlog::error("open port {} failed", port);
        return false;
    }
    spdlog::info("open port {} ok", port);
    return true;
}

size_t SerialDesktop::write(uint8_t* dataBuffer, size_t dataLen)
{
    if (_serial == nullptr)
        return false;
    return _serial->write(dataBuffer, dataLen);
}

size_t SerialDesktop::write(const std::string& data)
{
    if (_serial == nullptr)
        return false;
    return _serial->write(data);
}

size_t SerialDesktop::available()
{
    if (_serial == nullptr)
        return 0;
    return _serial->available();
}

size_t SerialDesktop::read(uint8_t* dataBuffer, size_t dataLen)
{
    if (_serial == nullptr)
        return false;
    return _serial->read(dataBuffer, dataLen);
}

bool SerialDesktop::deInit()
{
    if (_serial == nullptr)
    {
        spdlog::error("serial instance not exist");
        return false;
    }
    _serial->close();
    delete _serial;
    _serial = nullptr;
    return true;
}

void SerialDesktop::setBaudrate(uint32_t baudrate)
{
    if (_serial == nullptr)
        return;
    _serial->setBaudrate(baudrate);
}

size_t SerialDesktop::readline(std::string& buffer, size_t size, std::string eol)
{
    if (_serial == nullptr)
        return 0;
    return _serial->readline(buffer, size, eol);
}

std::string SerialDesktop::readline(size_t size, std::string eol)
{
    if (_serial == nullptr)
        return "";
    return _serial->readline(size, eol);
}

std::vector<std::string> SerialDesktop::readlines(size_t size, std::string eol)
{
    if (_serial == nullptr)
        return std::vector<std::string>();
    return _serial->readlines(size, eol);
};

#endif
#endif

/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Serial port interfaces
 *  
 *  © 2021—2024, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include "exception.hppi"
#include "SerialPort.hpp"

using namespace upp;

/******************************************************************************/

void SerialPortConfiguration::setInputBaudRate(speed_t speed) {
    cfsetispeed(&tty, speed);
}

void SerialPortConfiguration::setOutputBaudRate(speed_t speed) {
    cfsetospeed(&tty, speed);
}

void SerialPortConfiguration::setBaudRate(speed_t speed) {
    cfsetspeed(&tty, speed);
}

void SerialPortConfiguration::setFlags(unsigned flags) {
    tty.c_cflag|=flags;
}

void SerialPortConfiguration::clearFlags(unsigned flags) {
    tty.c_cflag&=~flags;
}

void SerialPortConfiguration::setLocalFlags(unsigned flags) {
    tty.c_lflag|=flags;
}

void SerialPortConfiguration::clearLocalFlags(unsigned flags) {
    tty.c_lflag&=~flags;
}

void SerialPortConfiguration::setInputFlags(unsigned flags) {
    tty.c_iflag|=flags;
}

void SerialPortConfiguration::clearInputFlags(unsigned flags) {
    tty.c_iflag&=~flags;
}

void SerialPortConfiguration::setOutputFlags(unsigned flags) {
    tty.c_oflag|=flags;
}

void SerialPortConfiguration::clearOutputFlags(unsigned flags) {
    tty.c_oflag&=~flags;
}

void SerialPortConfiguration::setTimeouts(cc_t vmin, cc_t vtime) {
    for (unsigned i=0; i<sizeof(tty.c_cc); i++)
        tty.c_cc[i]=_POSIX_VDISABLE;
    tty.c_cc[VTIME]=vtime;
    tty.c_cc[VMIN]=vmin;
}

/******************************************************************************/

SerialPort::SerialPort(const char * filename, int flags) : File(filename, flags) {}

SerialPortConfiguration SerialPort::getConfiguration() {
    SerialPortConfiguration configuration;
    if (tcgetattr(getDescriptor(), &configuration.tty) != 0)
        throw std::system_error(errno, std::system_category());
    return configuration;
}

void SerialPort::setConfiguration(const SerialPortConfiguration &configuration) {
    if (tcsetattr(getDescriptor(), TCSANOW, &configuration.tty) != 0)
        throw std::system_error(errno, std::system_category());
}

void SerialPort::sendBreak(int duration) {
    
}

void SerialPort::drain() {
    if (0!=tcdrain(getDescriptor()))
        throw std::system_error(errno, std::system_category());
}

void SerialPort::flush(int queueSelector) {
    if (0!=tcflush(getDescriptor(), queueSelector))
        throw std::system_error(errno, std::system_category());
}

void SerialPort::flow(int action) {
    NORMAL_OP_WRAPPER(tcflow(getDescriptor(), action));
}

int SerialPort::getModemStatus() {
    int result;
    ioctl(TIOCMGET, &result);
    return result;
}

void SerialPort::setModemStatus(int status) {
    ioctl(TIOCMSET, &status);
}

void SerialPort::clearModemBits(int bits) {
    ioctl(TIOCMBIC, &bits);
}

void SerialPort::setModemBits(int bits) {
    ioctl(TIOCMBIS, &bits);
}

void SerialPort::waitModemBits(int bits) {
    ioctl(TIOCMIWAIT, bits);
}


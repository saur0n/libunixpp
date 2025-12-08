/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Serial port interfaces
 *  
 *  © 2021—2025, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <cstring>
#include "exception.hppi"
#include "SerialPort.hpp"

using namespace upp;

#ifndef BOTHER
#  define BOTHER 0010000
#endif

#ifndef IBSHIFT
#  define IBSHIFT 16
#endif

static const unsigned IOC_TCGETS2=0x802c542a;
static const unsigned IOC_TCSETS2=0x402c542b;

/******************************************************************************/

SerialPortConfiguration::SerialPortConfiguration() {
    memset(&tty, 0, sizeof(tty));
}

void SerialPortConfiguration::setInputSpeed(speed_t speed) {
    cfsetispeed(&tty.tty, speed);
}

void SerialPortConfiguration::setInputBaudRate(speed_t speed) {
    tty.tty.c_cflag&=~CIBAUD;
    tty.tty.c_cflag|=BOTHER<<IBSHIFT;
    tty.c_ispeed=speed;
}

void SerialPortConfiguration::setOutputSpeed(speed_t speed) {
    cfsetospeed(&tty.tty, speed);
}

void SerialPortConfiguration::setOutputBaudRate(speed_t speed) {
    tty.tty.c_cflag&=~CBAUD;
    tty.tty.c_cflag|=BOTHER;
    tty.c_ospeed=speed;
}

void SerialPortConfiguration::setSpeed(speed_t speed) {
    cfsetspeed(&tty.tty, speed);
}

void SerialPortConfiguration::setBaudRate(speed_t speed) {
    tty.tty.c_cflag&=~(CIBAUD|CBAUD);
    tty.tty.c_cflag|=(BOTHER<<IBSHIFT)|BOTHER;
    tty.c_ispeed=speed;
    tty.c_ospeed=speed;
}

void SerialPortConfiguration::setFlags(unsigned flags) {
    tty.tty.c_cflag|=flags;
}

void SerialPortConfiguration::clearFlags(unsigned flags) {
    tty.tty.c_cflag&=~flags;
}

void SerialPortConfiguration::setLocalFlags(unsigned flags) {
    tty.tty.c_lflag|=flags;
}

void SerialPortConfiguration::clearLocalFlags(unsigned flags) {
    tty.tty.c_lflag&=~flags;
}

void SerialPortConfiguration::setInputFlags(unsigned flags) {
    tty.tty.c_iflag|=flags;
}

void SerialPortConfiguration::clearInputFlags(unsigned flags) {
    tty.tty.c_iflag&=~flags;
}

void SerialPortConfiguration::setOutputFlags(unsigned flags) {
    tty.tty.c_oflag|=flags;
}

void SerialPortConfiguration::clearOutputFlags(unsigned flags) {
    tty.tty.c_oflag&=~flags;
}

void SerialPortConfiguration::setTimeout(unsigned char index, cc_t value) {
    tty.tty.c_cc[index]=value;
}

void SerialPortConfiguration::setTimeouts(cc_t vmin, cc_t vtime) {
    for (unsigned i=0; i<sizeof(tty.tty.c_cc); i++)
        tty.tty.c_cc[i]=_POSIX_VDISABLE;
    tty.tty.c_cc[VTIME]=vtime;
    tty.tty.c_cc[VMIN]=vmin;
}

/******************************************************************************/

SerialPort::SerialPort(const char * filename, int flags) : File(filename, flags) {}

SerialPortConfiguration SerialPort::getConfiguration() {
    SerialPortConfiguration configuration;
    struct termios2 * ptty=&configuration.tty;
    Stream::ioctl(IOC_TCGETS2, ptty);
    return configuration;
}

void SerialPort::setConfiguration(const SerialPortConfiguration &configuration) {
    Stream::ioctl(IOC_TCSETS2, const_cast<termios2 *>(&configuration.tty));
}

void SerialPort::sendBreak(int duration) {
    tcsendbreak(getDescriptor(), duration);
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


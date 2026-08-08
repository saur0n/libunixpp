/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Serial port interfaces
 *  
 *  © 2021—2026, Sauron <libunixpp@saur0n.science>
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

void SerialPortConfiguration::setOutputSpeed(speed_t speed) {
    cfsetospeed(&tty.tty, speed);
}

void SerialPortConfiguration::setSpeed(speed_t speed) {
    cfsetspeed(&tty.tty, speed);
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

SerialPortConfiguration2::SerialPortConfiguration2() {
    memset(&tty, 0, sizeof(tty));
}

void SerialPortConfiguration2::setInputSpeed(speed_t speed) {
    cfsetispeed(&tty.tty, speed);
}

void SerialPortConfiguration2::setInputBaudRate(speed_t speed) {
    tty.tty.c_cflag&=~CIBAUD;
    tty.tty.c_cflag|=BOTHER<<IBSHIFT;
    tty.c_ispeed=speed;
}

void SerialPortConfiguration2::setOutputSpeed(speed_t speed) {
    cfsetospeed(&tty.tty, speed);
}

void SerialPortConfiguration2::setOutputBaudRate(speed_t speed) {
    tty.tty.c_cflag&=~CBAUD;
    tty.tty.c_cflag|=BOTHER;
    tty.c_ospeed=speed;
}

void SerialPortConfiguration2::setSpeed(speed_t speed) {
    cfsetspeed(&tty.tty, speed);
}

void SerialPortConfiguration2::setBaudRate(speed_t speed) {
    tty.tty.c_cflag&=~(CIBAUD|CBAUD);
    tty.tty.c_cflag|=(BOTHER<<IBSHIFT)|BOTHER;
    tty.c_ispeed=speed;
    tty.c_ospeed=speed;
}

void SerialPortConfiguration2::setFlags(unsigned flags) {
    tty.tty.c_cflag|=flags;
}

void SerialPortConfiguration2::clearFlags(unsigned flags) {
    tty.tty.c_cflag&=~flags;
}

void SerialPortConfiguration2::setLocalFlags(unsigned flags) {
    tty.tty.c_lflag|=flags;
}

void SerialPortConfiguration2::clearLocalFlags(unsigned flags) {
    tty.tty.c_lflag&=~flags;
}

void SerialPortConfiguration2::setInputFlags(unsigned flags) {
    tty.tty.c_iflag|=flags;
}

void SerialPortConfiguration2::clearInputFlags(unsigned flags) {
    tty.tty.c_iflag&=~flags;
}

void SerialPortConfiguration2::setOutputFlags(unsigned flags) {
    tty.tty.c_oflag|=flags;
}

void SerialPortConfiguration2::clearOutputFlags(unsigned flags) {
    tty.tty.c_oflag&=~flags;
}

void SerialPortConfiguration2::setTimeout(unsigned char index, cc_t value) {
    tty.tty.c_cc[index]=value;
}

void SerialPortConfiguration2::setTimeouts(cc_t vmin, cc_t vtime) {
    for (unsigned i=0; i<sizeof(tty.tty.c_cc); i++)
        tty.tty.c_cc[i]=_POSIX_VDISABLE;
    tty.tty.c_cc[VTIME]=vtime;
    tty.tty.c_cc[VMIN]=vmin;
}

/******************************************************************************/

SerialPort::SerialPort(Stream &stream) : Wrapper(stream) {}

SerialPortConfiguration SerialPort::getConfiguration() const {
    SerialPortConfiguration configuration;
    get(TCGETS, configuration.tty);
    return configuration;
}

void SerialPort::setConfiguration(const SerialPortConfiguration &configuration) {
    set(TCSETS, configuration.tty);
}

SerialPortConfiguration2 SerialPort::getConfiguration2() const {
    SerialPortConfiguration2 configuration;
    get(TCGETS2, configuration.tty);
    return configuration;
}

void SerialPort::setConfiguration2(const SerialPortConfiguration2 &configuration) {
    set(TCSETS2, configuration.tty);
}

void SerialPort::doAutoconfig() {
    ioctl(TIOCSERCONFIG);
}

struct ::serial_struct SerialPort::getInformation() const {
    struct ::serial_struct result;
    get(TIOCGSERIAL, result);
    return result;
}

void SerialPort::setInformation(const struct ::serial_struct &information) {
    set(TIOCSSERIAL, information);
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

int SerialPort::getModemStatus() const {
    int result;
    get(TIOCMGET, result);
    return result;
}

void SerialPort::setModemStatus(int status) {
    set(TIOCMSET, status);
}

void SerialPort::clearModemBits(int bits) {
    set(TIOCMBIC, bits);
}

void SerialPort::setModemBits(int bits) {
    set(TIOCMBIS, bits);
}

void SerialPort::waitModemBits(int bits) {
    ioctl(TIOCMIWAIT, bits);
}

bool SerialPort::getSoftCarrier() const {
    int result;
    get(TIOCGSOFTCAR, result);
    return result;
}

void SerialPort::setSoftCarrier(bool softCarrier) {
    set(TIOCSSOFTCAR, softCarrier?1:0);
}

int SerialPort::getLineStatusRegister() const {
    int result;
    get(TIOCSERGETLSR, result);
    return result;
}

int SerialPort::getOutputQueue() const {
    int result;
    get(TIOCOUTQ, result);
    return result;
}

void SerialPort::unshift(char ch) {
    set(TIOCSTI, ch);
}

Terminal::Terminal(Stream &stream) : SerialPort(stream) {}

bool Terminal::getExclusive() const {
    int result;
    get(TIOCGEXCL, result);
    return result;
}

void Terminal::setExclusive() {
    ioctl(TIOCEXCL);
}

void Terminal::clearExclusive() {
    ioctl(TIOCNXCL);
}

int Terminal::getLineDiscipline() const {
    int result;
    get(TIOCGETD, result);
    return result;
}

void Terminal::setLineDiscipline(int lineDiscipline) {
    set(TIOCSETD, lineDiscipline);
}

pid_t Terminal::getProcessGroup() const {
    pid_t result;
    get(TIOCGPGRP, result);
    return result;
}

void Terminal::setProcessGroup(pid_t processGroup) {
    set(TIOCSPGRP, processGroup);
}

int Terminal::getSessionID() const {
    int result;
    get(TIOCGSID, result);
    return result;
}

Terminal::WindowSize Terminal::getWindowSize() const {
    WindowSize result;
    get(TIOCGWINSZ, result);
    return result;
}

void Terminal::setWindowSize(const WindowSize &windowSize) {
    set(TIOCSWINSZ, windowSize);
}

void Terminal::setControlling(bool steal) {
    set(TIOCSCTTY, steal?1:0);
}

void Terminal::resetControlling() {
    ioctl(TIOCNOTTY);
}

void Terminal::redirectConsole() {
    ioctl(TIOCCONS);
}

void Terminal::hangup() {
    ioctl(TIOCVHANGUP);
}

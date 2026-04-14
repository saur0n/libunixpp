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

SerialPort::SerialPort(Stream &stream) : Wrapper(stream) {}

SerialPortConfiguration SerialPort::getConfiguration() const {
    SerialPortConfiguration configuration;
    struct termios2 * ptty=&configuration.tty;
    ioctl(/*IOC_*/TCGETS2, ptty);
    return configuration;
}

void SerialPort::setConfiguration(const SerialPortConfiguration &configuration) {
    ioctl(/*IOC_*/TCSETS2, &configuration.tty);
}

void SerialPort::doAutoconfig() {
    ioctl(TIOCSERCONFIG);
}

struct ::serial_struct SerialPort::getInformation() const {
    struct ::serial_struct result;
    ioctl(TIOCGSERIAL, &result);
    return result;
}

void SerialPort::setInformation(const struct ::serial_struct &information) {
    ioctl(TIOCSSERIAL, &information);
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
    ioctl(TIOCMGET, &result);
    return result;
}

void SerialPort::setModemStatus(int status) {
    const int * arg=&status;
    ioctl(TIOCMSET, arg);
}

void SerialPort::clearModemBits(int bits) {
    const int * arg=&bits;
    ioctl(TIOCMBIC, arg);
}

void SerialPort::setModemBits(int bits) {
    const int * arg=&bits;
    ioctl(TIOCMBIS, arg);
}

void SerialPort::waitModemBits(int bits) {
    ioctl(TIOCMIWAIT, bits);
}

bool SerialPort::getSoftCarrier() const {
    int result;
    ioctl(TIOCGSOFTCAR, &result);
    return result;
}

void SerialPort::setSoftCarrier(bool softCarrier) {
    const int arg=softCarrier?1:0;
    ioctl(TIOCSSOFTCAR, &arg);
}

int SerialPort::getLineStatusRegister() const {
    int result;
    ioctl(TIOCSERGETLSR, &result);
    return result;
}

int SerialPort::getOutputQueue() const {
    int result;
    ioctl(TIOCOUTQ, &result);
    return result;
}

void SerialPort::unshift(char ch) {
    const char * arg=&ch;
    ioctl(TIOCSTI, arg);
}

Terminal::Terminal(Stream &stream) : SerialPort(stream) {}

bool Terminal::getExclusive() const {
    int result;
    ioctl(TIOCGEXCL, &result);
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
    ioctl(TIOCGETD, &result);
    return result;
}

void Terminal::setLineDiscipline(int lineDiscipline) {
    const int * arg=&lineDiscipline;
    ioctl(TIOCSETD, arg);
}

pid_t Terminal::getProcessGroup() const {
    pid_t result;
    ioctl(TIOCGPGRP, &result);
    return result;
}

void Terminal::setProcessGroup(pid_t processGroup) {
    const pid_t * arg=&processGroup;
    ioctl(TIOCSPGRP, arg);
}

int Terminal::getSessionID() const {
    int result;
    ioctl(TIOCGSID, &result);
    return result;
}

Terminal::WindowSize Terminal::getWindowSize() const {
    WindowSize result;
    ioctl(TIOCGWINSZ, &result);
    return result;
}

void Terminal::setWindowSize(const WindowSize &windowSize) {
    ioctl(TIOCSWINSZ, &windowSize);
}

void Terminal::setControlling(bool steal) {
    ioctl(TIOCSCTTY, steal?1:0);
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

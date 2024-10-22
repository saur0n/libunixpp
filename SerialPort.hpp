/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Serial port interfaces
 *  
 *  © 2021—2024, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_SERIALPORT_HPP
#define __UNIXPP_SERIALPORT_HPP

#include <linux/serial.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "File.hpp"

namespace upp {

/**/
class SerialPortConfiguration {
    friend class SerialPort;
public:
    /** Set the input baud rate **/
    void setInputBaudRate(speed_t speed);
    /** Set the output baud rate **/
    void setOutputBaudRate(speed_t speed);
    /** Set both input and output baud rate **/
    void setBaudRate(speed_t speed);
    /** Set the specified control flags **/
    void setFlags(unsigned flags);
    /** Unset the specified control flags **/
    void clearFlags(unsigned flags);
    /** Set the specified local mode flags **/
    void setLocalFlags(unsigned flags);
    /** Unset the specified local mode flags **/
    void clearLocalFlags(unsigned flags);
    /** Set the specified input processing mode flags **/
    void setInputFlags(unsigned flags);
    /** Unset the specified input processing mode flags **/
    void clearInputFlags(unsigned flags);
    /** Set the specified output processing mode flags **/
    void setOutputFlags(unsigned flags);
    /** Unset the specified output processing mode flags **/
    void clearOutputFlags(unsigned flags);
    /** Set VMIN and VTIME **/
    void setTimeouts(cc_t vmin, cc_t vtime);
    
private:
    struct termios tty;
};

/**/
class SerialPort : public upp::File {
public:
    /** Modem bits **/
    enum {
        /** DSR (data set ready/line enable) **/
        LE=0x001,
        /** DTR (data terminal ready) **/
        DTR=0x002,
        /** RTS (request to send) **/
        RTS=0x004,
        /** Secondary TXD (transmit) **/
        ST=0x008,
        /** Secondary RXD (receive) **/
        SR=0x010,
        /** CTS (clear to send)**/
        CTS=0x020,
        /** DCD (data carrier detect)**/
        CAR=0x040,
        /** see CAR **/
        CD=CAR,
        /** RNG (ring) **/
        RNG=0x080,
        /** see RNG **/
        RI=RNG,
        /** DSR (data set ready) **/
        DSR=0x100,
        /** ? **/
        OUT1=0x2000,
        /** ? **/
        OUT2=0x4000,
    };
    /**/
    SerialPort(const char * filename, int flags=O_RDWR|O_NOCTTY|O_NDELAY);
    /** Get the serial port configuration **/
    SerialPortConfiguration getConfiguration();
    /** Set the serial port configuration **/
    void setConfiguration(const SerialPortConfiguration &configuration);
    /**/
    void sendBreak(int duration);
    /** Wait until all data previously written to the serial line **/
    void drain();
    /***/
    void flush(int queueSelector);
    /** Suspend or restart transmission on the serial port **/
    void flow(int action);
    /** Get the status of modem bits **/
    int getModemStatus();
    /** Set the status of modem bits **/
    void setModemStatus(int status);
    /** Clear the indicated modem bits **/
    void clearModemBits(int bits);
    /** Set the indicated modem bits **/
    void setModemBits(int bits);
    /** Wait for any of the 4 modem bits (DCD, RI, DSR, CTS) to change **/
    void waitModemBits(int bits);
    /** Get counts of input serial line interrupts (DCD, RI, DSR, CTS) **/
    serial_icounter_struct getInterruptCount();
};

}

#endif

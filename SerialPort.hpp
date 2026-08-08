/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Serial port interfaces
 *  
 *  © 2021—2026, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_SERIALPORT_HPP
#define __UNIXPP_SERIALPORT_HPP

#include <linux/serial.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "Wrapper.hpp"

namespace upp {

/** Copied from termbits.h, because including it directly leads to a conflict **/
struct termios2 {
    struct termios tty;
    speed_t c_ispeed;
    speed_t c_ospeed;
};

/**/
class SerialPortConfiguration {
    friend class SerialPort;
public:
    /** Initialize the structure with zeros **/
    SerialPortConfiguration();
    /** Set the input baud rate (from predefined speed list) **/
    void setInputSpeed(speed_t speed);
    /** Set the output baud rate (from predefined speed list)**/
    void setOutputSpeed(speed_t speed);
    /** Set both input and output baud rate (from predefined speed list)**/
    void setSpeed(speed_t speed);
    /** Returns the control flags **/
    unsigned getFlags() const { return tty.tty.c_cflag; }
    /** Set the specified control flags **/
    void setFlags(unsigned flags);
    /** Unset the specified control flags **/
    void clearFlags(unsigned flags);
    /** Returns the local flags **/
    unsigned getLocalFlags() const { return tty.tty.c_lflag; }
    /** Set the specified local mode flags **/
    void setLocalFlags(unsigned flags);
    /** Unset the specified local mode flags **/
    void clearLocalFlags(unsigned flags);
    /** Returns the input flags **/
    unsigned getInputFlags() const { return tty.tty.c_iflag; }
    /** Set the specified input processing mode flags **/
    void setInputFlags(unsigned flags);
    /** Unset the specified input processing mode flags **/
    void clearInputFlags(unsigned flags);
    /** Returns the output flags **/
    unsigned getOutputFlags() const { return tty.tty.c_oflag; }
    /** Set the specified output processing mode flags **/
    void setOutputFlags(unsigned flags);
    /** Unset the specified output processing mode flags **/
    void clearOutputFlags(unsigned flags);
    /** Set the specified timeout **/
    void setTimeout(unsigned char index, cc_t value);
    /** Set VMIN and VTIME **/
    void setTimeouts(cc_t vmin, cc_t vtime);
    
private:
    struct termios2 tty;
};

/** Extended serial port configuration, allows to set arbitrary baudrate **/
class SerialPortConfiguration2 {
    friend class SerialPort;
public:
    /** Initialize the structure with zeros **/
    SerialPortConfiguration2();
    /** Set the input baud rate (from predefined speed list) **/
    void setInputSpeed(speed_t speed);
    /** Set the non-standard input baud rate **/
    void setInputBaudRate(speed_t speed);
    /** Set the output baud rate (from predefined speed list)**/
    void setOutputSpeed(speed_t speed);
    /** Set the non-standard output baud rate **/
    void setOutputBaudRate(speed_t speed);
    /** Set both input and output baud rate (from predefined speed list)**/
    void setSpeed(speed_t speed);
    /** Set the non-standard input and output baud rate **/
    void setBaudRate(speed_t speed);
    /** Returns the control flags **/
    unsigned getFlags() const { return tty.tty.c_cflag; }
    /** Set the specified control flags **/
    void setFlags(unsigned flags);
    /** Unset the specified control flags **/
    void clearFlags(unsigned flags);
    /** Returns the local flags **/
    unsigned getLocalFlags() const { return tty.tty.c_lflag; }
    /** Set the specified local mode flags **/
    void setLocalFlags(unsigned flags);
    /** Unset the specified local mode flags **/
    void clearLocalFlags(unsigned flags);
    /** Returns the input flags **/
    unsigned getInputFlags() const { return tty.tty.c_iflag; }
    /** Set the specified input processing mode flags **/
    void setInputFlags(unsigned flags);
    /** Unset the specified input processing mode flags **/
    void clearInputFlags(unsigned flags);
    /** Returns the output flags **/
    unsigned getOutputFlags() const { return tty.tty.c_oflag; }
    /** Set the specified output processing mode flags **/
    void setOutputFlags(unsigned flags);
    /** Unset the specified output processing mode flags **/
    void clearOutputFlags(unsigned flags);
    /** Set the specified timeout **/
    void setTimeout(unsigned char index, cc_t value);
    /** Set VMIN and VTIME **/
    void setTimeouts(cc_t vmin, cc_t vtime);
    
private:
    struct termios2 tty;
};

/** Stream wrapper for serial ports **/
class SerialPort : public Wrapper {
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
    /** Argument for flush() **/
    enum Flush {
        /** Flushes data received but not read **/
        IFLUSH=TCIFLUSH,
        /** Flushes data written but not transmitted **/
        OFLUSH=TCOFLUSH,
        /** Flushes data received but not read and written but not transmitted **/
        IOFLUSH=TCIOFLUSH
    };
    /** Argument for flow() **/
    enum Flow {
        /** **/
        OOFF=TCOOFF,
        /** **/
        OON=TCOON,
        /** **/
        IOFF=TCIOFF,
        /** **/
        ION=TCION
    };
    /** Wrap the opened serial port **/
    explicit SerialPort(Stream &stream);
    /** Get the serial port configuration **/
    SerialPortConfiguration getConfiguration() const;
    /** Set the serial port configuration **/
    void setConfiguration(const SerialPortConfiguration &configuration);
    /** Get the serial port configuration **/
    SerialPortConfiguration2 getConfiguration2() const;
    /** Set the serial port configuration **/
    void setConfiguration2(const SerialPortConfiguration2 &configuration);
    /** Automatically configure the serial port **/
    void doAutoconfig();
    /** Get the lowlevel serial port information **/
    struct ::serial_struct getInformation() const;
    /** Set the lowlevel serial port information **/
    void setInformation(const struct ::serial_struct &information);
    /**/
    void sendBreak(int duration);
    /** Wait until all data previously written to the serial line **/
    void drain();
    /***/
    void flush(int queueSelector);
    /** Suspend or restart transmission on the serial port **/
    void flow(int action);
    /** Get the status of modem bits **/
    int getModemStatus() const;
    /** Set the status of modem bits **/
    void setModemStatus(int status);
    /** Clear the indicated modem bits **/
    void clearModemBits(int bits);
    /** Set the indicated modem bits **/
    void setModemBits(int bits);
    /** Wait for any of the 4 modem bits (DCD, RI, DSR, CTS) to change **/
    void waitModemBits(int bits);
    /** Get software carrier flag **/
    bool getSoftCarrier() const;
    /** Set software carrier flag **/
    void setSoftCarrier(bool softCarrier);
    /** Get counts of input serial line interrupts (DCD, RI, DSR, CTS) **/
    serial_icounter_struct getInterruptCount() const;
    /** Get line status register **/
    int getLineStatusRegister() const;
    /** Get output queue size **/
    int getOutputQueue() const;
    /** Insert the given byte in the input queue **/
    void unshift(char ch);
};

/** Stream wrapper for terminals **/
class Terminal : public SerialPort {
public:
    /** Terminal window size **/
    using WindowSize=struct ::winsize;
    /** Wrap the opened terminal **/
    explicit Terminal(Stream &stream);
    /** Returns whether the terminal is in exclusive mode **/
    bool getExclusive() const;
    /** Put the terminal into exclusive mode **/
    void setExclusive();
    /** Disable exclusive mode **/
    void clearExclusive();
    /** Get the line discipline of the terminal **/
    int getLineDiscipline() const;
    /** Set the line discipline of the terminal **/
    void setLineDiscipline(int lineDiscipline);
    /** Get the process group ID of the foreground process group on this terminal **/
    pid_t getProcessGroup() const;
    /** Set the foreground process group ID of this terminal **/
    void setProcessGroup(pid_t processGroup);
    /** Get the session ID of the given terminal **/
    int getSessionID() const;
    /** Get the window size **/
    WindowSize getWindowSize() const;
    /** Set the window size **/
    void setWindowSize(const WindowSize &windowSize);
    /** Make the given terminal the controlling terminal of the process **/
    void setControlling(bool steal);
    /** Give up this controlling terminal **/
    void resetControlling();
    /** Redirect the console output to this terminal **/
    void redirectConsole();
    /** Ask the terminal to be hung up **/
    void hangup();
    
};

}

#endif

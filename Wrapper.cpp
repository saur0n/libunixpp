#include "Wrapper.hpp"

using namespace upp;

/******************************************************************************/

Wrapper::Wrapper(Stream &stream) : stream(stream) {}

Wrapper::Wrapper(Stream::Standard no) : stream(Stream::get(no)) {}

int Wrapper::getDescriptor() const {
    return stream.getDescriptor();
}

unsigned Wrapper::ioctl(int request) {
    return stream.ioctl(request, nullptr);
}

unsigned Wrapper::ioctl(int request, void * argp) const {
    return stream.ioctl(request, argp);
}

unsigned Wrapper::ioctl(int request, const void * argp) {
    return stream.ioctl(request, argp);
}

unsigned Wrapper::ioctl(int request, int arg) {
    return stream.ioctl(request, arg);
}

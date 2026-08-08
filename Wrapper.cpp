#include "Wrapper.hpp"

using namespace upp;

/******************************************************************************/

Wrapper::Wrapper(Stream &stream) : stream(stream) {}

Wrapper::Wrapper(Stream::Standard no) : stream(Stream::get(no)) {}

int Wrapper::getDescriptor() const {
    return stream.getDescriptor();
}

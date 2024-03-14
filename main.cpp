#include <Pentagram.hpp>

int main(int argc, char *argv[])
{
    PNT::log.log(PNT::NOTE, "Hello", "test");
    PNT::log.log(PNT::NOTE, "Yello");
    PNT::initialize();
    return 0;
}

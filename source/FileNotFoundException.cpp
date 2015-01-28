
#include "SDLWrap/FileNotFoundException.hpp"

using namespace sdl;

FileNotFoundException::FileNotFoundException(const std::string &message) :
    std::runtime_error(message)
{ }
FileNotFoundException::FileNotFoundException(const std::string &message,
                                             const filesystem::path &path) :
    std::runtime_error(message + path.native())
{ }
FileNotFoundException::~FileNotFoundException() { }

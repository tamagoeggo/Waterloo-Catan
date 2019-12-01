#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <iostream>

enum class Resource {Caffeine, Lab, Lecture, Study, Tutorial, Netflix, None};

std::ostream &operator<<(std::ostream &out, const Resource &resource) {
    if (resource == Resource::Caffeine) {
        return out << "Caffeine";
    }
    else if (resource == Resource::Lab) {
        return out << "Lab";
    }
    else if (resource == Resource::Lecture) {
        return out << "Lecture";
    }
    else if (resource == Resource::Study) {
        return out << "Study";
    }
    else if (resource == Resource::Tutorial) {
        return out << "Tutorial";
    }
    else if (resource == Resource::Netflix) {
        return out << "Netflix";
    }
    else {
        return out << "Throw an exception in player ostream overload";
    }
}
#endif

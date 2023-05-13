module;

#include <iostream>

export module module_b;

import module_a;

export namespace modules{
class ClassB : public ClassA {
public:
    void foo() override
    {
        std::cout << "Hello module world!" << std::endl;
    }
};
}
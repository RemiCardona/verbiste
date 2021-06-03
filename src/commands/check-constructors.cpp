#include <verbiste/FrenchVerbDictionary.h>

void dummy()
{
    using namespace verbiste;

    FrenchVerbDictionary fvd0(true);
    FrenchVerbDictionary fvd1("", "", true, FrenchVerbDictionary::FRENCH);
}

int main()
{
    return 0;
}

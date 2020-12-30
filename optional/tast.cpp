#include "optional.hpp"
#include "../tast/tast_util.hpp"

int main(int argc, char* argv[])
{
    // std::string str(0);

    DESC("after default ctor");
    Int i;
    Double d;
    String s;

    COUT(i);
    COUT(d);
    COUT(s);
    COUT(!i);
    COUT(!d);
    COUT(!s.valid());
    COUT(i.has_value());
    COUT(d.has_value());
    COUT(s.has_value());

    DESC("i = 0; d = 0.0");
    i = 0;
    d = 0.0;
    COUT(i == true);
    COUT(d == true);
    COUT(i.has_value());
    COUT(d.has_value());

    DESC("i = 1; d = l.0");
    i = 1;
    d = 1.0;
    COUT(i == true);
    COUT(d == true);

    i = i + 1;
    COUT(i.value());
    COUT(i);

    DESC("set s = abc");
    s = "abc";
    COUT(s.value());
    COUT(s);

    DESC("asgin to native type");
    int ii = i;
    int dd = d;
    std::string ss = s;
    COUT(ii);
    COUT(dd);
    COUT(ss);
    return 0;
}

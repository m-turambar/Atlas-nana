#include "CajaListas.h"

CajaListas::CajaListas()
{
    lb.create(*this, nana::rectangle(10, 10, 400, 300), 1);
    lb.caption("Woot");
    lb.append_header("Header uno");
    lb.append_header("Que roles");
    auto cat = lb.at(0);
    cat.append({"Mike", "ftw"});
    cat.append({"Windows", "Super lame"});
}

CajaListas::~CajaListas()
{
    //dtor
}

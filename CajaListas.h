#ifndef CAJALISTAS_H
#define CAJALISTAS_H

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/listbox.hpp>

class CajaListas : public nana::form
{
public:
    CajaListas();
    ~CajaListas();

protected:

private:
        nana::listbox lb;
};

#endif // CAJALISTAS_H

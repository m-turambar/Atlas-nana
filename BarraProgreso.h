#ifndef BARRAPROGRESO_H
#define BARRAPROGRESO_H

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/progress.hpp>
#include <nana/system/timepiece.hpp>
#include <nana/system/platform.hpp>
#include <nana/system/dataexch.hpp>
#include <nana/system/shared_wrapper.hpp>
#include <nana/threads/pool.hpp>
#include "Dibujar.h"

class BarraProgreso : public nana::form
{
public:
    BarraProgreso();
    ~BarraProgreso();

private:
            volatile bool  working_ ;
            nana::button    btn_start_ ;
            nana::button    btn_cancel_ ;
            nana::progress prog_ ;
            nana::threads::pool pool_;
            elemento elem;
};

#endif // BARRAPROGRESO_H

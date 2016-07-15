#include "BarraProgreso.h"

BarraProgreso::BarraProgreso()
{
    btn_start_.create(*this, nana::rectangle(10, 10, 100, 20), 1);
    btn_start_.caption("Start");
    btn_start_.events().click(nana::threads::pool_push( pool_, [&]() {
        working_ = true;
        btn_start_.enabled(false);
        prog_.amount(1000);
        for(int i = 0; i < 1000 && working_; ++i)
        {
            nana::system::sleep(5); //a long-running simulation
            prog_.value(i + 1);
        }
        btn_start_.enabled(true);
        if(!working_)
            prog_.value(0);
    }));
    btn_start_.enabled(true);

    btn_cancel_.create(*this, nana::rectangle(120, 10, 100, 20));
    btn_cancel_.caption("Cancel");

    //si reseteas aqui prog_, al estar siendo modificada por dos hilos,
    //los dos hilos escribirán al mismo tiempo, por lo que habrá problemas. Mejor hacerlo en ambos
    btn_cancel_.events().click( [&](){working_ = false; prog_.value(0);});
    elem.create(*this, nana::rectangle(10, 100, 100, 30));
    elem.caption("wooooot");

    prog_.create(*this, nana::rectangle(10, 40, 280, 20));
}

BarraProgreso::~BarraProgreso()
{
    //dtor
}

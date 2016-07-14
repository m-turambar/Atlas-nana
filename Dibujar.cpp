#include "Dibujar.h"
#include <nana/paint/graphics.hpp>

/*
void B::attached(nana::widget& w, nana::paint::graphics& g)
{
    B::is_mouse_down_ = false;
    nana::window window = B::widget_->handle();
    make_drawer_event<nana::events::mouse_leave>(window);
    make_drawer_event<events::mouse_down>(window);
    make_drawer_event<events::mouse_up>(window);
    make_drawer_event<events::focus>(window);
}*/

Dibujar::Dibujar()
    :  dw(*this)
{
    dw.draw([](nana::paint::graphics& graph)
    {
        graph.rectangle(nana::rectangle{5, 5, 100, 100}, true, nana::colors::red);
    });
    dw.update();
}

Dibujar::~Dibujar()
{
    //dtor
}

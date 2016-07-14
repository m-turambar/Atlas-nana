#ifndef DIAGRAMA_H
#define DIAGRAMA_H

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/system/dataexch.hpp>
#include <nana/audio/player.hpp>
#include <nana/gui.hpp>

/*
using namespace nana;

class diagram_editor: public panel<true>
{
    using panel_type = panel<true>;
public:
    void create(window parent, const rectangle& r)
    {
        panel_type::create(parent, r);
        drawing dw(*this).draw([this](paint::graphics& graph)
        {
            _m_render(graph);
        });
    }

    void update()
    {
        API::refresh_window(*this);
    }

    void add(diagram_element* e)
    {
        elements_.push_back(e);
    }
private:
    void _m_render(paint::graphics& graph)
    {
        for(auto e : elements_)
            e->render(graph);
    }
private:
    std::vector<diagram_element*> elements_;
};
*/

#endif // DIAGRAMA_H


#ifndef DIBUJAR_H
#define DIBUJAR_H

#include <nana/gui/wvl.hpp>
#include <nana/paint/graphics.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/element.hpp>
#include <nana/gui/widgets/widget.hpp>
#include <nana/gui/basis.hpp>

template<typename DrawerTrigger>
class A: public nana::widget_object<nana::category::widget_tag, DrawerTrigger>
{
public:
    A() {}
    A(nana::widget& widget, nana::rectangle r) {this->create(widget.handle(), r);}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class B: public nana::drawer_trigger
{
public:
    B() : widget_(nullptr), is_mouse_down_(false), is_focus_(false) {};
    void bind_window(nana::widget& widget) {widget_ = &widget;}
    void set(nana::widget& w) {if(widget_==nullptr) widget_ = &w;}
private:
    void attached(nana::widget&, nana::paint::graphics&) override;
    void detached() override;
    void click(nana::paint::graphics&, const nana::arg_click&) override;
    void dbl_click(nana::paint::graphics&, const nana::arg_mouse&) override;
    void mouse_enter(nana::paint::graphics&, const nana::arg_mouse&) override;
    void mouse_move(nana::paint::graphics&, const nana::arg_mouse&) override;
    void mouse_leave(nana::paint::graphics&, const nana::arg_mouse&) override;
    void mouse_down(nana::paint::graphics&, const nana::arg_mouse&) override;
    void mouse_up(nana::paint::graphics&, const nana::arg_mouse&) override;
    void focus(nana::paint::graphics&, const nana::arg_focus&);
    void key_press(nana::paint::graphics&, const nana::arg_keyboard&);
private:
    void m_draw_title(nana::paint::graphics&, bool is_mouse_down, bool is_focus);
    void m_draw_background(nana::paint::graphics&, bool is_mouse_down);
    void m_draw_border(nana::paint::graphics&, bool is_mouse_down);

    nana::widget* widget_;
    bool is_mouse_down_;
    bool is_focus_;
};

class Dibujar : public nana::form
{
public:
    Dibujar();
    ~Dibujar();

protected:

private:
    nana::drawing dw;

};

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

#endif // DIBUJAR_H

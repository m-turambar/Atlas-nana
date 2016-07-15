#ifndef DIBUJAR_H
#define DIBUJAR_H

#include <nana/gui/wvl.hpp>
#include <nana/paint/graphics.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/element.hpp>
#include <nana/gui/widgets/widget.hpp>
#include <nana/gui/basis.hpp>

class gatillo: public nana::drawer_trigger
{
public:
    gatillo();
    ~gatillo();

   void emit_click();
   void icon(const nana::paint::image&);
   bool enable_pushed(bool);
   bool pushed(bool);
   bool pushed() const;
   void omitted(bool);
   bool focus_color(bool);

   nana::element::cite_bground& cite();
private:
    void attached(nana::widget&, nana::paint::graphics&) override;
    void refresh(nana::paint::graphics&) override;

    //void click(nana::paint::graphics&, const nana::arg_click&) override;
    //void dbl_click(nana::paint::graphics&, const nana::arg_mouse&) override;
    void mouse_enter(nana::paint::graphics&, const nana::arg_mouse&) override;
    //void mouse_move(nana::paint::graphics&, const nana::arg_mouse&) override;
    //void mouse_leave(nana::paint::graphics&, const nana::arg_mouse&) override;
    void mouse_down(nana::paint::graphics&, const nana::arg_mouse&) override;
    void mouse_up(nana::paint::graphics&, const nana::arg_mouse&) override;

    void focus(nana::paint::graphics&, const nana::arg_focus&);
    void key_press(nana::paint::graphics&, const nana::arg_keyboard&);
private:
    void _m_draw_title(nana::paint::graphics&, bool enabled);
    void _m_draw_background(nana::paint::graphics&);
    void _m_draw_border(nana::paint::graphics&);
    void _m_press(nana::paint::graphics&, bool);

private:
    nana::widget* wdgt_{nullptr};
    nana::paint::graphics* g_{nullptr};

    nana::element::cite_bground cite_{"BOSTON OK"};

    struct attr_tag
    {
        nana::element_state e_state;
        bool omitted;
        bool focused;
        bool pushed;
        bool keep_pressed;
        bool enable_pushed;
        bool focus_color;
        nana::paint::image * icon;
        ::nana::color bgcolor;
        ::nana::color fgcolor;
    }attr_;
};

class elemento: public nana::widget_object<nana::category::widget_tag, gatillo>
{
    using tipo_base = nana::widget_object<nana::category::widget_tag, gatillo>;
public:
    elemento();
    elemento(nana::window, bool);
    elemento(nana::window, const std::string&, bool visible=true);
    elemento(nana::window, const char*, bool visible=true);
    elemento(nana::window, const nana::rectangle& = nana::rectangle(), bool visible=true);

    elemento& icon(const nana::paint::image&);
    elemento& enable_pushed(bool);
    bool pushed() const;
    elemento& pushed(bool);
    elemento& omitted(bool); //habilita/deshabilita la omisión del despliegue de la "caption" si el texto es muy largo
    elemento& enable_focus_color(bool); //mostrar la capcion con un color especial para indicar si el boton está focuseado

    elemento& set_bground(const nana::pat::cloneable<nana::element::element_interface>&); //establece un elemento del bg definido por el usuario
    elemento& set_bground(const std::string&); //establece un bg prefedinido por nombre

    elemento& transparent(bool);
    bool transparent() const;

    elemento& edge_effects(bool enable);
private:
    //Overrideamos funciones virtuales de widget
    void _m_complete_creation() override; //el autocomplete te detecta funciones virtuales con color azul
    void _m_caption(nana::widget::native_string_type&&) override; //perdón, protected
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

#endif // DIBUJAR_H

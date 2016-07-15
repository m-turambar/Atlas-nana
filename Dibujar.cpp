#include "Dibujar.h"
#include <nana/paint/graphics.hpp>
#include <nana/paint/text_renderer.hpp>
#include <nana/gui/drawing.hpp> //no sé si necesario

#include <string>


gatillo::gatillo()
{
    attr_.e_state = nana::element_state::normal;
    attr_.omitted = attr_.focused = attr_.enable_pushed = attr_.keep_pressed = false;
    attr_.focus_color = true;
    attr_.icon = nullptr;
}

gatillo::~gatillo()
{
    delete attr_.icon;
}

void gatillo::attached(nana::widget& widget, nana::paint::graphics& g)
{
    g_ = &g;
    wdgt_ = &widget;
    nana::window wd = widget;

    nana::API::dev::enable_space_click(widget, true);
    nana::API::tabstop(wd);
    nana::API::effects_edge_nimbus(wd, nana::effects::edge_nimbus::active);
    nana::API::effects_edge_nimbus(wd, nana::effects::edge_nimbus::over);
}

bool gatillo::enable_pushed(bool eb)
{
    attr_.enable_pushed = eb;
    return ((eb == false) && pushed(false));
}

bool gatillo::pushed(bool pshd)
{
    if(pshd != attr_.pushed)
    {
        attr_.pushed = pshd;
        if(false == pshd)
        {
            if(nana::API::find_window(nana::API::cursor_position()) == wdgt_->handle())
                attr_.e_state = nana::element_state::hovered;
            else
                attr_.e_state = nana::element_state::normal;
        }
        else
            attr_.e_state = nana::element_state::pressed;

        return true;
    }
    return false;
}

bool gatillo::pushed() const
{
    return attr_.pushed;
}

void gatillo::omitted(bool om)
{
    attr_.omitted = om;
}

bool gatillo::focus_color(bool eb)
{
    if(eb != attr_.focus_color)
    {
        attr_.focus_color = eb;
        return true;
    }
    return false;
}

nana::element::cite_bground& gatillo::cite()
{
    return cite_;
}

void gatillo::refresh(nana::paint::graphics& g)
{
    bool eb = wdgt_->enabled();

    attr_.bgcolor = wdgt_->bgcolor();
    attr_.fgcolor = wdgt_->fgcolor();

    nana::element_state estado_e = attr_.e_state;
    if(eb)
    {
        if(attr_.focused)
        {
            if(nana::element_state::normal == estado_e)
                estado_e = nana::element_state::focus_normal;
            else if (nana::element_state::hovered == estado_e)
                estado_e = nana::element_state::focus_hovered;
        }
    }
    else
        estado_e = nana::element_state::disabled;

    if (false == cite_.draw(g, attr_.bgcolor, attr_.fgcolor, nana::rectangle{ g.size() }, estado_e))
    {
        if(nana::bground_mode::basic != nana::API::effects_bground_mode(wdgt_->handle()))
        {
            _m_draw_background(g);
            _m_draw_border(g);
        }
    }
    _m_draw_title(g, eb);
}

void gatillo::mouse_enter(nana::paint::graphics& g, const nana::arg_mouse&)
{
    attr_.e_state = (attr_.pushed || attr_.keep_pressed ? nana::element_state::pressed : nana::element_state::hovered);
    refresh(g);
    nana::API::lazy_refresh();
}

void gatillo::mouse_down(nana::paint::graphics& g, const nana::arg_mouse& arg)
{
    if(nana::mouse::left_button != arg.button)
        return;

    _m_press(g, true);
}

void gatillo::mouse_up(nana::paint::graphics& g, const nana::arg_mouse& arg)
{
    if(arg.button != nana::mouse::left_button)
        return;

    _m_press(g, false);
}

void gatillo::key_press(nana::paint::graphics& g, const nana::arg_keyboard& arg)
{
    bool ch_tabstop_next;
    switch(arg.key)
    {
    case nana::keyboard::os_arrow_left: case nana::keyboard::os_arrow_up:
        ch_tabstop_next = false;
        break;
    case nana::keyboard::os_arrow_right: case nana::keyboard::os_arrow_down:
        ch_tabstop_next = true;
        break;
    default:
        return;
    }

    nana::API::move_tabstop(*wdgt_, ch_tabstop_next);
}

void gatillo::focus(nana::paint::graphics& g, const nana::arg_focus& arg)
{
    attr_.focused = arg.getting; //la ventana recibió focus?
    refresh(g);
    nana::API::lazy_refresh();
}

void gatillo::_m_draw_title(nana::paint::graphics& g, bool enabled)
{
    wchar_t shortkey;
    std::string::size_type shortkey_pos;
    std::string mbstr = nana::API::transform_shortkey_text(wdgt_->caption(), shortkey, &shortkey_pos);
    std::wstring str = nana::to_wstring(mbstr);

    nana::size ts = g.text_extent_size(str);
    nana::size gsize = g.size();

    nana::size icon_sz;
    if(attr_.icon)
    {
        icon_sz = attr_.icon->size();
        icon_sz.width += 5; //ok??...
    }

    nana::point pos {static_cast<int>(gsize.width-1-ts.width) >> 1,
        static_cast<int>(gsize.height-1-ts.height) >> 1};

    if(pos.x < static_cast<int>(icon_sz.width))
        pos.x = static_cast<int>(icon_sz.width);

    unsigned pixeles_omitidos = gsize.width - icon_sz.width;
    std::size_t txtlen = str.size();
    const auto txtptr = str.c_str();
    if(ts.width)
    {
        nana::paint::text_renderer tr(g); //aquí se declara tr
        if(enabled)
        {
            if (attr_.e_state == nana::element_state::pressed)
                ++pos.x, ++pos.y;

            g.palette(true, attr_.focus_color && attr_.focused ? nana::color(nana::colors::purple) : attr_.fgcolor);

            if(attr_.omitted)
                tr.render(pos, txtptr, txtlen, pixeles_omitidos, true);
            else
                g.bidi_string(pos, txtptr, txtlen);

            if(shortkey)
            {
                unsigned off_w = (shortkey_pos ? g.text_extent_size(mbstr.c_str(), static_cast<unsigned>(shortkey_pos)).width : 0);

                wchar_t keystr[2] = {nana::utf::char_at(mbstr.c_str() + shortkey_pos, 0, 0), 0};
                auto shortkey_size = g.text_extent_size(keystr, 1);

                unsigned ascent, descent, inleading; //NO MAMEEES YA QUE ACABE
                g.text_metrics(ascent, descent, inleading);

                pos.x += off_w;
                pos.y += static_cast<int>(ascent + 2);

                g.line(pos, nana::point {
                    pos.x + static_cast<int>(shortkey_size.width) - 1, pos.y }, nana::colors::gold);
            }
        }
        else
        {
            g.palette(true, nana::color(nana::colors::brown));

            if(attr_.omitted)
            {
                tr.render(nana::point{pos.x + 1, pos.y + 1}, txtptr, txtlen, pixeles_omitidos, true);
                g.palette(true, nana::color(nana::colors::gray));
                tr.render(nana::point{pos.x + 1, pos.y +1 }, txtptr, txtlen, pixeles_omitidos, true);
            }
            else
            {
                g.bidi_string(nana::point{pos.x + 1, pos.y + 1}, txtptr, txtlen);
                g.palette(true, nana::color(nana::colors::gray));
                g.bidi_string(pos, txtptr, txtlen);
            }
        }

        if(attr_.icon)
            attr_.icon->paste(g, nana::point{ 3, static_cast<int>(gsize.height - icon_sz.height)/2 });

    }
}

void gatillo::_m_draw_background(nana::paint::graphics& g)
{
    using namespace nana;
    rectangle r(g.size());
    r.pare_off(1);

    auto from = attr_.bgcolor.blend(colors::white, 0.2);
    auto to = attr_.bgcolor.blend(colors::black, 0.95);

    if (element_state::pressed == attr_.e_state)
    {
        r.x = r.y = 2;
        std::swap(from, to);
    }
    g.gradual_rectangle(r, from, to, true);
}

void dibujar_punto_esquina(nana::paint::graphics& g, const nana::rectangle& r)
{
    g.set_pixel(r.x, r.y);
    g.set_pixel(r.right() - 1, r.y);
    g.set_pixel(r.right() - 1, r.bottom() - 1);
    g.set_pixel(r.x, r.bottom() - 1);
}

void gatillo::_m_draw_border(nana::paint::graphics& g)
{
    using namespace nana;
    rectangle r(g.size());

    color lt(static_cast<color_rgb>(0x7f7f7f)), rb(static_cast<color_rgb>(0x707070));
    g.frame_rectangle(r, lt, lt, rb, rb);

    g.palette(false, colors::button_face);
    dibujar_punto_esquina(g, r.pare_off(1));

    if(attr_.e_state == element_state::pressed)
        g.rectangle(r, false, static_cast<color_rgb>(0xc3c3c3));
}

void gatillo::_m_press(nana::paint::graphics& g, bool esta_presionado)
{
    using namespace nana;
    if(esta_presionado)
    {
        if(attr_.e_state == element_state::pressed)
            return;

        attr_.e_state = element_state::pressed;
        attr_.keep_pressed = true;
        API::capture_window(*wdgt_, true);
    }
    else
    {
        API::capture_window(*wdgt_, false);
        attr_.keep_pressed = false;
        if (attr_.enable_pushed && (attr_.pushed == false))
        {
            attr_.pushed = true;
            return;
        }

        if(attr_.e_state == element_state::pressed)
            attr_.e_state = element_state::hovered;
        else
            attr_.e_state = element_state::normal;

        attr_.pushed = false;
    }

    refresh(g);
    API::lazy_refresh();
}

void gatillo::emit_click()
{
    using namespace nana;
    arg_click arg;
    arg.window_handle = wdgt_->handle();
    arg.mouse_args = nullptr;
    API::emit_event(event_code::click, arg.window_handle, arg);
}

void gatillo::icon(const nana::paint::image& img)
{
    if(img.empty())
        return;
    if(nullptr == attr_.icon)
        attr_.icon = new nana::paint::image;
    *attr_.icon = img; //cómo supo cuánta memoria reservar?
}

//////////////////// elemento /////////////////////////////
elemento::elemento() {}

elemento::elemento(nana::window wd, bool visible)
{
    create(wd, nana::rectangle(), visible);
}

elemento::elemento(nana::window wd, const std::string& texto, bool visible)
{
    create(wd, nana::rectangle(), visible);
    nana::widget::caption(texto);
}

elemento::elemento(nana::window wd, const char* texto, bool visible)
{
    create(wd, nana::rectangle(), visible);
    nana::widget::caption(texto);
}

elemento::elemento(nana::window wd, const nana::rectangle& r, bool visible)
{
    create(wd, r, visible);
}

elemento& elemento::icon(const nana::paint::image& img)
{
    nana::internal_scope_guard isg;
    get_drawer_trigger().icon(img);
    nana::API::refresh_window(handle());
    return *this;
}

elemento& elemento::enable_pushed(bool eb)
{
    nana::internal_scope_guard isg;
    if(get_drawer_trigger().enable_pushed(eb))
        nana::API::refresh_window(handle());
    return *this;
}

bool elemento::pushed() const
{
    return get_drawer_trigger().pushed();
}

elemento& elemento::pushed(bool psd)
{
    nana::internal_scope_guard isg;
    if(get_drawer_trigger().pushed(psd))
        nana::API::refresh_window(handle());
    return *this;
}

elemento& elemento::omitted(bool om)
{
    nana::internal_scope_guard isg;
    get_drawer_trigger().omitted(om);
    nana::API::refresh_window(handle());
    return *this;
}

elemento& elemento::enable_focus_color(bool eb)
{
    nana::internal_scope_guard lock;
    if(get_drawer_trigger().focus_color(eb))
        nana::API::refresh_window(handle());
    return *this;
}

elemento& elemento::set_bground(const nana::pat::cloneable<nana::element::element_interface>& rv)
{
    nana::internal_scope_guard lock;
    get_drawer_trigger().cite().set(rv);
    return *this;
}

elemento& elemento::set_bground(const std::string& s)
{
    nana::internal_scope_guard lock;
    get_drawer_trigger().cite().set(s.data());
    return *this;
}

elemento& elemento::transparent(bool enabled)
{
    if(enabled)
        nana::API::effects_bground(*this, nana::effects::bground_transparent(0), 0.0);
    else
        nana::API::effects_bground_remove(*this);
    return *this;
}

bool elemento::transparent() const
{
    return (nana::bground_mode::basic == nana::API::effects_bground_mode(*this));
}

elemento& elemento::edge_effects(bool enable)
{
    using namespace nana;
    if (enable)
    {
        API::effects_edge_nimbus(*this, effects::edge_nimbus::active);
        API::effects_edge_nimbus(*this, effects::edge_nimbus::over);
    }
    else
        API::effects_edge_nimbus(*this, effects::edge_nimbus::none);

    return *this;
}

void elemento::_m_complete_creation()
{
    using namespace nana;
    events().shortkey.connect_unignorable([this]
    {
        get_drawer_trigger().emit_click();
    });
}

void elemento::_m_caption(nana::widget::native_string_type&& s)
{
    using namespace nana;
    API::unregister_shortkey(handle());

    wchar_t shortkey;
    API::transform_shortkey_text(to_utf8(s), shortkey, nullptr);
    if(shortkey)
        API::register_shortkey(handle(), shortkey);
    tipo_base::_m_caption(std::move(s));
}

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

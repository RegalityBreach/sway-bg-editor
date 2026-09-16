#include "window.h"
#include <iostream>

Window::Window()
{
    m_folder_selector.LoadConfig();

    m_backgrounds_list.ReloadBackgrounds(m_folder_selector);

    // Put your window setup code here!
    set_title("Sway Background Editor");
    set_default_size(500, 400);

    m_overlay.set_child(m_scroll_frame);
    m_overlay.add_overlay(m_header_label);

    m_header_label.set_valign(Gtk::Align::START);
    m_header_label.set_halign(Gtk::Align::FILL);

    m_header_label.add_css_class("header-label");
    m_scroll_frame.add_css_class("scroll-frame");
    m_folder_selector.add_css_class("folder-selector");
    m_backgrounds_list.add_css_class("backgrounds-list");

    m_box.append(m_overlay);
    m_box.append(m_folder_selector);

    m_backgrounds_list.set_vexpand(true);

    m_scroll_frame.set_child(m_backgrounds_list);
    set_child(m_box);

    m_folder_selector.get_reload_button().signal_clicked().connect([this]() {
        m_backgrounds_list.ReloadBackgrounds(m_folder_selector);
    });

    // LOADING CSS
    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_path("css/style.css");

    Gtk::StyleProvider::add_provider_for_display(
        get_display(),
        css_provider,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}
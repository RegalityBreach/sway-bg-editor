#pragma once

#include <gtkmm/window.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/overlay.h>
#include "backgroundslist.h"
#include "folderselector.h"

class Window : public Gtk::Window {
public:
	Window();
	// Destructor! override = default means to override the constructor code and set it to the default.
	~Window() override = default;
private:
	Gtk::Label m_header_label{"Select a background."};
	Gtk::Box m_box{Gtk::Orientation::VERTICAL};
	Gtk::Frame m_scroll_frame;
	Gtk::Overlay m_overlay;
	BackgroundsList m_backgrounds_list;
	FolderSelector m_folder_selector;
};
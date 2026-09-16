#pragma once

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <string>

class FolderSelector;

class BackgroundsList : public Gtk::ScrolledWindow 
{
public:
	BackgroundsList();
	~BackgroundsList() override = default;
	void ReloadBackgrounds(FolderSelector& selector);
private:
	Gtk::Box m_box{Gtk::Orientation::VERTICAL};
};
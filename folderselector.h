#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <iostream>

class FolderSelector : public Gtk::Box
{
public:
	FolderSelector();
	~FolderSelector() override = default;

	std::string get_folder_path() const;
	std::string get_result_path() const;
	Gtk::Button& get_reload_button();

	void Select();
	void SelectResult();

	void SaveConfig() const;
	void LoadConfig();
private:
	std::string m_folder_path = "";
	std::string m_result_path = "";
	Gtk::Button m_folder_button{"Select folder"};
	Gtk::Button m_result_button{"Select result folder"};
	Gtk::Button m_reload_button{"Reload folder"};

	const std::string m_config_file;
};
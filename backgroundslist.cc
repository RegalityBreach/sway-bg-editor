#include "backgroundslist.h"
#include "folderselector.h"
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <filesystem>
#include <iostream>
#include <cstdlib>

namespace fs = std::filesystem;

BackgroundsList::BackgroundsList()
{
	// Only add scrollbars if needed.
	set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
	
	set_child(m_box);
}

void BackgroundsList::ReloadBackgrounds(FolderSelector& selector)
{
	std::string path = selector.get_folder_path();
	std::string result_path = selector.get_result_path();

	while (auto child = m_box.get_first_child()) {
		m_box.remove(*child);
	}

	// Check if the path exists and that the path is a directory.
	if (path == "") {
		auto* entry_box = Gtk::manage(new Gtk::Box(Gtk::Orientation::HORIZONTAL, 5));
		entry_box->add_css_class("background-entry");
		entry_box->set_hexpand(true);

		auto* label = Gtk::manage(new Gtk::Label("No folder selected, please select a folder to browse."));
		label->set_hexpand(true);
		label->set_halign(Gtk::Align::CENTER);
		label->set_valign(Gtk::Align::CENTER);
		label->add_css_class("singular-bel");

		entry_box->append(*label);
		m_box.append(*entry_box);
	}
	if (result_path == "") {
		auto* entry_box = Gtk::manage(new Gtk::Box(Gtk::Orientation::HORIZONTAL, 5));
		entry_box->add_css_class("background-entry");
		entry_box->set_hexpand(true);

		auto* label = Gtk::manage(new Gtk::Label("No result folder selected, please select a folder to apply wallpaper."));
		label->set_hexpand(true);
		label->set_halign(Gtk::Align::CENTER);
		label->set_valign(Gtk::Align::CENTER);
		label->add_css_class("singular-bel");

		entry_box->append(*label);
		m_box.append(*entry_box);
	}

	if (!fs::exists(path) || !fs::is_directory(path)) {
		std::cerr << "Folder path does not exist: " << path << "\n";
		return;
	}

	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_regular_file() && (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")) {
			auto* entry_box = Gtk::manage(new Gtk::Box(Gtk::Orientation::HORIZONTAL, 5));
			entry_box->add_css_class("background-entry");
			entry_box->set_hexpand(true);

			std::string path_string = entry.path().string();

			auto pixbuf = Gdk::Pixbuf::create_from_file(entry.path().string());
			auto* image = Gtk::manage(new Gtk::Image(pixbuf));
			image->set_pixel_size(100);
			image->set_valign(Gtk::Align::CENTER);
			image->add_css_class("background-entry-image");

			auto* label = Gtk::manage(new Gtk::Label(entry.path().filename().string()));
			label->set_hexpand(true);
			label->set_halign(Gtk::Align::CENTER);
			label->set_valign(Gtk::Align::CENTER);
			label->add_css_class("background-entry-label");

			auto* button = Gtk::manage(new Gtk::Button("Apply"));
			button->set_valign(Gtk::Align::CENTER);
			button->add_css_class("background-entry-button");

			button->signal_clicked().connect([this, result_path, path_string]() {
				if (result_path == "" || !fs::exists(result_path) || !fs::is_directory(result_path)) {
					return;
				}

				std::string output = result_path + "/swaybg-wallpaper.png";
				std::string command = "ffmpeg -y -i " + path_string + " -update 1 " + output;
				int result = std::system(command.c_str());

				if (result == 0) {
					std::string reload = "swaymsg reload";
					std::system(reload.c_str());
				}
			});

			entry_box->append(*image);
			entry_box->append(*label);
			entry_box->append(*button);
			m_box.append(*entry_box);
		}
	}
}
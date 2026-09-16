#include "folderselector.h"
#include "backgroundslist.h"
#include <gtkmm/filedialog.h>
#include <gtkmm/button.h>
#include <iostream>
#include <glibmm.h>
#include <glibmm/miscutils.h>

FolderSelector::FolderSelector()
    : m_config_file(Glib::build_filename(Glib::get_user_config_dir(), "sway-bg-editor.ini"))
{
    set_orientation(Gtk::Orientation::HORIZONTAL);
    
    set_halign(Gtk::Align::FILL);

	append(m_folder_button);
    append(m_result_button);
	append(m_reload_button);

	add_css_class("folder-selector");

	m_folder_button.set_hexpand(true);
	m_reload_button.set_hexpand(true);
    m_result_button.set_hexpand(true);

	m_folder_button.signal_clicked().connect(sigc::mem_fun(*this, &FolderSelector::Select));
    m_result_button.signal_clicked().connect(sigc::mem_fun(*this, &FolderSelector::SelectResult));
}

std::string FolderSelector::get_folder_path() const
{
    return m_folder_path;
}

std::string FolderSelector::get_result_path() const
{
    return m_result_path;
}

Gtk::Button& FolderSelector::get_reload_button()
{
    return m_reload_button;
}

void FolderSelector::Select()
{
    m_folder_button.set_sensitive(false);

    auto dialog = Gtk::FileDialog::create();
    dialog->set_title("Select Folder");

    dialog->select_folder([this, dialog](const Glib::RefPtr<Gio::AsyncResult>& result) {
        try {
            auto file = dialog->select_folder_finish(result);
            if (file) {
                m_folder_path = file->get_path();
                std::cout << "Selected folder: " << file->get_path() << std::endl;
            }
        } catch (const Glib::Error& err) {
            std::cerr << "Cancelled or error: " << err.what() << std::endl;
        }

        m_folder_button.set_sensitive(true);
        SaveConfig();
    });
}

void FolderSelector::SelectResult()
{
    m_folder_button.set_sensitive(false);

    auto dialog = Gtk::FileDialog::create();
    dialog->set_title("Select Folder");

    dialog->select_folder([this, dialog](const Glib::RefPtr<Gio::AsyncResult>& result) {
        try {
            auto file = dialog->select_folder_finish(result);
            if (file) {
                m_result_path = file->get_path();
                std::cout << "Selected folder: " << file->get_path() << std::endl;
            }
        } catch (const Glib::Error& err) {
            std::cerr << "Cancelled or error: " << err.what() << std::endl;
        }

        m_folder_button.set_sensitive(true);
        SaveConfig();
    });
}

void FolderSelector::SaveConfig() const {
    auto key_file = Glib::KeyFile::create();
    key_file->set_string("Paths", "Folder", m_folder_path);
    key_file->set_string("Paths", "ResultFolder", m_result_path);

    try {
        key_file->save_to_file(m_config_file);
    } catch (const Glib::Error& err) {
        std::cerr << "Failed to save config: " << err.what() << std::endl;
    }
}

void FolderSelector::LoadConfig() {
    auto key_file = Glib::KeyFile::create();
    try {
        key_file->load_from_file(m_config_file);
        
        if (key_file->has_key("Paths", "Folder"))
            m_folder_path = key_file->get_string("Paths", "Folder");
            
        if (key_file->has_key("Paths", "ResultFolder"))
            m_result_path = key_file->get_string("Paths", "ResultFolder");
            
    } catch (const Glib::Error& ex) {
        // File doesn't exist yet, which is fine on first launch
    }
}
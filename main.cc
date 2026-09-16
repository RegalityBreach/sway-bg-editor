#include "window.h"
#include <gtkmm/application.h>

int main(int argc, char* argv[]) {
	auto app = Gtk::Application::create("org.gtkmm.sway-bg-editor");

	return app->make_window_and_run<Window>(argc, argv);
}
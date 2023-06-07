#include <gtkmm.h>
#include <iostream>
#include <regex>
#include <cstdlib>

class MyWindow : public Gtk::Window {
public:
  MyWindow() : Gtk::Window(), text_entry1(), text_entry2() {
    set_title("Whatsapp Link Maker");
    set_default_size(400, 200);
    set_border_width(10);

    Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox());
    add(*vbox);

    // Create an image widget with a URL
    Gtk::Image* image = Gtk::manage(new Gtk::Image());
    image->set_from_file("https://example.com/path/to/your/image.jpg");
    vbox->pack_start(*image, Gtk::PACK_SHRINK, 0);

    text_entry1.set_text("Numero de telefone aqui, EX: 5521999999999");
    vbox->pack_start(text_entry1, Gtk::PACK_SHRINK, 0);

    text_entry2.set_text("Mensagem aqui, EX: Oi, tudo bem?");
    vbox->pack_start(text_entry2, Gtk::PACK_SHRINK, 0);

    Gtk::Button* button = Gtk::manage(new Gtk::Button("Criar Link"));
    button->signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));
    vbox->pack_start(*button, Gtk::PACK_SHRINK, 0);

    show_all_children();

    signal_delete_event().connect(sigc::mem_fun(*this, &MyWindow::on_delete_event));
  }

private:
  Gtk::Entry text_entry1;
  Gtk::Entry text_entry2;

  void on_button_clicked() {
    std::string text1 = text_entry1.get_text();
    text1 = std::regex_replace(text1, std::regex("\\D"), "");

    std::string text2 = text_entry2.get_text();

    std::string base_link = "http://wa.me/";
    std::string base_msg = "?text=";

    std::string encoded_text2 = Glib::uri_escape_string(text2);

    std::string result_link = base_link + text1 + base_msg + encoded_text2;

    std::string command = "xdg-open " + result_link;
    std::system(command.c_str());
  }

  bool on_delete_event(GdkEventAny*)
  {
    // Handle the delete event here
    // ...

    // Return true to stop further processing or false to allow default handling
    return false;
  }
};

int main(int argc, char* argv[]) {
  Gtk::Main kit(argc, argv);

  MyWindow window;
  Gtk::Main::run(window);

  return 0;
}

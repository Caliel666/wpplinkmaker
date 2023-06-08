#include <gtkmm.h>
#include <iostream>
#include <regex>
#include <cstdlib>
class MyWindow : public Gtk::Window {
public:
  MyWindow() : Gtk::Window(), vbox(), text_label1(), text_entry1(), text_label2(), text_entry2() {
    set_title("Whatsapp Link Maker");
    set_default_size(400, 180);
    set_border_width(10);
    vbox = Gtk::manage(new Gtk::VBox());
    add(*vbox);
    text_label1.set_text("Numero de telefone aqui, EX: 5521999999999");
    vbox->pack_start(text_label1, Gtk::PACK_SHRINK, 0);
    text_entry1.set_placeholder_text("Numero de celular");
    vbox->pack_start(text_entry1, Gtk::PACK_SHRINK, 0);
    text_label2.set_text("Mensagem aqui, EX: Oi, tudo bem?");
    vbox->pack_start(text_label2, Gtk::PACK_SHRINK, 0);
    text_entry2.set_placeholder_text("Mensagem");
    vbox->pack_start(text_entry2, Gtk::PACK_SHRINK, 0);
    Gtk::Button* button = Gtk::manage(new Gtk::Button("Criar Link"));
    button->signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));
    vbox->pack_start(*button, Gtk::PACK_SHRINK, 0);
    show_all_children();
    signal_delete_event().connect(sigc::mem_fun(*this, &MyWindow::on_delete_event));
  }
private:
  Gtk::VBox* vbox;
  Gtk::Label text_label1;
  Gtk::Entry text_entry1;
  Gtk::Label text_label2;
  Gtk::Entry text_entry2;
  void on_button_clicked() {
    std::string text1 = text_entry1.get_text();
    text1 = std::regex_replace(text1, std::regex("\\D"), "");
    std::string text2 = text_entry2.get_text();
    std::string base_link = "https://web.whatsapp.com/send/?phone=";
    std::string base_msg = "&text=";
    std::string base_type = "&type=phone_number&app_absent=0";
    std::string encoded_text2 = Glib::uri_escape_string(text2);
    std::string result_link = base_link + text1;
    if (!encoded_text2.empty()) {
      result_link += base_msg + encoded_text2;
    }
    result_link += base_type;
    std::string command = "xdg-open \"" + result_link + "\"";
    std::system(command.c_str());
  }
};
int main(int argc, char* argv[]) {
  Gtk::Main kit(argc, argv);
  MyWindow window;
  Gtk::Main::run(window);
  return 0;
}

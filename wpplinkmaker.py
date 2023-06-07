import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk
import webbrowser
import urllib.parse
import re

class MyWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Whatsapp Link Maker")
        self.set_default_size(400, 200)  # Set custom width and height
        self.set_border_width(10)

        # Vertical box container
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        self.add(vbox)

        # First Text Entry
        self.text_entry1 = Gtk.Entry()
        self.text_entry1.set_text("Numero de telefone aqui, EX: 5521999999999")
        vbox.pack_start(self.text_entry1, True, True, 0)

        # Second Text Entry
        self.text_entry2 = Gtk.Entry()
        self.text_entry2.set_text("Mensagem aqui, EX: Oi, tudo bem?")
        vbox.pack_start(self.text_entry2, True, True, 0)

        # Button
        button = Gtk.Button.new_with_label("Criar Link")
        button.connect("clicked", self.on_button_clicked)
        vbox.pack_start(button, True, True, 0)

    def on_button_clicked(self, widget):
        text1 = self.text_entry1.get_text()
        text1 = re.sub(r'\D', '', text1)

        text2 = self.text_entry2.get_text()

        # Define your web link here
        base_link = "http://wa.me/"
        base_msg = "?text="

        # Convert spaces to "%20" in the second text
        encoded_text2 = urllib.parse.quote_plus(text2)

        # Append text to the web link
        result_link = base_link + text1 + base_msg + encoded_text2

        # Open the resulting link in a web browser
        webbrowser.open(result_link)

win = MyWindow()
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()


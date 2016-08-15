#include <gtk/gtk.h>


int main(int argc, char *argv[])
{
  GtkBuilder      *pending_builder;
  GtkWidget       *pending_window;

  gtk_init(&argc, &argv);

  pending_builder = gtk_builder_new();
  gtk_builder_add_from_file (pending_builder, "glade/pending_window.glade", NULL);

  pending_window = GTK_WIDGET(gtk_builder_get_object(pending_builder, "pending_window"));
  gtk_builder_connect_signals(pending_builder, NULL);

  //label_mensaje = GTK_WIDGET(gtk_builder_get_object(pending_builder, "label_mensaje"));
  g_object_unref(pending_builder);



  gtk_widget_show(pending_window);
  gtk_main();

  return 0;
}
void on_btn_terminar_clicked(){
  gtk_main_quit();
}

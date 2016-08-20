#include <gtk/gtk.h>



int main(int argc, char *argv[])
{
  GtkBuilder      *floyd_builder;
  GtkWidget       *floyd_window;
  GtkWidget       *table;
  GtkWidget       *entry1;
  GtkEntryBuffer  *buffer1;
  char str[15];

  int i,j;



  /*--- CSS -----------------*/
GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
/*-------------------------*/

  gtk_init(&argc, &argv);

  floyd_builder = gtk_builder_new();
  gtk_builder_add_from_file (floyd_builder, "glade/floyd_window.glade", NULL);

  floyd_window = GTK_WIDGET(gtk_builder_get_object(floyd_builder, "floyd_window"));
  gtk_builder_connect_signals(floyd_builder, NULL);

  table= gtk_grid_new();
  //table = GTK_WIDGET(gtk_builder_get_object(floyd_builder, "table");
  gtk_grid_set_row_spacing (GTK_GRID (table), 2);
  gtk_container_add (GTK_CONTAINER (floyd_window), table);


  for(i=0;i<=5;i++){
    for(j=0;j<=5;j++){
      buffer1= gtk_entry_buffer_new(NULL,-1);

      entry1 = gtk_entry_new_with_buffer(buffer1);
      gtk_grid_attach (GTK_GRID (table),entry1 , i, j, 1, 1);


    }
  }





  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gsize bytes_written, bytes_read;

  const gchar* home = "css/style.css";  // your path, for instance: /home/zerohour/Documents/programming/cssexternal.css

  GError *error = 0;

  gtk_css_provider_load_from_path (provider,
                                    g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),
                                    NULL);

  g_object_unref(floyd_builder);



  gtk_widget_show_all(floyd_window);
  gtk_main();

  return 0;

}

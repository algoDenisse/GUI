#include <gtk/gtk.h>

GtkWidget       *entry_grid_size;
int n;

static void generate_D1 (GtkWidget *widget, gpointer   data){
    GtkWidget  *entrada;
    entrada = gtk_entry_new();

    //char *column_names[n];
    char *column_names = calloc(n, 100*sizeof(char));

    int distancias[n];
    int matriz_distancias[n][n];


    int j,k,i, g =0;

    for(k =0; k< n+1;k++){
      for(j=0;j<n+1;j++){
        entrada = gtk_grid_get_child_at (data, j, k);

        //Guardamos valor de las column_names
        if (k !=0 && j == 0){
          printf("%s\n",gtk_entry_get_text(entrada) );
          g_stpcpy(column_names[i],gtk_entry_get_text(entrada));
          //printf("column -> %s\n", column_names[i] );
          i++;
        }
       if (k !=0 && j != 0){

       }
    }
    //gtk_widget_hide (widget);
}

}


void button_crear_grid_clicked_cb(){
  GtkBuilder      *floyd_builder;
  GtkWidget       *floyd_window;
  GtkWidget       *table;
  GtkWidget       *button;
  GtkWidget       *button_box;

  const char *alphabet[27]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","Ñ","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

  /*--- CSS -----------------*/
GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
/*-------------------------*/

  floyd_builder = gtk_builder_new();
  gtk_builder_add_from_file (floyd_builder, "glade/floyd_window.glade", NULL);

  floyd_window = GTK_WIDGET(gtk_builder_get_object(floyd_builder, "floyd_window"));
  gtk_builder_connect_signals(floyd_builder, NULL);



  table= gtk_grid_new();
  gtk_grid_set_row_spacing (GTK_GRID (table), 2);
  gtk_container_add (GTK_CONTAINER (floyd_window), table);




  GtkWidget ***entrada;

  printf("%s\n",gtk_entry_get_text (entry_grid_size) );

  n = atoi(gtk_entry_get_text (entry_grid_size));
  //gtk_entry_get_text (entry_grid_size);

  int j,k,i;
  entrada=calloc(n+1,sizeof(GtkWidget**));
  for(j = 0; j < n+1; j++){
    entrada[j]=calloc(n+1,sizeof(GtkWidget*));
  }
  for(k =0; k< n+1;k++){
    for(j=0;j<n+1;j++){

      entrada[k][j]= gtk_entry_new();
      gtk_grid_attach (GTK_GRID (table),entrada[k][j] , k, j, 1, 1);
      if(k==j && k != 0 && j != 0){
        gtk_entry_set_text (entrada[k][j],"0");
      }
      if (k == 0 && j != 0){
        gtk_entry_set_text (entrada[k][j],alphabet[j-1]);
      }
      if (j ==0 && k!=0){
        gtk_entry_set_text (entrada[k][j],alphabet[k-1]);
      }
    }
  }

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_grid_attach (GTK_GRID (table),button_box , n/2, j, 1, 1);

  button = gtk_button_new_with_label ("Generar D(1)");
  g_signal_connect (button, "clicked", G_CALLBACK (generate_D1), (gpointer) table);
  gtk_container_add (GTK_CONTAINER (button_box), button);


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

}



int main(int argc, char *argv[])
{

  GtkBuilder      *initial_floyd_builder;
  GtkWidget       *initial_floyd_window;

  /*--- CSS -----------------*/
GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
/*-------------------------*/

  gtk_init(&argc, &argv);

  initial_floyd_builder = gtk_builder_new();
  gtk_builder_add_from_file (initial_floyd_builder, "glade/initial_floyd.glade", NULL);

  initial_floyd_window = GTK_WIDGET(gtk_builder_get_object(initial_floyd_builder, "initial_floyd_window"));
  entry_grid_size = GTK_WIDGET(gtk_builder_get_object(initial_floyd_builder, "entry_grid_size"));


  gtk_builder_connect_signals(initial_floyd_builder,NULL);

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

  g_object_unref(initial_floyd_builder);



  gtk_widget_show_all(initial_floyd_window);
  gtk_main();

  return 0;

}

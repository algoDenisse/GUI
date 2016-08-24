#include <gtk/gtk.h>
#define INF 99999
GtkWidget       *entry_grid_size;

int n;
int **global_distance_mtx;
char **column_names;
const char *alphabet[27]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","Ñ","O","P","Q","R","S","T","U","V","W","X","Y","Z"};


static void generate_D1 (GtkWidget *widget, gpointer   data){
    GtkWidget  *entrada;
    gchar* entrance;
    entrada = gtk_entry_new();
    int i;
    //alojar memoria matriz global
    printf("%s\n"," alojar memoria matriz global");
    global_distance_mtx = calloc(n, 1+sizeof(int*));
    for (i = 0; i < n; ++i) {
        global_distance_mtx[i] = calloc(n,sizeof(int));
    }

    //alojamos la menmoria para el array
      printf("%s\n","alojamos la menmoria para el array");
    column_names =  calloc(n, 500*sizeof(gchar));
    //alojamos la memoria para cada espacio del char

    for (i = 0; i < n; ++i) {
        column_names[i] = (char *)malloc(500);
    }
    entrance = calloc(1, 500*sizeof(gchar));

    //alojamos memoria de lamatriz de distancias
    int **matriz_distancias = calloc(n, 1+sizeof(int*));

    for (i = 0; i < n; ++i) {
        matriz_distancias[i] = calloc(n,sizeof(int));
    }
    int j,k;
    i=0;
    for(k =0; k< n+1;k++){
      //printf("Entro al primer FOR\n" );
      for(j=0;j<n+1;j++){
        //printf("Entro al segundo FOR\n" );
        entrada = gtk_grid_get_child_at (data, k, j);
        g_stpcpy(entrance,gtk_entry_get_text(entrada));
        //Guardamos valor de las column_names
        if (k !=0 && j == 0){

          strcpy(column_names[i],entrance);
        //  printf("Nombre de la columna posicion %d, %d = %s\n",j, k ,entrance);
          i++;
        }
        //GUardamos el valor de los numeros en la matriz
        if (k!=0 && j!=0){
          if (strcmp(entrance, "INF")==0){
            //printf("%s\n","Encontre un infinito!" );
            matriz_distancias[j-1][k-1]  = 99999;
          }
          else{
            matriz_distancias[j-1][k-1] = atoi(entrance);
            //  printf("Valor de la entrada %d, %d = %d\n",j, k, atoi(entrance));
          }

        }
    }

}
  // for(i = 0; i < n ; i++){
  //   printf("Columna %s\n", column_names[i] );
  // }
  generate_Dn(matriz_distancias, 1);
  create_new_grid(global_distance_mtx, 1);
  gtk_widget_hide (widget);
  free(entrance);
  free_memory(matriz_distancias, column_names);
}

void create_new_grid(int **global_distance_mtx, int table_number){
  GtkWidget *window;
  GtkWidget *table;
  GtkWidget       *button;
  GtkWidget       *button_box;
  char cell_value[5];

  /* create a new window */
   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   char title[20];
   char str[5];
   strcpy(title, "D(");
   snprintf(str,5,"%d",table_number);
   strcat(title, str);
   strcat(title, ")");
   gtk_window_set_title (GTK_WINDOW (window), title);

   // create new table
   table= gtk_grid_new();
   gtk_grid_set_row_spacing (GTK_GRID (table), 2);
   gtk_container_add (GTK_CONTAINER (window), table);

   //alojamos espacio para cada entrada de la matriz
   GtkWidget ***entrada;
   int j,k,i;
   entrada=calloc(n+1,sizeof(GtkWidget**));
   for(j = 0; j < n+1; j++){
     entrada[j]=calloc(n+1,sizeof(GtkWidget*));
   }
   printf("A ver si podemos acceder a los datos\n" );
   for (i = 0; i < n; i++)
   {
       for ( j = 0; j < n; j++)
       {
         if (global_distance_mtx[i][j] == INF)
               printf("%7s", "INF");
           else
               printf ("%7d", global_distance_mtx[i][j]);
       }
       printf("\n");
   }

   for(k =0; k< n+1;k++){
     for(j=0;j<n+1;j++){

       entrada[k][j]= gtk_entry_new();
       gtk_grid_attach (GTK_GRID (table),entrada[k][j] , k, j, 1, 1);
       if(k==j && k != 0 && j != 0){
         gtk_entry_set_text (entrada[k][j],"0");
       }
       if (k == 0 && j != 0){
         //printf("column_names[j-1 %d] = %s\n",j-1, column_names[j-1] );
         gtk_entry_set_text (entrada[k][j],column_names[j-1]);
       }
       if (j ==0 && k!=0){
        // printf("column_names[k-1 %d] = %s\n",k-1, column_names[k-1] );
         gtk_entry_set_text (entrada[k][j],column_names[k-1]);
       }
       if (k != 0 && j != 0){
         if (global_distance_mtx[k-1][j-1] == INF)
            strcpy(cell_value, "INF");
         else{
           snprintf(cell_value,5,"%d",global_distance_mtx[j-1][k-1]);
         }
         gtk_entry_set_text (entrada[k][j], cell_value);
       }
     }
   }

   button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
   gtk_grid_attach (GTK_GRID (table),button_box , n/2, j, 1, 1);

   strcpy(title, "Generar D(");
   snprintf(str,5,"%d",table_number+1);
   strcat(title, str);
   strcat(title, ")");

   button = gtk_button_new_with_label (title);
   //g_signal_connect (button, "clicked", G_CALLBACK (generate_D1), (gpointer) table);
   gtk_container_add (GTK_CONTAINER (button_box), button);

   gtk_widget_show_all(window);

}


void free_memory(int **graph, char **nodes){
  //Libera los datos de la matriz_distancias
  free(graph);
  free(nodes);

}

void generate_Dn(int  **graph, int table_number){
  int dist[n][n], i, j, k;

   for (i = 0; i < n; i++)
       for (j = 0; j < n; j++)
           dist[i][j] = graph[i][j];

       for (i = 0; i < n; i++)
       {
           for (j = 0; j < n; j++)
           {

               if(i != table_number -1 && j != table_number -1){
                 if (dist[i][table_number-1] + dist[table_number-1][j] < dist[i][j])
                     dist[i][j] = dist[i][table_number-1] + dist[table_number-1][j];
               }
           }
   }
   //copio la solucion en el global distance matrix
   update_global_mtx(dist);
   //printSolution(global_distance_mtx);
}


void update_global_mtx(int dist[][n]){
  int i, j;
  for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
          global_distance_mtx[i][j] = dist[i][j];
}


void printSolution(int  **dist)
{
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    int i,j;
    for (i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
          if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}


void button_crear_grid_clicked_cb(){

  GtkBuilder      *floyd_builder;
  GtkWidget       *floyd_window;
  GtkWidget       *table;
  GtkWidget       *button;
  GtkWidget       *button_box;


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

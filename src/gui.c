#include "calc.h"

static GtkWidget *entry_string;
static GtkWidget *result_string;

void smart_calc(GtkWidget *calculator, gpointer data) {
  stack_n N;
  stack_s S;
  N.count = 0;
  S.count = 0;
  int errCode = 0;
  double result = 0;
  char buffer[256];
  char *og = (char *)gtk_entry_get_text(GTK_ENTRY(entry_string));
  if (strlen(og) > 256)
    errCode = 7;
  else
    errCode = stacker(og, &N, &S, &result);
  gcvt(result, 6, buffer);
  if (!errCode) {
    gtk_label_set_text(GTK_LABEL(result_string), buffer);
  } else {
    gtk_label_set_text(GTK_LABEL(result_string), error_codes(errCode));
  }
}

int main(int argc, char **argv) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *calculator;

  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  entry_string = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), entry_string, 0, 0, 1, 1);

  calculator = gtk_button_new_with_label("=");
  g_signal_connect(calculator, "clicked", G_CALLBACK(smart_calc), NULL);
  gtk_grid_attach(GTK_GRID(grid), calculator, 2, 0, 1, 1);

  result_string = gtk_label_new("result:");
  gtk_grid_attach(GTK_GRID(grid), result_string, 3, 0, 1, 1);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
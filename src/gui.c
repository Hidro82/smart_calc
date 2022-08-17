#include "calc.h"

static GtkWidget *entry_string;

void smart_calc(GtkWidget *calculator, gpointer data) {
  stack_n N;
  stack_s S;
  N.count = 0;
  S.count = 0;
  int position = 0;
  int errCode = 0;
  double result = 0;
  char buffer[256];
  char *og = (char *)gtk_entry_get_text(GTK_ENTRY(entry_string));
  og = strcat(og, "=");
  if (strlen(og) > 256)
    errCode = 7;
  else
    errCode = stacker(og, &N, &S, &result);
  gcvt(result, 6, buffer);
  gtk_entry_set_text(GTK_ENTRY(entry_string), "");
  if (!errCode) {
    gtk_editable_insert_text((GtkEditable *)GTK_ENTRY(entry_string), buffer, -1, &position);
  } else {
    gtk_editable_insert_text((GtkEditable *)GTK_ENTRY(entry_string), error_codes(errCode), -1, &position);
  }
}

void button_clicker(GtkButton *button, gpointer data)
{
    GtkEntry *entry = data;
    const gchar *text = gtk_button_get_label(button);
    gint position = -1;
    gtk_editable_insert_text(GTK_EDITABLE(entry_string), text, -1, &position);
}

int main(int argc, char **argv) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *calculator;

  GtkWidget *one;
  GtkWidget *two;
  GtkWidget *three;
  GtkWidget *four;
  GtkWidget *five;
  GtkWidget *six;
  GtkWidget *seven;
  GtkWidget *eight;
  GtkWidget *nine;
  GtkWidget *zero;

  GtkWidget *plus;
  GtkWidget *minus;
  GtkWidget *mult;
  GtkWidget *divide;
  GtkWidget *mod_button;
  GtkWidget *power_button;

  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  entry_string = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), entry_string, 1, 0, 6, 1);

  calculator = gtk_button_new_with_label("=");
  g_signal_connect(calculator, "clicked", G_CALLBACK(smart_calc), NULL);
  gtk_grid_attach(GTK_GRID(grid), calculator, 1, 4, 1, 1);

  one = gtk_button_new_with_label("1");
  g_signal_connect(one, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), one, 1, 1, 1, 1);

  two = gtk_button_new_with_label("2");
  g_signal_connect(two, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), two, 2, 1, 1, 1);

  three = gtk_button_new_with_label("3");
  g_signal_connect(three, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), three, 3, 1, 1, 1);

  four = gtk_button_new_with_label("4");
  g_signal_connect(four, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), four, 1, 2, 1, 1);

  five = gtk_button_new_with_label("5");
  g_signal_connect(five, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), five, 2, 2, 1, 1);

  six = gtk_button_new_with_label("6");
  g_signal_connect(six, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), six, 3, 2, 1, 1);

  seven = gtk_button_new_with_label("7");
  g_signal_connect(seven, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), seven, 1, 3, 1, 1);

  eight = gtk_button_new_with_label("8");
  g_signal_connect(eight, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), eight, 2, 3, 1, 1);

  nine = gtk_button_new_with_label("9");
  g_signal_connect(nine, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), nine, 3, 3, 1, 1);

  zero = gtk_button_new_with_label("0");
  g_signal_connect(zero, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), zero, 2, 4, 1, 1);

  plus = gtk_button_new_with_label("+");
  g_signal_connect(plus, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), plus, 4, 1, 1, 1);

  minus = gtk_button_new_with_label("-");
  g_signal_connect(minus, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), minus, 5, 1, 1, 1);

  mult = gtk_button_new_with_label("*");
  g_signal_connect(mult, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), mult, 6, 1, 1, 1);

  divide = gtk_button_new_with_label("/");
  g_signal_connect(divide, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), divide, 4, 2, 1, 1);

  mod_button = gtk_button_new_with_label("mod");
  g_signal_connect(mod_button, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), mod_button, 5, 2, 1, 1);

  power_button = gtk_button_new_with_label("^");
  g_signal_connect(power_button, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), power_button, 6, 2, 1, 1);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
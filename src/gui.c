#include "calc.h"

static GtkWidget *entry_string;
static GtkWidget *x_1;
static GtkWidget *x_2;

void smart_calc(GtkWidget *calculator, gpointer data) {
  stack_n N;
  stack_s S;
  N.count = 0;
  S.count = 0;
  int position = 0;
  int errCode = 0;
  int X_here = 0;
  int i = 0;
  double result = 0;
  double x_start = atof(gtk_entry_get_text(GTK_ENTRY(x_1)));
  double x_end = atof(gtk_entry_get_text(GTK_ENTRY(x_2)));
  double x = x_start;
  char buffer[256];
  char *og = (char *)gtk_entry_get_text(GTK_ENTRY(entry_string));

  og = strcat(og, "=");
  while (*og) {
    if (*og == 'X')
      X_here = 1;
    og++;
    i++
  }
  og -= i;
  if (strlen(og) > 256)
    errCode = 7;
  else if (X_here) {
    if (x_1 > x_2)
      errCode = 8;
    while ((x <= x_end) && !errCode) {
      errCode = stacker(og, &N, &S, x, &result);
      if ((x == x_start) && !errCode) {
        cairo_move_to(canvas, x, result);
      } else if (!errCode) {
        cairo_line_to(canvas, x, result);
      }
      if ((errCode == 1) || (errCode == 2) || (errCode == 6)) {
        errCode = 0;
      }
      x += (x / 1000);
      x_start = x;
    }
  } else
    errCode = stacker(og, &N, &S, 0.0, &result);
  gcvt(result, 6, buffer);
  gtk_entry_set_text(GTK_ENTRY(entry_string), "");
  if (!errCode) {
    gtk_editable_insert_text((GtkEditable *)GTK_ENTRY(entry_string), buffer, -1, &position);
  } else {
    gtk_editable_insert_text((GtkEditable *)GTK_ENTRY(entry_string), error_codes(errCode), -1, &position);
  }
}

void button_clicker(GtkButton *button, gpointer data) {
  GtkEntry *entry = data;
  const gchar *text = gtk_button_get_label(button);
  gint position = -1;
  gtk_editable_insert_text(GTK_EDITABLE(entry_string), text, -1, &position);
}

void func_button_clicker(GtkButton *button, gpointer data) {
  GtkEntry *entry = data;
  const gchar *text = gtk_button_get_label(button);
  gint position = -1;
  gtk_editable_insert_text(GTK_EDITABLE(entry_string), text, -1, &position);
  position++;
  gtk_editable_insert_text(GTK_EDITABLE(entry_string), "(", -1, &position);
}

void clear_button_clicker(GtkButton *button, gpointer data) {
  gtk_entry_set_text(GTK_ENTRY(entry_string), "");
}

void math_module(GtkButton *button, gpointer data) {
  GtkWidget *window;
  GtkWidget *grid;

  GtkWidget *sin_button;
  GtkWidget *cos_button;
  GtkWidget *tan_button;
  GtkWidget *asin_button;
  GtkWidget *acos_button;
  GtkWidget *atan_button;
  GtkWidget *sqrt_button;
  GtkWidget *log_button;
  GtkWidget *log10_button;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

    sin_button = gtk_button_new_with_label("sin");
  g_signal_connect(sin_button, "clicked", G_CALLBACK(func_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), sin_button, 7, 1, 1, 1);

  cos_button = gtk_button_new_with_label("cos");
  g_signal_connect(cos_button, "clicked", G_CALLBACK(func_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), cos_button, 8, 1, 1, 1);

  tan_button = gtk_button_new_with_label("tan");
  g_signal_connect(tan_button, "clicked", G_CALLBACK(func_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), tan_button, 9, 1, 1, 1);

  asin_button = gtk_button_new_with_label("asin");
  g_signal_connect(asin_button, "clicked", G_CALLBACK(func_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), asin_button, 7, 2, 1, 1);

  acos_button = gtk_button_new_with_label("acos");
  g_signal_connect(acos_button, "clicked", G_CALLBACK(func_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), acos_button, 8, 2, 1, 1);

  atan_button = gtk_button_new_with_label("atan");
  g_signal_connect(atan_button, "clicked", G_CALLBACK(func_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), atan_button, 9, 2, 1, 1);

  sqrt_button = gtk_button_new_with_label("sqrt");
  g_signal_connect(sqrt_button, "clicked", G_CALLBACK(func_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), sqrt_button, 7, 3, 1, 1);

  log_button = gtk_button_new_with_label("ln");
  g_signal_connect(log_button, "clicked", G_CALLBACK(func_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), log_button, 8, 3, 1, 1);

  log10_button = gtk_button_new_with_label("log");
  g_signal_connect(log10_button, "clicked", G_CALLBACK(func_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), log10_button, 9, 3, 1, 1);

  gtk_widget_show_all(window);
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
  GtkWidget *dot;

  GtkWidget *plus;
  GtkWidget *minus;
  GtkWidget *mult;
  GtkWidget *divide;
  GtkWidget *mod_button;
  GtkWidget *power_button;
  GtkWidget *open_bracket;
  GtkWidget *close_bracket;
  GtkWidget *X_button;
  GtkWidget *clear_button;

  GtkWidget *math_mod;

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

  dot = gtk_button_new_with_label(".");
  g_signal_connect(dot, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), dot, 3, 4, 1, 1);

  plus = gtk_button_new_with_label("+");
  g_signal_connect(plus, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), plus, 4, 2, 1, 1);

  minus = gtk_button_new_with_label("-");
  g_signal_connect(minus, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), minus, 5, 2, 1, 1);

  mult = gtk_button_new_with_label("*");
  g_signal_connect(mult, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), mult, 6, 2, 1, 1);

  divide = gtk_button_new_with_label("/");
  g_signal_connect(divide, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), divide, 4, 3, 1, 1);

  mod_button = gtk_button_new_with_label("mod");
  g_signal_connect(mod_button, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), mod_button, 5, 3, 1, 1);

  power_button = gtk_button_new_with_label("^");
  g_signal_connect(power_button, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), power_button, 6, 3, 1, 1);

  open_bracket = gtk_button_new_with_label("(");
  g_signal_connect(open_bracket, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), open_bracket, 4, 4, 1, 1);

  close_bracket = gtk_button_new_with_label(")");
  g_signal_connect(close_bracket, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), close_bracket, 5, 4, 1, 1);

  X_button = gtk_button_new_with_label("X");
  g_signal_connect(X_button, "clicked", G_CALLBACK(button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), X_button, 6, 4, 1, 1);

  clear_button = gtk_button_new_with_label("AC");
  g_signal_connect(clear_button, "clicked", G_CALLBACK(clear_button_clicker), NULL);
  gtk_grid_attach(GTK_GRID(grid), clear_button, 4, 1, 1, 1);

  math_mod = gtk_button_new_with_label("math");
  g_signal_connect(math_mod, "clicked", G_CALLBACK(math_module), NULL);
  gtk_grid_attach(GTK_GRID(grid), math_mod, 5, 1, 1, 1);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
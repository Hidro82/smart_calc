#include "gui.h"

void credit_proc(GtkButton *button, gpointer data) {
  cred_in I;
  cred_out O;
  char buffer[256] = "";
  char buffer_1[256] = "";
  int errCode = 0;

  I.cash = atof((char *)gtk_entry_get_text(GTK_ENTRY(credit)));
  I.percent = atof((char *)gtk_entry_get_text(GTK_ENTRY(percent)));
  I.time = atof((char *)gtk_entry_get_text(GTK_ENTRY(time_amount)));
  I.month = (int)gtk_switch_get_state(GTK_SWITCH(time_type));
  I.differ = (int)gtk_switch_get_state(GTK_SWITCH(diff));

  errCode = credit_calculus(&I, &O);

  if (!errCode) {
    gcvt(O.whole, 6, buffer);
    gtk_label_set_text(GTK_LABEL(cred_res), buffer);
    if (I.differ) {
      sprintf(buffer_1, "%.2f..%.2f", O.monthly[0], O.monthly[1]);
      gtk_label_set_text(GTK_LABEL(cr_pay), buffer_1);
    } else {
      gcvt(O.monthly[0], 6, buffer);
      gtk_label_set_text(GTK_LABEL(cr_pay), buffer);
    }
    gcvt(O.over, 6, buffer);
    gtk_label_set_text(GTK_LABEL(cr_over), buffer);
  }
}

void credit_gui(GtkButton *button, gpointer data) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *message;
  GtkWidget *start_button;

  GtkWidget *cr_label;
  GtkWidget *per_label;
  GtkWidget *time_label;
  GtkWidget *time_1;
  GtkWidget *time_2;
  GtkWidget *dif_1;
  GtkWidget *dif_2;

  GtkWidget *result;
  GtkWidget *monthly;
  GtkWidget *overdraft;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Credit calculator");

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  message = gtk_label_new_with_mnemonic("Enter the parameters");
  gtk_grid_attach(GTK_GRID(grid), message, 0, 0, 6, 1);

  cr_label = gtk_label_new_with_mnemonic("Amount:");
  gtk_grid_attach(GTK_GRID(grid), cr_label, 0, 1, 1, 1);

  credit = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), credit, 1, 1, 2, 1);

  per_label = gtk_label_new_with_mnemonic("Percent:");
  gtk_grid_attach(GTK_GRID(grid), per_label, 0, 2, 1, 1);

  percent = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), percent, 1, 2, 2, 1);

  time_label = gtk_label_new_with_mnemonic("Time:");
  gtk_grid_attach(GTK_GRID(grid), time_label, 0, 3, 1, 1);

  time_amount = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), time_amount, 1, 3, 2, 1);

  time_1 = gtk_label_new_with_mnemonic("Years");
  gtk_grid_attach(GTK_GRID(grid), time_1, 0, 4, 1, 1);

  time_type = gtk_switch_new();
  gtk_grid_attach(GTK_GRID(grid), time_type, 1, 4, 1, 1);

  time_2 = gtk_label_new_with_mnemonic("Months");
  gtk_grid_attach(GTK_GRID(grid), time_2, 2, 4, 1, 1);

  dif_1 = gtk_label_new_with_mnemonic("Anuite");
  gtk_grid_attach(GTK_GRID(grid), dif_1, 0, 5, 1, 1);

  diff = gtk_switch_new();
  gtk_grid_attach(GTK_GRID(grid), diff, 1, 5, 1, 1);

  dif_2 = gtk_label_new_with_mnemonic("Differ");
  gtk_grid_attach(GTK_GRID(grid), dif_2, 2, 5, 1, 1);

  start_button = gtk_button_new_with_label("Start!");
  g_signal_connect(start_button, "clicked", G_CALLBACK(credit_proc), NULL);
  gtk_grid_attach(GTK_GRID(grid), start_button, 0, 6, 3, 1);

  result = gtk_label_new_with_mnemonic("Result:");
  gtk_grid_attach(GTK_GRID(grid), result, 0, 7, 1, 1);

  cred_res = gtk_label_new_with_mnemonic("0");
  gtk_grid_attach(GTK_GRID(grid), cred_res, 1, 7, 1, 1);

  monthly = gtk_label_new_with_mnemonic("Month pay:");
  gtk_grid_attach(GTK_GRID(grid), monthly, 0, 8, 1, 1);

  cr_pay = gtk_label_new_with_mnemonic("0");
  gtk_grid_attach(GTK_GRID(grid), cr_pay, 1, 8, 1, 1);

  overdraft = gtk_label_new_with_mnemonic("Overdraft:");
  gtk_grid_attach(GTK_GRID(grid), overdraft, 0, 9, 1, 1);

  cr_over = gtk_label_new_with_mnemonic("0");
  gtk_grid_attach(GTK_GRID(grid), cr_over, 1, 9, 1, 1);

  gtk_widget_show_all(window);
}

void grid_maker(cairo_t *brush, double x_zero, double y_zero, double x_scale,
                double y_scale) {
  double offset = 0;
  char num[10];

  cairo_set_source_rgb(brush, 192.0, 192.0, 192.0);
  offset = x_zero + 30;
  while (offset < 300) {
    cairo_move_to(brush, offset, 0);
    cairo_line_to(brush, offset, 300);
    cairo_stroke(brush);
    if (y_zero > 30)
      cairo_move_to(brush, offset, y_zero - 5);
    else
      cairo_move_to(brush, offset, y_zero + 10);
    cairo_set_source_rgb(brush, 0.0, 0.0, 0.0);
    gcvt((offset - x_zero) / x_scale, 6, num);
    cairo_show_text(brush, num);
    cairo_stroke(brush);
    cairo_set_source_rgb(brush, 192.0, 192.0, 192.0);
    offset += 30;
  }
  offset = x_zero - 30;
  while (offset > 0) {
    cairo_move_to(brush, offset, 0);
    cairo_line_to(brush, offset, 300);
    cairo_stroke(brush);
    if (y_zero > 30)
      cairo_move_to(brush, offset, y_zero - 5);
    else
      cairo_move_to(brush, offset, y_zero + 10);
    cairo_set_source_rgb(brush, 0.0, 0.0, 0.0);
    gcvt((offset - x_zero) / x_scale, 6, num);
    cairo_show_text(brush, num);
    cairo_stroke(brush);
    cairo_set_source_rgb(brush, 192.0, 192.0, 192.0);
    offset -= 30;
  }
  offset = y_zero + 30;
  while (offset < 300) {
    cairo_move_to(brush, 0, offset);
    cairo_line_to(brush, 300, offset);
    cairo_stroke(brush);
    if (x_zero > 30)
      cairo_move_to(brush, x_zero - 10, offset);
    else
      cairo_move_to(brush, x_zero + 5, offset);
    cairo_set_source_rgb(brush, 0.0, 0.0, 0.0);
    gcvt(-(offset - y_zero) / y_scale, 6, num);
    cairo_show_text(brush, num);
    cairo_stroke(brush);
    cairo_set_source_rgb(brush, 192.0, 192.0, 192.0);
    offset += 30;
  }
  offset = y_zero - 30;
  while (offset > 0) {
    cairo_move_to(brush, 0, offset);
    cairo_line_to(brush, 300, offset);
    cairo_stroke(brush);
    if (x_zero > 30)
      cairo_move_to(brush, x_zero - 10, offset);
    else
      cairo_move_to(brush, x_zero + 5, offset);
    cairo_set_source_rgb(brush, 0.0, 0.0, 0.0);
    gcvt(-(offset - y_zero) / y_scale, 6, num);
    cairo_show_text(brush, num);
    cairo_stroke(brush);
    cairo_set_source_rgb(brush, 192.0, 192.0, 192.0);
    offset -= 30;
  }
  cairo_stroke(brush);

  cairo_set_source_rgb(brush, 1.0, 0.0, 0.0);
  cairo_move_to(brush, 0, y_zero);
  cairo_line_to(brush, 300, y_zero);
  cairo_move_to(brush, x_zero, 0);
  cairo_line_to(brush, x_zero, 300);
  cairo_stroke(brush);
}

gboolean smart_graph(GtkWidget *widget, cairo_t *brush, gpointer data) {
  stack_n N;
  stack_s S;
  N.count = 0;
  S.count = 0;
  int errCode = 0;
  char *og = (char *)gtk_entry_get_text(GTK_ENTRY(entry_string));
  double x_start = atof((char *)gtk_entry_get_text(GTK_ENTRY(x_1)));
  double x_end = atof((char *)gtk_entry_get_text(GTK_ENTRY(x_2)));
  double x_scale = 300 / (fabs(x_start) + fabs(x_end));
  double x_step = (fabs(x_start) + fabs(x_end)) / 600;
  double x_zero = fabs(x_start) * x_scale;
  double y_start = atof((char *)gtk_entry_get_text(GTK_ENTRY(y_1)));
  double y_end = atof((char *)gtk_entry_get_text(GTK_ENTRY(y_2)));
  double y_scale = 300 / (fabs(y_start) + fabs(y_end));
  double y_zero = fabs(y_end) * y_scale;
  double x = x_start;
  double y = 0;

  grid_maker(brush, x_zero, y_zero, x_scale, y_scale);

  cairo_set_source_rgb(brush, 0.0, 0.0, 1.0);
  og = strcat(og, "=");
  if (x_1 > x_2) errCode = 8;
  while ((x <= x_end) && !errCode) {
    errCode = stacker(og, &N, &S, x, &y);
    if ((x == x_start) && !errCode) {
      cairo_move_to(brush, (x * x_scale) + x_zero, y_zero - (y * y_scale));
    } else if (!errCode) {
      cairo_line_to(brush, (x * x_scale) + x_zero, y_zero - (y * y_scale));
    }
    if ((errCode == 1) || (errCode == 2) || (errCode == 6)) {
      errCode = 0;
      x_start = x;
    }
    x += x_step;
  }
  cairo_stroke(brush);
  return FALSE;
}

void graph_module() {
  GtkWidget *window;
  GtkWidget *canvas;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
  gtk_window_set_title(GTK_WINDOW(window), "Graph drawing");

  canvas = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), canvas);
  gtk_widget_add_events(canvas, GDK_BUTTON_PRESS_MASK);
  gtk_widget_set_size_request(canvas, 300, 300);
  g_signal_connect(canvas, "draw", G_CALLBACK(smart_graph), NULL);

  gtk_widget_show_all(window);
}

void coor_win() {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *message;

  GtkWidget *x_coors;
  GtkWidget *y_coors;

  GtkWidget *start_button;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Graph prepare");

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  message = gtk_label_new_with_mnemonic("Enter the coordinates");
  gtk_grid_attach(GTK_GRID(grid), message, 0, 0, 6, 1);

  x_coors = gtk_label_new_with_mnemonic("X");
  gtk_grid_attach(GTK_GRID(grid), x_coors, 0, 1, 2, 1);

  x_1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), x_1, 2, 1, 2, 1);

  x_2 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), x_2, 4, 1, 2, 1);

  y_coors = gtk_label_new_with_mnemonic("Y");
  gtk_grid_attach(GTK_GRID(grid), y_coors, 0, 2, 2, 1);

  y_1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), y_1, 2, 2, 2, 1);

  y_2 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), y_2, 4, 2, 2, 1);

  start_button = gtk_button_new_with_label("Start!");
  g_signal_connect(start_button, "clicked", G_CALLBACK(graph_module), NULL);
  gtk_grid_attach(GTK_GRID(grid), start_button, 0, 3, 6, 1);

  gtk_widget_show_all(window);
}

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
  char buffer[256];
  char *og = (char *)gtk_entry_get_text(GTK_ENTRY(entry_string));

  og = strcat(og, "=");
  while (*og) {
    if (*og == 'X') X_here = 1;
    og++;
    i++;
  }
  og -= i;
  if (strlen(og) > 256) {
    errCode = 7;
  } else if (X_here) {
    coor_win();
  } else {
    errCode = stacker(og, &N, &S, 0.0, &result);
    gcvt(result, 6, buffer);
  }

  if (!errCode && !X_here) {
    gtk_entry_set_text(GTK_ENTRY(entry_string), "");
    gtk_editable_insert_text((GtkEditable *)GTK_ENTRY(entry_string), buffer, -1,
                             &position);
  } else if (!X_here) {
    gtk_entry_set_text(GTK_ENTRY(entry_string), "");
    gtk_editable_insert_text((GtkEditable *)GTK_ENTRY(entry_string),
                             error_codes(errCode), -1, &position);
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
  g_signal_connect(sin_button, "clicked", G_CALLBACK(func_button_clicker),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), sin_button, 7, 1, 1, 1);

  cos_button = gtk_button_new_with_label("cos");
  g_signal_connect(cos_button, "clicked", G_CALLBACK(func_button_clicker),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), cos_button, 8, 1, 1, 1);

  tan_button = gtk_button_new_with_label("tan");
  g_signal_connect(tan_button, "clicked", G_CALLBACK(func_button_clicker),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), tan_button, 9, 1, 1, 1);

  asin_button = gtk_button_new_with_label("asin");
  g_signal_connect(asin_button, "clicked", G_CALLBACK(func_button_clicker),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), asin_button, 7, 2, 1, 1);

  acos_button = gtk_button_new_with_label("acos");
  g_signal_connect(acos_button, "clicked", G_CALLBACK(func_button_clicker),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), acos_button, 8, 2, 1, 1);

  atan_button = gtk_button_new_with_label("atan");
  g_signal_connect(atan_button, "clicked", G_CALLBACK(func_button_clicker),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), atan_button, 9, 2, 1, 1);

  sqrt_button = gtk_button_new_with_label("sqrt");
  g_signal_connect(sqrt_button, "clicked", G_CALLBACK(func_button_clicker),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), sqrt_button, 7, 3, 1, 1);

  log_button = gtk_button_new_with_label("ln");
  g_signal_connect(log_button, "clicked", G_CALLBACK(func_button_clicker),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), log_button, 8, 3, 1, 1);

  log10_button = gtk_button_new_with_label("log");
  g_signal_connect(log10_button, "clicked", G_CALLBACK(func_button_clicker),
                   NULL);
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
  GtkWidget *credit_start;

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
  g_signal_connect(clear_button, "clicked", G_CALLBACK(clear_button_clicker),
                   NULL);
  gtk_grid_attach(GTK_GRID(grid), clear_button, 4, 1, 1, 1);

  math_mod = gtk_button_new_with_label("math");
  g_signal_connect(math_mod, "clicked", G_CALLBACK(math_module), NULL);
  gtk_grid_attach(GTK_GRID(grid), math_mod, 5, 1, 1, 1);

  credit_start = gtk_button_new_with_label("Cr");
  g_signal_connect(credit_start, "clicked", G_CALLBACK(credit_gui), NULL);
  gtk_grid_attach(GTK_GRID(grid), credit_start, 6, 1, 1, 1);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

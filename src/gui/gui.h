#ifndef SRC_GUI_H_
#define SRC_GUI_H_

#include "../calc.h"
#include <cairo.h>
#include <gtk/gtk.h>

static GtkWidget *entry_string;
static GtkWidget *x_1;
static GtkWidget *x_2;
static GtkWidget *y_1;
static GtkWidget *y_2;

static GtkWidget *credit;
static GtkWidget *percent;
static GtkWidget *diff;
static GtkWidget *time_amount;
static GtkWidget *time_type;

static GtkWidget *cred_res;
static GtkWidget *cr_over;
static GtkWidget *cr_pay;

char *error_codes(int errCode);

void credit_proc(GtkButton *button, gpointer data);
void credit_gui(GtkButton *button, gpointer data);
void grid_maker(cairo_t *brush, double x_zero, double y_zero, double x_scale,
                double y_scale);
gboolean smart_graph(GtkWidget *widget, cairo_t *brush, gpointer data);
void graph_module();
void coor_win();
void smart_calc(GtkWidget *calculator, gpointer data);
void button_clicker(GtkButton *button, gpointer data);
void func_button_clicker(GtkButton *button, gpointer data);
void clear_button_clicker(GtkButton *button, gpointer data);
void math_module(GtkButton *button, gpointer data);

#endif  // SRC_GUI_H_
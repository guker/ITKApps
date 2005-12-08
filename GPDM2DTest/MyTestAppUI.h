// generated by Fast Light User Interface Designer (fluid) version 1.0100

#ifndef MyTestAppUI_h
#define MyTestAppUI_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "MySegmentation.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Value_Slider.H>

class MyTestAppInterface : private MySegmentation {
public:
  MyTestAppInterface();
  Fl_Window *mainwin;
private:
  Fl_Button *execute;
  inline void cb_execute_i(Fl_Button*, void*);
  static void cb_execute(Fl_Button*, void*);
  Fl_Button *load;
  inline void cb_load_i(Fl_Button*, void*);
  static void cb_load(Fl_Button*, void*);
  Fl_Button *Display;
  inline void cb_Display_i(Fl_Button*, void*);
  static void cb_Display(Fl_Button*, void*);
  static Fl_Menu_Item menu_[];
  Fl_Button *Set;
  inline void cb_Set_i(Fl_Button*, void*);
  static void cb_Set(Fl_Button*, void*);
  Fl_Light_Button *Seed;
  inline void cb_Seed_i(Fl_Light_Button*, void*);
  static void cb_Seed(Fl_Light_Button*, void*);
  Fl_Button *save;
  inline void cb_save_i(Fl_Button*, void*);
  static void cb_save(Fl_Button*, void*);
  Fl_Button *nload;
  inline void cb_nload_i(Fl_Button*, void*);
  static void cb_nload(Fl_Button*, void*);
  Fl_Output *currentslice;
  Fl_Button *dseed;
  inline void cb_dseed_i(Fl_Button*, void*);
  static void cb_dseed(Fl_Button*, void*);
  Fl_Button *dsetting;
  inline void cb_dsetting_i(Fl_Button*, void*);
  static void cb_dsetting(Fl_Button*, void*);
  Fl_Button *dfitting;
  inline void cb_dfitting_i(Fl_Button*, void*);
  static void cb_dfitting(Fl_Button*, void*);
  Fl_Button *setpotential;
  inline void cb_setpotential_i(Fl_Button*, void*);
  static void cb_setpotential(Fl_Button*, void*);
public:
  Fl_Window *setting;
private:
  Fl_Group *iscolor;
  Fl_Check_Button *rgb;
  Fl_Check_Button *gray;
  Fl_Value_Input *width;
  Fl_Value_Input *height;
  Fl_Value_Input *slice;
public:
  Fl_Window *gsetting;
private:
  Fl_Value_Input *radius;
  Fl_Value_Input *classnum;
  Fl_Value_Input *step;
  Fl_Value_Input *errorrate;
  Fl_Value_Input *gradient;
  Fl_Value_Input *regionlimit;
  Fl_Value_Slider *weight_grad;
  Fl_Value_Slider *weight_gibbs;
  Fl_Value_Slider *weight_c1;
  Fl_Value_Slider *weight_c2;
  Fl_Value_Slider *weight_c3;
  Fl_Value_Slider *weight_c4;
  Fl_Value_Slider *weight_o;
  Fl_Button *ok;
  inline void cb_ok_i(Fl_Button*, void*);
  static void cb_ok(Fl_Button*, void*);
  Fl_Button *cancel;
  inline void cb_cancel_i(Fl_Button*, void*);
  static void cb_cancel(Fl_Button*, void*);
public:
  Fl_Window *dfsetting;
private:
  Fl_Value_Input *bfsteps;
  Fl_Value_Input *gfsteps;
  Fl_Value_Input *vstiffness;
  Fl_Value_Input *hstiffness;
  Fl_Button *dfok;
  inline void cb_dfok_i(Fl_Button*, void*);
  static void cb_dfok(Fl_Button*, void*);
  Fl_Button *dfcancel;
  inline void cb_dfcancel_i(Fl_Button*, void*);
  static void cb_dfcancel(Fl_Button*, void*);
  Fl_Value_Input *resolution;
  Fl_Value_Input *timestep;
public:
  ~MyTestAppInterface();
  virtual void segment();
  void display();
  void Show();
  void init();
  void setpar();
  void dminit();
};
#endif

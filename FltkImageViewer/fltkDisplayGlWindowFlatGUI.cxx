// generated by Fast Light User Interface Designer (fluid) version 1.0009

#include "fltkDisplayGlWindowFlatGUI.h"

fltkDisplayGlWindowFlatGUI::fltkDisplayGlWindowFlatGUI() {
  Fl_Window* w;
  { Fl_Window* o = parentWindow = new Fl_Window(565, 585);
    w = o;
    o->user_data((void*)(this));
    { fltk::GlWindowInteractiveFlat* o = drawWindow = new fltk::GlWindowInteractiveFlat(0, 0, 565, 585);
      Fl_Group::current()->resizable(o);
    }
    o->end();
  }
}

void fltkDisplayGlWindowFlatGUI::Show(void) {
  parentWindow->show();
drawWindow->show();
}

void fltkDisplayGlWindowFlatGUI::SetLabel(const char *newlabel) {
  parentWindow->label(newlabel);
}

void fltkDisplayGlWindowFlatGUI::Redraw(void) {
  parentWindow->redraw();
drawWindow->redraw();
}

void fltkDisplayGlWindowFlatGUI::Size(unsigned int nx, unsigned int ny) {
  parentWindow->size(nx,ny);
drawWindow->size(nx,ny);
}

void fltkDisplayGlWindowFlatGUI::Hide(void) {
  parentWindow->hide();
}

void fltkDisplayGlWindowFlatGUI::Update(void) {
  Redraw();
}

int fltkDisplayGlWindowFlatGUI::GetWidth(void) {
  return drawWindow->w();
}

int fltkDisplayGlWindowFlatGUI::GetHeight(void) {
  return drawWindow->h();
}

void fltkDisplayGlWindowFlatGUI::MakeCurrent(void) {
  drawWindow->make_current();
}

int fltkDisplayGlWindowFlatGUI::IsVisible(void) {
  return drawWindow->visible_r();
}

const fltk::GlWindow::RedrawCommandType::Pointer & fltkDisplayGlWindowFlatGUI::GetRedrawCommand(void) {
  return drawWindow->GetRedrawCommand();
}

itk::LightObject::Pointer & fltkDisplayGlWindowFlatGUI::GetNotifier(void) {
  return drawWindow->GetNotifier();
}

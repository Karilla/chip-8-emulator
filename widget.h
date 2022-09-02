//
// Created by benoit on 31/08/2022.
//

#ifndef REVISON_PRG2_WIDGET_H
#define REVISON_PRG2_WIDGET_H
#include <windows.h>
#include <stdbool.h>


HWND create_label(HWND winHandle, int x, int y,int w,int h,const char* initialText);

void set_Label_text(HWND label,const char* text);

HWND create_edit(HWND winHandle, int x, int y, const char* placeHolder, bool readonly);

char* get_text_value(HWND edit);

void set_text_value(HWND edit, char* text);

HWND create_button(HWND parent, char* text, int id);

void edit_button_text(HWND button, char* text);
#endif //REVISON_PRG2_WIDGET_H


//
// Created by benoit on 31/08/2022.
//

#include "widget.h"
#include "windows.h"
#include "stdbool.h"

HWND create_label(HWND winHandle, int x, int y,int w,int h,const char* initialText){
    HWND editHandle = CreateWindow("static", "ST_U",
                                   WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
                                   x, y, w, h,
                                   winHandle, NULL,
                                   NULL, NULL);
    SetWindowText(editHandle, initialText);
    return editHandle;
}

void set_Label_text(HWND label,const char* text){

}

HWND create_edit(HWND winHandle, int x, int y, const char* placeHolder, bool readonly){

}

char* get_text_value(HWND edit){

}

void set_text_value(HWND edit, char* text){

}

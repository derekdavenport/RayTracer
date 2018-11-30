/*
 *  Window.hpp
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/16/06.
 *  Copyright 2006 All rights reserved.
 *
 */
#ifndef __WINDOW_HPP
#define __WINDOW_HPP

//#include <GLUT/glut.h>

class Window
{
    public:
        int width, height;
        int x, y;   // Upper corner's position
        const char * title;
    
        Window() : width(100), height(100), x(100), y(100), title("Hello") { }
    
        Window(int _w, int _h) : width(_w), height(_h), x(100), y(100), title("Hello") { }
    
        Window(int _w, int _h, int _x, int _y, const char * _title) : width(_w), height(_h), x(_x), y(_y), title(_title) { }
    
        /*
        void createWindow()
        {
            glutInitWindowSize(width, height);
            glutInitWindowPosition(x, y);
            glutCreateWindow(title);
        }
         */
};
#endif

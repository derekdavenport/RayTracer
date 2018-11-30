/*
 *  Color.hpp
 *  RayTracer
 *
 *  Created by Derek Davenport on 11/19/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef __COLOR_HPP
#define __COLOR_HPP

class Color
{
    public:
        float r, g, b;
        Color() : r(0), g(0), b(0) { }
        Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) { }
        
        void set(float _r, float _g, float _b)
        {
            r = _r;
            g = _g;
            b = _b;
        }
        
        friend Color operator + (const Color & A, const Color & B)
        {
            return Color(A.r + B.r, A.g + B.g, A.b + B.b);
        }
};
#endif
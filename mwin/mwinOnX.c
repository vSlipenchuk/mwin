#include "mwin.h"

#include<X11/Xlib.h>
#include<stdio.h>
#include<stdlib.h> // prevents error for exit on line 18 when compiling with gcc

// XLib driver for mwin

mscreen screen = { .x=200, .y=150} ; // initial screen


// winX implementation static parameters

 Display *d;
 int s;
 Window w;
 XEvent e;

int mwin_init() { //

                        /* open connection with the server */
   d=XOpenDisplay(NULL);
   if(d==NULL) return -1; // cant open display
   s=DefaultScreen(d);

                        /* create window */
   w=XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, screen.x, screen.y, 1,
                         BlackPixel(d, s), WhitePixel(d, s));

 // Process Window Close Event through event handler so XNextEvent does Not fail
        Atom delWindow = XInternAtom( d, "WM_DELETE_WINDOW", 0 );
        XSetWMProtocols(d , w, &delWindow, 1);

                        /* select kind of events we are interested in */
   XSelectInput(d, w, ExposureMask | KeyPressMask);

                        /* map (show) the window */
   XMapWindow(d, w);
return 1; // OK
}

int mwin_step() {
 XNextEvent(d, &e);
                    /* draw or redraw the window */
     if(e.type==Expose) {
       XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);

     }
                        /* exit on key press */
     if(e.type==KeyPress) return 0; // exit on key press - ZUZUKA

     // Handle Windows Close Event
     if(e.type==ClientMessage) return 0; // exit on any client message - ZUZUKA
     return 1; // OK, again
}

int mwin_done() {
XDestroyWindow(d, w);
                    /* close connection to server */
XCloseDisplay(d);
return 0;
}

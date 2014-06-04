#ifndef mwin
#define mwin

typedef struct { // main screen where all win resides, must be defined in controller
  int x,y; // H&V here
  //struct _mwin * mwin; // current active window
  } mscreen;

extern mscreen screen; // must be defined in win-driver as global variable

typedef struct _mwin { // the window, defined in a project
  void *hwnd;
  int (*proc)(); // win proc handler
  } mwin;


int mwin_init(); // start library, returns 0 on OK.
int mwin_step(); // call it until it returns 1 (OK)
int mwin_done(); // stop

#endif //mwin

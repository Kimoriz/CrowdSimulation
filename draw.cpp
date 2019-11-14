#include "draw.h"

void click ( int button, int state, int x, int y )
{   
    switch ( button ) 
    {   
        case GLUT_LEFT_BUTTON:
        if ( state == GLUT_DOWN)
        {
            glutIdleFunc ( timeUpdate );
            break;
        }

        case GLUT_RIGHT_BUTTON:
        if ( state == GLUT_DOWN)
        {
            glutIdleFunc ( NULL );
            break;
        }
        default: break;
    }
}

void crowding ()
{   
    handler ();
    glutMouseFunc ( click );
    glutMainLoop ();
}
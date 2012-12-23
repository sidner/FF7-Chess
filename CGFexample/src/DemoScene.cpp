#include "DemoScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include <cmath>
#include "CGFappearance.h"
DemoScene::DemoScene (char* nome)
{
    strcpy (this->nome, nome);  
}
void
DemoScene::activateCamera (int i)
{
    active = vec_cameras.at (i);
}
void
DemoScene::init ()
{
    
   
    lsf = new XMLScene (nome);
    //Globals
    glFrontFace (lsf->frontfaceorder);
    glCullFace (lsf->cullface);
    if (lsf->cull_enable)
        glEnable (GL_CULL_FACE);
    else
        glDisable (GL_CULL_FACE);

    //Setting cameras
    def = activeCamera;
    vec_cameras.push_back (def);
    nr_cams = 0;

    for (map<string, CGFcamera*>::iterator it = lsf->cameras.begin (); it != lsf->cameras.end (); it++)
    {
        vec_cameras.push_back ((*it).second);
    }
    cout << vec_cameras.size () << endl;
    active = lsf->camera_init;
    number = vec_cameras.size ();
    // Enables lighting computations
    glEnable (GL_LIGHTING);
  
    // Sets up some lighting parameters
    glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient); // Define ambient light

    // Declares and enables a light
    for (map<string, CGFlight*>::iterator it = lsf->luzes.begin (); it != lsf->luzes.end (); it++)
    {
        scene_lights.push_back ((*it).second);
    }

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   
    nr = scene_lights.size ();

//MODELS
    
    cloud = new Model("Cloud.obj");
    
    //Argonath

    //argonathFront = new Appearance (emissiv, difuse, specular, shi_value);
    // argonathFront->setTexture ("../textures/argonathFront.jpg");

    skyboxFront = new Plane (100, "../textures/argonathFront.bmp");
    //skyboxFront->terrainAppearance = argonathFront;

    coiso = new Sphere (0.5, 12, 12);
    // Defines a default normal
    glNormal3f (0, 0, 1);

    setUpdatePeriod (30); 
}
void
DemoScene::update (long t) { }
void
DemoScene::display ()
{
    activateCamera (nr_cams);
    active->updateProjectionMatrix (CGFapplication::vpw, CGFapplication::vph);
    // ---- BEGIN Background, camera and axis setup

    //Setting background color
    glClearColor (lsf->colors[0], lsf->colors[1], lsf->colors[2], lsf->colors[3]);

    // Clear image and depth buffer everytilme we update the scene
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize Model-View matrix as identity (no transformation
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    // Apply transformations corresponding to the camera position relative to the origin
    active->applyView ();
    
    // Draw (and update) lights
    int x = 0;
   for (list<CGFlight*>::iterator it = scene_lights.begin (); it != scene_lights.end (); it++, x++)
    {
        if (lz[x])
        {
            (*it)->enable ();
        }
        else
        {
            (*it)->disable ();
        }
        (*it)->update ();
    }

    // Draw axis
   // axis.draw();


    // ---- END Background, camera and axis setup

    //Polygon mode and shading
    glShadeModel (lsf->shade);
    glPolygonMode (GL_FRONT_AND_BACK, lsf->mode);

    // ---- BEGIN drawing
    
    glPushMatrix();
    if(cloud->isPicked)
        cloud->animate ();
    cloud->draw ();
    glPopMatrix();
    
    glPushMatrix ();
    glTranslatef (-50.0, 0, 0);
    glRotatef (-90.0, 0, 0, 1);
    glTranslatef (-25.0, 0, -25.0);
    skyboxFront->draw ();
    glPopMatrix ();

    glPushMatrix ();
    //coiso->draw ();
    glPopMatrix ();

    
    // ---- END drawing

    // We have been drawing in a memory area that is not visible - the back buffer, 
    // while the graphics card is showing the contents of another buffer - the front buffer
    // glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
    glutSwapBuffers ();
}
void
DemoScene::display_select ()
{


    // Initialize Model-View matrix as identity (no transformation
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    // Apply transformations corresponding to the camera position relative to the origin
    active->applyView ();


    glShadeModel (lsf->shade);
    glPolygonMode (GL_FRONT_AND_BACK, lsf->mode);

    //Draw here the parts of the scene that we want to have picked.
    glPushName(cloud->name);
    glPushMatrix();    
    cloud->draw ();
    glPopMatrix();
    glPopName();
    
}
DemoScene::~DemoScene ()
{
    for (list<CGFlight*>::iterator it = scene_lights.begin (); it != scene_lights.end (); it++)
    {
        delete((*it));
    }
    for (int i = 0; i < vec_cameras.size (); i++)
    {
        delete(vec_cameras[i]);
    }
    delete(lsf);
}

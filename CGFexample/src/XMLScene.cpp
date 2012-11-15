#include "XMLScene.h"
XMLScene::XMLScene (char *filename)
{

    // Read XML from file
    string app_id;
    doc = new TiXmlDocument (filename);
    bool loadOkay = doc->LoadFile ();

    if (!loadOkay)
    {
        printf ("Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc ());
        exit (1);
    }
    //TODO Cenas.
    TiXmlElement* lsfElement = doc->FirstChildElement ("lsf");

    if (lsfElement == NULL)
    {
        printf ("Main lsf block element not found! Exiting!\n");
        exit (1);
    }

    globalElement = lsfElement->FirstChildElement ("globals");
    camerasElement = lsfElement->FirstChildElement ("cameras");
    lightElement = lsfElement->FirstChildElement ("lighting");
    appElement = lsfElement->FirstChildElement ("appearances");
    graphElement = lsfElement->FirstChildElement ("graph");

    // Global tag
    // Fetching all require nodes

    if (globalElement == NULL)
    {
        printf ("Global block not found!\n");
        exit (-1);
    }
    else
    {
        printf ("Processing global:\n");
    }

    //Processing of global elements		
    TiXmlElement* backElement = globalElement->FirstChildElement ("background");
    if (backElement)
    {
        if (backElement->QueryFloatAttribute ("r", &colors[0]) == TIXML_SUCCESS &&
            backElement->QueryFloatAttribute ("g", &colors[1]) == TIXML_SUCCESS &&
            backElement->QueryFloatAttribute ("b", &colors[2]) == TIXML_SUCCESS &&
            backElement->QueryFloatAttribute ("a", &colors[3]) == TIXML_SUCCESS
            )
            printf ("  background attributes: %f %f %f %f\n", colors[0], colors[1], colors[2], colors[3]);
        else
        {
            printf ("Error parsing background\n");
            exit (1);
        }
    }
    else
    {
        printf ("background not found\n");
        exit (1);
    }

    TiXmlElement* polyElement = globalElement->FirstChildElement ("polygon");
    if (polyElement)
    {
        string mode1 = (string) (polyElement->Attribute ("mode"));
        string shading1 = (string) (polyElement->Attribute ("shading"));

        if (!mode1.empty () && !shading1.empty ())
        {
            if (mode1 == "line")
            {
                mode = GL_LINE;
            }
            else if (mode1 == "point")
            {
                mode = GL_POINT;
            }
            else if (mode1 == "fill")
            {
                mode = GL_FILL;
            }
            else
            {
                cout << "Specified mode does not exist. Fallback is fill.\n";
                mode = GL_FILL;
            }

            if (shading1 == "flat")
            {
                shade = GL_FLAT;
            }
            else if (shading1 == "gouraud")
            {
                shade = GL_SMOOTH;
            }
            else
            {
                cout << "That shading mode does not exit. Fallback is flat.\n";
                shade = GL_FLAT;
            }

            cout << "Values of mode and shading: " << mode1 << " | " << shading1 << endl;
        }
        else
        {
            printf ("Error parsing polygon\n");
            exit (1);
        }
    }
    else
    {
        printf ("polygon not found");
        exit (1);
    }

    TiXmlElement* cullElement = globalElement->FirstChildElement ("culling");
    if (cullElement)
    {

        string front = (string) (cullElement->Attribute ("frontfaceorder"));
        string cull = (string) (cullElement->Attribute ("cullface"));

        if (strcmp (cullElement->Attribute ("enabled"), "true") == 0)
            cull_enable = true;
        else
            cull_enable = false;


        if (!front.empty () && !cull.empty ())
        {
            if (front == "CCW")
            {
                frontfaceorder = GL_CCW;
            }
            else if (front == "CW")
            {
                frontfaceorder = GL_CW;
            }
            else
            {
                cout << "Specified frontfaceorder invalid. Fallbck is CCW.\n";
                frontfaceorder = GL_CCW;
            }

            if (cull == "front")
            {
                cullface = GL_FRONT;
            }
            else if (cull == "back")
            {
                cullface = GL_BACK;
            }
            else
            {
                cout << "Default value is both\n";
                cullface = GL_FRONT_AND_BACK;
            }

            cout << "Cullface attributes loaded: " << front << " " << cull << " " << cull_enable << endl;
        }
        else
        {
            printf ("Error parsing culling attributes\n");
            exit (1);
        }
    }
    else
    {
        printf ("cullface not found");
        exit (1);
    }

    ///////////////////////////// CAMERAS ////////////////////////////////

    if (camerasElement)
    {
        printf ("Processing cameras:\n");

        string init = (string) (camerasElement->Attribute ("initial"));

        cout << init << endl;

        TiXmlElement* camera = camerasElement->FirstChildElement ();

        do
        {
            if ((string) camera->Value () == "perspective")
            {
                float far, near, angle;
                std::string id (camera->Attribute ("id"));

                if (!id.empty () &&
                    camera->QueryFloatAttribute ("far", &far) == TIXML_SUCCESS &&
                    camera->QueryFloatAttribute ("near", &near) == TIXML_SUCCESS &&
                    camera->QueryFloatAttribute ("angle", &angle) == TIXML_SUCCESS
                    )
                    cout << id << " " << far << " " << near << " " << angle << endl;

                TiXmlElement* fromElement = camera->FirstChildElement ("from");

                float pos[3];

                if (fromElement->QueryFloatAttribute ("x", &pos[0]) == TIXML_SUCCESS &&
                    fromElement->QueryFloatAttribute ("y", &pos[1]) == TIXML_SUCCESS &&
                    fromElement->QueryFloatAttribute ("z", &pos[2]) == TIXML_SUCCESS
                    )
                {
                    //printf("from: %f %f %f\n", xf,yf,zf);
                }
                else
                {
                    printf ("erro no from\n");
                    exit (1);
                }

                TiXmlElement* toElement = camera->FirstChildElement ("to");
                float tar[3];

                if (toElement->QueryFloatAttribute ("x", &tar[0]) == TIXML_SUCCESS &&
                    toElement->QueryFloatAttribute ("y", &tar[1]) == TIXML_SUCCESS &&
                    toElement->QueryFloatAttribute ("z", &tar[2]) == TIXML_SUCCESS
                    )
                {
                    //printf("to: %f %f %f\n", xt,yt,zt);
                }
                else
                {
                    printf ("erro no to\n");
                    exit (1);
                }
                cameras[id] = new CameraPers (id, near, far, angle, pos, tar);
            }
            else
                printf ("Error or no perspective element\n");

            if ((string) camera->Value () == "ortho")
            {
                float nearo, faro, left, right, top, bottom;
                std::string ido (camera->Attribute ("id"));

                if (!ido.empty () &&
                    camera->QueryFloatAttribute ("near", &nearo) == TIXML_SUCCESS &&
                    camera->QueryFloatAttribute ("far", &faro) == TIXML_SUCCESS &&
                    camera->QueryFloatAttribute ("left", &left) == TIXML_SUCCESS &&
                    camera->QueryFloatAttribute ("right", &right) == TIXML_SUCCESS &&
                    camera->QueryFloatAttribute ("top", &top) == TIXML_SUCCESS &&
                    camera->QueryFloatAttribute ("bottom", &bottom) == TIXML_SUCCESS
                    )
                    cout << ido << " " << nearo << " " << faro << " " << left << " " << right << " " << top << " " << bottom << endl;
                else
                {
                    printf ("error parsing ortho");
                    exit (1);
                }
                cameras[ido] = new CameraOrth (ido, nearo, faro, left, right, top, bottom);
            }
            else
                printf ("Error or not ortho Element\n");

            camera = camera->NextSiblingElement ();
        }
        while (camera);

        map<string, CGFcamera*>::iterator it = cameras.find (init);
        if (it != cameras.end ())
        {
            camera_init = it->second;
        }
        else
        {
            cout << "The camera defined as init is not defined\n";
            exit (1);
        }
    }
    else
    {
        printf ("Error parsing cameras\n");
    }


    ////////////////////////////////////LUZES/////////////////////////////////////////////////////////


    if (lightElement)
    {
        bool doublesided, local, enabled;

        if (strcmp (lightElement->Attribute ("doublesided"), "true") == 0)
            doublesided = true;
        else
            doublesided = false;

        if (strcmp (lightElement->Attribute ("local"), "true") == 0)
            local = true;
        else
            local = false;

        if (strcmp (lightElement->Attribute ("enabled"), "true") == 0)
            enabled = true;
        else
            enabled = false;
    }
    else
    {
        cout << "There must be a light element, at least ambient.";
        exit (1);
    }

    TiXmlElement* ambientElement = lightElement->FirstChildElement ("ambient");
    if (ambientElement)
    {
        float amb_r, amb_g, amb_b, amb_a;

        if (ambientElement->QueryFloatAttribute ("r", &amb_r) == TIXML_SUCCESS &&
            ambientElement->QueryFloatAttribute ("g", &amb_g) == TIXML_SUCCESS &&
            ambientElement->QueryFloatAttribute ("b", &amb_b) == TIXML_SUCCESS &&
            ambientElement->QueryFloatAttribute ("a", &amb_a) == TIXML_SUCCESS
            )
        {
            float new_back[4] = {amb_r, amb_g, amb_b, amb_a};
            for (int i = 0; i < 4; i++)
            {
                CGFlight::background_ambient[i] = new_back[i];
            }

            printf ("Ambient light attributes: %f %f %f %f\n", amb_r, amb_g, amb_b, amb_a);
        }
        else
        {
            printf ("Error parsing ambient light\n");
            exit (1);
        }
    }
    else
    {
        printf ("ambient light not found\n");
        exit (1);
    }

    TiXmlElement* lights = lightElement->FirstChildElement ("lights");
    if (lights == NULL)
    {
        cout << "There must be a light block!!" << endl;
        exit (1);
    }
    else
    {
        TiXmlElement* L0 = lights->FirstChildElement ();
        float light_pos[4];
        CGFlight* light;
        string L_id;
        int count = 0;
        do
        {
            if (luzes.size () < 9)
            {
                if (L0)
                {
                    L_id = (string) (L0->Attribute ("id"));

                    if (!L_id.empty ())
                        cout << "A luz com id " << L_id << endl;
                    else
                    {
                        cout << "Issues reading attribute id of light \n";
                        exit (1);
                    }


                    TiXmlElement* L0_loca = L0->FirstChildElement ();
                    TiXmlElement* L0_ambi = L0_loca->NextSiblingElement ();
                    TiXmlElement* L0_diff = L0_ambi->NextSiblingElement ();
                    TiXmlElement* L0_spec = L0_diff->NextSiblingElement ();

                    float L_ambi[4], L_diff[4], L_spec[4];

                    if (L0_loca->QueryFloatAttribute ("x", &light_pos[0]) == TIXML_SUCCESS &&
                        L0_loca->QueryFloatAttribute ("y", &light_pos[1]) == TIXML_SUCCESS &&
                        L0_loca->QueryFloatAttribute ("z", &light_pos[2]) == TIXML_SUCCESS &&
                        L0_ambi->QueryFloatAttribute ("r", &L_ambi[0]) == TIXML_SUCCESS &&
                        L0_ambi->QueryFloatAttribute ("g", &L_ambi[1]) == TIXML_SUCCESS &&
                        L0_ambi->QueryFloatAttribute ("b", &L_ambi[2]) == TIXML_SUCCESS &&
                        L0_ambi->QueryFloatAttribute ("a", &L_ambi[3]) == TIXML_SUCCESS &&
                        L0_diff->QueryFloatAttribute ("r", &L_diff[0]) == TIXML_SUCCESS &&
                        L0_diff->QueryFloatAttribute ("g", &L_diff[1]) == TIXML_SUCCESS &&
                        L0_diff->QueryFloatAttribute ("b", &L_diff[2]) == TIXML_SUCCESS &&
                        L0_diff->QueryFloatAttribute ("a", &L_diff[3]) == TIXML_SUCCESS &&
                        L0_spec->QueryFloatAttribute ("r", &L_spec[0]) == TIXML_SUCCESS &&
                        L0_spec->QueryFloatAttribute ("g", &L_spec[1]) == TIXML_SUCCESS &&
                        L0_spec->QueryFloatAttribute ("b", &L_spec[2]) == TIXML_SUCCESS &&
                        L0_spec->QueryFloatAttribute ("a", &L_spec[3]) == TIXML_SUCCESS)
                    {
                        light_pos[3] = 1;

                        //Spot lights
                        TiXmlElement* L_spot = L0_spec->NextSiblingElement ();
                        if (L_spot)
                        {
                            float dir[3];
                            float angle, exp;

                            if (L_spot->QueryFloatAttribute ("angle", &angle) == TIXML_SUCCESS &&
                                L_spot->QueryFloatAttribute ("exponent", &exp) == TIXML_SUCCESS &&
                                L_spot->QueryFloatAttribute ("dirx", &dir[0]) == TIXML_SUCCESS &&
                                L_spot->QueryFloatAttribute ("diry", &dir[1]) == TIXML_SUCCESS &&
                                L_spot->QueryFloatAttribute ("dirz", &dir[2]) == TIXML_SUCCESS)
                            {
                                light = new CGFlight (GL_LIGHT0 + count, light_pos, dir);
                                glLightf (GL_LIGHT0 + count, GL_SPOT_CUTOFF, angle);
                                glLightf (GL_LIGHT0 + count, GL_SPOT_EXPONENT, exp);
                            }
                        }
                        else
                        {
                            light = new CGFlight (GL_LIGHT0 + count, light_pos);
                        }

                        light->setAmbient (L_ambi);
                        light->setDiffuse (L_diff);
                        light->setSpecular (L_spec);
                        if (strcmp (L0->Attribute ("enabled"), "true") == 0)
                            light->enable ();
                        else
                            light->disable ();

                        cout << "Success at loading all light " << L_id << " attributes\n";
                    }
                    else
                    {
                        cout << "Couldn't load one or some light attributes\n";
                        exit (1);
                    }

                    luzes[L_id] = light;
                    count++;
                }
                else
                {
                    cout << "There should be at least one light block. Exiting\n";
                    exit (1);
                }

                L0 = L0->NextSiblingElement ();
            }
            else
            {
                cout << "There can be no more lights.\n";
                exit (1);
            }
        }
        while (L0);
    }


    ///////////////////////////////////////////////Apearances////////////////////////////////////////
    TiXmlElement* appearance = appElement->FirstChildElement ("appearance");


    do
    {
        Appearance* materialAppearance;

        if (appearance)
        {
            printf ("Processing appeareances:\n");

            app_id = (string) (appearance->Attribute ("id"));

            if (app_id.empty ())
            {
                cout << "No appearance id.\n";
                exit (1);
            }

            cout << " id= " << app_id << endl;
            float emissiv[4];
            float ambient[4];
            float difuse[4];
            float specular[4];
            float shi_value;

            TiXmlElement* emiElement = appearance->FirstChildElement ("emissive");
            TiXmlElement* ambiElement = appearance->FirstChildElement ("ambient");
            TiXmlElement* diffElement = appearance->FirstChildElement ("diffuse");
            TiXmlElement* specElement = appearance->FirstChildElement ("specular");
            TiXmlElement* shineElement = appearance->FirstChildElement ("shininess");
            TiXmlElement* textureElement = appearance->FirstChildElement ("texture");

            if (emiElement)
            {
                if (emiElement->QueryFloatAttribute ("r", &emissiv[0]) == TIXML_SUCCESS &&
                    emiElement->QueryFloatAttribute ("g", &emissiv[1]) == TIXML_SUCCESS &&
                    emiElement->QueryFloatAttribute ("b", &emissiv[2]) == TIXML_SUCCESS &&
                    emiElement->QueryFloatAttribute ("a", &emissiv[3]) == TIXML_SUCCESS)
                {
                    cout << "success reading emissive light" << endl;
                }
                else
                {
                    cout << "error with emissive light" << endl;
                    exit (1);
                }
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    emissiv[i] = 0;
                }
                cout << "no appearance light was found. Could be it's not a light." << endl;
            }

            if (ambiElement)
            {
                if (ambiElement->QueryFloatAttribute ("r", &ambient[0]) == TIXML_SUCCESS &&
                    ambiElement->QueryFloatAttribute ("g", &ambient[1]) == TIXML_SUCCESS &&
                    ambiElement->QueryFloatAttribute ("b", &ambient[2]) == TIXML_SUCCESS &&
                    ambiElement->QueryFloatAttribute ("a", &ambient[3]) == TIXML_SUCCESS)
                {
                    cout << "sucess reading ambient light from appearance  " << app_id << endl;
                }
                else
                {
                    cout << "error with appearance attributes" << endl;
                    exit (1);
                }
            }
            else
            {
                cout << "no ambient found" << endl;
                exit (1);
            }

            /////////////////////////////difuse//////////////////////////
            if (diffElement)
            {
                if (diffElement->QueryFloatAttribute ("r", &difuse[0]) == TIXML_SUCCESS &&
                    diffElement->QueryFloatAttribute ("g", &difuse[1]) == TIXML_SUCCESS &&
                    diffElement->QueryFloatAttribute ("b", &difuse[2]) == TIXML_SUCCESS &&
                    diffElement->QueryFloatAttribute ("a", &difuse[3]) == TIXML_SUCCESS)
                {
                    cout << "sucess reading diffuse light from appearance " << app_id << endl;
                }
                else
                {
                    cout << "error with diffuse attributes" << endl;
                    exit (1);
                }
            }
            else
            {
                cout << "no diffuse found" << endl;
                exit (1);
            }

            ///////////////////////////specular///////////////////////////////////////////////

            if (specElement)
            {
                if (specElement->QueryFloatAttribute ("r", &specular[0]) == TIXML_SUCCESS &&
                    specElement->QueryFloatAttribute ("g", &specular[1]) == TIXML_SUCCESS &&
                    specElement->QueryFloatAttribute ("b", &specular[2]) == TIXML_SUCCESS &&
                    specElement->QueryFloatAttribute ("a", &specular[3]) == TIXML_SUCCESS)
                {
                    cout << "sucess reading specular light from appearance " << app_id << endl;
                }
                else
                {
                    cout << "error with specular attributes" << endl;
                    exit (1);
                }
            }
            else
            {
                cout << "no specular found" << endl;
                exit (1);
            }
            /////////////////////shininess////////////////////////////////
            if (shineElement)
            {
                if (shineElement->QueryFloatAttribute ("value", &shi_value) == TIXML_SUCCESS)
                {
                    cout << "shininess value of appearance " << shi_value << endl;
                }
                else
                {
                    cout << "Error loading shininess attributes" << endl;
                    exit (1);
                }
            }
            else
            {
                cout << "shininess not found" << endl;
                exit (1);
            }

            materialAppearance = new Appearance (app_id, emissiv, ambient, difuse, specular, shi_value);

            ///////////////////////////////////////// Texture //////////////////////////////////////////
            if (textureElement)
            {
                std::string path (textureElement->Attribute ("file"));
                float length_s, length_t;

                if (!path.empty () &&
                    textureElement->QueryFloatAttribute ("length_s", &length_s) == TIXML_SUCCESS &&
                    textureElement->QueryFloatAttribute ("length_t", &length_t) == TIXML_SUCCESS)
                {
                    materialAppearance->setTexture (path);
                    materialAppearance->set_lengths (length_s, length_t);
                    cout << path << " " << length_s << " " << length_t << endl;
                }
                else
                {
                    cout << "Error reading texture attributes" << endl;
                    exit (1);
                }
            }
            else
            {
                cout << "There is no texture" << endl;
            }
            cout << "app_id: " << app_id << endl;
            appearances[app_id] = materialAppearance;
            if(app_id == "heli")
            {
                heli_app = materialAppearance;
            }
            else if(app_id == "pads")
            {
                pads_app = materialAppearance;
            }
        }
        appearance = appearance->NextSiblingElement ();
    }
    while (appearance);


    /////////// Graph Parsin ////////////	
    if (graphElement)
    {
        std::string root_id (graphElement->Attribute ("rootid"));

        if (!root_id.empty ())
        {
            cout << "Root's id: " << root_id << endl;
            TiXmlElement* nodeElement = graphElement->FirstChildElement ("node");

            do
            {

                ///////////// Node Parsing. Runs cycle once per node and while there are nodes ////////////////
                if (nodeElement)
                {
                    // Variables to construct a Node
                    GLfloat matrix[16];
                    list<Primitive*> Prim;
                    list<string> children_id;
                    string apref_id;
                    string node_id = (string) nodeElement->Attribute ("id");
                    bool isCL = false;
                    nodeElement->QueryBoolAttribute ("displaylist", &isCL);
                    bool isEval = false;
                    cout << "id: " << node_id << " isCL: " << isCL << endl;

                    TiXmlElement* transform_node = nodeElement->FirstChildElement ("transforms");

                    //////////////// Parsing of Geometric Transformations ////////////////
                    if (transform_node)
                    {
                        TiXmlElement* transf = transform_node->FirstChildElement ();

                        glMatrixMode (GL_MODELVIEW);
                        glPushMatrix ();
                        glLoadIdentity ();

                        if (transf)
                        {
                            do
                            {

                                //////////////// Translation ////////////////
                                if ((string) transf->Value () == "translate")
                                {
                                    float tr_x, tr_y, tr_z;

                                    if (transf->QueryFloatAttribute ("x", &tr_x) == TIXML_SUCCESS &&
                                        transf->QueryFloatAttribute ("y", &tr_y) == TIXML_SUCCESS &&
                                        transf->QueryFloatAttribute ("z", &tr_z) == TIXML_SUCCESS)
                                    {

                                        glTranslatef (tr_x, tr_y, tr_z);

                                        cout << "Translation with values: x= " << tr_x << " y= " << tr_y << " z= " << tr_z << endl;
                                    }
                                    else
                                    {
                                        cout << "Error reading translation attributes\n";
                                        exit (1);
                                    }
                                }
                                else
                                {
                                    cout << "Could not find or there is no translation." << endl;
                                }

                                //////////////// Rotation ////////////////
                                if ((string) transf->Value () == "rotate")
                                {
                                    std::string axis (transf->Attribute ("axis"));
                                    float angle;

                                    if (!axis.empty () && axis.size () == 1 && transf->QueryFloatAttribute ("angle", &angle) == TIXML_SUCCESS)
                                    {
                                        if (axis == "x")
                                            glRotatef (angle, 1, 0, 0);
                                        else if (axis == "y")
                                            glRotatef (angle, 0, 1, 0);
                                        else if (axis == "z")
                                            glRotatef (angle, 0, 0, 1);
                                        else
                                            cout << "That axis is invalid. Thank you come again!\n";

                                        cout << "Axis is " << axis << " and angle is " << angle << endl;
                                    }
                                    else
                                    {
                                        cout << "Error reading rotation attributes\n";
                                        exit (1);
                                    }
                                }
                                else
                                {
                                    cout << "Could not find or there is no rotation." << endl;
                                }

                                //////////////// Scaling ////////////////
                                if ((string) transf->Value () == "scale")
                                {
                                    float s_x, s_y, s_z;

                                    if (transf->QueryFloatAttribute ("x", &s_x) == TIXML_SUCCESS &&
                                        transf->QueryFloatAttribute ("y", &s_y) == TIXML_SUCCESS &&
                                        transf->QueryFloatAttribute ("z", &s_z) == TIXML_SUCCESS)
                                    {
                                        glScalef (s_x, s_y, s_z);
                                        cout << "Scaling with values: x= " << s_x << " y= " << s_y << " z= " << s_z << endl;
                                    }
                                    else
                                    {
                                        cout << "Error reading scaling attributes\n";
                                        exit (1);
                                    }
                                }
                                else
                                {
                                    cout << "Could not find or there is no scaling." << endl;
                                }
                                transf = transf->NextSiblingElement ();
                            }
                            while (transf);
                        }
                        cout << endl;
                        glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
                        glPopMatrix ();
                    }
                    else
                    {
                        cout << "There is not transform node and there must be at least one. Exiting." << endl;
                        exit (1);
                    }

                    //////////////// Parsing of appearance ////////////////
                    TiXmlElement* appearanceref = nodeElement->FirstChildElement ("appearanceref");

                    if (appearanceref)
                    {
                        apref_id = (string) (appearanceref->Attribute ("id"));

                        if (!apref_id.empty ())
                        {
                            cout << "Appearance's id for this node is: " << apref_id << endl;
                        }
                        else
                        {
                            cout << "Error reading appearance id." << endl;
                            exit (1);
                        }
                    }
                    else
                    {
                        cout << "This node inherits his father's appearance." << endl;
                    }

                    TiXmlElement* children = nodeElement->FirstChildElement ("children");

                    //////////////// Parsing of Node's children. 0-4 is each Primitive while 5 being another node. ////////////////
                    if (children)
                    {
                        TiXmlElement* tag = children->FirstChildElement ();

                        string teste[] = {"rectangle", "triangle", "cylinder", "sphere", "torus", "patch", "noderef","plane"};
                        int x;
                        float tag_x1, tag_x2, tag_x3, tag_y1, tag_y2, tag_y3;
                        float tag_z1, tag_z2, tag_z3, base, top, height, radius, inner, outer;
                        float OrderU, OrderV, partsU, partsV;
                        int slices, stacks, loops;
                        GLfloat control;
                        //string ctrl;
                        
                        string tag_s;

                        if (tag)
                        {
                            do
                            {

                                tag_s = (string) tag->Value ();
                                x = 0;

                                while (teste[x] != tag_s)
                                {
                                    x++;
                                }

                                switch (x)
                                {
                                case 0: // Rectangle
                                {
                                    if (tag->QueryFloatAttribute ("x1", &tag_x1) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("y1", &tag_y1) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("x2", &tag_x2) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("y2", &tag_y2) == TIXML_SUCCESS)
                                    {
                                        Prim.push_back (new Rectangle (tag_x1, tag_x2, tag_y1, tag_y2)); // Creates new rectangle and adds it to Prim list
                                        cout << "Values for rectangle primitive: x1= " << tag_x1 << " x2= " << tag_x2 << " y1= " << tag_y1 << " y2= " << tag_y2 << endl;
                                    }
                                    else
                                    {
                                        cout << "Error loading rectangle values." << endl;
                                        exit (1);
                                    }
                                    break;
                                }
                                case 1: // Triangle
                                {
                                    if (tag->QueryFloatAttribute ("x1", &tag_x1) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("y1", &tag_y1) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("z1", &tag_z1) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("x2", &tag_x2) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("y2", &tag_y2) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("z2", &tag_z2) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("x3", &tag_x3) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("y3", &tag_y3) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("z3", &tag_z3) == TIXML_SUCCESS)
                                    {
                                        Prim.push_back (new Triangle (tag_x1, tag_x2, tag_x3, tag_y1, tag_y2, tag_y3, tag_z1, tag_z2, tag_z3));
                                        cout << "Values for triangle primitive: x1= " << tag_x1 << " x2= " << tag_x2 << " x3= " << tag_x3 << " y1= " << tag_y1;
                                        cout << " y2= " << tag_y2 << " y3= " << tag_y3 << " z1= " << tag_z1 << " z2= " << tag_z2 << " z3= " << tag_z3 << endl;
                                    }
                                    else
                                    {
                                        cout << "Error loading triangle values." << endl;
                                        exit (1);
                                    }
                                    break;
                                }
                                case 2: // Cylinder
                                {
                                    if (tag->QueryFloatAttribute ("base", &base) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("top", &top) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("height", &height) == TIXML_SUCCESS &&
                                        tag->QueryIntAttribute ("slices", &slices) == TIXML_SUCCESS &&
                                        tag->QueryIntAttribute ("stacks", &stacks) == TIXML_SUCCESS)
                                    {
                                        Prim.push_back (new Cylinder (base, top, height, slices, stacks));
                                        cout << "Values of cylinder primitive: base= " << base << " top= " << top << " height= " << height << " slices= " << slices
                                                << " stacks= " << stacks << endl;
                                    }
                                    else
                                    {
                                        cout << "Error loading cylinder values." << endl;
                                        exit (1);
                                    }
                                    break;
                                }
                                case 3: // Sphere
                                {
                                    if (tag->QueryFloatAttribute ("radius", &radius) == TIXML_SUCCESS &&
                                        tag->QueryIntAttribute ("slices", &slices) == TIXML_SUCCESS &&
                                        tag->QueryIntAttribute ("stacks", &stacks) == TIXML_SUCCESS)
                                    {
                                        Prim.push_back (new Sphere (radius, slices, stacks));
                                        cout << "Values of sphere primitive: radius= " << radius << " slices= " << slices << " stacks= " << stacks << endl;
                                    }
                                    else
                                    {
                                        cout << "Error loading sphere values." << endl;
                                        exit (1);
                                    }
                                    break;
                                }
                                case 4: // Torus
                                {
                                    if (tag->QueryFloatAttribute ("inner", &inner) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("outer", &outer) == TIXML_SUCCESS &&
                                        tag->QueryIntAttribute ("slices", &slices) == TIXML_SUCCESS &&
                                        tag->QueryIntAttribute ("loops", &loops) == TIXML_SUCCESS)
                                    {
                                        Prim.push_back (new Torus (inner, outer, slices, loops));
                                        cout << "Values of torus primitive: inner= " << inner << " outer= " << outer << " slices= " << slices << " loops= " << loops << endl;
                                    }
                                    else
                                    {
                                        cout << "Error loading torus values." << endl;
                                        exit (1);
                                    }
                                    break;
                                }
                                case 5: //Patch
                                {
                                    const char* ctrl = tag->Attribute ("control");
                                    
                                    if (tag->QueryFloatAttribute ("orderU", &OrderU) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("orderV", &OrderV) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("partsU", &partsU) == TIXML_SUCCESS &&
                                        tag->QueryFloatAttribute ("partsV", &partsV) == TIXML_SUCCESS &&
                                        sizeof(ctrl) != 0)
                                    {
                                        int size = OrderU * OrderV;
                                        GLfloat ** coordpoints;
                                        coordpoints = new GLfloat*[size];
                                        for(int i = 0; i<size;i++)
                                        {
                                            coordpoints[i] = new GLfloat[3];
                                        }
                                        

                                        TiXmlElement* controlpoint = tag->FirstChildElement ();

                                        if (strcmp(ctrl,"fill") == 0)
                                        {
                                            control = GL_FILL;
                                        }
                                        else if (strcmp(ctrl,"line") == 0)
                                        {
                                            control = GL_LINE;
                                        }
                                        else if (strcmp(ctrl,"point") == 0)
                                        {
                                            control = GL_POINT;
                                        }
                                        else
                                        {
                                            cout << "Error. Such Control does not exist.\n";
                                            exit (1);
                                        }


                                        for (int i = 0; i < size; i++)
                                        {
                                            if (controlpoint &&
                                                controlpoint->QueryFloatAttribute ("x", &coordpoints[i][0]) == TIXML_SUCCESS &&
                                                controlpoint->QueryFloatAttribute ("y", &coordpoints[i][1]) == TIXML_SUCCESS &&
                                                controlpoint->QueryFloatAttribute ("z", &coordpoints[i][2]) == TIXML_SUCCESS)
                                            {
                                               
                                                
                                                controlpoint = controlpoint->NextSiblingElement ();
                                            }
                                            else
                                            {
                                                cout << "Error reading values of control points\n";
                                                exit (1);
                                            }
                                        }
                                        isEval = true;
                                        
                                        for(int i = 0; i<size; i++)
                                                {
                                                    cout << coordpoints[i][0] << " " << coordpoints[i][1] << " " << coordpoints[i][2] <<endl;
                                                }
                                         cout << "bleh\n";
                                        Prim.push_back (new Patch (OrderU, OrderV, partsU, partsV, control,size, coordpoints));
                                        
                                    }
                                    else
                                    {
                                        cout << "Error creating patch.\n";
                                        exit (1);
                                    }
                                    break;
                                }
                                case 6: // Another composed node (i.e. not a leaf)
                                {

                                    string child_id = (string)tag->Attribute ("id");

                                    if (!child_id.empty())
                                    {
                                        children_id.push_back (child_id);
                                        cout << "Child id= " << child_id << endl;
                                    }
                                    else
                                    {
                                        cout << "Error getting child's id. Please investigate. Exiting..." << endl;
                                        exit (-1);
                                    }
                                    break;
                                }
                                case 7: //Plane
                                {
                                    int parts;
                                    if(tag->QueryIntAttribute ("parts",&parts) == TIXML_SUCCESS)
                                    {
                                        Prim.push_back (new Plane(parts));
                                    }
                                    else
                                    {
                                        cout << "Error reading parts for plane primitive.\n";
                                        exit(1);
                                    }
                                    break;
                                }
                                }
                                tag = tag->NextSiblingElement ();
                            }
                            while (tag);
                        }
                        else
                        {
                            cout << "This node has no children.\n";
                        }
                    }
                    else
                    {
                        cout << "There is no children block. There has to be one. Error..." << endl;
                        exit (-1);
                    }

                    No* node = new No (node_id, apref_id, matrix, children_id, isCL,isEval); // create a new node pointer with its values

                    //fill the node's list of Primitives
                    if (Prim.size () != 0)
                    {
                        for (list<Primitive*>::iterator it = Prim.begin (); it != Prim.end (); ++it)
                        {
                            cout << (*it) << endl;
                            node->fill_primitive (*it);
                        }
                    }
                    
                    nodes[node_id] = node; // Adds this iterations node to the map, referencing by its id

                    nodeElement = nodeElement->NextSiblingElement ();
                }
                else
                {
                    cout << "There are no nodes... There have to be nodes in a Scene Graph... ERROR!!!!" << endl;
                    exit (-1);
                }
            }
            while (nodeElement);
        }
        else
        {
            cout << "There is no root tag. BIG ERROR!!!!!!!!1" << endl;
            exit (-1);
        }
        root = nodes.find (root_id)->second; // Finds the root's pointer in the map and transfers it to root
    }
    else
    {
        cout << "There has to be a graph block. HUGE ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11" << endl;
        exit (-1);
    }


    //////////////// DO REST OF MAP FINDS HERE ////////////////
    for (map<string, No*>::iterator it = nodes.begin (); it != nodes.end (); it++) // For every entry on nodes' map
    {

        for (list<string>::iterator it2 = (*it).second->child_ids.begin (); it2 != (*it).second->child_ids.end (); it2++) // For every string in a node's children_id list
        {
            (*it).second->children.push_back (nodes.find ((*it2))->second); // Inserts into children list of pointer to nodes the pointer to a given child.
        }

        cout << "App ID: " << (*it).second->appearanceid << endl;
        cout << "Antes da atribuicao ao no: " << appearances.find ((*it).second->appearanceid)->second << endl;
        (*it).second->materialAppearance = appearances.find ((*it).second->appearanceid)->second;
    }

    /*if (!Verifica (root))
    {
        exit (1);
    }*/
}

//Função que verifica recursivamente se há ciclos.
bool
XMLScene::Verifica (No* node)
{
    bool res;

    if (!node->visited)
    {
        for (list<No*>::iterator it = node->children.begin (); it != node->children.end (); it++)
        {
            node->visited = true;
            if (!Verifica ((*it)))
            {
                res = false;
                return res;
            }
            node->visited = false;
        }
    }
    else
    {
        cout << "There is a loop to node " << node->name << endl;
        res = false;
        return res;
    }

    res = true;
    return res;
}
void
XMLScene::GenerateList (No* node)
{
    for (list<No*>::iterator it = node->children.begin (); it != node->children.end (); it++)
    {
        
        if ((*it)->isCallList)
        {
            (*it)->fatherAppearance = node->materialAppearance;
        }
        GenerateList ((*it));
    }
    if (node->isCallList)
    {
        node->generateCallList ();
    }
}

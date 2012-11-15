#ifndef NO_H
#define NO_H

#include "CGFobject.h"
#include "Appearance.h"
#include <list>
#include <iostream>
#include "CGFobject.h"
#include "Primitive.h"
#include <stack>

using namespace std;

class No: public CGFobject{	
	public:
		bool visited,isCallList,isEval;
		GLuint myCallList;
		string name,appearanceid;
		GLfloat matrix[16];
		list<string> child_ids;
		list<No*> children;
		list<Primitive*> primitives;
		Appearance* materialAppearance;
                Appearance* fatherAppearance;
		static stack<Appearance*> pilha;
		No(){};
		virtual ~No(){};
		No(string name,string ap, GLfloat m[16], list<string> child_ids,bool isCL,bool isEval);
		void fill_children(No* child)
		{
			children.push_back(child);
		}
		
		void fill_primitive(Primitive* prim)
		{
			primitives.push_back(prim);
		}
		void generateCallList();
		void draw();
		void drawAll();
};



#endif

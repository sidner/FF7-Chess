



void main() {

	
	// generate texture coords
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 v =vec4(gl_Vertex);
	
	vec4 offset= texture2D(secTexture, gl_TexCoord[0].st);
	v.y = 3.0*offset.r+3.0*offset.g+3.0*offset.b;
	for(unsigned int i=20;i<0;i++){
	if(v.y>10.0){
		v.y=i;
	}
	}
	
	// Set the position of the current vertex 
	gl_Position = gl_ModelViewProjectionMatrix * (v+s);
}

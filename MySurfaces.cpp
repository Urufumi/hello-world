//
//  MySurfaces.cpp
//
//   Sets up and renders 
//     - the ground plane, and
//     - the surface of rotation
//   for the Math 155A project #4.
//
//   Comes supplied with the code for Sam Buss's "S".
//


// Use the static library (so glew32.dll is not needed):
#define GLEW_STATIC
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "LinearR3.h"		// Adjust path as needed.
#include "LinearR4.h"		// Adjust path as needed.
#include "MathMisc.h"       // Adjust path as needed

#include "MySurfaces.h"
#include "LetterProj.h"
#include "ShaderMgrLTR2.h"

using namespace std;

// ************************
// General data helping with setting up VAO (Vertex Array Objects)
//    and Vertex Buffer Objects.
// ***********************
const int NumObjects = 2;
const int iFloor = 0;
const int iCircularSurf = 1;

unsigned int myVBO[NumObjects];  // a Vertex Buffer Object holds an array of data
unsigned int myVAO[NumObjects];  // a Vertex Array Object - holds info about an array of vertex data;
unsigned int myEBO[NumObjects];  // a Element Array Buffer Object - holds an array of elements (vertex indices)

// **********************
// This sets up geometries needed for the "Initial" (the 3-D alphabet letter)
//  It is called only once.
// **********************
void MySetupSurfaces() {
    // Initialize the VAO's, VBO's and EBO's for the ground plane,
    // and the surface of rotation. Give them the "aPos" location,
    // and the "aNormal" location in the shader program.
    // No data is loaded into the VBO's or EBO's until the "Remesh"
    //   routines are called.

    // For the floor:
    // Allocate the needed Vertex Array Objects (VAO's),
    //      Vertex Buffer Objects (VBO's) and Element Array Buffer Objects (EBO's)
    // Since the floor has normal (0,1,0) everywhere, it will be given as
    // generic vertex attribute, not loaded in the VBO as a per-vertex value.
    // The color is also a generic vertex attribute.
    glGenVertexArrays(NumObjects, &myVAO[0]);
    glGenBuffers(NumObjects, &myVBO[0]);
    glGenBuffers(NumObjects, &myEBO[0]);

    glBindVertexArray(myVAO[iFloor]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);

    glVertexAttribPointer(aPos_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Store vertices in the VBO
    glEnableVertexAttribArray(aPos_loc);									// Enable the stored vertices
 
    // For the circular surface:
    // Allocate the needed VAO, VBO< EBO
    // The normal vectors is specified separately for each vertex. (It is not a generic attribute.)
    // The color is still a generic vertex attribute.
    glBindVertexArray(myVAO[iCircularSurf]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);

    glVertexAttribPointer(aPos_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Store vertices in the VBO
    glEnableVertexAttribArray(aPos_loc);									// Enable the stored vertices
    glVertexAttribPointer(aNormal_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Store normals in the VBO
    glEnableVertexAttribArray(aNormal_loc);                                 // Enabled the stored normals (so they are not generic)

    // No data has been loaded into the VBO's yet.
    // This is done next by the "Remesh" routines.

    MyRemeshSurfaces();
    
    check_for_opengl_errors();      // Watch the console window for error messages!
}

// **********************************************
// MODIFY THIS ROUTINE TO CALL YOUR OWN CODE IN
//   MyRemeshFloor AND MyRemeshCircularSurf
// INSTEAD OF THE "DEMO" VERSIONS.
// **********************************************

void MyRemeshSurfaces() 
{
	
    // WRITE MyRemeshFloor AND USE IT INSTEAD OF RemeshPlaneDemo
    //RemeshFloorDemo();
    MyRemeshFloor();

    // WRITE MyRemeshCircularSurf AND USE IT INSTEAD OF RemeshCircularDemo
    //RemeshCircularDemo();
    MyRemeshCircularSurf();

    check_for_opengl_errors();      // Watch the console window for error messages!
}

// **********************************************
// MODIFY THIS ROUTINE TO CALL YOUR OWN CODE IN
//   MyRemeshFloor AND MyRemeshCircularSurf
// INSTEAD OF THE "DEMO" VERSIONS.
// **********************************************

void MyRenderSurfaces() {
    // WRITE MyRemeshFloor AND USE IT INSTEAD OF RemeshPlaneDemo
    //RenderFloorDemo();
    MyRenderFloor();

    // WRITE MyRemeshCircularSurf AND USE IT INSTEAD OF RemeshCircularDemo
    //RenderCircularDemo();
    MyRenderCircularSurf();

    check_for_opengl_errors();      // Watch the console window for error messages!
}

// *********************************************
// THE CODE FOR THE NEXT FOUR ROUIINTES BELOW GIVES SIMPLE FIXED SIZE OBJECTS:
// A plane gridded into 4x4 array of rectangles (triangulated)
// and Circular piece with 4 slices, and 4 rings.
// THIS CODE WILL NOT BE USED IN YOUR PROGRAMMING SOLUTION.
// INSTEAD, FINISH WRITING MyRemeshFloor() and MyRemeshCircularSurf() below.
// *********************************************************

// Make the floor a 4x4 grid of triangulated quads.
// Render it as four triangle strips.
void RemeshFloorDemo()
{
    // Floor vertices.
    float floorVerts[][3] = {
        { -5.0f, 0.0f, -5.0f }, { -2.5f, 0.0f, -5.0f }, { 0.0f, 0.0f, -5.0f }, { 2.5f, 0.0f, -5.0f }, { 5.0f, 0.0f, -5.0f },  // Back row
        { -5.0f, 0.0f, -2.5f }, { -2.5f, 0.0f, -2.5f }, { 0.0f, 0.0f, -2.5f }, { 2.5f, 0.0f, -2.5f }, { 5.0f, 0.0f, -2.5f },  // Fourth row
        { -5.0f, 0.0f,  0.0f }, { -2.5f, 0.0f,  0.0f }, { 0.0f, 0.0f,  0.0f }, { 2.5f, 0.0f,  0.0f }, { 5.0f, 0.0f,  0.0f },  // Third row
        { -5.0f, 0.0f,  2.5f }, { -2.5f, 0.0f,  2.5f }, { 0.0f, 0.0f,  2.5f }, { 2.5f, 0.0f,  2.5f }, { 5.0f, 0.0f,  2.5f },  // Second row
        { -5.0f, 0.0f,  5.0f }, { -2.5f, 0.0f,  5.0f }, { 0.0f, 0.0f,  5.0f }, { 2.5f, 0.0f,  5.0f }, { 5.0f, 0.0f,  5.0f },  // Front row
    };


    // Floor elements (indices to vertices in a triangle strip)
    unsigned int floorElements[] = {
        0,5,1,6,2,7,3,8,4,9,            // Elements for first triangle strip (back strip)
        5,10,6,11,7,12,8,13,9,14,       // Elements for second triangle strip
        10,15,11,16,12,17,13,18,14,19,  // Elements for third triangle strip
        15,20,16,21,17,22,18,23,19,24,  // Elements for fourth triangle strip (front strip)
    };
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVerts) * sizeof(float), floorVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorElements) * sizeof(unsigned int), floorElements, GL_STATIC_DRAW);
}

void RemeshCircularDemo()
{
    // Circular surface as four triangle strips (low resolution)
    // Both vertex positions AND normal vectors
    // Note how this corresponds to the call to glVertexAttribPointer and glEnableVertexAttribArray
    //      in MySetupSurfaces() above.
    float circularVerts[] = {
        // Vertex positions     Normals (please make them *unit* vectors)
        0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 0.0f,        // Central vertex
        0.0f, 0.866f, 0.5f,     0.0f, 0.866f, 0.5f,     // Over positive z axis
        0.0f, 0.5f, 0.866f,     0.0f, 0.5f, 0.866f,     
        0.5f, 0.866f, 0.0f,     0.5f, 0.866f, 0.0f,     // Over positive x-axis
        0.866f, 0.5f, 0.0f,     0.866f, 0.5f, 0.0f,
        0.0f, 0.866f, -0.5f,    0.0f, 0.866f, -0.5f,    // Over negative z axis
        0.0f, 0.5f, -0.866f,    0.0f, 0.5f, -0.866f,
        -0.5f, 0.866f, 0.0f,    -0.5f, 0.866f, 0.0f,    // Over negative x-axis
        -0.866f, 0.5f, 0.0f,    -0.866f, 0.5f, 0.0f,
    };
    // Circular elements (indices to vertices in triangle strips)
    unsigned int circularElements[] = {
        0, 1, 3, 2, 4,            // Elements for first triangle strip 
        0, 3, 5, 4, 6,            // Elements for second triangle strip
        0, 5, 7, 6, 8,            // Elements for third triangle strip
        0, 7, 1, 8, 2            // Elements for fourth triangle strip 
    };
    glBindVertexArray(myVAO[iCircularSurf]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circularVerts) * sizeof(float), circularVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circularElements) * sizeof(unsigned int), circularElements, GL_STATIC_DRAW);
}

void RenderFloorDemo()
{
    glBindVertexArray(myVAO[iFloor]);

    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    glVertexAttrib3f(aNormal_loc, 0.0, 1.0, 0.0);    // Generic vertex attribute: Normal is (0,1,0) for the floor.
    glVertexAttrib3f(aColor_loc, 1.0f, 0.4f, 0.4f);	 // Generic vertex attribute: Color (light red) for the floor. 
    viewMatrix.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    // Draw the four triangle strips
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)0);                              // Draw first triangle strip (back strip)
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(20 * sizeof(unsigned int)));    // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));    // Draw fourth triangle strip (front strip)
}

void RenderCircularDemo()
{
    glBindVertexArray(myVAO[iCircularSurf]);

    // Calculute the model view matrix for the circular surface
    LinearMapR4 matDemo = viewMatrix;
    matDemo.Mult_glTranslate(2.5, 1.0, 2.5);     // Center in the front right quadrant & raise up
    matDemo.Mult_glScale(3.0, 1.0, 3.0);         // Increase the circular diameter

    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    glVertexAttrib3f(aColor_loc, 1.0f, 0.8f, 0.4f);	 // Generic vertex attribute: Color (yellow-ish) for the circular surface. 
    matDemo.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    // Draw the four triangle strips
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)0);                             // Draw first triangle strip 
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(5 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));   // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int)));   // Draw fourth triangle strip 

}


// *********************************************
// THE CODE BELOW MUST BE WRITTEN FOR PROJECT 4.
// *********************************************

void MyRemeshFloor() //TODO fix the line issue
{
    // Allocate an array for the vertex positions of the floor vertices.
    int numFloorVerts = (meshRes + 1) * (meshRes + 1);   // calculates the number of vertices on the floor
    float* floorVerts = new float[3 * numFloorVerts];

    // Allocate an array for the floor elements (indices to vertices in a triangle strip)
    int numFloorElts = meshRes * ((meshRes * 2) + 2);   // calculates the number of elements for triangle strip
    unsigned int* floorElements = new unsigned int[numFloorElts];
	
	//Calculates the contents of the floorVerts array
	float stepSize = 10.0f / ((float)meshRes); //Calculates how large each step to the next vertex should be
	float colVal; //stores how much the x value should be
	float rowVal; //stores how much the z value should be
	int iVert; //stores the current vertex index
	int shift = 0; //stores amount to shift

	//Fills the floorVerts array
	for (int row = 0; row < meshRes + 1; row++) { //Goes down row 
		for (int col = 0; col < meshRes + 1; col++) { //Goes down the columns first of the row
			colVal = -5 + (stepSize * col);
			rowVal = -5 + (stepSize * row);
			iVert = row + (row * meshRes) + col + shift;
			floorVerts[iVert] = colVal;
			floorVerts[iVert + 1] = 0.0f;
			floorVerts[iVert + 2] = rowVal;

			shift += 2;
		}

		//Resets the the colVal
		colVal = 0;
	}

	//Calculates the indices of the triangle strip
	int evenNum = 0; //For even indices
	int oddNum = meshRes + 1; //For odd indices

	//Fills array with indices of the triangle strip
	for (int i = 0; i < numFloorElts - 1; i = i + 2) {
		floorElements[i] = evenNum;
		floorElements[i + 1] = oddNum;

		evenNum++;
		oddNum++;
	}

	//Loads the data into the VBO and EBO Buffers
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
	glBufferData(GL_ARRAY_BUFFER, 3 * numFloorVerts * sizeof(float), floorVerts, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numFloorElts * sizeof(unsigned int), floorElements, GL_STATIC_DRAW);

    // The array should have been copied into the GPU buffers now.
    // If you use "new" above, you MUST delete the arrays here to avoid a memory leak.
    delete[] floorVerts;
    delete[] floorElements;
}

void MyRemeshCircularSurf()
{
    // WRITE THIS ENTIRE ROUTINE FOR THE CIRCULAR SURFACE
    // CALCULATE THE VERTEX DATA NEEDED FOR THE CIRCULAR SURFACE
    // THIS INCLUDES VERTEX POSITIONS AND NORMALS.
    // THEN LOAD THE DATA INTO THE VBO AND EBO BUFFERS
    // AND DELETE ANY TEMPORARILY ALLOCATED MEMORY.

	// Allocate an array for the vertex positions of the circular surface
	int numCircularVerts = (meshRes * meshRes) + 1;   // calculates the number of vertices on the surface
	float* circularVerts = new float[6 * numCircularVerts]; //6 because of normals

	// Allocate an array for the circular elements (indices to vertices in a triangle strip)
	int numCircularElts = meshRes * ((meshRes * 2) + 2);   // calculates the number of elements for triangle strip
	unsigned int* circularElements = new unsigned int[numCircularElts];

	/*****Calculates vertices of the circular surface********/
	float currRadius = 0; //Stores what the current radius is
	float currTheta = 0; //Stores what the current angle of rotation is
	float thetaInc = (2 * PI) / meshRes; //How much to increment theta by
	float radiusInc = (5 * PI) / meshRes; //How much to increment the radius by
	float currX, currY, currZ; //stores the current x,y,z values
	int iVert = 6; //stores current index 

	//Sets the very first vertex since it shouldn't be different regardless of meshRes
	circularVerts[0] = 0.0f;
	circularVerts[1] = 1.0f;
	circularVerts[2] = 0.0f;
	circularVerts[3] = 0.0f;
	circularVerts[4] = 1.0f;
	circularVerts[5] = 0.0f;

	//The rotation part of the circular surface
	for (int numRotate = 0; numRotate < meshRes; numRotate++) {
		//The actual points on a particular x-z
		for (int numRad = 0; numRad < meshRes; numRad++) {
			currRadius += radiusInc; //increments the radius

			//Calculates the x, y, z coordinates
			currX = currRadius * sin(currTheta);
			currY = sin(currRadius) / currRadius;
			currZ = currRadius * cos(currTheta);

			//Fills the array
			circularVerts[iVert] = currX;
			circularVerts[iVert + 1] = currY;
			circularVerts[iVert + 2] = currZ;

			//TODO Calculate normals
			circularVerts[iVert + 3] = 0.0f;
			circularVerts[iVert + 4] = 1.0f;
			circularVerts[iVert + 5] = 0.0f;

			iVert += 6; //For now to skip over normals
		}

		currTheta += thetaInc; //increments the angle of rotation
		currRadius = 0; //resets the radius
	}


	/*****Calculates indices of the triangle strips********/
	int baseNum = 0; //For base indices
	int nextNum = meshRes + 1; //For next indices
	int iElt = 0; //holds current index for elements

	//Fills array with indices of the triangle strip
	for (int section = 0; section < meshRes; section++) {
		circularElements[iElt] = 0; //Sets where the first vertex is
		iElt++;

		baseNum = (section * meshRes) + 1;

		//When drawing last section
		if (section == meshRes - 1) {
			nextNum = 1;
		}
		else {
			nextNum = (meshRes * (section + 1)) + 1;
		}

		//Setting remainder of indices
		for (int iStrip = 0; iStrip < 2 * meshRes; iStrip += 2) {
			circularElements[iElt] = baseNum;
			circularElements[iElt + 1] = nextNum;

			baseNum++;
			nextNum++;

			iElt += 2;
		}
	}

	//loads the data into the VBO and EBO buffers
	glBindVertexArray(myVAO[iCircularSurf]);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
	glBufferData(GL_ARRAY_BUFFER, 6 * numCircularVerts * sizeof(float), circularVerts, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numCircularElts * sizeof(unsigned int), circularElements, GL_STATIC_DRAW);

	//Deletes objects to avoid memory leaks
	delete[] circularVerts;
	delete[] circularElements;
}

void MyRenderFloor()
{
	glBindVertexArray(myVAO[iFloor]);

	// Set the uniform values (they are not stored with the VAO and thus must be set again everytime
	glVertexAttrib3f(aNormal_loc, 0.0, 1.0, 0.0);    // Generic vertex attribute: Normal is (0,1,0) for the floor.
	glVertexAttrib3f(aColor_loc, 1.0f, 0.4f, 0.4f);	 // Generic vertex attribute: Color (light red) for the floor. 
	viewMatrix.DumpByColumns(matEntries);
	glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

	// Draw the meshRes number of triangle strips
	int numVertStrip = 2 + (meshRes * 2); //Stores number of vertices in one strip
	for (int numStrip = 0; numStrip < meshRes; numStrip++) {
		glDrawElements(GL_TRIANGLE_STRIP, numVertStrip, GL_UNSIGNED_INT, (void*)((numStrip * numVertStrip) * sizeof(unsigned int)));
	}
}

void MyRenderCircularSurf()
{
	glBindVertexArray(myVAO[iCircularSurf]);

	// Calculute the model view matrix for the circular surface
	LinearMapR4 matDemo = viewMatrix;
	matDemo.Mult_glTranslate(2.5, 0.7, 2.5);     // Center in the front right quadrant & raise up
	matDemo.Mult_glScale(0.2, 2.7, 0.2);         // Scaling to make it similar to demo

												 // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
	glVertexAttrib3f(aColor_loc, 1.0f, 0.8f, 0.4f);	 // Generic vertex attribute: Color (yellow-ish) for the circular surface. 
	matDemo.DumpByColumns(matEntries);
	glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

	// Draw the meshRes number of triangle strips
	for (int i = 0; i < meshRes; i++) {
		glDrawElements(GL_TRIANGLE_STRIP, (2 * meshRes) + 1, GL_UNSIGNED_INT, (void*)(((2 * meshRes) + 1) * i * sizeof(unsigned int)));
	}
}
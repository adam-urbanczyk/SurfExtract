#pragma once
/*
class SurfacePosRenderer

The class renders the fragement positions of a 3d model into a 32-bit frame buffer object (fbo). 
All points are stored in local object space. 
Use 'draw' to start rendering the current frame from the current camera position.
The output is avaialble as opencv Mat of type CV_32FC3 using getCurrData().
Optionally, the output can be stored to a png image. 

Rafael Radkowski
Iowa State University
rafael@iastate.edu
March 2019
MIT License

--------------------------------------------------------------------------
Last edits:

Dec 20, 2019, RR
- Added CommonTypes.h 
*/

#include <iostream>
#include <string>
#include <time.h>


// opencv
#include <opencv2/opencv.hpp>


// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>  // transformation
#include <glm/gtx/quaternion.hpp> // quaternions


// local
#include "ModelOBJ.h"
#include "ModelSphere.h"
#include "ModelPlane.h"
#include "RenderToTexture.h"
#include "ImageWriter.h"
#include "CommonTypes.h"
#include "GLSLSource.h"

namespace surfe
{

class SurfacePosRenderer
{
public:

	/*
	Constructor
	@param window_width, window_height - width and height of the current render window in pixel
	@param render_width, render_height - width and height of the image to render in pixel
	*/
	SurfacePosRenderer(int window_width, int window_height, int render_width, int render_height);
	~SurfacePosRenderer();

	/*
	Load a 3D model from a file
	@param path_and_file - string containing the relative or absolute path.
	@return true - if successfully loaded
	*/
	bool setModelFromFile(std::string path_and_file);

	
	/*
	Return the latest data image.
	@return OpenCV matrix of type CV_32F_C3 with the rendered positions
	*/
	cv::Mat getCurrData(void);


	/*
	Set verbose mode to get more text output
	@param v - true to enable verbose mode, false to disable it
	*/
	void setVerbose(bool v);


	/*
	Set the view matrix - the prerender image is rendered from this position
	@param vm
	*/
	void setViewMatrix(glm::mat4 vm);


	/*
	Set an output path for the images
	@param path - relative or absolute output path
	@param name - name template for the output images.
	*/
	void setOutputPath(std::string path, std::string name = "image");

protected:

	/*
	Draw the object
	*/
	bool draw(void);


	/*
	Prepare a set of visual helpers
	*/
	bool prepareHelpers(void);

	/*
	Render all helper content
	*/
	bool renderHelpers(void);

	/*
	Prepare the fbo renderer
	*/
	bool prepareFBO(void);

	/*
	Draw the FBO renderer
	*/
	bool drawFBO(void);

	/*
	Disable and enable the file writer
	*/
	bool enable_writer(bool enable);


	//-----------------------------------------
	// Members

	unsigned int				_program;
	cs557::OBJModel*			_model;

	cs557::Sphere*			_sphere;
	cs557::Material			_sphere_mat;
	

	//  front light
	cs557::LightSource		_light0;
	


	// for helpers
	// a helper plane to render the pre-render content
	cs557::Plane				_display;
	glm::mat4				_display_m;
	glm::mat4				_display_p; 
	glm::mat4				_display_v;   


	glm::mat4				_proj_matrix;
	glm::mat4				_view_matrix;

	// preremder scene
	unsigned int				_fboHidden;
	GLuint					_color_texture_idx;
	GLuint					_depth_texture_idx;
	int						_image_width; 
	int						_image_height;
	int						_window_width;
	int						_window_height;

	unsigned char*			_data_rgb;


	bool						_verbose;

	bool						_writer_enabled;
	ImageWriter*				_writer;
	std::string					_output_file_path;
	std::string					_output_file_name;
	int						_output_file_id;

};

}// namespace
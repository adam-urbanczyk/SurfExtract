#pragma once
/*
Class PointCloudAssembly


Rafael Radkowski
Iowa State University
rafael@iastate.edu
+1 (515) 294 7044
March 4, 2019
All copyrights reserved

--------------------------------------------------------------------
Last edits:

Dec 14, 2019, RR:
- Added a function to set the minimum allowed point cloud density. This can prevent low performance. 

Dec 15, 2019, RR:
- Added a PCD ASCII writer, to write the model as a pcd file.
- Changed the api for the function writeToFile. The file type is now a function argument. 
- Added a PLY ASCII writer
- Added a function to return the model output scale.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>

// GLEW include
#include <GL/glew.h>

// opencv
#include <opencv2/opencv.hpp>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>  // transformation
#include <glm/gtx/quaternion.hpp> // quaternions


// local
#include "Sampling.h"
#include "Types.h"
#include "Mat2Points.h"
#include "LoaderOBJ.h"
#include "ReaderWriterPCD.h"
#include "ReaderWriterPLY.h"


class PointCloudAssembly
{
public:
	PointCloudAssembly();
	~PointCloudAssembly();

	/*
	Set the minimum acceptable distance between points,
	defined via the sampling grid size
	@param density -  a float values > 0.005 for the denisty.
	*/
	void setPointCloudDensity(float density);

	/*
	Set the a scale parameter for the final point cloud.
	The output point cloud will be scaled by this parameter
	before written into a file.
	@param scale - float value larger than 0.0001;
	*/
	bool setOutputScale(float scale);

	/*
	Return the output scale as float
	*/
	float getOutputScale(void);

	/*
	Return the current density;
	*/
	float getPointCloudDensity(void) { return _user_param.grid_x; }

	/*
	Add a data matrix to the current point cloud and invoke processing
	The matrix needs to be of type CV_32F_C3 with width x height x 3, 
	the channels encode the x, y, z values. 
	All empty points must contain values = 0
	@param data - the opencv matrix with the data. 
	*/
	void addData(cv::Mat data);


	/*
	Set mode to verbose to get more output
	@param v - true makes this class verbose
	*/
	void setVerbose(bool v) { _verbose = v; };

	/*
	Resample the point cloud with a new density value.
	Note that a initial point cloud  must already exist
	@param density - a float values > 0.005 for the denisty.
	*/
	void resample(float density);

	/*
	Write the point cloud to an obj file
	@param path_and_filename - string with the relative or abosolute path. 
	@param type - string containing the type. Currently, "obj", "ply", and "pcd" are supported. 
	*/
	bool writeToFile(string path_and_filename, std::string type = "obj");




	/*
	Return the final point cloud
	*/
	PointCloud&	getPointCloud(void);


	/*
	Return the number of points
	*/
	int getNumPoints(void);


	/*
	Set the minimum allowed point cloud density.
	This value can be calcualted in advance when knowing the 
	number of voxels. It will prevent that the applications crashs
	@param denisty  - float with the minimum allowed density;
	*/
	bool setMinimumPointCloudDensity(float density);

	/*
	Return the minimum point cloud density
	*/
	float getMinimumPointCloudDensity(void);

private:

	// converts the data matrix into points
	Mat2Points					_m2p;

	// currently processing points
	vector<Eigen::Vector3f> 		_points_processing;
	vector<Eigen::Vector3f> 		_normals_processing;

	// the points for the point cloud
	PointCloud				    _points_ready;
	PointCloud				    _points_final;

	// the original set of points before the denisty value is applied
	PointCloud					_points_original; 


	// sampling parameters
	SamplingParam				_default_param;
    SamplingMethod				_default_method;
	SamplingParam				_user_param;
	float						_min_density;
 
	float						_output_scale;

	// helpers

	bool							_verbose;

};
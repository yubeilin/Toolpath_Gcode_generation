#pragma once
#include "../QMeshLib/PolygenMesh.h"

class GcodeGeneration {

public:
	GcodeGeneration() {};
	~GcodeGeneration() {};

	void initial(PolygenMesh* Slices, PolygenMesh* Waypoints, PolygenMesh* CncPart);
	void updateParameter(int FromIndex, int ToIndex, double lambdaValue,
		double width, double tool_length);
	void calDHW();
	void singularityOpt();
	void feedrateOpt();
	void writeGcode(std::string GcodeDir);
	void readGcodeFile(Eigen::MatrixXf& Gcode_Table, std::string FileName);

private:

	void _cal_Dist();
	void _initialSmooth(int loopTime);
	void _cal_Height();
	std::vector<QMeshPatch*> _getJumpSection_patchSet(QMeshPatch* patch);
	double _safe_acos(double value);
	void _markSingularNode(QMeshPatch* patch);
	void _filterSingleSingularNode(QMeshPatch* patch);
	void _getSingularSec(QMeshPatch* patch, Eigen::MatrixXd& sectionTable);
	void _projectAnchorPoint(QMeshPatch* patch);
	void _getBCtable2(QMeshPatch* patch, Eigen::MatrixXd& B1C1table, Eigen::MatrixXd& B2C2table);
	void _motionPlanning3(
		QMeshPatch* patch, const Eigen::MatrixXd& sectionTable, const Eigen::MatrixXd& B1C1table,
		const Eigen::MatrixXd& B2C2table, Eigen::RowVector2d& prevBC);
	bool _chooseB1C1(
		const Eigen::RowVector2d& B1C1, const Eigen::RowVector2d& B2C2,
		Eigen::RowVector2d& prevBC);
	double _toLeft(
		const Eigen::RowVector2d& origin_p, const Eigen::RowVector2d& startPnt_q,
		const Eigen::RowVector2d& endPnt_s);
	void _getXYZ(QMeshPatch* patch);
	void _calDHW2E(QMeshPatch* patch, bool hysteresis_switch);
	void _optimizationC(QMeshPatch* patch);
	void _verifyPosNor();
	double _getAngle3D(const Eigen::Vector3d& v1,
		const Eigen::Vector3d& v2, const bool in_degree);


	PolygenMesh* m_Slices = NULL;
	PolygenMesh* m_Waypoints = NULL;
	PolygenMesh* m_CncPart = NULL;

	int m_FromIndex = 0;
	int m_ToIndex = 0;
	double m_lambdaValue = 0.0;
	double m_width = 0.0;
	double h = 0.0;     // tool length

	//inner parameters
	int m_jump_detection_threshold = 4.0;
	int Core = 16; 
	int layerNum = 40;	 // The number of detected bottom layer for height calculation
	bool is_planar_printing = false; //switch for the planar printing
	double ratio = 0.58;  // extrusion ratio
};
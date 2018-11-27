class Camera
{
public:
	double camera_matrix[16];
	double object_matrix[16];
	Camera();
	void init(double _matrix_1[16], double _matrix_2[16]);
	void zoomout(double _matrix_1[16], double _matrix_2[16]);
	void zoomout(double _matrix_1[16], double _matrix_2[16], double num);
	void zoomin(double _matrix_1[16], double _matrix_2[16]);
	void zoomin(double _matrix_1[16], double _matrix_2[16], double num);
	void moveUp(double _matrix_1[16], double _matrix_2[16]);
	void moveDown(double _matrix_1[16], double _matrix_2[16]);
	void moveLeft(double _matrix_1[16], double _matrix_2[16]);
	void moveRight(double _matrix_1[16], double _matrix_2[16]);
};

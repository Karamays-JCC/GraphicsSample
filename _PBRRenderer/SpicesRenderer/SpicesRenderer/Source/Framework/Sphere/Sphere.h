#pragma once
class MeshBase;

class Sphere
{
public:
	MeshBase* Mesh;

public:
	float Radius;

public:
	Sphere();
	virtual ~Sphere();
};


#include <iostream>
#include <string>
#include <vector>

#include <cam/preset/perspective_camera.h>
#include <scn/obj/preset/sphere.h>
#include <scn/scene.h>
#include <scn/lit/light.h>
#include <scn/mat/material.h>

#include "render.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace Eigen;

void init() {
	Scene scene;

	scene.set_ambient_light(1);
	scene.set_background_colour(Vector3d(0, 0, 0));

	scene.add_light(Light(Vector3d(50, 50, 50), 2));
	scene.add_light(Light(Vector3d(-100, 300, -200), 0.3));

	Material reflective(0.3, 0.3, 0.7, 0.7, 100);
	Material glossy(0.1, 0.5, 0.7, 0.1, 1000);
	Material dull(0.1, 0.7, 0.3, 0.1, 10);
	Material ground(0.1, 0.2, 0, 0.7, 0);

	Vector3d yellow(1, 0.8, 0.2);
	Vector3d red(0.56, 0.28, 0.14);
	Vector3d blue(0, 0.2, 0.8);
	Vector3d green(0.75, 0.85, 0.95);
	Vector3d grey(0.4, 0.4, 0.4);

	Sphere sphere1(Vector3d(9, 0, -2), 5);
	sphere1.set_material(reflective);
	sphere1.set_colour(yellow);

	Sphere sphere2(Vector3d(-9, 0, -2), 5);
	sphere2.set_material(dull);
	sphere2.set_colour(red);

	Sphere sphere3(Vector3d(0, 0, -17), 5);
	sphere3.set_material(glossy);
	sphere3.set_colour(green);
	
	Sphere sphere4(Vector3d(0, -10000, 0), 10000-5);
	sphere4.set_material(ground);
	sphere4.set_colour(grey);

	Object* obj1 = &sphere1;
	Object* obj2 = &sphere2;
	Object* obj3 = &sphere3;
	Object* obj4 = &sphere4;

	scene.add_object(obj1);
	scene.add_object(obj2);
	scene.add_object(obj3);
	scene.add_object(obj4);

	// ---------------------------------------------- //

	PerspectiveCamera* camera = new PerspectiveCamera();
	camera->set_basis(Vector3d(1, 0, 0), Vector3d(0, 1, 0), Vector3d(0, 0, 1));
	camera->set_origin(Vector3d(0, 10, 40));
	camera->set_bounds(-10, 10, -10, 10);
	camera->set_distance(20);

	Camera* cam = camera;

	// ---------------------------------------------- //

	render_image(scene, cam, 800, 800, "../renders/render.png");
}

int main() {
	init();

	return 0;
}
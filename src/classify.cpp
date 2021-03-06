#include <iostream>
#include <string>
#include "facenet_tf.h"
using namespace std;

int main (int argc, char *argv[]) {
	if (argc < 6) {
		cout << "Usage:\n"
						"./facenet_classify <TRAIN|CLASSIFY>  <Path/To/20170512-110547.pb> <Path/To/Image/Directory/Structure> <Path/To/SVM/Model> <SVM/Class/Labels>\n"
						"Directory structure should be <class_name>/<image_files>\n"
						"Face Images Should be 160x160\n" << endl;
		return 1;
	}
	string operation, images_path, model_path, svm_model_path, labels_file_path;
	operation = string (argv[1]);
	model_path = string (argv[2]);
	images_path = string (argv[3]);
	svm_model_path = string (argv[4]);
	labels_file_path = string (argv[5]);
	FacenetClassifier classifier = FacenetClassifier (operation, model_path, svm_model_path, labels_file_path);
	classifier.parse_images_path (images_path, 0);
	classifier.create_input_tensor ();
	classifier.create_phase_tensor ();
	classifier.run ();
	
	if (operation == "TRAIN") {
		classifier.save_svm ();
		classifier.save_labels ();
	}
	else if (operation == "CLASSIFY") {	
		classifier.load_svm ();
		classifier.load_labels ();
		classifier.predict_labels ();
	}
	
	return 0;
}


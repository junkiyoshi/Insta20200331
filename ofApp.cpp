#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 180, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<string> word_list = { 
		"over",
		"1200",
		"days", "a"
	};

	vector<glm::vec2> base_location_list = {
		glm::vec2(ofGetWidth() * 0.5 - this->font.stringWidth(word_list[0]) * 0.5, ofGetHeight() * 0.5 - 150),
		glm::vec2(ofGetWidth() * 0.5 - this->font.stringWidth(word_list[1]) * 0.5, ofGetHeight() * 0.5 + 60),
		glm::vec2(ofGetWidth() * 0.5 - this->font.stringWidth(word_list[2]) * 0.5, ofGetHeight() * 0.5 + 270)
	};

	assert(word_list.size() == base_location_list.size());

	for(int i = 0; i < word_list.size(); i++){

		auto word = word_list[i];
		auto base_location = base_location_list[i];

		int sample_count = 180;
		vector<ofPath> word_path = this->font.getStringAsPoints(word, true, false);
		for (int word_index = 0; word_index < word_path.size(); word_index++) {

			vector<ofPolyline> outline = word_path[word_index].getOutline();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
				vector<glm::vec3> vertices = outline[outline_index].getVertices();
				vector<glm::vec2> black_vertices, white_vertices;
				glm::vec2 circle_location;
				int param = ofGetFrameNum() + base_location.y;

				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					auto location = base_location + vertices[vertices_index];

					if (param % (sample_count * 2) < sample_count) {

						if (vertices_index < param % sample_count) {

							black_vertices.push_back(location);
						}
						else {
						
							white_vertices.push_back(location);
						}
					}
					else {

						if (vertices_index > param % sample_count) {

							black_vertices.push_back(location);
						}
						else {

							white_vertices.push_back(location);
						}
					}

					if (vertices_index == param % sample_count) {

						circle_location = location;
					}

				}

				ofNoFill();

				ofSetColor(255);
				ofBeginShape();
				ofVertices(white_vertices);
				ofEndShape();

				ofSetColor(39);
				ofBeginShape();
				ofVertices(black_vertices);
				ofEndShape();

				ofFill();
				ofSetColor(39);
				ofDrawCircle(circle_location, 5);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
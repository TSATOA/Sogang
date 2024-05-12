#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    /* WaterFall-related member variables Regions */
    
    // flag variables
    int draw_flag;
    int load_flag;
	int pour_flag;
	int maintain_flag=0;
	int num = 0;
	int cntinit = 0;
	int ka = 0;

    // Line segment and dot related variables
    int num_of_line, num_of_dot;
    float dot_diameter;
	int location=0;
	int maxx, maxy;
	int path=0;
	int dotlocx[100];
	int dotlocy[100];

	int **a;
	int **b;
	int **c;
    /* WaterFall-related member functions */
    
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    void initializeWaterLines(); // 2nd week portion.
		
};
